#ifndef LOWER_LEVEL_LIBRARY_LLS_SERIALIZE
#define LOWER_LEVEL_LIBRARY_LLS_SERIALIZE

#include "../LLT/LLT.h"

#include "types.h"

namespace LLS
{
	
	/** Get the Serialization size of a Standard Character. **/
	unsigned int SerializeSize(unsigned char   nChar)   { return 1;   }
	unsigned int SerializeSize(signed char     nChar)   { return 1;   }
	
	
	/** Get the Serialization size of a 16 Bit Integer. **/
	unsigned int SerializeSize(unsigned short  nShort)  { return 2;   }
	unsigned int SerializeSize(signed short    nShort)  { return 2;   }
	
	
	/** Get the Serialization size of 32 Bit Integer. **/
	unsigned int SerializeSize(unsigned int   nInt)     { return 4;   }
	unsigned int SerializeSize(signed int     nInt)     { return 4;   }
	
	
	/** Get the Serialization size of 64 bit Integers. **/
	unsigned int SerializeSize(int64  nInt)             { return 8;   }
	unsigned int SerializeSize(uint64 nInt)             { return 8;   }
	
	
	/** Get the Serialization size of Large Unsigned Integers. **/
	unsigned int SerializeSize(uint256  nInt)           { return 32;  }
	unsigned int SerializeSize(uint512  nInt)           { return 64;  }
	unsigned int SerializeSize(uint576  nInt)           { return 72;  }
	unsigned int SerializeSize(uint1024 nInt)           { return 128; }
	
	
	/** Get the Serialization size of a String. **/
	unsigned int SerializeSize(std::string str)        { return str.size() + 4; }
	
	
	/** Get the Serialization Size of a Class. **/
	template<typename ClassType> unsigned int SerializeSize(ClassType cValue){ return cValue.SerializeSize(); }
	
	
	/** Forward Declaration for Use of Pair / Vector Combinations. **/
	template<typename DataType> unsigned int SerializeSize(std::vector<DataType> vElements);
	
	
	/** Get the Serialization Size of a Pair. [For Two Data Types]**/
	template<typename Type1, typename Type2> unsigned int SerializeSize(std::pair<Type1, Type2> pairData)
	{
		unsigned int nSerializeSize = 0;
		nSerializeSize += SerializeSize(pairData.first);
		nSerializeSize += SerializeSize(pairData.second);
		
		return nSerializeSize;
	}
	
	
	/** Get the Serialization Size of a Vector [For Data Type]. **/
	template<typename DataType> unsigned int SerializeSize(std::vector<DataType> vElements)
	{
		/** 4 Bytes for Vector Record Count. **/
		unsigned int nSerializeSize = 4;
		for(int nIndex = 0; nIndex < vElements.size(); nIndex++)
			nSerializeSize += SerializeSize(vElements[nIndex]);
			
		return nSerializeSize;
	}
	
	

	
	
	
	/** ------------------------------------------------ Serialization Functions ---------------------------------------------------------------- **/
	
	
	/** Convert a 32 bit Unsigned Short to Byte Vector using Bitwise Shifts. **/
	std::vector<unsigned char> Serialize(unsigned char nChar)
	{
		std::vector<unsigned char> vData(1, nChar);
		return vData;
	}
	
	/** Convert a 32 bit Unsigned Short to Byte Vector using Bitwise Shifts. **/
	std::vector<unsigned char> Serialize(unsigned short nInt)
	{
		std::vector<unsigned char> vData;
		vData.push_back(nInt >> 8);
		vData.push_back(nInt);
					
		return vData;
	}
	
	
	/** Convert a 32 bit Unsigned Integer to Byte Vector using Bitwise Shifts. **/
	std::vector<unsigned char> Serialize(unsigned int nInt)
	{
		std::vector<unsigned char> vData;
		vData.push_back(nInt >> 24);
		vData.push_back(nInt >> 16);
		vData.push_back(nInt >> 8);
		vData.push_back(nInt);
					
		return vData;
	}
							
	
	/** Convert a 64 bit Unsigned Integer to Byte Vector using Bitwise Shifts. **/
	std::vector<unsigned char> Serialize(uint64 nInt)
	{
		std::vector<unsigned char> vInts[2];
		vInts[0] = Serialize((unsigned int) nInt);
		vInts[1] = Serialize((unsigned int) (nInt >> 32));
		
		std::vector<unsigned char> vData;
		vData.insert(vData.end(), vInts[0].begin(), vInts[0].end());
		vData.insert(vData.end(), vInts[1].begin(), vInts[1].end());
					
		return vData;
	}
	
	
	/** Push a Signed char to Vector. **/
	std::vector<unsigned char> Serialize(signed char nChar)
	{
		std::vector<unsigned char> vData(1, (unsigned char) nChar);
		
		return vData;
	}
	
	
	/** Convert a 16 bit Signed Short to Byte Stream using Bitwise Shifts. **/
	std::vector<unsigned char> Serialize(signed short nInt)
	{
		std::vector<unsigned char> vData;
		vData.push_back(nInt >> 8);
		vData.push_back(nInt);
					
		return vData;
	}
	
	
	/** Convert a 32 bit Signed Integer to Byte Vector using Bitwise Shifts. **/
	std::vector<unsigned char> Serialize(signed int nInt)
	{
		std::vector<unsigned char> vData;
		vData.push_back(nInt >> 24);
		vData.push_back(nInt >> 16);
		vData.push_back(nInt >> 8);
		vData.push_back(nInt);
					
		return vData;
	}
	
	
	/** Serialize Signed Integers by Normal methods, then casting. **/
	std::vector<unsigned char> Serialize(int64 nInt)
	{
		std::vector<unsigned char> vInts[2];
		vInts[0] = Serialize((unsigned int) nInt);
		vInts[1] = Serialize((unsigned int) (nInt >> 32));
		
		std::vector<unsigned char> vData;
		vData.insert(vData.end(), vInts[0].begin(), vInts[0].end());
		vData.insert(vData.end(), vInts[1].begin(), vInts[1].end());
					
		return vData;
	}
	
	
	/** Serialize Unsigned Integer. [256 bit.]. **/
	std::vector<unsigned char> Serialize(uint256 nInt){ return nInt.GetBytes(); }
	
	
	/** Serialize Unsigned Integer. [512 bit.]. **/
	std::vector<unsigned char> Serialize(uint512 nInt){ return nInt.GetBytes(); }
	
	
	/** Serialize Unsigned Integer. [576 bit.]. **/
	std::vector<unsigned char> Serialize(uint576 nInt){ return nInt.GetBytes(); }
	
	
	/** Serialize Unsigned Integer. [1024 bit.]. **/
	std::vector<unsigned char> Serialize(uint1024 nInt){ return nInt.GetBytes(); }
	
	
	/** Convert Standard String into a byte stream. **/
	std::vector<unsigned char> Serialize(std::string strData)
	{
		std::vector<unsigned char> vData = Serialize((unsigned int) strData.size());
		vData.insert(vData.end(), strData.begin(), strData.end());
		
		return vData;
	}
	
	
	/** Template to Serialize a Class. **/
	template<typename ClassType> std::vector<unsigned char> Serialize(ClassType cType)
	{ 
		BinaryStream cStream;
		cType.Serialize(cStream);
		
		return cStream.Data();
	}
	
	/** Template Forward Declarations [So pair and vector can Serialize Classes and Classes Can Serialize Vectors and Pairs] **/
	template<typename Type> std::vector<unsigned char> Serialize(std::vector<Type> vElements);
	
	
	/** Template to Serialize a Pair. **/
	template<typename Type1, typename Type2> std::vector<unsigned char> Serialize(std::pair<Type1, Type2> pairData)
	{
		BinaryStream cStream;
		cStream.Write(pairData.first);
		cStream.Write(pairData.second);
	
		return cStream.Data();
	}
	
	
	/** Template to Serialize a Vector **/
	template<typename Type> std::vector<unsigned char> Serialize(std::vector<Type> vElements)
	{
		BinaryStream cStream;
		cStream.Write((unsigned int) vElements.size());
		for(int nIndex = 0; nIndex < vElements.size(); nIndex++)
			cStream.Write(vElements[nIndex]);

		return cStream.Data();
	}
	
	
	/** ------------------------------------------------ De-Serialization Functions ---------------------------------------------------------------- **/
	
	
	/** De-Serialize a byte stream into unsigned char **/	
	int Deserialize(std::vector<unsigned char> vData, unsigned char& nValue, int nOffset = 0)
	{ 
		nValue = vData[nOffset];
		
		return 1;
	}
	
	
	/** De-Serialize a byte stream into unsigned short 16 bit. **/	
	int Deserialize(std::vector<unsigned char> vData, unsigned short& nValue, int nOffset = 0)
	{ 
		nValue = (vData[0 + nOffset] << 8) + vData[1 + nOffset];
		
		return 2;
	}
	
	
	/** De-Serialize a byte stream into unsigned integer 32 bit. **/	
	int Deserialize(std::vector<unsigned char> vData, unsigned int& nValue, int nOffset = 0)
	{
		nValue = (vData[0 + nOffset] << 24) + (vData[1 + nOffset] << 16) + (vData[2 + nOffset] << 8) + vData[3 + nOffset]; 
		
		return 4;
	}
	
	
	/** De-Serialize a byte stream into unsigned integer 64 bit. **/
	int Deserialize(std::vector<unsigned char> vData, uint64& nValue, int nOffset = 0)
	{
		unsigned int nFirst, nSecond;
		Deserialize(vData, nFirst,  nOffset);
		Deserialize(vData, nSecond, 4 + nOffset);
		
		nValue = (nFirst | ((uint64) nSecond << 32)); 
		
		return 8;
	}
	
	
	/** De-Serialize a byte stream into unsigned char **/	
	int Deserialize(std::vector<unsigned char> vData, signed char& nValue, int nOffset = 0)
	{ 
		nValue = (signed char)vData[nOffset];
		
		return 1;
	}
	
	
	/** De-Serialize a byte stream into signed short 16 bit. **/	
	int Deserialize(std::vector<unsigned char> vData, signed short& nValue, int nOffset = 0)
	{ 
		nValue = (vData[0 + nOffset] << 8) + vData[1 + nOffset];
		
		return 2;
	}
	
	
	/** De-Serialize Signed Integer normally, then sign by casting. **/
	int Deserialize(std::vector<unsigned char> vData, signed int& nValue, int nOffset = 0)
	{
		nValue = (vData[0 + nOffset] << 24) + (vData[1 + nOffset] << 16) + (vData[2 + nOffset] << 8) + vData[3 + nOffset]; 
		
		return 4;
	}
	
	
	/** De-Serialize Signed Integers by Normal methods, then casting. **/
	int Deserialize(std::vector<unsigned char> vData, int64& nValue, int nOffset = 0)
	{
		unsigned int nFirst, nSecond;
		Deserialize(vData, nFirst,  nOffset);
		Deserialize(vData, nSecond, 4 + nOffset);
		
		nValue = (nFirst | ((uint64) nSecond << 32));
		
		return 8;
	}
	
	
	/** De-Serialize Unsigned Integer Classes. [256 bit.]. **/
	int Deserialize(std::vector<unsigned char> vData, uint256& nValue, int nOffset = 0)
	{
		std::vector<unsigned char> vBytes(vData.begin() + nOffset, vData.begin() + nOffset + 32);
		nValue.SetBytes(vBytes);
		
		return 32;
	}
	
	
	/** De-Serialize Unsigned Integer Classes. [512 bit.]. **/
	int Deserialize(std::vector<unsigned char> vData, uint512& nValue, int nOffset = 0)
	{ 
		std::vector<unsigned char> vBytes(vData.begin() + nOffset, vData.begin() + nOffset + 64);
		nValue.SetBytes(vBytes);
		
		return 64;
	}
	
	
	/** De-Serialize Unsigned Integer Classes. [576 bit.]. **/
	int Deserialize(std::vector<unsigned char> vData, uint576& nValue, int nOffset = 0)
	{ 
		std::vector<unsigned char> vBytes(vData.begin() + nOffset, vData.begin() + nOffset + 72);
		nValue.SetBytes(vBytes);
		
		return 72;
	}
	
	
	/** De-Serialize Unsigned Integer Classes. [1024 bit.]. **/
	int Deserialize(std::vector<unsigned char> vData, uint1024& nValue, int nOffset = 0)
	{
		std::vector<unsigned char> vBytes(vData.begin() + nOffset, vData.begin() + nOffset + 128);
		nValue.SetBytes(vBytes);
		
		return 128;
	}
	
	
	/** De-Serialize a byte stream into Standard String. **/
	int Deserialize(std::vector<unsigned char> vData, std::string& strData, int nOffset = 0)
	{
		unsigned int nSize;
		nOffset += Deserialize(vData, nSize, nOffset);
		
		std::vector<unsigned char> vBytes(vData.begin() + nOffset, vData.begin() + nOffset + nSize);
		std::string strTemp(vBytes.begin(), vBytes.end());
		strData = strTemp;
		
		return nSize + 4;
	}
	
	
	/** Template to De-Serialize Custom Class Type. Class must Implement Serialize and De-Serialize Methods. **/
	template<typename Type> int Deserialize(std::vector<unsigned char> vData, Type& cType, int nOffset = 0)
	{
		BinaryStream cStream(vData, nOffset);
		cType.Deserialize(cStream);
		
		return SerializeSize(cType);
	}
	
	
	/** Template Forward Declarations [So pair and vector can De-Serialize Classes and Classes Can De-Serialize Vectors and Pairs] **/
	template<typename Type> int Deserialize(std::vector<unsigned char> vData, std::vector<Type>& vReturn, int nOffset = 0);
	
	
	/** Template to De-Serialize a Pair. **/
	template<typename Type1, typename Type2> int Deserialize(std::vector<unsigned char> vData, std::pair<Type1, Type2>& pairData, int nOffset = 0)
	{
		unsigned int nBytes = 0;
		nBytes += Deserialize(vData, pairData.first,  nOffset);
		nBytes += Deserialize(vData, pairData.second, nOffset + nBytes);
		
		return nBytes;
	}
	
	
	/** Template to De-Serialize a Vector **/
	template<typename Type> int Deserialize(std::vector<unsigned char> vData, std::vector<Type>& vReturn, int nOffset = 0)
	{
		unsigned int nElements, nBytes = 0;
		nBytes += Deserialize(vData, nElements, nOffset);
		vReturn.clear();
		
		for( ; nElements > 0 ; nElements-- )
		{
			Type cElement;
			nBytes += Deserialize(vData, cElement, nOffset + nBytes);

			vReturn.push_back(cElement);
		}
		
		return nBytes;
	}
	
}

#endif