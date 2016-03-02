#ifndef LOWER_LEVEL_LIBRARY_LLD_DATABASE
#define LOWER_LEVEL_LIBRARY_LLD_DATABASE

#include "types.h"
#include "../LLU/macro.h"

/** Lower Level Database Namespace. Store your Databases in this Namespace. **/
namespace LLD
{

	/** Base Template Class for the Database Handle. Processes main Lower Level Disk Communications. **/
	template< typename KeyType, class RecordType> class SectorDatabase
	{
		/** Mutex for Thread Synchronization. **/
		boost::mutex DATABASE_MUTEX;
		
		
		/** The String to hold the Disk Location of Database File. 
			Each Database File Acts as a New Table as in Conventional Design.
			Key can be any Type, which is how the Database Records are Accessed. **/
		std::string strFilename;
		
		
		/** Integer to Keep track of the Binary Size of the Database File. 
			This is used to reduce need to call tellg or tellp from Binary Stream.
			Keeping Cache promotes Efficiency. Maximum Database Size is 4.3 GB. **/
		uint64 nBinarySize;
		
		
		/** Size of Record on Each Database Sector. This is used to Iterate Quickly Through Binary Data
			While Allowing their Data Lengths to not Be Fixed Individually. **/
		unsigned int nRecordAllocation;
	
		
		/** Size of Key Storage on Each Database Sector. Used to Iterate to Record Quickly from
			Header Information. **/
		unsigned int nHeaderAllocation;
		
		
		
		/** Size of Each Database Sector. Combination of Record and Key Allocation. **/
		unsigned int nSectorSize;
		
		
		/** Map to Contain the Binary Positions of Each Sector.
			Used to Quickly Read the Database File at Given Position
			To Obtain the Record from its Database Key. This is Read
			Into Memory on Database Initialization. **/
		typename std::map<KeyType, uint64 > mapSectorPositions;
		
		
		
		/** Vector to Contain the Sector Positions that have been Erased.
			This is useful for new Records to be Written to Available Sectors. **/
		std::vector<uint64> vEmptySectors;
		
	public:
		/** The Database Constructor. To determine file location and the Bytes per Record. **/
		SectorDatabase(std::string fileout, unsigned int nRecordSize= 2048, unsigned int nKeySize = 512) : strFilename(fileout), nRecordAllocation(nRecordSize), nHeaderAllocation(nKeySize), nBinarySize(0) { nSectorSize = nHeaderAllocation + nRecordAllocation; }
		
		
		/** Return the Keys to the Records Held in the Database. **/
		std::vector<KeyType> GetKeys()
		{
			LOCK(DATABASE_MUTEX);
			
			std::vector<KeyType> vKeys;
			for(typename std::map<KeyType, uint64>::iterator nIterator = mapSectorPositions.begin(); nIterator != mapSectorPositions.end(); nIterator++)
				vKeys.push_back(nIterator->first);
				
			return vKeys;
		}
		
		
		/** Get the associated Keys with the Given Tag. **/
		std::vector<KeyType> GetKeys(TagType cTag)
		{
			LOCK(DATABASE_MUTEX);
			
			/** Establish Return Object. **/
			std::vector<KeyType> vKeys;
			
			/** If the Tag exists add in Active Sector Keys. **/
			if(mapHeaderTags.count(cTag))
			{
				
				/** Check through all the Keys associated with Given Tag. **/
				for(int nIndex = 0; nIndex < mapHeaderTags[cTag].size(); nIndex++)
					if(mapSectorPositions.count(mapHeaderTags[cTag][nIndex]))
						vKeys.push_back(mapHeaderTags[cTag][nIndex]);

				/** Reassign to only Active Tags. **/
				mapHeaderTags[cTag] = vKeys;
			}
			
			return vKeys;
		}
		
		
		/** Return Whether a Key Exists in the Database. **/
		bool HasKey(KeyType cKey)
		{
			LOCK(DATABASE_MUTEX);
			
			return mapSectorPositions.count(cKey);
		}
		
		
		/** Return Whether a Tag is assigned to any specific Keys. **/
		bool HasTag(TagType cTag) { return mapHeaderTags.count(cTag); }
		
		
		
		/** Erase a Record from the Database. **/
		void EraseRecord(KeyType cKey)
		{
			LOCK(DATABASE_MUTEX);
			
			/** Don't try to Erase a Record that isn't Available. **/
			if(!mapSectorPositions.count(cKey))
				return;
			
			/** Tell Database Sector is Empty in Memory. **/			
			vEmptySectors.push_back(mapSectorPositions[cKey]);
			
			/** Establish the Outgoing Stream. **/
			std::fstream cStream(strFilename.c_str(), std::ios::out | std::ios::in | std::ios::binary);
			
			/** Seek to the Position of the Sector. **/
			cStream.seekp(mapSectorPositions[cKey]);
			
			/** Fill Sector with Blank Data. **/
			std::vector<unsigned char> vBlankData(nSectorSize, 0);
			cStream.write((char*) &vBlankData[0],   vBlankData.size());
			cStream.close();
			
			/** Erase the Sector position from Memory. **/
			mapSectorPositions.erase(cKey);
		}
		
		
		/** Read the Database Keys and File Positions. **/
		void Initialize()
		{
			LOCK(DATABASE_MUTEX);
			
			/** Open the Stream to Read from the File Stream. **/
			std::fstream fIncoming(strFilename.c_str(), std::ios::in | std::ios::binary);
			if(!fIncoming)
			{
				printf("[DATABASE] Initializing New Database File.\n");
				std::ofstream cStream(strFilename.c_str(), std::ios::binary);
				cStream.close();
				
					
				return;
			}
			
			/** Get the Binary Size. **/
			fIncoming.seekg (0, fIncoming.end);
			nBinarySize = fIncoming.tellg();
			
			/** Iterator for Sectors. **/
			unsigned int nTotalSectors = nBinarySize / nSectorSize;
			
			
			/** Loop through the Sectors on Disk. **/
			for(unsigned int nIterator = 0; nIterator < nTotalSectors; nIterator++)
			{
			
				/** Get the Position of the Record. **/
				uint64 nPosition = nIterator * nSectorSize;
				
				/** Read the State of the Sector First. **/
				Header<KeyType, TagType> cHeader(nPosition, nHeaderAllocation);
				cHeader.ReadFromDisk(fIncoming);
				
				/** If the Sector is Empty, Set it to Available in Database. **/
				if(cHeader.Empty())
				{
					vEmptySectors.push_back(cHeader.Begin());
					
					continue;
				}
				
					
				/** Add the Sector to the List of Positions. **/
				mapSectorPositions[cHeader.cKey] = cHeader.Begin();
				
				
				/** Add the Access tags to the Database Keys from Headers. **/
				for(int nIndex = 0; nIndex < cHeader.vTags.size(); nIndex++)
					mapHeaderTags[cHeader.vTags[nIndex]].push_back(cHeader.cKey);
					
			}
			
			printf("[DATABASE] Initialized with Binary Size of %I64d Bytes\n", nBinarySize);
			fIncoming.close();
		}
		
		
		/** Get a Record from the Database with Given Key. **/
		bool GetRecord(KeyType cKey, RecordType& cRecord)
		{
			LOCK(DATABASE_MUTEX);
			
			/** Read a Record from Binary Data. **/
			if(mapSectorPositions.count(cKey))
			{
				std::fstream cStream(strFilename.c_str(), std::ios::in | std::ios::binary);

				/** Seek to the Sector Position on Disk. **/
				cStream.seekg(mapSectorPositions[cKey] + nHeaderAllocation);
			
				/** Read the State and Size of Sector Header. **/
				std::vector<unsigned char> vRecord(nRecordAllocation, 0);
				cStream.read((char*) &vRecord[0], nRecordAllocation);
				LLS::Deserialize(vRecord, cRecord);
				cStream.close();
				
				return true;
			}
			
			return false;
		}
		
		
		/** Add / Update A Record in the Database **/
		void UpdateRecord(KeyType cKey, RecordType cRecord)
		{
			LOCK(DATABASE_MUTEX);
			
			/** Establish the Outgoing Stream. **/
			std::fstream cStream(strFilename.c_str(), std::ios::out | std::ios::in | std::ios::binary);
			
			/** Write Header if First Update. **/
			if(!mapSectorPositions.count(cKey))
			{
				/** If it is a New Sector, Assign a Binary Position. **/
				uint64 nPosition;
			
				if(!vEmptySectors.empty())
				{
					nPosition = vEmptySectors[0];
					vEmptySectors.erase(vEmptySectors.begin());
				}
				else 
				{
					nPosition = nBinarySize;
					nBinarySize += nSectorSize;
					
					cStream.seekp(nPosition);
				}
				
				Header<KeyType, TagType> cHeader(nPosition, nHeaderAllocation);
				cHeader.cKey = cKey;
				
				cHeader.WriteToDisk(cStream);
				mapSectorPositions[cKey] = nPosition;
			}
			
			
			/** Seek to the Position of the Sector. **/
			cStream.seekp(mapSectorPositions[cKey] + nHeaderAllocation);
			
			
			/** Serialize the Record. **/
			std::vector<unsigned char> vRecordData = LLS::Serialize(cRecord);
			std::vector<unsigned char> vBlankData(nRecordAllocation - vRecordData.size(), 0);
			
			/** Write the Record. **/
			cStream.write((char*) &vRecordData[0], vRecordData.size());
			cStream.write((char*) &vBlankData[0],   vBlankData.size());
			cStream.close();
			
		}
	};
}

#endif