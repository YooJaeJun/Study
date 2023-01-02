#include <stdio.h>
#include <Windows.h>

int main()
{
	// 컴퓨터가 뽑은 랜덤한 숫자를 기회 안에 맞추는 게임입니다.
	// 예시 : 컴퓨터는 1 ~ 20까지의 숫자를 뽑습니다.
	//			컴퓨터가 17이라는 숫자를 뽑았다면
	//			입력 : 10 (컴퓨터가 뽑은 숫자보다 낮게 입력했다면)
	//			UP !
	//			입력 : 18 (컴퓨터가 뽑은 숫자보다 높게 입력했다면)
	//			DOWN !
	//			입력: 25 (범위를 벗어나 입력했다면)
	//			1 ~ 20 사이의 수만 입력하셔야 합니다.

	// _3 경우에는 라이프가 차감되지 않습니다. (입력 범위 벗어나 입력)
	// 기회 안에 맞췄다면 정답입니다를 출력하시고
	// 기회 안에 맞추지 못했다면 정답은 무엇입니다를 출력해주세요.
	// 기회를 모두 소진하면 종료.

	srand(GetTickCount64());
	int computer = rand() % 20 + 1;
	int life = 5;

	printf("------------------------------------------------------------ \n");
	printf("[Up Down] 게임 \n");
	printf("컴퓨터가 뽑은 랜덤한 숫자를 기회 안에 맞추는 게임입니다. \n");
	printf("------------------------------------------------------------ \n");

	printf("컴퓨터가 1 ~ 20까지의 숫자 중 하나를 뽑았습니다. \n");

	while (life > 0)
	{
		printf("숫자 입력(라이프 %i): \n", life);
		int player;
		scanf_s("%i", &player);

		if (player < 1 || player > 20)
		{
			printf("입력한 범위를 벗어났습니다. 다시 시도해주세요. \n");
		}
		else
		{
			if (player > computer)
			{
				printf("DOWN ! \n");
				--life;
			}
			else if (player < computer)
			{
				printf("UP ! \n");
				--life;
			}
			else
			{
				printf("정답입니다 ! \n");
				break;
			}
		}
	}
	
	if (life == 0)
	{
		printf("\n실패! 정답은 %i 입니다. \n", computer);
	}
	printf("\n프로그램을 종료합니다. \n");

	return 0;
}