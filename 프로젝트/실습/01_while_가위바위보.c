#include <stdio.h>
#include <Windows.h>

// �ݺ��� (Loop)
// �ߺ��� �ڵ带 �����ϱ� ���Ͽ� �ݺ��� ����� �����ϱ� ���� �ۼ��ϴ� ����

int main()
{
	// ���������� ������ ���׷��̵� �غ��ô�.
	// �������� �������� ���� �ƴ� 3�� 2�������� �ٲ��ּ���.
	// �ݺ����� �����ų� �ºΰ� �����Ǿ��ٸ� �¸��� ����� ������ּ���.

	srand(GetTickCount64());

	int count = 0, total = 3, playerWin = 0, computerWin = 0;

	printf("���������� ������ �����մϴ�. \n");

	while (count++ < total)	// ++
	{
		int computer = rand() % 3 + 1;

		printf("��ȣ�� �Է��ϼ���([1. ����], [2. ����], [3. ��]): ");
		int player;
		scanf_s("%i", &player);

		system("cls");
		Sleep(400);
		printf("���� ");
		Sleep(400);
		printf("���� ");
		Sleep(400);
		printf("�� ! \n\n");
		Sleep(400);

		printf("���: %s \n", 
			computer == 1 ? "����" : 
			computer == 2 ? "����" : "��");

		printf("��: %s \n\n", 
			player == 1 ? "����" : 
			player == 2 ? "����" : 
			player == 3 ? "��" : "��ȿ���� ���� ��ȣ");


		if (computer == player)
		{
			printf("���º� ! \n\n");
		}
		else if ((computer == 1 && player == 2) ||
			(computer == 2 && player == 3) ||
			(computer == 3 && player == 1))
		{
			printf("���� ���ڴ� \"�÷��̾�\" ! \n\n");
			
			if (++playerWin == 2)
			{
				break;
			}
		}
		else
		{
			printf("���� ���ڴ� \"��ǻ��\" ! \n\n");
			
			if (++computerWin == 2)
			{
				break;
			}
		}

		printf("���� �÷��̾� �� : %i \n", playerWin);
		printf("���� ��ǻ�� �� : %i \n\n", computerWin);
	}

	printf("\n\n");
	printf("���� �÷��̾� �� : %i \n", playerWin);
	printf("���� ��ǻ�� �� : %i \n\n", computerWin);

	if (playerWin < 2 && computerWin < 2)
	{
		printf("2���� ���� �ºΰ� �������� �ʾҽ��ϴ� ! \n\n");
	}
	else 
	{
		printf("���� ���ڴ� %s !!! \n\n",
			playerWin > computerWin ? "�÷��̾� " : "��ǻ��");
	}

	printf("���α׷��� ����Ǿ����ϴ�. \n");
	return 0;
}