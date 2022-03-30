//�ؽ�Ʈ RPG ----------21.10.11 ����2 ��ô�� 100�� �� ó�� ����
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
//��
//����Ű
enum DirKey {
	Up = 72, Down = 80, Left = 75, Right = 77
};
//��ǥ
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
//����
enum DungeonStage {
	D1, D2
};
typedef struct Dungeon {
	int index;
	int progress;
};
void InitDungeon();
//������Ʈ ����
typedef struct Stat {
	int hp;
	int atk;
};
//�÷��̾�
typedef struct Player {
	Stat stat;
	int exp;
	BOOL bDie;
};
void InitPlayerStat(Player*);
void PrintPlayerStat(const Player*);
void clrStat(enum ECoords);
int DungeonExploreExp(Player*);
//����
typedef struct Mob {
	int index;
	char name[20];
	char say[64];
	Stat stat;
	char image[5][7][40] = {
		{
	   " -------    ",
	   " ||^ ^||  //",
	   " || �� || // ",
	   " -------    "
		},
		{
	   " ���ѤѤѤѤѦ� ",
	   " |�Ѥ� �Ѥ� | ",
	   " |    |    | ",
	   " ��---------�� ",
	   },
		{
	   "  *********** ",
	   " /  >   <  /",
	   "/     ��   /   ",
	   "**********  ",
	   },
		{
	   "  ?????????  ",
	   "  ||�� ��||  ",
	   "  ||  ��  ||  ",
	   "  ����������  ",
	   },
		{
	   "  ---------  ",
	   "  (�� �� �ƣ� ",
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
//�ݺ��Ǵ� Ư������
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
//��������
DungeonStage curDungeonStage;	//enum
Dungeon dungeon[2];	//����ü �迭
BOOL bClear = 0;
//-----------------------------------------------------------------
//------------------------------����--------------------------------
//-----------------------------------------------------------------
int main()
{
	//���� ���� ������
	srand((unsigned int)time(NULL));
	//���� �ʱ�ȭ
	InitDungeon();
	//�÷��̾�
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
		"===============--�������� �ؽ�Ʈ RPG v.0.1--===============" };
	SpecialCharRepet(sChar);
	sChar = { CoordList[TitleEtc].x , CoordList[TitleEtc].y, 60, '=',
		"ver.0.1" };
	gotoxy(sChar.x, sChar.y + 1);      puts("������ : ������");
	gotoxy(sChar.x - 3, sChar.y + 5);   puts("�ƹ� Ű�� �Է��� ����");
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
		"|   �������� ��������. [���ݷ� ����]   |" };
	SpecialCharRepet(sChar);
	sChar = { CoordList[TownBtn2].x , CoordList[TownBtn2].y, 40, '-',
		"|    ��ƿ�� �¾ƺ���. [ü�� ����]    |" };
	SpecialCharRepet(sChar);
	gotoxy(CoordList[MoveTownDungeon].x, CoordList[MoveTownDungeon].y);      printf("�������� ('f'Ű �Է�)");
	gotoxy(CoordList[SysMsg].x, CoordList[SysMsg].y);   printf("(��Ŀ�� �� 'Enter' �Է�)       ");
	//��Ŀ�� ǥ��
	setcursortype(NOCURSOR);
	int curX = CoordList[TownBtn1].x - 4;
	int curY = CoordList[TownBtn1].y;
	gotoxy(curX, curY);
	_putch('@');
	//��Ŀ�� �̵�
	int ch;
	while (1) {
		ch = _getch();
		//��������
		if (ch == 'F' || ch == 'f') {
			clrscr();
			break;
		}
		//��Ŀ�� �̵�
		if (ch == 0xE0 || ch == 0) {
			//����Ű�� getch �� �� 2�� ����
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
				gotoxy(CoordList[SysMsg].x, CoordList[SysMsg].y);   printf("\a����ġ�� �����մϴ�.    ");
			}
			else if (curY >= CoordList[TownBtn2].y) {
				ExpMinus(player);
				(player->stat.hp)++;
				gotoxy(CoordList[Hp].x, CoordList[Hp].y);         printf("ü�� : %2d ", player->stat.hp);
			}
			else if (curY <= CoordList[TownBtn1].y) {
				ExpMinus(player);
				(player->stat.atk)++;
				gotoxy(CoordList[Atk].x, CoordList[Atk].y);      printf("���ݷ� : %2d ", player->stat.atk);
			}
			gotoxy(CoordList[Exp].x, CoordList[Exp].y);      printf("����ġ : %2d ", player->exp);
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
			"|   Ž��   |" };
		SpecialCharRepet(sChar);
		gotoxy(CoordList[DungeonExploreBtn].x - 4, CoordList[DungeonExploreBtn].y);
		printf("@");
		gotoxy(CoordList[DungeonExploreBtn].x - 17, CoordList[DungeonExploreBtn].y + 5);
		printf("-------------------------------------------------");
		gotoxy(CoordList[MoveTownDungeon].x, CoordList[MoveTownDungeon].y);
		printf("������ ('f'Ű �Է�)");
		gotoxy(CoordList[DungeonProgress].x, CoordList[DungeonProgress].y);
		printf("���� Level : %2d", curDungeonStage + 1);
		gotoxy(CoordList[DungeonProgress].x, CoordList[DungeonProgress].y + 1);
		printf("��ô�� : %2d %", dungeon[curDungeonStage].progress);
		ch = _getch();
		//������
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
				printf("���� ������ ���� �� �� �˰� �Ǿ����ϴ�. ����ġ + 1              ");
			}
			else if (randVal >= 2 && randVal <= 3) {
				addExp = DungeonExploreExp(player);
				gotoxy(CoordList[SysMsg].x, CoordList[SysMsg].y);
				printf("������ ���ƴٴϸ� ����� ������ ������� �������ϴ�. ����ġ + 1  ");
			}
			else if (randVal >= 4 && randVal <= 5) {
				addExp = DungeonExploreExp(player);
				gotoxy(CoordList[SysMsg].x, CoordList[SysMsg].y);
				printf("������ ������ �����Ⱑ ����� ���׸� ���ø��� �մϴ�. ����ġ + 1  ");
			}
			else if (randVal >= 6 && randVal <= 10) {
				clrscr();
				//���;�����
				MonsterProcess(player);
				if (player->bDie == 1) {
					player->bDie = 0;
					break;
				}
				//���� ��
				if (curDungeonStage == 1 && dungeon[curDungeonStage].progress >= 100) {
					bClear = 1;
				}
			}
		}
	}
}
void MonsterProcess(Player* player)
{
	//���� ��
	Mob mob[5];
	gotoxy(CoordList[DungeonProgress].x, CoordList[DungeonProgress].y);
	printf("���� Level : %2d", curDungeonStage + 1);
	gotoxy(CoordList[DungeonProgress].x, CoordList[DungeonProgress].y + 1);
	printf("��ô�� : %2d ", dungeon[curDungeonStage].progress);
	gotoxy(CoordList[SysMsg].x, CoordList[SysMsg].y);
	printf("���͸� ������! (���� 'Enter')          ");
	PrintPlayerStat(player);
	//�ʱ�ȭ
	InitMob(mob);
	//���� ���� �� �׸���
	*mob = CreateMob(mob);
	//��Ʋ��
	BattleProcess(player, mob);
}
void BattleProcess(Player* player, Mob* mob)
{
	//�Է�
	int ch;
	int addExp = 1;
	int addDungeonProgress = 15;
	while (1) {
		ch = _getch();
		//Enter
		if (ch == 13) {
			gotoxy(CoordList[SysMsg].x, CoordList[SysMsg].y);
			mob->stat.hp -= player->stat.atk;
			printf("���� �����ߴ�! %2d��ŭ�� ���ظ� ������!", player->stat.atk);
			if (mob->stat.hp > 0) {
				player->stat.hp -= mob->stat.atk;
				gotoxy(CoordList[MobStat].x, CoordList[MobStat].y);         printf("ü��   : %2d ", mob->stat.hp);
				gotoxy(CoordList[SysMsg].x, CoordList[SysMsg].y + 1);
				printf("���� �����ߴ�! %2d��ŭ�� ���ظ� �Ծ���..", mob->stat.atk);
				clrStat(Hp);
				gotoxy(CoordList[Hp].x, CoordList[Hp].y);					printf("ü�� : %2d ", player->stat.hp);
			}
			else if (mob->stat.hp <= 0) {
				mob->stat.hp = 0;
				clrscr();
				clrStat(Exp);
				PrintPlayerStat(player);
				gotoxy(CoordList[SysMsg].x, CoordList[SysMsg].y);
				(player->exp) += addExp;
				printf("���� �����ƴ�!! ����ġ�� %2d ȹ���ߴ�! (��� Ž�� : 'Enter')", addExp);
				gotoxy(CoordList[Exp].x, CoordList[Exp].y);					printf("����ġ : %2d ", player->exp);
				(dungeon[curDungeonStage].progress) += addDungeonProgress;
				if (dungeon[curDungeonStage].progress >= 100) {
					dungeon[curDungeonStage].progress = 100;
					curDungeonStage = D2;
				}
				gotoxy(CoordList[DungeonProgress].x, CoordList[DungeonProgress].y);
				printf("���� Level : %2d", curDungeonStage + 1);
				gotoxy(CoordList[DungeonProgress].x, CoordList[DungeonProgress].y + 1);
				printf("��ô�� : %2d ", dungeon[curDungeonStage].progress);
				break;
			}
			if (player->stat.hp <= 0) {
				player->stat.hp = 0;
				gotoxy(CoordList[Hp].x, CoordList[Hp].y);					printf("ü�� : %2d ", player->stat.hp);
				clrscr();
				clrStat(Hp);
				gotoxy(CoordList[SysMsg].x, CoordList[SysMsg].y);
				printf("����߽��ϴ�. ������ ���ư��ϴ�.");
				Sleep(1500);
				player->stat.hp = 1;	//����
				player->bDie = 1;
				break;
			}
			Sleep(200);	//���� �Է� ����
		}
	}
}
//����
void Ending()
{
	clrscr();
	gotoxy(CoordList[EndingMsg].x, CoordList[EndingMsg].y);
	printf("===============�����ϼ̽��ϴ�=================");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n");
}
//���� ����
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
	printf("��ô�� : %2d ", dungeon[curDungeonStage].progress);
	PrintPlayerStat(player);
	return player->exp;
}
//�� ����
void InitMob(Mob* mob)
{
	mob[0] = { 0, "ģ���� ������", "\"����\"", 5, 1 };
	mob[1] = { 1, "�ο��", "\"���� �� �ڽľ�\"", 7, 2 };
	mob[2] = { 2, "������ ��", "\"zzzzzzz��������������������\"", 10, 3, };
	mob[3] = { 3, "��", "\"���� �� ���̴�\"", 12, 4, };
	mob[4] = { 4, "ŷ ����", "\"�� ���� �� ���� �Ŷ� �����߾�?\"", 12, 4, };
}
//�� �׸���
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
	gotoxy(CoordList[MobStat].x, CoordList[MobStat].y);         printf("ü��   : %2d", mob[randVal].stat.hp);
	gotoxy(CoordList[MobStat].x, CoordList[MobStat].y + 1);     printf("���ݷ� : %2d", mob[randVal].stat.atk);
	gotoxy(CoordList[MobName].x, CoordList[MobName].y);     printf("%s", mob[randVal].name);
	gotoxy(CoordList[MobSay].x, CoordList[MobSay].y);     printf("%s", mob[randVal].say);
	gotoxy(CoordList[MobStat].x - 37, CoordList[MobStat].y + 3);
	printf("-------------------------------------------------");
	return mob[randVal];
}
//�ݺ��Ǵ� ���ڿ�
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
//�÷��̾� ����
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
	printf("����ġ : %2d", player->exp);
	gotoxy(CoordList[Hp].x, CoordList[Hp].y);
	printf("ü�� : %2d", player->stat.hp);
	gotoxy(CoordList[Atk].x, CoordList[Atk].y);
	printf("���ݷ� : %2d", player->stat.atk);
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
//���� Turboc.h
void clrscr()
{
	system("cls");
}
// Ŀ���� x,y��ǥ�� �̵���Ų��.
void gotoxy(int x, int y)
{
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}
// Ŀ���� ����ų� �ٽ� ǥ���Ѵ�.
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