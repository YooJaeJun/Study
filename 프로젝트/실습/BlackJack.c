/*
// 셔플알고리즘
☆ 블랙잭 게임 ☆
- 카드의 숫자는 아래와 같이 생각합니다.
    A 2 3 4 5 6 7 8 9 10 J  Q  K
    1 2 3 4 5 6 7 8 9 10 10 10 10
 ♤ ♡ ♧ ◇ 를 모두 사용하기 때문에 총 52장으로 구성되어 시작합니다.
 룰
 1. 딜러와 플레이어가 존재합니다.
 2. 게임 시작시 플레이어만 카드 두장을 받습니다. ex ) 5 , J(10)
 3. 받은 카드의 숫자의 합을 계산합니다.          ex ) 5 + J(10) = 15
 4. 플레이어는 계산한 합이 21을 넘지 않는다면 카드를 한장 더 받을 수 있습니다.
    - 카드를 더 받을 경우
       플레이어가 카드를 더 받는다면 가지고 있는 카드의 합을 다시 계산합니다.
       ex ) 5 + J(10) + 3 = 18
       역시 21을 넘지 않는다면 계속해서 받을 수 있고 스탑또한 가능합니다.
       받은 카드의 숫자의 합이 21을 넘게 된다면 바로 패배합니다.
       ex ) 5 + J(10) + 7 = 22 (패배)
 5. 카드를 받지 않는다면 스탑후 딜러와 대결을 시작합니다.
 6. 대결을 시작한다면 이 때부터 딜러가 카드를 뽑기 시작합니다.
 7. 딜러는 카드의 합이 17이 넘을 때 까지 카드를 뽑습니다.
    ex ) Player의 합 (18) / Dealer : 10 + 6 = 16;
         1. Player의 합 (18) / Dealer : 10 + 6 + 3 = 19 (딜러 승리)
         2. Player의 합 (18) / Dealer : 10 + 7 + 5 = 22 (플레이어의 승리)
 8. 위의 예시와 같이 딜러가 카드를 뽑아 21을 넘기전에 플레이어의 카드의 합보다
    커지게 된다면 딜러의 승리이며 21을 초과하게 된다면 플레이어가 승리합니다.
 - 즉 블랙잭은 21을 초과하지 않는 선에서 21과 가장 가까운 합이 나온 사람이 승리하는 게임입니다.
 특별한 규칙
 - 1. 21이 나오게 된다면 해당은 블랙잭이며 바로 승리하게 됩니다.
 - 2. 1 을 뽑게된다면 1은 1 혹은 11로 사용하실 수 있습니다.
 ex ) 1 + 10 = 21 or 1 + 10 = 11
 - 3. J Q K 는 모두 10으로 생각합니다.
 - 4. 같은 숫자는 4장을 초과해서는 안됩니다.
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
    printf("[블랙잭 게임] 시작 \n");
    printf("%i을 초과하지 않는 선에서 [%i]과 가장 가까운 합이 나온 사람이 승리합니다. \n", limit, limit);
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

// 플레이어 턴. return 1: 계속.. return 0: 게임 종료 판정(딜러 턴 생략 가능하게)  
int playerTurn(const int card[], int* player, int* idx, const int limit)
{
    printf("플레이어가 최초 카드 2장을 뽑습니다. \n");
    Sleep(500);
    for (int i = 0; i < 2; ++i)
    {
        playerDraw(card, player, idx);
    }
    printf("----------------------------------------------------------------------------\n");

    while (*player < limit)
    {
        printf("현재 카드의 합은 [%i] 입니다. \n", *player);
        printf("%i보다 작습니다. 한 장 더 받으시겠습니까? (y/n) \n", limit);
        char input;
        while (1)
        {
            scanf_s("%c", &input);
            while (getchar() != '\n');
            if (input == 'y' || input == 'n') break;
            else printf("잘못 입력했습니다. 다시 입력해주세요. 한 장 더 받으시겠습니까? (y/n) \n");
        }
        if (input == 'n') break;

        playerDraw(card, player, idx);
    }

    if (*player == limit) return 0;
    else if (*player > limit) return 0;

    return 1;
}

// 플레이어 드로우 (중복 때문에 따로 뺌)
void playerDraw(const int card[], int* player, int* idx)
{
    printf("플레이어가 카드 [%i] (을/를) 뽑았습니다. \n", card[*idx]);
    if (card[*idx] == 1)
        playerSelectAceCard(card, player);
    else *player += card[*idx];
    *idx += 1;
    Sleep(500);
}

// 플레이어 에이스 카드 선택
void playerSelectAceCard(const int card[], int* player)
{
    int select;
    printf("플레이어가 1을 뽑았습니다. 룰에 의해 1이나 11 중 선택해주세요. (1 or 11) \n");
    while (1)
    {
        scanf_s("%i", &select);
        while (getchar() != '\n');
        if (select == 1 || select == 11) break;
        printf("잘못된 숫자를 입력했습니다. 다시 선택해주세요. (1 or 11) \n");
    }
    printf("플레이어가 %i 을 선택했습니다. \n", select);
    if (select == 1) *player += 1;
    else *player += 11;
}


// 딜러 턴
void dealerTurn(const int card[], int* player, int* dealer, int* idx, const int limit)
{
    printf("딜러가 뽑기 시작합니다. \n");
    while (1)
    {
        printf("딜러가 카드 [%i] (을/를) 뽑았습니다. \n", card[*idx]);
        if (card[*idx] == 1)
            dealerSelectAceCard(card, dealer, limit);
        else *dealer += card[*idx];
        *idx += 1;
        Sleep(500);
        printf("현재 카드의 합은 [%i] 입니다. \n", *dealer);
        if (*dealer > 17) break;
        Sleep(500);
    }
    printf("----------------------------------------------------------------------------\n");

    return;
}

// 딜러 에이스 카드 선택 패턴
void dealerSelectAceCard(const int card[], int* dealer, const int limit)
{
    printf("딜러가 1을 뽑았습니다. 룰에 의해 1이나 11 중 선택합니다. \n");
    int n1 = 1, n2 = 11;
    int select = n1;
    // 11 더했을 때 21 초과하면 1 더해줌
    if (*dealer + n2 > limit) select = n1;
    // 아님 11 더해줌
    else select = n2;
    printf("딜러는 %i를 선택했습니다 ! \n", select);
    *dealer += select;
}

// 승패 판단
void checkWinner(int* player, int* dealer, const int limit)
{
    printf("----------------------------------------------------------------------------\n");
    if (*player == limit)
    {
        printf("플레이어 현재 카드의 합 [%i] ! 블랙잭 ! \n", limit);
        printf("플레이어의 승리 ! \n\n");
        return;
    }
    else if (*player > limit)
    {
        printf("플레이어 현재 카드의 합 [%i] ! \n", *player);
        printf("[%i]을 넘었으므로 플레이어의 패배 ! \n\n", limit);
        return;
    }
    else if (*dealer > 21)
    {
        printf("딜러가 [%i]를 넘겼으므로 딜러의 패배 ! \n", limit);
        printf("플레이어 승리 ! \n");
        return;
    }

    printf("플레이어 : [%i] \n", *player);
    printf("딜러 : [%i] \n", *dealer);
    printf("----------------------------------------------------------------------------\n");
    if (*player > *dealer) printf("플레이어 승리 ! \n");
    else if (*player < *dealer) printf("딜러 승리 ! \n");
    else printf("무승부 ! \n");
}