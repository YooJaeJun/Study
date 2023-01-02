#include <stdio.h>
#include <Windows.h>
// ����� ������ �������ּ���.

// ���� : 3�� 2�������� �������ּ���.
//		�Լ��� �ϳ� �̻� ����Ͽ� ������ּ���.

void printInput(int computer, int player) 
{
	printf("���: %s \n", 
		computer == 1 ? "����" : 
		computer == 2 ? "����" : "��");

	printf("��: %s \n", 
		player == 1 ? "����" : 
		player == 2 ? "����" : 
		player == 3 ? "��" : "��ȿ���� ���� ��ȣ");
}

int randomDice()
{
	return rand() % 3 + 1;	// 1 ~ 3 ������ ������ ���� �̽��ϴ�.
}

int mukjipa(int atkRight)
{
	int computer = randomDice();
	int player;

	printf("��ȣ�� �Է��ϼ���([1. ��], [2. ��], [3. ��]): ");
	scanf_s("%i", &player);
	printf("\n");

	printf("��! \n");
	Sleep(500);
	printf("��! \n");
	Sleep(500);
	printf("��!\n\n");
	Sleep(500);

	printInput(computer, player);

	if (computer == player)
	{
		printf("�ɷȽ��ϴ�! \n");
		printf("���ݱ��� ���� %s�� �¸� ! \n\n\n", atkRight == 1 ? "player" : "computer");
		return atkRight;
	}
	else if ((computer == 1 && player == 2) ||
		(computer == 2 && player == 3) ||
		(computer == 3 && player == 1))
	{
		printf("���ݱ��� player ! \n");
		atkRight = 1;
		return mukjipa(atkRight);
	}
	else
	{
		printf("���ݱ��� computer ! \n");
		atkRight = 2;
		return mukjipa(atkRight);
	}
}

int rockScissorsPaper()
{
	int computer = randomDice();
	int player;

	printf("��ȣ�� �Է��ϼ���([1. ����], [2. ����], [3. ��]): ");
	scanf_s("%i", &player);
	printf("\n");

	printf("����! \n");
	Sleep(500);
	printf("����! \n");
	Sleep(500);
	printf("��! \n\n");
	Sleep(500);

	printInput(computer, player);

	printf("\n");

	if (computer == player)
	{
		printf("���º� ! �ٽ� �õ����ּ���. \n");
		return rockScissorsPaper();
	}
	else if ((computer == 1 && player == 2) ||
		(computer == 2 && player == 3) ||
		(computer == 3 && player == 1))
	{
		printf("���ݱ��� player ! \n");
		return 1;
	}
	else
	{
		printf("���ݱ��� computer ! \n");
		return 2;
	}

	printf("\n");
}

void printScoreBoard(int result, int computerWin, int playerWin)
{
	printf("------------------------------------\n");
	printf("�÷��̾� �¸� Ƚ��: %i \n", playerWin);
	printf("��ǻ�� �¸� Ƚ��: %i \n", computerWin);
	printf("-------------------------------------\n\n\n");

	if (playerWin == 2 || computerWin == 2)
	{
		printf("�ºΰ� ������ ���α׷��� �����մϴ�. \n");
		exit(0);
	}
}

int main()
{
	srand(GetTickCount64());

	printf("����� ������ �����մϴ�. (3�� 2������) \n");

	int computerWin = 0;
	int playerWin = 0;

	int t = 3;
	while (t--)
	{
		printf("���� ������������ ���ּ���. \n");
		int atkRight = rockScissorsPaper();

		Sleep(1500);
		system("cls");

		printf("\n");
		printf("������� �����մϴ�. \n");
		int result = mukjipa(atkRight);

		Sleep(1500);
		system("cls");

		if (result == 1) playerWin++;
		else computerWin++;

		printScoreBoard(result, computerWin, playerWin);
	}

	return 0;
}