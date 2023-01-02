#include <stdio.h>
#include <Windows.h>

// 반복문 (Loop)
// 중복된 코드를 방지하기 위하여 반복된 명령을 실행하기 위해 작성하는 문장

int main()
{
	// 가위바위보 게임을 업그레이드 해봅시다.
	// 단판으로 결정짓는 것이 아닌 3판 2선승으로 바꿔주세요.
	// 반복문이 끝나거나 승부가 결정되었다면 승리한 사람을 출력해주세요.

	srand(GetTickCount64());

	int count = 0, total = 3, playerWin = 0, computerWin = 0;

	printf("가위바위보 게임을 시작합니다. \n");

	while (count++ < total)	// ++
	{
		int computer = rand() % 3 + 1;

		printf("번호를 입력하세요([1. 가위], [2. 바위], [3. 보]): ");
		int player;
		scanf_s("%i", &player);

		system("cls");
		Sleep(400);
		printf("가위 ");
		Sleep(400);
		printf("바위 ");
		Sleep(400);
		printf("보 ! \n\n");
		Sleep(400);

		printf("상대: %s \n", 
			computer == 1 ? "가위" : 
			computer == 2 ? "바위" : "보");

		printf("나: %s \n\n", 
			player == 1 ? "가위" : 
			player == 2 ? "바위" : 
			player == 3 ? "보" : "유효하지 않은 번호");


		if (computer == player)
		{
			printf("무승부 ! \n\n");
		}
		else if ((computer == 1 && player == 2) ||
			(computer == 2 && player == 3) ||
			(computer == 3 && player == 1))
		{
			printf("현재 승자는 \"플레이어\" ! \n\n");
			
			if (++playerWin == 2)
			{
				break;
			}
		}
		else
		{
			printf("현재 승자는 \"컴퓨터\" ! \n\n");
			
			if (++computerWin == 2)
			{
				break;
			}
		}

		printf("현재 플레이어 승 : %i \n", playerWin);
		printf("현재 컴퓨터 승 : %i \n\n", computerWin);
	}

	printf("\n\n");
	printf("최종 플레이어 승 : %i \n", playerWin);
	printf("최종 컴퓨터 승 : %i \n\n", computerWin);

	if (playerWin < 2 && computerWin < 2)
	{
		printf("2승을 못해 승부가 가려지지 않았습니다 ! \n\n");
	}
	else 
	{
		printf("최종 승자는 %s !!! \n\n",
			playerWin > computerWin ? "플레이어 " : "컴퓨터");
	}

	printf("프로그램이 종료되었습니다. \n");
	return 0;
}