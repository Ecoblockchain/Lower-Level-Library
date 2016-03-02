#ifndef LOWER_LEVEL_LIBRARY_LLS_TYPES
#define LOWER_LEVEL_LIBRARY_LLS_TYPES

#include <vector>

namespace LLS
{	
	
	
	/** Basic Stream object to Contain the Binary Serialization Data of a Class. **/
	class BinaryStream : public std::vector<unsigned char>
	{
		/** Iterator for Reading Stream. **/
		unsigned int nIterator;
		
	public:
		/** Allow Blank Constructors. **/
		BinaryStream() : nIterator(0) {}
		
		/** Build a Binary Stream from Binary Stream. **/
		BinaryStream(const BinaryStream& cStream) : 
			std::vector<unsigned char>(cStream.begin(), cStream.end()), nIterator(0) {}
			
		/** Build a Binary Stream from Section of Larger Stream with End of stream being end Binary Iterator. **/
		BinaryStream(const std::vector<unsigned char> vData, unsigned int nBegin) : 
			std::vector<unsigned char>(vData.begin() + nBegin, vData.end()), nIterator(0) {}
		
		/** Build a Binary Stream from Section of Larger Stream with Size being the end of stream. **/
		BinaryStream(const std::vector<unsigned char> vData, unsigned int nBegin, unsigned int nSize) : 
			std::vector<unsigned char>(vData.begin() + nBegin, vData.begin() + nBegin + nSize), nIterator(0) {}
			
		/** Check if there is still data in the stream. **/
		bool HasData() { return nIterator < size(); }
	
		/** Serialize the Data into Byte Stream, inserting to end of Stream. **/
		template<class Type> void Write(Type cType)
		{
			std::vector<unsigned char> vData = Serialize(cType);
			insert(end(), vData.begin(), vData.end());
		}
		
		
		/** De-Serialize the Data from Byte Stream, and erase from Stream. **/
		template<class Type> bool Read(Type& cType)
		{
			if(!HasData())
				return false;
				
			std::vector<unsigned char> vData(begin(), end());
			nIterator += Deserialize(vData, cType, nIterator);
			
			return true;
		}
		
		/** Return a copy of the Data in the Vector to deal with Vector Types. **/
		std::vector<unsigned char> Data() { std::vector<unsigned char> vCopy(begin(), end()); return vCopy; }
		
		/** Reset the Reading Iterator of Stream. **/
		void Reset() { nIterator = 0; }
		
	};
}

#endif