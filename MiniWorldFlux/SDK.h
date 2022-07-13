#pragma once
#include "pch.h"
#include "Offsets.h"

using Address = unsigned long;
using Pointer = unsigned long;

namespace SDK {

	constexpr int POINTTO_AIR = 0;
	constexpr int POINTTO_BLOCK = 1;
	constexpr int POINTTO_ENTITY = 2;

	constexpr int MODE_CREATIVE = 1;
	constexpr int MODE_ULTIMATE = 2;
	constexpr int MODE_SURVIVE = 3;
	constexpr int MODE_EDIT = 4;
	constexpr int MODE_FUN = 5;

	constexpr int TEAM_NONE = 0;
	constexpr int TEAM_RED = 1;
	constexpr int TEAM_BLUE = 2;
	constexpr int TEAM_GREEN = 3;
	constexpr int TEAM_YELLOW = 4;
	constexpr int TEAM_ORANGE = 5;
	constexpr int TEAM_PURPLE = 6;

	constexpr int PERMISSION_SINGLEPLAYER = 0;
	constexpr int PERMISSION_ROOMMEMBER = 2;
	constexpr int PERMISSION_ROOMADMIN = 3;

	class World
	{
	public:
		char pad_0000[540]; //0x0000
		class WorldManager* worldManager; //0x021C
		char pad_0220[17664]; //0x0220
		class PlayerList_Level1* playerList_Level1; //0x4720
	}; //Size: 0x4724

	class WorldManager
	{
	public:
		char pad_0000[208]; //0x0000
		int mode; //0x00D0
	}; //Size: 0x00D4

	class ClientPlayer
	{
	public:
		char pad_0004[1164]; //0x0004
		class ActorBody* actorBody; //0x0490
		char pad_0494[96]; //0x0494
		int32_t flyState; //0x04F4
		char pad_04F8[20]; //0x04F8
		class PlayerLocoMotion* playerLocoMotion; //0x050C
		char pad_0510[4]; //0x0510
		class PlayerAttribuLua* playerAttribuLua; //0x0514
		char pad_0518[32]; //0x0518
		int32_t uid; //0x0538
		char pad_053C[156]; //0x053C
		class PlayerHpProgressComponent* playerHpProgressComponent; //0x05D8
		class PlayerTeamComponent* playerTeamComponent; //0x05DC
		char pad_05E0[8]; //0x05E0
		float modelScale; //0x05E8
		char pad_05EC[420]; //0x05EC
		class Weapon* weapon; //0x0790
		char pad_0794[664]; //0x0794
		class GameCamera* gameCamera; //0x0A2C
		char pad_0A30[100]; //0x0A30
		int32_t crossPointTo; //0x0A94

		virtual void Function0();
		virtual void Function1();
		virtual void Function2();
		virtual void Function3();
		virtual void Function4();
		virtual void Function5();
		virtual void Function6();
		virtual void Function7();
		virtual void Function8();
		virtual void Function9();
		virtual void Function10();
		virtual void Function11();
		virtual void Function12();
		virtual void Function13();
		virtual void Function14();
		virtual void Function15();
		virtual void Function16();
		virtual void Function17();
		virtual void Function18();
		virtual void Function19();
		virtual void Function20();
		virtual void Function21();
		virtual void Function22();
		virtual void Function23();
		virtual void Function24();
		virtual void Function25();
		virtual void Function26();
		virtual void Function27();
		virtual void Function28();
		virtual void Function29();
		virtual void Function30();
		virtual void Function31();
		virtual void Function32();
		virtual void Function33();
		virtual void Function34();
		virtual void Function35();
		virtual void Function36();
		virtual void Function37();
		virtual void Function38();
		virtual void Function39();
		virtual void Function40();
		virtual void Function41();
		virtual void Function42();
		virtual void Function43();
		virtual void Function44();
		virtual void Function45();
		virtual void Function46();
		virtual void Function47();
		virtual void Function48();
		virtual void Function49();
		virtual void Function50();
		virtual void Function51();
		virtual void Function52();
		virtual void Function53();
		virtual void Function54();
		virtual void Function55();
		virtual void Function56();
		virtual void Function57();
		virtual void Function58();
		virtual void Function59();
		virtual void Function60();
		virtual void Function61();
		virtual void Function62();
		virtual void Function63();
		virtual void Function64();
		virtual void Function65();
		virtual void Function66();
		virtual void Function67();
		virtual void Function68();
		virtual void Function69();
		virtual void Function70();
		virtual void Function71();
		virtual void Function72();
		virtual void Function73();
		virtual void Function74();
		virtual void Function75();
		virtual void Function76();
		virtual void Function77();
		virtual void Function78();
		virtual void Function79();
		virtual void Function80();
		virtual void Function81();
		virtual void Function82();
		virtual void Function83();
		virtual void Function84();
		virtual void Function85();
		virtual void Function86();
		virtual void Function87();
		virtual void Function88();
		virtual void Function89();
		virtual void Function90();
		virtual void Function91();
		virtual void Function92();
		virtual void Function93();
		virtual void Function94();
		virtual void Function95();
		virtual void Function96();
		virtual void Function97();
		virtual void Function98();
		virtual void Function99();
		virtual void Function100();
		virtual void Function101();
		virtual void Function102();
		virtual void Function103();
		virtual void Function104();
		virtual void Function105();
		virtual void Function106();
		virtual void Function107();
		virtual void Function108();
		virtual void Function109();
		virtual void Function110();
		virtual void Function111();
		virtual void Function112();
		virtual void Function113();
		virtual void Function114();
		virtual void Function115();
		virtual void Function116();
		virtual void Function117();
		virtual void Function118();
		virtual void Function119();
		virtual void Function120();
		virtual void Function121();
		virtual void Function122();
		virtual void Function123();
		virtual void Function124();
		virtual void Function125();
		virtual void Function126();
		virtual void Function127();
		virtual void Function128();
		virtual void Function129();
		virtual void Function130();
		virtual void Function131();
		virtual void Function132();
		virtual void Function133();
		virtual void Function134();
		virtual void Function135();
		virtual void Function136();
		virtual void Function137();
		virtual void Function138();
		virtual void Function139();
		virtual void Function140();
		virtual void Function141();
		virtual void Function142();
		virtual void Function143();
		virtual void Function144();
		virtual void Function145();
		virtual void Function146();
		virtual void Function147();
		virtual void Function148();
		virtual void Function149();
		virtual void Function150();
		virtual void Function151();
		virtual void Function152();
		virtual void Function153();
		virtual void Function154();
		virtual void Function155();
		virtual void Function156();
		virtual void Function157();
		virtual void Function158();
		virtual void Function159();
		virtual void Function160();
		virtual void Function161();
		virtual void Function162();
		virtual void Function163();
		virtual void Function164();
		virtual void Function165();
		virtual void Function166();
		virtual void Function167();
		virtual void Function168();
		virtual void Function169();
		virtual void Function170();
		virtual void Function171();
		virtual void Function172();
		virtual void Function173();
		virtual void Function174();
		virtual void Function175();
		virtual void Function176();
		virtual void Function177();
		virtual void Function178();
		virtual void Function179();
		virtual void Function180();
		virtual void Function181();
		virtual void Function182();
		virtual void Function183();
		virtual void Function184();
		virtual void Function185();
		virtual void Function186();
		virtual void Function187();
		virtual void Function188();
		virtual void Function189();
		virtual void Function190();
		virtual void Function191();
		virtual void Function192();
		virtual void Function193();
		virtual void Function194();
		virtual void Function195();
		virtual void Function196();
		virtual void Function197();
		virtual void Function198();
		virtual void Function199();
		virtual void Function200();
		virtual void Function201();
		virtual void Function202();
		virtual void Function203();
		virtual void Function204();
		virtual void Function205();
		virtual void Function206();
		virtual void Function207();
		virtual void Function208();
		virtual void Function209();
		virtual void Function210();
		virtual void Function211();
		virtual void Function212();
		virtual void Function213();
		virtual void Function214();
		virtual void Function215();
		virtual void Function216();
		virtual void Function217();
		virtual void Function218();
		virtual void Function219();
		virtual void Function220();
		virtual void Function221();
		virtual void Function222();
		virtual void Function223();
		virtual void Function224();
		virtual void Function225();
		virtual void Function226();
		virtual void Function227();
		virtual void Function228();
		virtual void Function229();
		virtual void Function230();
		virtual void Function231();
		virtual void Function232();
		virtual void Function233();
		virtual void Function234();
		virtual void Function235();
		virtual void Function236();
		virtual void Function237();
		virtual void Function238();
		virtual void Function239();
		virtual void Function240();
		virtual void Function241();
		virtual void Function242();
		virtual void Function243();
		virtual void Function244();
		virtual void Function245();
		virtual void Function246();
		virtual void Function247();
		virtual void Function248();
		virtual void Function249();
		virtual void Function250();
		virtual void Function251();
		virtual void Function252();
		virtual void Function253();
		virtual void Function254();
		virtual void Function255();
		virtual void Function256();
		virtual void Function257();
		virtual void Function258();
		virtual void Function259();
		virtual void Function260();
		virtual void Function261();
		virtual void Function262();
		virtual void Function263();
		virtual void Function264();
		virtual void Function265();
		virtual void Function266();
		virtual void Function267();
		virtual void Function268();
		virtual void Function269();
		virtual void Function270();
		virtual void Function271();
		virtual void Function272();
		virtual void attackEntity(uintptr_t target);
		virtual void doActualRangeAttack(uintptr_t target);
		virtual void Function275();
		virtual void Function276();
		virtual void Function277();
		virtual void Function278();
		virtual void Function279();
		virtual void Function280();
		virtual void Function281();
		virtual void Function282();
		virtual void Function283();
		virtual void Function284();
		virtual void Function285();
		virtual void Function286();
		virtual void Function287();
		virtual void Function288();
		virtual void Function289();
		virtual void Function290();
		virtual void Function291();
		virtual void Function292();
		virtual void Function293();
		virtual void Function294();
		virtual void Function295();
		virtual void Function296();
		virtual void Function297();
		virtual void Function298();
		virtual void Function299();
		virtual void Function300();
		virtual void Function301();
		virtual void Function302();
		virtual void Function303();
		virtual void Function304();
		virtual void Function305();
		virtual void Function306();
		virtual void Function307();
		virtual void Function308();
		virtual void Function309();
		virtual void Function310();
		virtual void Function311();
		virtual void Function312();
		virtual void Function313();
		virtual void Function314();
		virtual void Function315();
		virtual void Function316();
		virtual void Function317();
		virtual void Function318();
		virtual void Function319();
		virtual void Function320();
		virtual void Function321();
		virtual void Function322();
		virtual void Function323();
		virtual void Function324();
		virtual void Function325();
		virtual void Function326();
		virtual void Function327();
		virtual void Function328();
		virtual void Function329();
		virtual void Function330();
		virtual void Function331();
		virtual void Function332();
		virtual void Function333();
		virtual void Function334();
		virtual void Function335();
		virtual void setJumping(bool jump);
	}; //Size: 0x0A98

	class PlayerList_Level1
	{
	public:
		char pad_0000[12]; //0x0000
		unsigned long* playerList; //0x000C
		char pad_0010[12]; //0x0010
		int length; //0x001C
		char pad_0020[56]; //0x0020
		int mobListLength; //0x0058
	}; //Size: 0x005C

	class ActorBody
	{
	public:
		char pad_0000[528]; //0x0000
		class Entity* entity; //0x0210
	}; //Size: 0x0214

	class Entity
	{
	public:
		char pad_0000[108]; //0x0000
		float posX; //0x006C
		float posY; //0x0070
		float posZ; //0x0074
	}; //Size: 0x0078

	class PlayerAttribuLua
	{
	public:
		char pad_0000[460]; //0x0000
		float currentHealth; //0x01CC
		char pad_01D0[4]; //0x01D0
		float maxHealth; //0x01D4
		char pad_01D8[36]; //0x01D8
		float walkingSpeed; //0x01FC
		float runningSpeed; //0x0200
		float sneakingSpeed; //0x0204
		float swimmingSpeed; //0x0208
		float jumpHeight; //0x020C
		char pad_0210[24]; //0x0210
		float oxygen; //0x0228
		char pad_022C[108]; //0x022C
		float currentHunger; //0x0298
		char pad_029C[8]; //0x029C
		float maxHunger; //0x02A4
	}; //Size: 0x02A8

	class GameCamera
	{
	public:
		char pad_0000[4]; //0x0000
		float yaw; //0x0004
		float pitch; //0x0008
		char pad_000C[44]; //0x000C
		class Camera* camera; //0x0038
		char pad_003C[48]; //0x003C
		float fov; //0x006C
	}; //Size: 0x0070

	class Camera
	{
	public:
		char pad_0000[108]; //0x0000
		float posX; //0x006C
		float posY; //0x0070
		float posZ; //0x0074
	}; //Size: 0x0078

	class UIRenderer
	{
	public:
		char pad_0000[572]; //0x0000
		class Matrix_Level1* matrixLevel1; //0x023C
	}; //Size: 0x0240

	class Matrix_Level1
	{
	public:
		char pad_0000[2252]; //0x0000
		class Matrix_Level2* matrixLevel2; //0x08CC
	}; //Size: 0x08D0

	class Matrix_Level2
	{
	public:
		char pad_0000[56]; //0x0000
		float matrix[4][4]; //0x0038
		float camPosX; //0x0078
		float camPosY; //0x007C
		float camPosZ; //0x0080
	}; //Size: 0x0084

	class PlayerLocoMotion
	{
	public:
		char pad_0000[12]; //0x0000
		float yaw; //0x000C
		float pitch; //0x0010
		char pad_0014[52]; //0x0014
		int32_t posX; //0x0048
		int32_t posY; //0x004C
		int32_t posZ; //0x0050
		char pad_0054[28]; //0x0054
		float motionX; //0x0070
		float motionY; //0x0074
		float motionZ; //0x0078
		char pad_007C[32]; //0x007C
		int32_t onGround; //0x009C
		char pad_00A0[80]; //0x00A0
		int32_t phase; //0x00F0
	}; //Size: 0x00F4

	class PlayerTeamComponent
	{
	public:
		char pad_0000[8]; //0x0000
		int team; //0x0008
	}; //Size: 0x000C

	class PlayerHpProgressComponent
	{
	public:
		char pad_0000[32]; //0x0000
		int team; //0x0020
	}; //Size: 0x0024

	class MpGameSurvive
	{
	public:
		char pad_0000[72]; //0x0000
		unsigned long* playerInfo; //0x0048
	}; //Size: 0x004C

	class PlayerInfo
	{
	public:
		int uid; //0x0000
		char pad_0004[16]; //0x0004
		int posX; //0x0014
		int posY; //0x0018
		int posZ; //0x001C
		char pad_0020[4]; //0x0020
		int team; //0x0024
		char pad_0028[16]; //0x0028
		char name[32]; //0x0038
		char pad_0058[24]; //0x0058
		int inRoom; //0x0070
	}; //Size: 0x0074

	class Weapon
	{
	public:
		class WeaponAttribute* currentWeaponAttr; //0x0000
		char pad_0004[8]; //0x0004
		int32_t remainAmmo; //0x000C
		float spread; //0x0010
	}; //Size: 0x0014

	class WeaponAttribute
	{
	public:
		int32_t itemID; //0x0000
		char weaponName[16]; //0x0004
		char pad_0014[48]; //0x0014
		int16_t N00001A94; //0x0044
		int16_t shootInterval; //0x0046
		int16_t N00001A95; //0x0048
		int16_t maxClipAmmo; //0x004A
		char pad_004C[56]; //0x004C
		int32_t fireMode; //0x0084
	}; //Size: 0x0088

	class RoomManager
	{
	public:
		char pad_0000[1576]; //0x0000
		int32_t permission; //0x0628
	}; //Size: 0x062C

	World* getWorld();
	UIRenderer* getUIRenderer();
	RoomManager* getRoomManager();
	float getIngameFPS();
	int getIngamePing();
	std::string getGameVersion();

}

