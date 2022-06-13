/*
// ���þ˰���
�� ���� ���� ��
- ī���� ���ڴ� �Ʒ��� ���� �����մϴ�.
    A 2 3 4 5 6 7 8 9 10 J  Q  K
    1 2 3 4 5 6 7 8 9 10 10 10 10
 �� �� �� �� �� ��� ����ϱ� ������ �� 52������ �����Ǿ� �����մϴ�.
 ��
 1. ������ �÷��̾ �����մϴ�.
 2. ���� ���۽� �÷��̾ ī�� ������ �޽��ϴ�. ex ) 5 , J(10)
 3. ���� ī���� ������ ���� ����մϴ�.          ex ) 5 + J(10) = 15
 4. �÷��̾�� ����� ���� 21�� ���� �ʴ´ٸ� ī�带 ���� �� ���� �� �ֽ��ϴ�.
    - ī�带 �� ���� ���
       �÷��̾ ī�带 �� �޴´ٸ� ������ �ִ� ī���� ���� �ٽ� ����մϴ�.
       ex ) 5 + J(10) + 3 = 18
       ���� 21�� ���� �ʴ´ٸ� ����ؼ� ���� �� �ְ� ��ž���� �����մϴ�.
       ���� ī���� ������ ���� 21�� �Ѱ� �ȴٸ� �ٷ� �й��մϴ�.
       ex ) 5 + J(10) + 7 = 22 (�й�)
 5. ī�带 ���� �ʴ´ٸ� ��ž�� ������ ����� �����մϴ�.
 6. ����� �����Ѵٸ� �� ������ ������ ī�带 �̱� �����մϴ�.
 7. ������ ī���� ���� 17�� ���� �� ���� ī�带 �̽��ϴ�.
    ex ) Player�� �� (18) / Dealer : 10 + 6 = 16;
         1. Player�� �� (18) / Dealer : 10 + 6 + 3 = 19 (���� �¸�)
         2. Player�� �� (18) / Dealer : 10 + 7 + 5 = 22 (�÷��̾��� �¸�)
 8. ���� ���ÿ� ���� ������ ī�带 �̾� 21�� �ѱ����� �÷��̾��� ī���� �պ���
    Ŀ���� �ȴٸ� ������ �¸��̸� 21�� �ʰ��ϰ� �ȴٸ� �÷��̾ �¸��մϴ�.
 - �� ������ 21�� �ʰ����� �ʴ� ������ 21�� ���� ����� ���� ���� ����� �¸��ϴ� �����Դϴ�.
 Ư���� ��Ģ
 - 1. 21�� ������ �ȴٸ� �ش��� �����̸� �ٷ� �¸��ϰ� �˴ϴ�.
 - 2. 1 �� �̰Եȴٸ� 1�� 1 Ȥ�� 11�� ����Ͻ� �� �ֽ��ϴ�.
 ex ) 1 + 10 = 21 or 1 + 10 = 11
 - 3. J Q K �� ��� 10���� �����մϴ�.
 - 4. ���� ���ڴ� 4���� �ʰ��ؼ��� �ȵ˴ϴ�.
*/

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

void title(const int limit);
void shuffle(int card[], const int n);
void swap(int* const a, int* const b);
void printCard(const int card[], const int n);
int playerTurn(const int card[], int* player, int* idx, const int limit);
void playerDraw(const int card[], int* player, int* idx);
void playerSelectAceCard(const int card[], int* player);
void dealerTurn(const int card[], int* player, int* dealer, int* idx, const int limit);
void dealerSelectAceCard(const int card[], int* dealer, const int limit);
void checkWinner(int* player, int* dealer, const int limit);

int main()
{
    const int n = 52;
    const int limit = 21;
    srand(GetTickCount64());
    int card[52] =
    {
        1,2,3,4,5,6,7,8,9,10,10,10,10,
        1,2,3,4,5,6,7,8,9,10,10,10,10,
        1,2,3,4,5,6,7,8,9,10,10,10,10,
        1,2,3,4,5,6,7,8,9,10,10,10,10
    };

    title(limit);

    shuffle(card, n);
    // printCard(card, n);  // test

    int idx = 0;
    int player = 0;
    int dealer = 0;

    if (playerTurn(card, &player, &idx, limit))
    {
        dealerTurn(card, &player, &dealer, &idx, limit);
    }

    checkWinner(&player, &dealer, limit);

    return 0;
}

void title(const int limit)
{
    printf("----------------------------------------------------------------------------\n");
    printf("[���� ����] ���� \n");
    printf("%i�� �ʰ����� �ʴ� ������ [%i]�� ���� ����� ���� ���� ����� �¸��մϴ�. \n", limit, limit);
    printf("----------------------------------------------------------------------------\n");
}

void shuffle(int card[], const int n)
{
    for (int i = n - 1; i >= 0; --i)
    {
        int j = rand() % n;
        swap(&card[i], &card[j]);
    }
}

void swap(int* const a, int* const b)
{
    int tmp = *a;
    *a = *b;
    tmp = *a;
}

// test
void printCard(const int card[], const int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", card[i]);
        if (i != 0 && i % 13 == 0) printf("\n");
    }
    printf("\n");
}

// �÷��̾� ��. return 1: ���.. return 0: ���� ���� ����(���� �� ���� �����ϰ�)  
int playerTurn(const int card[], int* player, int* idx, const int limit)
{
    printf("�÷��̾ ���� ī�� 2���� �̽��ϴ�. \n");
    Sleep(500);
    for (int i = 0; i < 2; ++i)
    {
        playerDraw(card, player, idx);
    }
    printf("----------------------------------------------------------------------------\n");

    while (*player < limit)
    {
        printf("���� ī���� ���� [%i] �Դϴ�. \n", *player);
        printf("%i���� �۽��ϴ�. �� �� �� �����ðڽ��ϱ�? (y/n) \n", limit);
        char input;
        while (1)
        {
            scanf_s("%c", &input);
            while (getchar() != '\n');
            if (input == 'y' || input == 'n') break;
            else printf("�߸� �Է��߽��ϴ�. �ٽ� �Է����ּ���. �� �� �� �����ðڽ��ϱ�? (y/n) \n");
        }
        if (input == 'n') break;

        playerDraw(card, player, idx);
    }

    if (*player == limit) return 0;
    else if (*player > limit) return 0;

    return 1;
}

// �÷��̾� ��ο� (�ߺ� ������ ���� ��)
void playerDraw(const int card[], int* player, int* idx)
{
    printf("�÷��̾ ī�� [%i] (��/��) �̾ҽ��ϴ�. \n", card[*idx]);
    if (card[*idx] == 1)
        playerSelectAceCard(card, player);
    else *player += card[*idx];
    *idx += 1;
    Sleep(500);
}

// �÷��̾� ���̽� ī�� ����
void playerSelectAceCard(const int card[], int* player)
{
    int select;
    printf("�÷��̾ 1�� �̾ҽ��ϴ�. �꿡 ���� 1�̳� 11 �� �������ּ���. (1 or 11) \n");
    while (1)
    {
        scanf_s("%i", &select);
        while (getchar() != '\n');
        if (select == 1 || select == 11) break;
        printf("�߸��� ���ڸ� �Է��߽��ϴ�. �ٽ� �������ּ���. (1 or 11) \n");
    }
    printf("�÷��̾ %i �� �����߽��ϴ�. \n", select);
    if (select == 1) *player += 1;
    else *player += 11;
}


// ���� ��
void dealerTurn(const int card[], int* player, int* dealer, int* idx, const int limit)
{
    printf("������ �̱� �����մϴ�. \n");
    while (1)
    {
        printf("������ ī�� [%i] (��/��) �̾ҽ��ϴ�. \n", card[*idx]);
        if (card[*idx] == 1)
            dealerSelectAceCard(card, dealer, limit);
        else *dealer += card[*idx];
        *idx += 1;
        Sleep(500);
        printf("���� ī���� ���� [%i] �Դϴ�. \n", *dealer);
        if (*dealer > 17) break;
        Sleep(500);
    }
    printf("----------------------------------------------------------------------------\n");

    return;
}

// ���� ���̽� ī�� ���� ����
void dealerSelectAceCard(const int card[], int* dealer, const int limit)
{
    printf("������ 1�� �̾ҽ��ϴ�. �꿡 ���� 1�̳� 11 �� �����մϴ�. \n");
    int n1 = 1, n2 = 11;
    int select = n1;
    // 11 ������ �� 21 �ʰ��ϸ� 1 ������
    if (*dealer + n2 > limit) select = n1;
    // �ƴ� 11 ������
    else select = n2;
    printf("������ %i�� �����߽��ϴ� ! \n", select);
    *dealer += select;
}

// ���� �Ǵ�
void checkWinner(int* player, int* dealer, const int limit)
{
    printf("----------------------------------------------------------------------------\n");
    if (*player == limit)
    {
        printf("�÷��̾� ���� ī���� �� [%i] ! ���� ! \n", limit);
        printf("�÷��̾��� �¸� ! \n\n");
        return;
    }
    else if (*player > limit)
    {
        printf("�÷��̾� ���� ī���� �� [%i] ! \n", *player);
        printf("[%i]�� �Ѿ����Ƿ� �÷��̾��� �й� ! \n\n", limit);
        return;
    }
    else if (*dealer > 21)
    {
        printf("������ [%i]�� �Ѱ����Ƿ� ������ �й� ! \n", limit);
        printf("�÷��̾� �¸� ! \n");
        return;
    }

    printf("�÷��̾� : [%i] \n", *player);
    printf("���� : [%i] \n", *dealer);
    printf("----------------------------------------------------------------------------\n");
    if (*player > *dealer) printf("�÷��̾� �¸� ! \n");
    else if (*player < *dealer) printf("���� �¸� ! \n");
    else printf("���º� ! \n");
}