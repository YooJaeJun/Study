#include <stdio.h>

// ��ø while ���� ����Ͽ� �������� ������ּ���.
// [ 1�� ] [ 2�� ] [ 3�� ]
// [ 4�� ] [ 5�� ] [ 6�� ]
// [ 7�� ] [ 8�� ] [ 9�� ]

int main()
{
	printf("������ ���� \n\n");

	int i = 1, j = 1, k = 1;
	while (i <= 3)
	{
		j = i * 3 - 2;
		while (j <= i * 3)
		{
			printf("%i��\t\t", j);
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