#ifndef LOWER_LEVEL_LIBRARY_LLE_ENCRYPTION
#define LOWER_LEVEL_LIBRARY_LLE_ENCRYPTION

#include "../LLT/LLT.h"
#include "../LLS/LLS.h"
#include "../LLH/LLH.h"

namespace LLE
{
	
	/** Stream inherited from Binary Stream to Encrypt Data once Written. **/
	class EncryptedStream : public LLS::BinaryStream
	{
	public:
		/** Encrypt the Given Data with Encryption Key. **/
		template<typename KeyType> void Encrypt(KeyType cKey)
		{
			const std::vector<unsigned char> vData = Serialize(cKey);
			uint256 hashKey = LLH::SK::SK256(vData);
			
			for(int nIndex = 0; nIndex < vBinaryData.size(); nIndex++)
			{
				CBigNum bnMod(hashKey + vBinaryData[nIndex]);
				vBinaryData[nIndex] = bnMod % 256;
			}
		}
		
		
		/** De-crypt the Given Data with Encryption Key. **/
		template<typename KeyType> void Decrypt(KeyType cKey)
		{
			const std::vector<unsigned char> vData = Serialize(cKey);
			uint256 hashKey = LLH::SK::SK256(vData);
			
			for(int nIndex = 0; nIndex < vBinaryData.size(); nIndex++)
			{
				CBigNum bnMod(hashKey - vBinaryData[nIndex]);
				
				vBinaryData[nIndex] = bnMod % 256;
			}
		}
		
	}
	
}

#endif