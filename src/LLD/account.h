#ifndef LOWER_LEVEL_LIBRARY_LLD_ACCOUNT
#define LOWER_LEVEL_LIBRARY_LLD_ACCOUNT

#include "database.h"

namespace LLD
{
	class Account
	{
		/** Data Objects the Class Contains. The Objects that are Serialized and De-Serialized. **/
		LLT::uint64 nAccountBalance;
		LLT::uint64 nRoundShares;
		
		
		/** Password for the Current Account. **/
		std::string strPassword;
		
		
		/** Counter for Blocks Found. **/
		unsigned int nBlocksFound;
		
		
		/** Vector to Hold Registered Addresses. **/
		//std::vector<std::string> vAddresses;
		
		
		/** Vector to Hold Workers. **/
		//std::vector<Worker> vWorkers;
	public:
		
		/** Required Serialization Function. **/
		template<class StreamType> void Serialize(StreamType& cStream)
		{
			cStream.Write(nAccountBalance);
			cStream.Write(nRoundShares);
			cStream.Write(strPassword);
			cStream.Write(nBlocksFound);
			//cStream.Write(vAddresses);
			//cStream.Write(vWorkers);
		}
		
		
		/** Required De-Serialization Function. **/
		template<class StreamType> void Deserialize(StreamType& cStream)
		{
			cStream.Read(nAccountBalance);
			cStream.Read(nRoundShares);
			cStream.Read(strPassword);
			cStream.Read(nBlocksFound);
			//cStream.Read(vAddresses);
			//cStream.Read(vWorkers);
		}
		
		/** Required Serialization Size Function. **/
		unsigned int SerializeSize()
		{
			unsigned int nSerializeSize = 0;
			nSerializeSize += LLS::SerializeSize(nAccountBalance);
			nSerializeSize += LLS::SerializeSize(nRoundShares);
			nSerializeSize += LLS::SerializeSize(strPassword);
			nSerializeSize += LLS::SerializeSize(nBlocksFound);
			//nSerializeSize += LLS::SerializeSize(vAddresses);
			//nSerializeSize += LLS::SerializeSize(vWorkers);
			
			return nSerializeSize;
		}
	};
}

#endif