#ifndef LOWER_LEVEL_LIBRARY_LLS_TESTS
#define LOWER_LEVEL_LIBRARY_LLS_TESTS

namespace LLS
{

	void Tests()
	{

		unsigned short usA = 22132, usB;
		std::vector<unsigned char> vData = LLS::Serialize(usA);
		LLS::Deserialize(vData, usB);
		
		printf("Unsigned Short: %u Deserialized: %u\n", usA, usB);
		printf("\tBytes = %u - Size = %u\n", vData.size(), SerializeSize(usA));
		
		signed short ssA = 10132, ssB;
		vData = LLS::Serialize(ssA);
		LLS::Deserialize(vData, ssB);
		
		printf("Signed Short [+]: %i Deserialized: %i\n", ssA, ssB);
		printf("\tBytes = %u - Size = %u\n", vData.size(), SerializeSize(ssA));
		
		ssA = -10132, ssB;
		vData = LLS::Serialize(ssA);
		LLS::Deserialize(vData, ssB);
		
		printf("Signed Short [-]: %i Deserialized: %i\n", ssA, ssB);
		printf("\tBytes = %u - Size = %u\n", vData.size(), SerializeSize(ssB));
		
		unsigned int uA = 3351654654, uB;
		vData = LLS::Serialize(uA);
		LLS::Deserialize(vData, uB);
		printf("Unsigned Integer: %u Deserialized: %u\n", uA, uB);
		printf("\tBytes = %u - Size = %u\n", vData.size(), SerializeSize(uA));
		
		signed int sA = 81631087, sB;
		vData = LLS::Serialize(sA);
		LLS::Deserialize(vData, sB);
		
		printf("Signed Integer [+]: %i Deserialized: %i\n", sA, sB);
		printf("\tBytes = %u - Size = %u\n", vData.size(), SerializeSize(sA));
		
		
		sA = -81631087, sB;
		vData = LLS::Serialize(sA);
		LLS::Deserialize(vData, sB);
		
		printf("Signed Integer [-]: %i Deserialized: %i\n", sA, sB);
		printf("\tBytes = %u - Size = %u\n", vData.size(), SerializeSize(sA));
		
		
		uint64 uA64 = 335165465435105, uB64;
		vData = LLS::Serialize(uA64);
		LLS::Deserialize(vData, uB64);
		
		printf("Unsigned Integer 64: %llu Deserialized: %llu\n", uA64, uB64);
		printf("\tBytes = %u - Size = %u\n", vData.size(), SerializeSize(uA64));
		
		int64 sA64 = 3351654654, sB64;
		vData = LLS::Serialize(sA64);
		LLS::Deserialize(vData, sB64);
		
		printf("Signed Integers 64 [+]: %I64d Deserialized: %I64d\n", sA64, sB64);
		printf("\tBytes = %u - Size = %u\n", vData.size(), SerializeSize(sA64));
		
		sA64 = -662513161;
		sB64 = 0;
		vData = LLS::Serialize(sA64);
		LLS::Deserialize(vData, sB64);
		
		printf("Signed Integers 64 [-]: %I64d Deserialized: %I64d\n", sA64, sB64);
		printf("\tBytes = %u - Size = %u\n", vData.size(), SerializeSize(sA64));
		
		uint512 hash512("49898dbe3523c2eb0cb2f215e43df5567c974988bc8b87777bd0f093e18a071d90d249f914210ef9e27e27d2e97e15b10ea0af9ad5c49a97ba4d5dd1732d1d9f");
		vData = LLS::Serialize(hash512);
		
		uint512 hashNew512;
		LLS::Deserialize(vData, hashNew512);
		
		printf("Unsigned Int 512 %s\n\nDeserialized: %s\n\n", hash512.ToString().c_str(), hashNew512.ToString().c_str());
		printf("\tBytes = %u - Size = %u\n", vData.size(), SerializeSize(hash512));
		
		uint1024 hashGenesis("00000bb8601315185a0d001e19e63551c34f1b7abeb3445105077522a9cbabf3e1da963e3bfbb87d260218b7c6207cb9c6df90b86e6a3ce84366434763bc8bcbf6ccbd1a7d5958996aecbe8205c20b296818efb3a59c74acbc7a2d1a5a6b64aab63839b8b11a6b41c4992f835cbbc576d338404fb1217bdd7909ca7db63bbc02");
		vData = LLS::Serialize(hashGenesis);
		
		uint1024 hashNew;
		LLS::Deserialize(vData, hashNew);
		printf("Unsigned Int 1024 %s\n\nDeserialized: %s\n\n", hashGenesis.ToString().c_str(), hashNew.ToString().c_str());
		printf("\tBytes = %u - Size = %u\n", vData.size(), SerializeSize(hashGenesis));
		
		std::string strMessage = "This is a Serialization message from the String. Let us see how this works.\n";
		vData = LLS::Serialize(strMessage);
		
		std::string strNewMessage;
		LLS::Deserialize(vData, strNewMessage);
		
		printf("%s\n%s\n\n", strMessage.c_str(), strNewMessage.c_str());
		printf("\tBytes = %u - Size = %u\n", vData.size(), SerializeSize(strMessage));
		
		std::pair<uint1024, uint512> pairTest = std::make_pair(hashGenesis, hash512);
		vData = LLS::Serialize(pairTest);
		
		std::pair<uint1024, uint512> pairNew;
		LLS::Deserialize(vData, pairNew);

		printf("Pair: %s - %s\n\n Deserialized: %s - %s\n", pairTest.first.ToString().c_str(), pairTest.second.ToString().c_str(), pairNew.first.ToString().c_str(), pairNew.second.ToString().c_str());
		printf("\tBytes = %u - Size = %u\n", vData.size(), SerializeSize(pairTest));
		

		
		std::vector<std::string> vStrings;
		vStrings.push_back("Testing Alpha Numerical 1");
		vStrings.push_back("Testing Alpha Numerical 12");
		vStrings.push_back("Testing Alpha Numerical 133");
		vStrings.push_back("Testing Alpha Numerical 1444");
		vStrings.push_back("Testing Alpha Numerical 15555");
		vStrings.push_back("Testing Alpha Numerica 1");
		vStrings.push_back("Testing Alpha Numeric 1");
		vStrings.push_back("Testing Alpha Numeri 1");
		vStrings.push_back("Testing Alpha Numer 1");
		vStrings.push_back("Testing Alpha Nume 1");
		
		for(int nIndex = 0; nIndex < vStrings.size(); nIndex++)
			printf("Vector %u: %s\n", nIndex, vStrings[nIndex].c_str());
		
		vData = LLS::Serialize(vStrings);
		std::vector<std::string> vNewStrings;
		LLS::Deserialize(vData, vNewStrings);
		
		for(int nIndex = 0; nIndex < vNewStrings.size(); nIndex++)
			printf("Deserialized Vector %u: %s\n", nIndex, vNewStrings[nIndex].c_str());
			
		printf("\tBytes = %u - Size = %u\n", vData.size(), SerializeSize(vStrings));
		
		std::vector< std::pair<uint1024, uint512> > vPairs;
		vPairs.push_back(std::make_pair(hashGenesis, hash512));
		vPairs.push_back(std::make_pair(hashGenesis, hash512));
		vPairs.push_back(std::make_pair(hashGenesis, hash512));
		vPairs.push_back(std::make_pair(hashGenesis, hash512));
		
		vData = LLS::Serialize(vPairs);
		
		std::vector< std::pair<uint1024, uint512> > vNewPairs;
		LLS::Deserialize(vData, vNewPairs);

		for(int nIndex = 0; nIndex < vNewPairs.size(); nIndex++)
			printf("Vector Pair: %s - %s\n\n", vNewPairs[nIndex].first.ToString().c_str(), vNewPairs[nIndex].second.ToString().c_str());
			
		printf("\tBytes = %u - Size = %u\n", vData.size(), SerializeSize(vPairs));
	}
}

#endif