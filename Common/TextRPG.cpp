//텍스트 RPG ----------21.10.11 던전2 진척도 100일 때 처리 부족
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
//씬
//방향키
enum DirKey {
	Up = 72, Down = 80, Left = 75, Right = 77
};
//좌표
typedef struct Coord {
	int x, y;
};
enum ECoords {
	Exp, Hp, Atk,
	TitleName, TitleEtc,
	SysMsg, TownBtn1, TownBtn2,
	DungeonExploreBtn, MoveTownDungeon, DungeonProgress,
	MobImage, MobStat, MobName, MobSay,
	EndingMsg,
	CoordMax
};
const Coord CoordList[CoordMax] = {
	Coord {15, 18}, Coord {34, 18}, Coord {52, 18},
	Coord {9, 7}, Coord {30, 13},
	Coord {15, 14}, Coord {15, 5}, Coord {15, 10},
	Coord {32, 7}, Coord {44, 1}, Coord {1, 1},
	Coord {30, 6}, Coord {52, 9}, Coord {52, 8}, Coord {45, 4},
	Coord {25, 15}
};
//던전
enum DungeonStage {
	D1, D2
};
typedef struct Dungeon {
	int index;
	int progress;
};
void InitDungeon();
//오브젝트 공통
typedef struct Stat {
	int hp;
	int atk;
};
//플레이어
typedef struct Player {
	Stat stat;
	int exp;
	BOOL bDie;
};
void InitPlayerStat(Player*);
void PrintPlayerStat(const Player*);
void clrStat(enum ECoords);
int DungeonExploreExp(Player*);
//몬스터
typedef struct Mob {
	int index;
	char name[20];
	char say[64];
	Stat stat;
	char image[5][7][40] = {
		{
	   " -------    ",
	   " ||^ ^||  //",
	   " || ∼ || // ",
	   " -------    "
		},
		{
	   " ┌ㅡㅡㅡㅡㅡ┐ ",
	   " |ㅡㅡ ㅡㅡ | ",
	   " |    |    | ",
	   " └---------┘ ",
	   },
		{
	   "  *********** ",
	   " /  >   <  /",
	   "/     ∞   /   ",
	   "**********  ",
	   },
		{
	   "  ?????????  ",
	   "  ||ㅡ ㅡ||  ",
	   "  ||  ˚  ||  ",
	   "  ¿¿¿¿¿  ",
	   },
		{
	   "  ---------  ",
	   "  (° □ °） ",
	   "  (  ~~~  )  ",
	   "  (  ~~~  )  ",
	   "  (  ~~~  )  ",
	   "  (  ~~~  )  ",
	   "~~~~~~~~~~~~~~",
	   }
	};
};
void InitMob(Mob* mob);
Mob CreateMob(const Mob* mob);
//반복되는 특수문자
typedef struct SpecialChar {
	int x, y;
	int count;
	char ch;
	const char* str;
};
void SpecialCharRepet(SpecialChar sChr);
//Game Flow
void Title();
void ExpMinus(Player*);
void TownProcess(Player*);
void DungeonProcess(Player*);
void MonsterProcess(Player*);
void BattleProcess(Player*, Mob*);
void Ending();
//Turboc.h
void clrscr();
void gotoxy(int x, int y);
typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;
void setcursortype(CURSOR_TYPE c);
//전역변수
DungeonStage curDungeonStage;	//enum
Dungeon dungeon[2];	//구조체 배열
BOOL bClear = 0;
//-----------------------------------------------------------------
//------------------------------시작--------------------------------
//-----------------------------------------------------------------
int main()
{
	//몬스터 랜덤 스폰용
	srand((unsigned int)time(NULL));
	//월드 초기화
	InitDungeon();
	//플레이어
	Player player;
	InitPlayerStat(&player);
	Title();
	while (1) {
		if (bClear == 0) {
			TownProcess(&player);
			DungeonProcess(&player);
		}
		else if (bClear == 1) {
			break;
		}
	}
	Ending();
	return 0;
}
void Title() {
	SpecialChar sChar = { CoordList[TitleName].x , CoordList[TitleName].y, 59, '=',
		"===============--윾재준의 텍스트 RPG v.0.1--===============" };
	SpecialCharRepet(sChar);
	sChar = { CoordList[TitleEtc].x , CoordList[TitleEtc].y, 60, '=',
		"ver.0.1" };
	gotoxy(sChar.x, sChar.y + 1);      puts("제작자 : 유재준");
	gotoxy(sChar.x - 3, sChar.y + 5);   puts("아무 키를 입력해 시작");
	int ch;
	if (ch = _getch()) {
		clrscr();
	}
}
void TownProcess(Player* player)
{
	PrintPlayerStat(player);
	SpecialChar sChar;
	sChar = { CoordList[TownBtn1].x , CoordList[TownBtn1].y, 40, '-',
		"|   마구마구 때려본다. [공격력 증가]   |" };
	SpecialCharRepet(sChar);
	sChar = { CoordList[TownBtn2].x , CoordList[TownBtn2].y, 40, '-',
		"|    우걱우걱 맞아본다. [체력 증가]    |" };
	SpecialCharRepet(sChar);
	gotoxy(CoordList[MoveTownDungeon].x, CoordList[MoveTownDungeon].y);      printf("던전으로 ('f'키 입력)");
	gotoxy(CoordList[SysMsg].x, CoordList[SysMsg].y);   printf("(포커스 후 'Enter' 입력)       ");
	//포커스 표시
	setcursortype(NOCURSOR);
	int curX = CoordList[TownBtn1].x - 4;
	int curY = CoordList[TownBtn1].y;
	gotoxy(curX, curY);
	_putch('@');
	//포커스 이동
	int ch;
	while (1) {
		ch = _getch();
		//던전으로
		if (ch == 'F' || ch == 'f') {
			clrscr();
			break;
		}
		//포커스 이동
		if (ch == 0xE0 || ch == 0) {
			//방향키는 getch 시 수 2번 들어옴
			ch = _getch();
			switch (ch)
			{
			case Up:
				if (curY >= CoordList[TownBtn2].y) {
					gotoxy(curX, curY); _putch(' ');
					curY -= CoordList[TownBtn2].y - CoordList[TownBtn1].y;
				}
				break;
			case Down:
				if (curY <= CoordList[TownBtn1].y) {
					gotoxy(curX, curY); _putch(' ');
					curY += CoordList[TownBtn2].y - CoordList[TownBtn1].y;
				}
				break;
			}
		}
		//Enter
		if (ch == 13) {
			if (player->exp <= 0) {
				gotoxy(CoordList[SysMsg].x, CoordList[SysMsg].y);   printf("\a경험치가 부족합니다.    ");
			}
			else if (curY >= CoordList[TownBtn2].y) {
				ExpMinus(player);
				(player->stat.hp)++;
				gotoxy(CoordList[Hp].x, CoordList[Hp].y);         printf("체력 : %2d ", player->stat.hp);
			}
			else if (curY <= CoordList[TownBtn1].y) {
				ExpMinus(player);
				(player->stat.atk)++;
				gotoxy(CoordList[Atk].x, CoordList[Atk].y);      printf("공격력 : %2d ", player->stat.atk);
			}
			gotoxy(CoordList[Exp].x, CoordList[Exp].y);      printf("경험치 : %2d ", player->exp);
		}
		gotoxy(curX, curY);
		_putch('@');
	}
}
void DungeonProcess(Player* player)
{
	SpecialChar sChar;
	int ch;
	int randVal;
	while (1) {
		PrintPlayerStat(player);
		sChar = { CoordList[DungeonExploreBtn].x , CoordList[DungeonExploreBtn].y, 12, '-',
			"|   탐색   |" };
		SpecialCharRepet(sChar);
		gotoxy(CoordList[DungeonExploreBtn].x - 4, CoordList[DungeonExploreBtn].y);
		printf("@");
		gotoxy(CoordList[DungeonExploreBtn].x - 17, CoordList[DungeonExploreBtn].y + 5);
		printf("-------------------------------------------------");
		gotoxy(CoordList[MoveTownDungeon].x, CoordList[MoveTownDungeon].y);
		printf("마을로 ('f'키 입력)");
		gotoxy(CoordList[DungeonProgress].x, CoordList[DungeonProgress].y);
		printf("던전 Level : %2d", curDungeonStage + 1);
		gotoxy(CoordList[DungeonProgress].x, CoordList[DungeonProgress].y + 1);
		printf("진척도 : %2d %", dungeon[curDungeonStage].progress);
		ch = _getch();
		//마을로
		if (ch == 'F' || ch == 'f') {
			clrscr();
			break;
		}
		//Enter
		if (ch == 13) {
			Sleep(100);
			randVal = rand() % 10 + 1;
			gotoxy(CoordList[SysMsg].x, CoordList[SysMsg].y);
			int addExp = 0;
			if (randVal >= 1 && randVal <= 1) {
				addExp = DungeonExploreExp(player);
				gotoxy(CoordList[SysMsg].x, CoordList[SysMsg].y);
				printf("던전 지형에 대해 더 잘 알게 되었습니다. 경험치 + 1              ");
			}
			else if (randVal >= 2 && randVal <= 3) {
				addExp = DungeonExploreExp(player);
				gotoxy(CoordList[SysMsg].x, CoordList[SysMsg].y);
				printf("던전을 돌아다니며 당신의 마음은 기쁨으로 가득찹니다. 경험치 + 1  ");
			}
			else if (randVal >= 4 && randVal <= 5) {
				addExp = DungeonExploreExp(player);
				gotoxy(CoordList[SysMsg].x, CoordList[SysMsg].y);
				printf("던전의 스산한 분위기가 당신의 버그를 떠올리게 합니다. 경험치 + 1  ");
			}
			else if (randVal >= 6 && randVal <= 10) {
				clrscr();
				//몬스터씬으로
				MonsterProcess(player);
				if (player->bDie == 1) {
					player->bDie = 0;
					break;
				}
				//던전 끝
				if (curDungeonStage == 1 && dungeon[curDungeonStage].progress >= 100) {
					bClear = 1;
				}
			}
		}
	}
}
void MonsterProcess(Player* player)
{
	//몬스터 수
	Mob mob[5];
	gotoxy(CoordList[DungeonProgress].x, CoordList[DungeonProgress].y);
	printf("던전 Level : %2d", curDungeonStage + 1);
	gotoxy(CoordList[DungeonProgress].x, CoordList[DungeonProgress].y + 1);
	printf("진척도 : %2d ", dungeon[curDungeonStage].progress);
	gotoxy(CoordList[SysMsg].x, CoordList[SysMsg].y);
	printf("몬스터를 만났다! (공격 'Enter')          ");
	PrintPlayerStat(player);
	//초기화
	InitMob(mob);
	//몬스터 생성 및 그리기
	*mob = CreateMob(mob);
	//배틀로
	BattleProcess(player, mob);
}
void BattleProcess(Player* player, Mob* mob)
{
	//입력
	int ch;
	int addExp = 1;
	int addDungeonProgress = 15;
	while (1) {
		ch = _getch();
		//Enter
		if (ch == 13) {
			gotoxy(CoordList[SysMsg].x, CoordList[SysMsg].y);
			mob->stat.hp -= player->stat.atk;
			printf("적을 공격했다! %2d만큼의 피해를 입혔다!", player->stat.atk);
			if (mob->stat.hp > 0) {
				player->stat.hp -= mob->stat.atk;
				gotoxy(CoordList[MobStat].x, CoordList[MobStat].y);         printf("체력   : %2d ", mob->stat.hp);
				gotoxy(CoordList[SysMsg].x, CoordList[SysMsg].y + 1);
				printf("적이 공격했다! %2d만큼의 피해를 입었다..", mob->stat.atk);
				clrStat(Hp);
				gotoxy(CoordList[Hp].x, CoordList[Hp].y);					printf("체력 : %2d ", player->stat.hp);
			}
			else if (mob->stat.hp <= 0) {
				mob->stat.hp = 0;
				clrscr();
				clrStat(Exp);
				PrintPlayerStat(player);
				gotoxy(CoordList[SysMsg].x, CoordList[SysMsg].y);
				(player->exp) += addExp;
				printf("적을 물리쳤다!! 경험치를 %2d 획득했다! (계속 탐색 : 'Enter')", addExp);
				gotoxy(CoordList[Exp].x, CoordList[Exp].y);					printf("경험치 : %2d ", player->exp);
				(dungeon[curDungeonStage].progress) += addDungeonProgress;
				if (dungeon[curDungeonStage].progress >= 100) {
					dungeon[curDungeonStage].progress = 100;
					curDungeonStage = D2;
				}
				gotoxy(CoordList[DungeonProgress].x, CoordList[DungeonProgress].y);
				printf("던전 Level : %2d", curDungeonStage + 1);
				gotoxy(CoordList[DungeonProgress].x, CoordList[DungeonProgress].y + 1);
				printf("진척도 : %2d ", dungeon[curDungeonStage].progress);
				break;
			}
			if (player->stat.hp <= 0) {
				player->stat.hp = 0;
				gotoxy(CoordList[Hp].x, CoordList[Hp].y);					printf("체력 : %2d ", player->stat.hp);
				clrscr();
				clrStat(Hp);
				gotoxy(CoordList[SysMsg].x, CoordList[SysMsg].y);
				printf("사망했습니다. 마을로 돌아갑니다.");
				Sleep(1500);
				player->stat.hp = 1;	//보정
				player->bDie = 1;
				break;
			}
			Sleep(200);	//연속 입력 방지
		}
	}
}
//엔딩
void Ending()
{
	clrscr();
	gotoxy(CoordList[EndingMsg].x, CoordList[EndingMsg].y);
	printf("===============수고하셨습니다=================");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n");
}
//던전 세팅
void InitDungeon()
{
	dungeon[0] = { 0, 0 };
	dungeon[1] = { 1, 0 };
}
int DungeonExploreExp(Player* player)
{
	int addExp = 1;
	int addDungeonProgress = 10;
	(player->exp) += addExp;
	(dungeon[curDungeonStage].progress) += addDungeonProgress;
	if (dungeon[curDungeonStage].progress >= 100) {
		dungeon[curDungeonStage].progress = 100;
		curDungeonStage = D2;
	}
	gotoxy(CoordList[DungeonProgress].x, CoordList[DungeonProgress].y);
	printf("진척도 : %2d ", dungeon[curDungeonStage].progress);
	PrintPlayerStat(player);
	return player->exp;
}
//몹 세팅
void InitMob(Mob* mob)
{
	mob[0] = { 0, "친절한 오덕씨", "\"여ㅡ\"", 5, 1 };
	mob[1] = { 1, "싸움꾼", "\"덤벼 이 자식아\"", 7, 2 };
	mob[2] = { 2, "유쾌한 적", "\"zzzzzzzㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋ\"", 10, 3, };
	mob[3] = { 3, "짐", "\"내가 곧 짐이다\"", 12, 4, };
	mob[4] = { 4, "킹 버그", "\"날 잡을 수 있을 거라 생각했어?\"", 12, 4, };
}
//몹 그리기
Mob CreateMob(const Mob* mob)
{
	int randVal = 0;
	switch (curDungeonStage)
	{
	case D1:
		randVal = rand() % 2;
		break;
	case D2:
		randVal = rand() % 5;
		break;
	default:
		randVal = rand() % 5;
		break;
	}
	int addLine = 1;
	int row = sizeof(mob->image) / sizeof(mob->image[randVal]);
	gotoxy(CoordList[MobImage].x, CoordList[MobImage].y);
	for (int i = 0; i != row; i++) {
		printf("%s", mob->image[randVal][i]);
		gotoxy(CoordList[MobImage].x, CoordList[MobImage].y + addLine++);
	}
	gotoxy(CoordList[MobStat].x, CoordList[MobStat].y);         printf("체력   : %2d", mob[randVal].stat.hp);
	gotoxy(CoordList[MobStat].x, CoordList[MobStat].y + 1);     printf("공격력 : %2d", mob[randVal].stat.atk);
	gotoxy(CoordList[MobName].x, CoordList[MobName].y);     printf("%s", mob[randVal].name);
	gotoxy(CoordList[MobSay].x, CoordList[MobSay].y);     printf("%s", mob[randVal].say);
	gotoxy(CoordList[MobStat].x - 37, CoordList[MobStat].y + 3);
	printf("-------------------------------------------------");
	return mob[randVal];
}
//반복되는 문자열
void SpecialCharRepet(SpecialChar sChr)
{
	int tempX = sChr.x;
	int tempY = sChr.y;
	for (int i = 0; i < sChr.count; i++) {
		gotoxy(sChr.x++, sChr.y - 1);
		printf("%c", sChr.ch);
	}
	sChr.x = tempX;
	if (sChr.str != NULL) {
		gotoxy(sChr.x, sChr.y);
		printf("%s", sChr.str);
	}
	for (int i = 0; i < sChr.count; i++) {
		gotoxy(sChr.x++, sChr.y + 1);
		printf("%c", sChr.ch);
	}
}
void clrStat(enum ECoords xy) {
	gotoxy(CoordList[xy].x, CoordList[xy].y);
	printf("               ");
}
//플레이어 세팅
void InitPlayerStat(Player* player)
{
	player->stat.hp = 10;
	player->stat.atk = 2;
	player->exp = 5;
}
void PrintPlayerStat(const Player* player)
{
	gotoxy(CoordList[Exp].x, CoordList[Exp].y - 1);
	printf("-------------------------------------------------");
	gotoxy(CoordList[Exp].x, CoordList[Exp].y);
	printf("경험치 : %2d", player->exp);
	gotoxy(CoordList[Hp].x, CoordList[Hp].y);
	printf("체력 : %2d", player->stat.hp);
	gotoxy(CoordList[Atk].x, CoordList[Atk].y);
	printf("공격력 : %2d", player->stat.atk);
	gotoxy(CoordList[Exp].x, CoordList[Exp].y + 1);
	printf("-------------------------------------------------");
}
void ExpMinus(Player* player)
{
	if (player->exp <= 0) {
		player->exp = 0;
	}
	else {
		player->exp--;
	}
}
void GoToCoord(const Coord* coord) {
	gotoxy(coord->x, coord->y);
}
//이하 Turboc.h
void clrscr()
{
	system("cls");
}
// 커서를 x,y좌표로 이동시킨다.
void gotoxy(int x, int y)
{
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}
// 커서를 숨기거나 다시 표시한다.
void setcursortype(CURSOR_TYPE c)
{
	CONSOLE_CURSOR_INFO CurInfo;
	switch (c) {
	case NOCURSOR:
		CurInfo.dwSize = 1;
		CurInfo.bVisible = FALSE;
		break;
	case SOLIDCURSOR:
		CurInfo.dwSize = 100;
		CurInfo.bVisible = TRUE;
		break;
	case NORMALCURSOR:
		CurInfo.dwSize = 20;
		CurInfo.bVisible = TRUE;
		break;
	}
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}