/*
============ = ����1============ =
1~10�� ����ī�尡 3�徿 ����ִ� ī��30���� ī�并ġ�� ����� �����.

<��¿���>--------------------
4, 3, 5, 6, 7, 8, 1, 10, 1, 4,
10, 9, 6, 4, 2, 3, 2, 10, 1, 8,
9, 7, 3, 2, 5, 6, 7, 9, 5, 8
------------------------------
*/

/*
=============����2=============
A, B �θ��� �÷��̾�� 5�徿 �й��Ͽ� ���� �꿡 ���� ������ �ޱ�� ���ڸ� ǥ���϶�.
�������:
 >> �⺻���� = 5���� ��������� + 5���� ���峷����
 >> ���� ���ڰ� 2���϶� + 10��(�ߺ�����)
 >> ���� ���ڰ� 3���϶� + 20��
 >> 3�� �̻��� ��Ʈ����Ʈ�� ������ + 15��(10, 1, 2 �� �������� ���)
 >> �����ϰ�� ���º�

<��¿���>--------------------
A : 1, 5, 5, 7, 7 = 28 Point
B : 1, 2, 3, 4, 4 = 30 Point
B �¸�
------------------------------
*/



//�� Ǯ��
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Shuffle(int * arr);
void Distribute(int * arr, int * p);
int GetScore(int * arr);

int main()
{
	srand((unsigned)time(NULL));

	int arr[30] = { 1,2,3,4,5,6,7,8,9,10,
				1,2,3,4,5,6,7,8,9,10,
				1,2,3,4,5,6,7,8,9,10 };

	Shuffle(arr);

	int p1[5];
	Distribute(arr, p1);
	printf("A : ");
	int scoreA = GetScore(p1);

	int p2[5];
	Distribute(arr, p2);
	printf("B : ");
	int scoreB = GetScore(p2);

	if (scoreA < scoreB) {
		printf("B �¸�");
	}
	else if (scoreA > scoreB) {
		printf("A �¸�");
	}
	else {
		printf("���º�");
	}
}

void Shuffle(int * arr)
{
	//����
	int n = 30;
	int r;
	int temp;
	while (--n)
	{
		int r = rand() % (n + 1);
		temp = arr[n];
		arr[n] = arr[r];
		arr[r] = temp;
	}
	//���
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 10; j++) {
			printf("%d", arr[j + (10 * i)]);
			if (i == 2 && j == 9) {}
			else {
				printf(", ");
			}
		}
		printf("\n");
	}
	printf("\n");
}

void Distribute(int * arr, int * p)
{
	//�й�
	int r = 0;
	for (int i = 0; i < 5; i++) {
		do {
			r = rand() % 30;
		} while (arr[r] == -1);

		p[i] = arr[r];
		arr[r] = -1;
		//printf("%d ", p[i]);
	}
}

int GetScore(int * p)
{
	int size = 5;	//�й�� ī�� ����

	//����
	int temp;
	for (int i = 0; i < 4; i++)
		for (int j = i + 1; j < 5; j++)
			if (p[i] > p[j]) {
				temp = p[i];
				p[i] = p[j];
				p[j] = temp;
			}

	//�⺻����
	int max = p[size - 1], min = p[0];
	int score = max + min;
	//printf("max: %d / min: %d / score: %d\n", max, min, score);

	//��������
	int equal = 0;
	for (int i = 0; i < 4; i++)
		if (p[i] == p[i + 1])
			equal++;
	//printf("equal: %d\n", equal);
	switch (equal)
	{
	case 1:
		score += 10;
		break;
	case 2:
		score += 20;
		break;
	case 3:
		score += 30;
		break;
	}

	//��Ʈ����Ʈ
	int continuous = 1;
	for (int i = 0; i < size + 2; i++) {

		//10 1 2
		if (i == size - 1) {
			//���� ù ��
			if (p[i] == p[size - i - 1] + 9) {
				//ù�� �� ��
				if (p[size - i - 1] == p[size - i] - 1) {
					score += 15;
					break;
				}
				//�� ���� �� ��
				if (p[i - 1] == p[i] - 1) {
					score += 15;
					break;
				}
			}
		}

		//�Ϲݿ���
		if (p[i] == p[i + 1] - 1) {
			if (p[i + 1] == p[i + 2] - 1) {
				score += 15;
				break;
			}
			else if (p[i + 1] == p[i + 2]) {
				if (p[i + 1] == p[i + 3] - 1) {
					score += 15;
					break;
				}
			}
		}
	}

	//���
	for (int i = 0; i < 4; i++) {
		printf("%d, ", p[i]);
	}
	printf("%d = %d Point\n", p[4], score);

	return score;
}









//������ Ǯ��
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Shuffle(int* deck_arr);
void DrawCards(int* deck_arr, int* hand_arr);
void SortHandCards(int* hand_arr);
int GetScore(int* hand_arr);

const int HAND_COUNT = 5;
const int DECK_COUNT = 30;
int DeckIndex = 0;

int main()
{
	srand((unsigned)time(NULL));

	int Deck[DECK_COUNT] = { 1,2,3,4,5,6,7,8,9,10,
			 1,2,3,4,5,6,7,8,9,10,
			 1,2,3,4,5,6,7,8,9,10 };

	Shuffle(Deck);
	//Print Deck
	for (int i = 0; i < DECK_COUNT; i++) {

		const char* PrintFormat = (i == DECK_COUNT - 1) ? "%2d" : "%2d,";
		printf(PrintFormat, Deck[i]);
		if (i % 10 == 9)
		{
			printf("\n");
		}
	}
	//~Print Deck 

	int PlayerHand_A[HAND_COUNT];
	int PlayerHand_B[HAND_COUNT];

	DrawCards(Deck, PlayerHand_A);
	DrawCards(Deck, PlayerHand_B);
	int scoreA = GetScore(PlayerHand_A);
	int scoreB = GetScore(PlayerHand_B);

	printf("A : ");
	for (int i = 0; i < HAND_COUNT; i++) {
		printf("%d, ", PlayerHand_A[i]);
	}
	printf("%d = %d Point\n", PlayerHand_A[HAND_COUNT - 1], scoreA);

	printf("B : ");
	for (int i = 0; i < HAND_COUNT; i++) {
		printf("%d, ", PlayerHand_B[i]);
	}
	printf("%d = %d Point\n", PlayerHand_B[HAND_COUNT - 1], scoreB);


	if (scoreA < scoreB) {
		printf("B �¸�");
	}
	else if (scoreA > scoreB) {
		printf("A �¸�");
	}
	else {
		printf("���º�");
	}
}


void Shuffle(int* deck_arr)
{
	//shuffle
	int n = DECK_COUNT;
	while (--n)
	{
		int r = rand() % (n + 1);
		int temp = deck_arr[n];
		deck_arr[n] = deck_arr[r];
		deck_arr[r] = temp;
	}
}

void DrawCards(int* deck_arr, int* hand_arr)
{
	for (int i = 0; i < HAND_COUNT; i++) {
		if (DeckIndex == DECK_COUNT)
		{
			//[error] Deck is Empty
			return;
		}
		hand_arr[i] = deck_arr[DeckIndex++];
	}

	SortHandCards(hand_arr);
}

void SortHandCards(int* hand_arr)
{
	//bubble sort
	for (int i = 0; i < HAND_COUNT - 1; i++) {
		for (int j = i + 1; j < HAND_COUNT; j++) {
			if (hand_arr[i] > hand_arr[j]) {
				int temp = hand_arr[i];
				hand_arr[i] = hand_arr[j];
				hand_arr[j] = temp;
			}
		}
	}
}

int GetScore(int* hand_arr)
{
	//default score
	int score = hand_arr[0] + hand_arr[HAND_COUNT - 1]; //���ĵ��ִٴ� �����Ͽ�

	//create CardCountingArray for calculate
	int CArr[10] = { 0, };
	for (int i = 0; i < HAND_COUNT; ++i)
	{
		++CArr[hand_arr[i] - 1];
	}

	//calculate additional score
	bool HasStraight = false;
	for (int i = 0; i < 10; ++i)
	{
		//pair
		if (CArr[i] == 2)
			score += 10;

		//triple
		if (CArr[i] == 3)
			score += 20;

		//check has straight
		if (HasStraight == false && CArr[i] > 0 && CArr[(i + 1) % 10] > 0 && CArr[(i + 2) % 10] > 0)
			HasStraight = true;
	}
	//add straight score
	if (HasStraight)
		score += 15;

	return score;
}