// ��ī�� ����
// 1 ~ 13 ������ ���ڸ� �� ���� �̾�
// ������ ū��, �������� ū�� �ƴϸ� �������� ���ߴ� �����Դϴ�.

// 1. ��ǻ�ʹ� 1 ~ 13 �� �� ���� �������� �̽��ϴ�.
// 2. ���� Left : 1, Right : 3 �� �̾��� ��
// 3. Left, Middle, Right �� �����մϴ�.
//    ���� ���� ���ڰ� Left ũ�ų�, Right ũ�ٸ� 1���� ����ϴ�.
//    Middle(����) �̶�� 4���� ����ϴ�.
//    ���� Left, Right �� Ʋ�ȴٸ� 1���� �ҽ��ϴ�.
//    Middle(����) �̶�� 4���� �ҽ��ϴ�.

// �� 10�� �����ϸ� �������� ������ �� ���� ����� �̱�� �����Դϴ�.

#include <stdio.h>
#include <Windows.h>

void swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void shuffle(int card[], int n)
{
	for (int i = n - 1; i > 0; i--)
	{
		int j = rand() % i;
		swap(&card[i], &card[j]);
	}
}

// test
void printCard(int card[], int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%i ", card[i]);
	}
}

void title()
{
	printf("-----------------------------------------------------------\n");
	printf("[��ī�� ����] \n");
	printf("1 ~ 13 ������ ���ڸ� �� ���� �̾� \n");
	printf("������ ū��, �������� ū�� �ƴϸ� �������� ���ߴ� �����Դϴ�. \n");
}

void success(int* playerScore, int* dealerScore, int score)
{
	printf("���� ! %i���� ȹ���մϴ�. \n", score);
	if (score == 4) printf("Middle�� ���������Ƿ� ������ ũ�� �����ϴ�. \n");
	*playerScore += score;
	*dealerScore -= score;
}

void fail(const int left, const int right, int* playerScore, int* dealerScore, int score)
{
	printf("���� ! Left : %i, Right : %i �����ϴ�. \n", left, right);
	if (score == -4) printf("Middle�� ���������Ƿ� ������ ũ�� ���Դϴ�. \n");
	printf("���� %i�� ! \n", score);
	*playerScore += score;
	*dealerScore -= score;
}

int main()
{
	// ���� �ð��� ��ȯ
	// �и� ������
	srand(GetTickCount64());

	title();

	const int n = 13;
	int card[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
	Sleep(500);
	// printCard(card, n);

	int t = 0;
	int playerScore = 0;
	int dealerScore = 0;

	while (++t <= 10)
	{
		printf("-----------------------------------------------------------\n");
		printf("���� �÷��̾� ����: %i \n", playerScore);
		printf("���� ���� ����:     %i \n", dealerScore);
		printf("-----------------------------------------------------------\n");

		Sleep(500);

		printf("������ ī�带 �����մϴ�. \n");
		shuffle(card, n);
		printf("������ ī�� 1 ~ 13 ���� ī�带 �� �� �̽��ϴ�. \n");
		int idx = 0;
		int left = card[idx++];
		int right = card[idx++];
		printf("�� �� �� �� ���� �����մϴ�. \n");
		printf("[ Left: %i, Right: ?? ] \n", left);

		Sleep(1000);

		printf("-----------------------------------------------------------\n");
		printf("�� �� �� � ���� ū�� �����ּ���. \n(Left: 1 \nRight: 2 \nMiddle(���� ���� ��): 3) \n\n");
		int input;
		scanf_s("%d", &input);

		if (input == 1)
		{
			if (left > right)
			{
				success(&playerScore, &dealerScore, 1);
			}
			else if (left == right)
			{
				fail(left, right, &playerScore, &dealerScore, -4);
			}
			else
			{
				fail(left, right, &playerScore, &dealerScore, -1);
			}
		}
		else if (input == 2)
		{
			if (left < right)
			{
				success(&playerScore, &dealerScore, 1);
			}
			else if (left == right)
			{
				fail(left, right, &playerScore, &dealerScore, -4);
			}
			else
			{
				fail(left, right, &playerScore, &dealerScore, -1);
			}
		}
		else if (input == 3)
		{
			if (left == right)
			{
				success(&playerScore, &dealerScore, 4);
			}
			else
			{
				fail(left, right, &playerScore, &dealerScore, -4);
			}
		}
		else
		{
			printf("�߸� �Է��߽��ϴ�. \n");

			if (left == right)
			{
				fail(left, right, &playerScore, &dealerScore, -4);
			}
			else
			{
				fail(left, right, &playerScore, &dealerScore, -1);
			}
		}

		printf("��� �� �ٽ� ������ �����մϴ�. \n");
		Sleep(1500);
		system("cls");
	}

	printf("���� �÷��̾� ����: %i \n", playerScore);
	printf("���� ���� ����:     %i \n", dealerScore);
	printf("-----------------------------------------------------------\n");
	
	printf("���� �¸��ڴ� %s !!! \n", playerScore > dealerScore ? 
		"�÷��̾�" : 
		playerScore < dealerScore ? 
		"����" : "�����ϴ�! ���º�");

	printf("[��ī�� ����] �� �����մϴ�. \n");

	return 0;
}