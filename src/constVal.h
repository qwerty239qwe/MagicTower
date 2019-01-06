#pragma once
#include <string>					// std::string
#include <vector>					// std::vector
#include <map>						// std::map
#include <fstream>
#include <iostream>
#include <algorithm>				// std::sort
#include <SFML/Graphics.hpp>

const int window_width = 1430, window_height = 880;
const int FONT_SIZE = 25;
const int countMonster = 60;
const int countNPC = 12;
const int countTile = 355;
const float GRID_LEN = 80;
const std::string FONT_PATH = ".\/resources\/font\/";
const std::string SAVEFILE_PATH = ".\/resources\/data\/";
const std::string SOUND_PATH = ".\/resources\/sound effects\/";
const std::string BGM_PATH = ".\/resources\/music\/";
const std::string SPRITE_PATH = ".\/resources\/sprites\/";

namespace NPCid {
	enum ID {
		NPC1, NPC2, NPC3, NPC4, NPC5,
		NPC6, NPC7, NPC8, NPC9, NPC10,
		NPC11, NPC12
	};
}

namespace TileID {
	enum ID {
		Wall1, Upstair1, Wall2, Wall3, Wall4, Wall5, Wall6, 
		Wall7, Wall8, Wall9, Wall10, Wall11, Wall12, Wall13, 
		Wall14, Irondoor1, Wall15, Wall16, Wall17, Wall18, 
		Wall19, Wall20, Wall21, Wall22, Wall23, Wall24, Wall25, 
		Wall26, Downstair1, Wall27, Wall28, Upstair2, Wall29, 
		Wall30, Wall31, Wall32, Wall33, Wall34, Wall35, 
		YellowKey1, Wall36, Wall37, Wall38, Wall39, Wall40, Wall41, 
		Wall42, Wall43, YellowDoor1, Wall44, Wall45, YellowDoor2, 
		Wall46, Wall47, Wall48, Wall49, RedWater1, RedWater2, Wall50, 
		Wall51, YellowKey2, Wall52, Wall53, RedKey1, YellowKey3, YellowKey4, 
		Wall54, Wall55, Wall56, Wall57, Downstair2, Irondoor2, Irondoor3,
		Irondoor4, Wall58, Wall59, Wall60, Wall61, Wall62, Irondoor5,
		Wall63, Irondoor6, Wall64, Irondoor7, Wall65, Irondoor8, Wall66,
		Irondoor9, Wall67, Irondoor10, Wall68, Irondoor11, Wall69,
		Irondoor12, Wall70, Wall71, Wall72, Wall73, Wall74, Irondoor13,
		Irondoor14, Irondoor15, Wall75, Wall76, Wall77, Wall78, Wall79,
		Upstair3, Wall80, Wall81, YellowKey5, BlueWater1, YellowDoor3, Wall82,
		BlueKey1, Wall83, Wall84, Wall85, Wall86, Wall87, Wall88, Wall89,
		Wall90, Wall91, YellowDoor4, Wall92, Wall93, Wall94, Wall95, Wall96,
		Wall97, YellowDoor5, Wall98, Wall99, Wall100, Wall101, Wall102, Wall103,
		Upstair4, Wall104, Downstair3, Upstair5, Wall105, Wall106, RedWater3,
		Wall107, Wall108, RedWater4, YellowKey6, Wall109, Wall110, Wall111,
		YellowDoor6, Wall112, Wall113, Wall114, Wall115, Wall116, Wall117,
		Wall118, Wall119, Wall120, Wall121, Wall122, Wall123, Wall124,
		Wall125, Wall126, Wall127, Wall128, BlueKey2, Wall129, Wall130,
		BlueDoor1, Downstair4, Wall131, Wall132Wall133, Sword1, Downstair5,
		Wall134, Wall135, Wall136, Wall137, Wall138, Wall139, Wall140, Wall141,
		Wall142, Wall143, Wall144, Wall145, YellowDoor7, Wall146, Wall147,
		Wall148, Wall149, BlueDoor2, Wall150, Wall151, Wall152, YellowDoor8,
		Wall153, Wall154, Wall155, Wall156, Upstair6, Wall157, Wall158, Wall159,
		Upstair7, Wall160, Wall161, Wall162, Wall163, YellowDoor9, Wall164, Wall165,
		Wall166, Wall167, Wall168, Wall169, Wall170, Wall171, Wall172, Wall173,
		Wall174, YellowDoor10, BlueWater2, RedWater5, Wall175, Wall176, YellowDoor11,
		Wall177, Wall178, Wall179, Wall180, Wall181, Wall182, Wall183, Wall184, Wall185,
		Wall186, Wall187, Wall188, Downstair6, Wall189, Wall190, Sword2, Downstair7, 
		Wall191, Wall192, Wall193, Wall194, Wall195, Wall196, Wall197, Wall198, Wall199,
		Wall200, Wall201, Wall202, Wall203, Wall204, Wall205, Wall206, Wall207, Wall208,
		Wall209, Wall210, Wall211, Wall212, Wall213, YellowKey7, BlueKey3, Wall214, Wall215,
		BlueKey4, BlueKey5, Wall216, Upstair8, Wall217, Wall218, Wall219, Wall220, RedKey2,
		Upstair9, Wall221, Wall222, Wall223, Wall224, Wall225, Wall226, Wall227, Wall228,
		Wall229, Wall230, Wall231, BlueDoor3, Wall232, Wall233, Wall234, Wall235, Wall236,
		Wall237, Wall238, RedWater6, RedWater7, RedWater8, Wall239, Wall240, Wall241, Shield1,
		BlueWater3, RedWater9, RedDoor1, Wall242, Wall243, Wall244, RedWater10, RedWater11,
		RedWater12, Wall245, Downstair8, Wall246, Wall247, BlueWater4, Wall248, Downstair9,
		Wall249, Wall250, Wall251, Wall252, Wall253, Wall254, Wall255, Wall256, Wall257, 
		Upstair10, Wall258, Wall259, Wall260, Wall261, Wall262, Wall263, Wall264, Wall265, 
		Wall266, Wall267, Wall268, Wall269, Wall270, Wall271, Wall272, Downstair10
	};
}

namespace Monsterid {
	enum ID {
		Monster1,Monster2,Monster3,Monster4,Monster5,
		Monster6,Monster7,Monster8,Monster9,Monster10,
		Monster11,Monster12,Monster13,Monster14,Monster15,
		Monster16,Monster17,Monster18,Monster19,Monster20,
		Monster21,Monster22,Monster23,Monster24,Monster25,
		Monster26,Monster27,Monster28,Monster29,Monster30,
		Monster31,Monster32,Monster33,Monster34,Monster35,
		Monster36,Monster37,Monster38,Monster39,Monster40,
		Monster41,Monster42,Monster43,Monster44,Monster45,
		Monster46,Monster47,Monster48,Monster49,Monster50,
		Monster51,Monster52,Monster53,Monster54,Monster55,
		Monster56,Monster57,Monster58,Monster59,Monster60

	};
	enum Type {
		Slime = 1,
		Slime2,
		Skeleton, SkeletonWarrior,
		GitCat
	};
}
class npcSentence
{
public:
	npcSentence();
	std::vector<sf::String>& getSentence(NPCid::ID id);
private:
	std::map< NPCid::ID , std::vector<sf::String>> npcSentences;
};

class FileManager
{
public :
	FileManager() { ; }
	FileManager(const std::string monsterFileName, const std::string NPCFileName, const std::string tileFileName);
	std::vector<std::vector<int>> getMonsterData();
	std::vector<std::vector<int>> getNPCData();
	std::vector<std::vector<int>> getTileData();
private:
	void loadFile(const std::string &fileName, std::vector<std::vector<int>> &data, const int countData);

	std::vector<std::vector<int>> monsterData;
	std::vector<std::vector<int>> NPCData;
	std::vector<std::vector<int>> tileData;
};