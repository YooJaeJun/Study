#include <stdio.h>

// 중첩 while 문을 사용하여 구구단을 출력해주세요.
// [ 1단 ] [ 2단 ] [ 3단 ]
// [ 4단 ] [ 5단 ] [ 6단 ]
// [ 7단 ] [ 8단 ] [ 9단 ]

int main()
{
	printf("구구단 시작 \n\n");

	int i = 1, j = 1, k = 1;
	while (i <= 3)
	{
		j = i * 3 - 2;
		while (j <= i * 3)
		{
			printf("%i단\t\t", j);
			j++;
		}

		printf("\n");

		j = 1;
		while (j <= 9)
		{
			k = i * 3 - 2;
			while (k <= i * 3)
			{
				printf("%i x %i = %i \t", k, j, k * j);
				k++;
			}
			printf("\n");
			j++;
		}

		printf("\n\n");
		i++;
	}

	return 0;
}