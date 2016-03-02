#include "LLD/LLD.h"
#include "LLU/macro.h"

	/** Used to Sort the Database Account Keys by Balance. *
	bool BalanceSort(const std::string& firstElem, const std::string& secondElem)
	{
		return Core::AccountDB.GetRecord(firstElem).nAccountBalance > Core::AccountDB.GetRecord(secondElem).nAccountBalance; 
	}
	
	

	std::vector<std::string> GetSortedAccounts()
	{
		std::vector<std::string> vAccounts = AccountDB.GetKeys();
		std:sort(vAccounts.begin(), vAccounts.end(), BalanceSort);
		
		return vAccounts; 
	}
	**/  
	  
	class Worker 
	{
	public:
		Worker() {}
		Worker(std::string pass, unsigned int nMin) { strPassword = pass; nMinimumShare = nMin; nRoundShares = 0;}
		
		std::string workerName;
		std::string strPassword;
		
		unsigned int nMinimumShare;
		uint64 nRoundShares;
		
		
		/** Required Serialization Function. **/
		template<class StreamType> void Serialize(StreamType& cStream)
		{
			cStream.Write(workerName);
			cStream.Write(strPassword);
			cStream.Write(nMinimumShare);
			cStream.Write(nRoundShares);
		}
		
		
		/** Required De-Serialization Function. **/
		template<class StreamType> void Deserialize(StreamType& cStream)
		{
			cStream.Read(workerName);
			cStream.Read(strPassword);
			cStream.Read(nMinimumShare);
			cStream.Read(nRoundShares);
		}
		
		
		/** Required Serialization Size Function. **/
		unsigned int SerializeSize()
		{
			unsigned int nSerializeSize = 0;
			nSerializeSize += LLS::SerializeSize(workerName);
			nSerializeSize += LLS::SerializeSize(strPassword);
			nSerializeSize += LLS::SerializeSize(nMinimumShare);
			nSerializeSize += LLS::SerializeSize(nRoundShares);
			
			return nSerializeSize;
		}
		
		void Print() { printf("Worker: %s Minimum: %u Shares: %I64d\n", strPassword.c_str(), nMinimumShare, nRoundShares); }
	};
	
	class Account
	{
	public:
		/** Data Objects the Class Contains. The Objects that are Serialized and De-Serialized. **/
		uint64 nAccountBalance;
		
		
		/** Password for the Current Account. **/
		std::string strPassword;
		
		
		/** Counter for Blocks Found. **/
		unsigned int nBlocksFound;
		
		
		/** Vector to Hold Registered Addresses. **/
		std::vector<std::string> vAddresses;
		
		
		/** Vector to Hold Workers. **/
		std::vector<Worker> vWorkers;
		
		
		/** Add Worker to The Account. **/
		void AddWorker(std::string strPassword, unsigned int nMinimumShare)
		{
			Worker cWorker(strPassword, nMinimumShare);
			vWorkers.push_back(cWorker);
		}
		
		
		/** Remove a Worker From Account. **/
		void RemoveWorker(unsigned int nIndex) {  }
		
		
		/** Required Serialization Function. **/
		template<class StreamType> void Serialize(StreamType& cStream)
		{
			cStream.Write(nAccountBalance);
			cStream.Write(strPassword);
			cStream.Write(nBlocksFound);
			//cStream.Write(vAddresses);
			cStream.Write(vWorkers);
		}
		
		
		/** Required De-Serialization Function. **/
		template<class StreamType> void Deserialize(StreamType& cStream)
		{
			cStream.Read(nAccountBalance);
			cStream.Read(strPassword);
			cStream.Read(nBlocksFound);
			//cStream.Read(vAddresses);
			cStream.Read(vWorkers);
		}
		
		/** Required Serialization Size Function. **/
		unsigned int SerializeSize()
		{
			unsigned int nSerializeSize = 0;
			nSerializeSize += LLS::SerializeSize(nAccountBalance);
			nSerializeSize += LLS::SerializeSize(strPassword);
			nSerializeSize += LLS::SerializeSize(nBlocksFound);
			//nSerializeSize += LLS::SerializeSize(vAddresses);
			nSerializeSize += LLS::SerializeSize(vWorkers);
			
			return nSerializeSize;
		}
		
		void Print()
		{
			printf("Account Balance: %I64d Password: %s Blocks: %u\n", nAccountBalance, strPassword.c_str(), nBlocksFound);
			
			for(int nIndex = 0; nIndex < vWorkers.size(); nIndex++)
				vWorkers[nIndex].Print();
		}
	};


	static unsigned int nRequests = 0;
	static Account cAccount;
	static LLD::SectorDatabase<std::string, Account> DATABASE("database.dat");
	
void LoadThread()
{
	unsigned int nCounter = 1;   
	Account cNewAccount;
	
	while(true)
	{ 
		DATABASE.UpdateRecord("account9", cAccount);
		DATABASE.UpdateRecord("accouasdfnt9", cAccount);
		DATABASE.UpdateRecord("acc3wefsount9", cAccount);
		DATABASE.Commit();
		
		//DATABASE.UpdateRecord("account5522", cAccount);
		//DATABASE.UpdateRecord("account33", cAccount);
		//DATABASE.UpdateRecord("account44", cAccount);
		//DATABASE.UpdateRecord("account99", cAccount);
		//DATABASE.UpdateRecord("accouasdfnt9", cAccount);   
		//DATABASE.UpdateRecord("acc3wefsount9", cAccount);
		   
		//bool fSuccess = true;

			 
		//if(DATABASE.GetRecord("account44", cNewAccount))
		//	 cNewAccount.Print();
			 
		//if(DATABASE.GetRecord("account99", cNewAccount))
		//	cNewAccount.Print();
		   
		//DATABASE.EraseRecord("account22"); 
		//DATABASE.EraseRecord("account33");
		//DATABASE.EraseRecord("account44"); 
		//DATABASE.EraseRecord("account99");
		//DATABASE.EraseRecord("accouasdfnt9");
		//DATABASE.EraseRecord("acc3wefsount9");
		//DATABASE.Commit();
		 

		//std::string strOld = strprintf("account-new-test-next-%u", nCounter - 100);
			 
		//if(DATABASE.GetRecord(strOld, cNewAccount));
		//cNewAccount.Print();
		//DATABASE.EraseRecord(strOld);
		
		//std::string strNew = strprintf("account-new-test-next-%u", nCounter);
		//DATABASE.UpdateRecord(strNew, cAccount);
		//DATABASE.Commit();
		
		nCounter++;
		nRequests++;
		nRequests++;
		nRequests++;
	}
}

int main(int argc, char *argv[])
{
	
	
	cAccount.nAccountBalance = 53151351;
	cAccount.nBlocksFound = 1531;
	cAccount.strPassword = "test_password";
	cAccount.AddWorker("pass1", 999381);
	cAccount.AddWorker("pasdfss1", 8131813);
	cAccount.AddWorker("pasdfasdfass1", 8133813);
	cAccount.AddWorker("pasasdgasdgasds1", 818133);
	cAccount.AddWorker("pasdgasdgasdss1", 81813);
	cAccount.Print();
	
	printf("\n\n------------------------------------------------------------------------------\n\n");
	
	
	DATABASE.Initialize();
	
	//Account cNewAccount = DATABASE.GetRecord("account2");
	//cNewAccount.Print();
		   
	for(int nIndex = 0; nIndex < 1; nIndex++)
	{
		boost::thread cThread(LoadThread);
	}
	
	while(true)
	{
		Sleep(2000);
		printf("[LLD] Database Running at %f Requests per Second\n", nRequests / 2.0);
		
		nRequests = 0;
	}

	
	return 0;
}