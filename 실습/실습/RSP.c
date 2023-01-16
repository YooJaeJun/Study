#include <stdio.h>
#include <Windows.h>
// 묵찌빠 게임을 구현해주세요.

// 조건 : 3판 2선승제로 구현해주세요.
//		함수를 하나 이상 사용하여 만들어주세요.

void printInput(int computer, int player) 
{
	printf("상대: %s \n", 
		computer == 1 ? "가위" : 
		computer == 2 ? "바위" : "보");

	printf("나: %s \n", 
		player == 1 ? "가위" : 
		player == 2 ? "바위" : 
		player == 3 ? "보" : "유효하지 않은 번호");
}

int randomDice()
{
	return rand() % 3 + 1;	// 1 ~ 3 사이의 랜덤한 값을 뽑습니다.
}

int mukjipa(int atkRight)
{
	int computer = randomDice();
	int player;

	printf("번호를 입력하세요([1. 찌], [2. 묵], [3. 빠]): ");
	scanf_s("%i", &player);
	printf("\n");

	printf("묵! \n");
	Sleep(500);
	printf("찌! \n");
	Sleep(500);
	printf("빠!\n\n");
	Sleep(500);

	printInput(computer, player);

	if (computer == player)
	{
		printf("걸렸습니다! \n");
		printf("공격권을 가진 %s의 승리 ! \n\n\n", atkRight == 1 ? "player" : "computer");
		return atkRight;
	}
	else if ((computer == 1 && player == 2) ||
		(computer == 2 && player == 3) ||
		(computer == 3 && player == 1))
	{
		printf("공격권은 player ! \n");
		atkRight = 1;
		return mukjipa(atkRight);
	}
	else
	{
		printf("공격권은 computer ! \n");
		atkRight = 2;
		return mukjipa(atkRight);
	}
}

int rockScissorsPaper()
{
	int computer = randomDice();
	int player;

	printf("번호를 입력하세요([1. 가위], [2. 바위], [3. 보]): ");
	scanf_s("%i", &player);
	printf("\n");

	printf("가위! \n");
	Sleep(500);
	printf("바위! \n");
	Sleep(500);
	printf("보! \n\n");
	Sleep(500);

	printInput(computer, player);

	printf("\n");

	if (computer == player)
	{
		printf("무승부 ! 다시 시도해주세요. \n");
		return rockScissorsPaper();
	}
	else if ((computer == 1 && player == 2) ||
		(computer == 2 && player == 3) ||
		(computer == 3 && player == 1))
	{
		printf("공격권은 player ! \n");
		return 1;
	}
	else
	{
		printf("공격권은 computer ! \n");
		return 2;
	}

	printf("\n");
}

void printScoreBoard(int result, int computerWin, int playerWin)
{
	printf("------------------------------------\n");
	printf("플레이어 승리 횟수: %i \n", playerWin);
	printf("컴퓨터 승리 횟수: %i \n", computerWin);
	printf("-------------------------------------\n\n\n");

	if (playerWin == 2 || computerWin == 2)
	{
		printf("승부가 가려져 프로그램을 종료합니다. \n");
		exit(0);
	}
}

int main()
{
	srand(GetTickCount64());

	printf("묵찌빠 게임을 시작합니다. (3판 2선승제) \n");

	int computerWin = 0;
	int playerWin = 0;

	int t = 3;
	while (t--)
	{
		printf("먼저 가위바위보를 해주세요. \n");
		int atkRight = rockScissorsPaper();

		Sleep(1500);
		system("cls");

		printf("\n");
		printf("묵찌빠를 시작합니다. \n");
		int result = mukjipa(atkRight);

		Sleep(1500);
		system("cls");

		if (result == 1) playerWin++;
		else computerWin++;

		printScoreBoard(result, computerWin, playerWin);
	}

	return 0;
}