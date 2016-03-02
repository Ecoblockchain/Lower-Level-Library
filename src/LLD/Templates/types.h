#ifndef LOWER_LEVEL_LIBRARY_LLD_TYPES
#define LOWER_LEVEL_LIBRARY_LLD_TYPES

#include <fstream>
#include "../LLS/LLS.h"


namespace LLD
{

	/** Enumeration to give the States of the Database Sector. 
		+ Empty States that the Sector is Empty.
		+ Ready States that the Sector Should not Change. **/
	enum
	{
		EMPTY = NULL,
		READY = 1
	};
	
	
	template<class KeyType> class Header : public LLS::BinaryStream
	{	
		uint64       nPosition;
		unsigned int nFile;
	public:
	
		/** Components of an LLD Header Packet.
			Tells the Database the State, Iterators to End of Header,
			and End of Sector Header is Representing. **/
		unsigned char nState;
		unsigned int  nHeaderSize;
		unsigned int  nSectorSize;
		
		/** The main accessor key that must be unique. **/
		KeyType cKey;
		
		
		/** The Header Constructors. **/
		Header() { nPosition = NULL; nState = NULL; }
		Header(uint64 nPos, unsigned int nHeaderSizeIn) { nPosition = nPos; nHeaderSize = nHeaderSizeIn; nState = READY; }
		
		
		/** Flag to Determine if Sector Header State is Empty. **/
		bool Empty() { return !nState; }
		
		
		/** Flag to ensure Header is within range. **/
		bool Valid() { return (size() < nHeaderSize); }
		
		
		/** Clear the Header For Empty Sector. **/
		void Clear() { nState = EMPTY; clear(); }
		
		
		/** Get the Iterator Position at Beginning of Header. **/
		uint64 Begin() { return nPosition; }
		
		
		/** Get the Iterator Position at End of the Header. **/
		uint64 End()   { return (nPosition + nHeaderSize); }
		
		
		/** Serialize the Header into Stream. **/
		void ReadFromDisk(std::fstream& cStream)
		{
			/** Seek to the Sector Position on Disk. **/
			cStream.seekg(Begin());
			
			/** Read the State and Size of Sector Header. **/
			std::vector<unsigned char> vHeader(nHeaderSize, 0);
			cStream.read((char*) &vHeader[0], nHeaderSize);
			
			/** Set the Read contents into Binary Stream. **/
			swap(vHeader);
			
			/** Reset the Reading Pointer. **/
			Reset();

			/** Deserialize the State and Header Size. **/
			Read(nState);
			
			/** Read the Key if the Sector Header isn't Empty. **/
			if(nState != EMPTY)
			{
				Read(cKey);
				
				if(HasData())
					Read(vTags);
			}
			
			//Print();
		}
		

		/** Serialize the Header into Stream. **/
		void WriteToDisk(std::fstream& cStream)
		{
			/** Seek to the Position of the Sector. **/
			cStream.seekp(Begin());
			
			/** Write the Header State. **/
			Reset();
			clear();
			
			Write(nState);
			Write(cKey);
			
			std::vector<unsigned char> vHeaderData = Data();
			std::vector<unsigned char> vBlankData(nHeaderSize - vHeaderData.size(), 0);
			cStream.write((char*) &vSectorData[0], vSectorData.size());
			cStream.write((char*) &vBlankData[0],   vBlankData.size());
			
			//Print();
		}
		
		void Print() { printf("[HEADER] State: %s Begin: %I64d End: %I64d\n", Empty() ? "EMPTY" : "ACTIVE", Begin(), End()); }
	};
	
	/** Used to Sort the Sectors by Position in Database File. **/
	//template<typename SectorType> bool SectorSort(const SectorType& cSectorFirst, const SectorType& cSectorSecond) { return cSectorFirst.nPosition < cSectorSecond.nPosition; }
}

#endif