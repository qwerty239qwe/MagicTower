#include "initialize.h"

npcSentence::npcSentence()
{
	std::vector<sf::String> sentenceContainer1;
	sentenceContainer1.push_back(L"\u53c8\u4e00\u689d\u5e74\u8f15\u7684\u751f\u547d\u963f\u002e\u002e\u002e\u53ef\u60dc\u4e86\u000d\u000a");
	//又一條年輕的生命阿...可惜了

	std::vector<sf::String> sentenceContainer2;
	sentenceContainer2.push_back(L"\u5728\u9019\u5ea7\u5854\u88e1\uff0c\u9577\u5f97\u50cf\u6211\u9019\u6a23\u7684\u4eba\u6703\u544a\u8a34\u4f60\u8a31\u591a\u6709\u7528\u7684\u8cc7\u8a0a\u548c\u5efa\u8b70\uff0c\u7136\u5f8c\u795e\u79d8\u7684\u6d88\u5931\u3002\n\u76e1\u91cf\u591a\u627e\u50cf\u6211\u9019\u7a2e\u4eba\u804a\u5929\uff0c\u5c0d\u65bc\u5f80\u5f8c\u7684\u8def\u7a0b\u5927\u6709\u5e6b\u52a9\u3002");
	//在這座塔裡，長得像我這樣的人會告訴你許多有用的資訊和建議，然後神秘的消失。盡量多找像我這種人聊天，對於往後的路程大有幫助。

	std::vector<sf::String> sentenceContainer3;
	sentenceContainer3.push_back(L"\u9019\u5ea7\u5854\u5371\u6a5f\u56db\u4f0f\uff0c\u602a\u7269\u6a6b\u884c\uff0c\u60f3\u8981\u722c\u4e0a\u5854\u9802\uff0c\u5fc5\u9808\u8981\u5230\u5546\u5e97\u63d0\u5347\u81ea\u6211\uff0c\u4f46\u662f\u9019\u4e9b\u4e0d\u662f\u514d\u8cbb\u7684\u3002");
	//這座塔危機四伏，怪物橫行，想要爬上塔頂，必須要到商店提升自我，但是這些不是免費的。
	sentenceContainer3.push_back(L"\u6bba\u6b7b\u602a\u7269\u53ef\u4ee5\u7372\u5f97\u91d1\u9322\uff0c\u4f46\u662f\u6703\u640d\u5931\u751f\u547d\u4e14\u6548\u7387\u4e0d\u9ad8\uff0c\u6240\u4ee5\u8aaa\u6709\u500b\u6709\u9322\u7684\u8001\u7238\u9084\u662f\u6bd4\u8f03\u597d");
	//殺死怪物可以獲得金錢，但是會損失生命且效率不高，所以說有個有錢的老爸還是比較好

	std::vector<sf::String> sentenceContainer4;
	sentenceContainer4.push_back(L"\u9632\u79a6\u529b\u7684\u91cd\u8981\u6027\u5f80\u5f80\u88ab\u5ffd\u7565\u4e86");
	//防禦力的重要性往往被忽略了

	std::vector<sf::String> sentenceContainer5;
	sentenceContainer5.push_back(L"\u807d\u8aaa\u9ec3\u9470\u5319\u53ea\u80fd\u958b\u9ec3\u8272\u7684\u9580\u002e\u002e\u002e\u002e\u002e\u002e");
	//聽說黃鑰匙只能開黃色的門......

	std::vector<sf::String> sentenceContainer6;
	sentenceContainer6.push_back(L"\u662f\u5426\u8981\u82b1\u0031\u0030\u0030\u5143\u8b93");
	//是否要花100元讓
	

	std::vector<sf::String> sentenceContainer7;
	sentenceContainer7.push_back(L"\u66fe\u7d93\u6709\u4eba\u544a\u8a34\u6211\uff0c\u5929\u4e0a\u6389\u4e0b\u4f86\u7684\u53ea\u6709\u9ce5\u5c4e\u3002");
	
	std::vector<sf::String> sentenceContainer8;
	sentenceContainer8.push_back(L"\u662f\u5426\u8981\u82b1\u0032\u0030\u0030\u5143\u8b93");

	std::vector<sf::String> sentenceContainer9;
	sentenceContainer9.push_back(L"\u662f\u5426\u8981\u82b1\u0033\u0030\u0030\u5143\u8b93");

	std::vector<sf::String> sentenceContainer10;
	sentenceContainer10.push_back(L"\u60f3\u4e0d\u5230\u4f60\u53ef\u4ee5\u8d70\u5230\u9019\u88e1\uff0c\u7de8\u5287\u9084\u6c92\u7d66\u6211\u8b1b\u7a3f");
	
	std::vector<sf::String> sentenceContainer11;
	sentenceContainer11.push_back(L"\u99ac\u4e0a\u8981\u5230\u5341\u6a13\u4e86\uff0c\u52a0\u6cb9\u597d\u55ce\u0021");

	std::vector<sf::String> sentenceContainer12;
	sentenceContainer12.push_back(L"\u5947\u72bd\uff0c\u5230\u6b64\u70ba\u6b62\u4e86\uff0c\u63a5\u4e0b\u4f86\u5c31\u7531\u6211\u9396\u93c8\u7684\u5eab\u62c9\u76ae\u5361\u4e18\u4f86\u505a\u4f60\u7684\u5c0d\u624b");

	npcSentences.insert(std::make_pair(NPCid::NPC1, sentenceContainer1));
	npcSentences.insert(std::make_pair(NPCid::NPC2, sentenceContainer2));
	npcSentences.insert(std::make_pair(NPCid::NPC3, sentenceContainer3));
	npcSentences.insert(std::make_pair(NPCid::NPC4, sentenceContainer4));
	npcSentences.insert(std::make_pair(NPCid::NPC5, sentenceContainer5));
	npcSentences.insert(std::make_pair(NPCid::NPC6, sentenceContainer6));
	npcSentences.insert(std::make_pair(NPCid::NPC7, sentenceContainer7));
	npcSentences.insert(std::make_pair(NPCid::NPC8, sentenceContainer8));
	npcSentences.insert(std::make_pair(NPCid::NPC9, sentenceContainer9));
	npcSentences.insert(std::make_pair(NPCid::NPC10, sentenceContainer10));
	npcSentences.insert(std::make_pair(NPCid::NPC11, sentenceContainer11));
	npcSentences.insert(std::make_pair(NPCid::NPC12, sentenceContainer12));
}

std::vector<sf::String>& npcSentence::getSentence(NPCid::ID id)
{
	auto finder = npcSentences.find(id);
	return finder->second;
}

FileManager::FileManager(const std::string monsterFileName, const std::string NPCFileName, const std::string tileFileName)
{
	monsterData.resize(countMonster);
	for (int m = 0; m < countMonster; ++m)
	{
		monsterData[m] = std::vector<int>(5); // x, y, z, category, type
	}

	NPCData.resize(countNPC);
	for (int n = 0; n < countNPC; ++n)
	{
		NPCData[n] = std::vector<int>(5); // x, y, z, category, type
	}

	tileData.resize(countTile);
	for (int n = 0; n < countTile; ++n)
	{
		tileData[n] = std::vector<int>(5); // x, y, z, category, type
	}

	loadFile(SAVEFILE_PATH + monsterFileName, monsterData, countMonster);
	loadFile(SAVEFILE_PATH + NPCFileName, NPCData, countNPC);
	loadFile(SAVEFILE_PATH + tileFileName, tileData, countTile);
}

void FileManager::loadFile(const std::string &fileName, std::vector<std::vector<int>> &data, const int countData)
{
	std::ifstream file(fileName);
	if (!file.is_open())
		std::cout << "couldn't open file" << '\n';
	else
	{
		std::vector<std::string> fline(5);

		for (int row = 0; row < countData; ++row)
		{
			for (int col = 0; col < 5; ++col)
			{
				if (col != 4)
				{
					std::getline(file, fline[col], ',');
					data[row][col] = std::stoi(fline[col]);
					
				}
				else
				{
					std::getline(file, fline[col], '\n');
					data[row][col] = std::stoi(fline[col]);
					
				}
			}
		}
		file.close();
	}
	
}


std::vector<std::vector<int>> FileManager::getMonsterData()
{
	return monsterData;
}

std::vector<std::vector<int>> FileManager::getNPCData()
{
	return NPCData;
}

std::vector<std::vector<int>> FileManager::getTileData()
{
	return tileData;
}