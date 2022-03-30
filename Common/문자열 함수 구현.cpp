/*
//strlen
#include <stdio.h>

int Strlen(const char * str)
{
	int len = 0;
	for (int i = 0; str[i] != '\0'; i++)
	{
		len++;
	}
	return len;
}

int main()
{
	char str[4] = "abc";

	printf("���ڿ� ����: %d", Strlen(str));

	return 0;
}
*/

/*
//strcpy
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

void Strcpy(char * str2, const char * str1)
{
	for (int i = 0; str1[i] != '\0'; i++)
	{
		str2[i] = str1[i];
		printf("%c", str2[i]);	//��� �׽�Ʈ��
	}
}

int main()
{
	char str1[6] = "abcde";
	char str2[6];

	Strcpy(str2, str1);

	return 0;
}
*/

/*
//strcmp
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int Strcmp(const char * str1, const char * str2)
{
	//��ȯ
	for (int i = 0; str1[i] != '\0' || str2[i] != '\0'; i++)
	{
		if (str1[i] > str2[i])
			return 1;
		else if (str1[i] < str2[i])
			return -1;
	}

	return 0;
}

int main()
{
	char str1[2] = "a";
	char str2[3] = "ab";
	char str3[3] = "ba";
	char str4[2] = "b";

	printf("a�� ab: %d\n", Strcmp(str1, str2));
	printf("a�� ba: %d\n", Strcmp(str1, str3));
	printf("ab�� a: %d\n", Strcmp(str2, str1));
	printf("ba�� a: %d\n", Strcmp(str3, str1));
	printf("ba�� ab: %d\n", Strcmp(str3, str2));
	printf("b�� ab: %d\n", Strcmp(str4, str2));
	return 0;
}
*/


//strcat
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

void Strcat(char * str1, const char * str2)
{
	int strNull = 0;

	for (int i = 0; str1[i] != '\0'; i++)
	{
		strNull = i + 1;
	}
	for (int i = 0; str2[i] != '\0'; i++)
	{
		str1[strNull++] = str2[i];
	}
	str1[strNull] = '\0';
}

int main()
{
	char str1[10] = "Yoo";
	char str2[10] = "Jae";

	Strcat(str1, str2);
	printf("%s", str1);

	return 0;
}





//strcmp - Ǯ��2 - 
//strcat
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

void Strcat(char * str1, const char * str2)
{
	for (int i = 0; str1[i] != '\0'; i++)
	{
		if (str1[i + 1] == '\0')
		{
			for (int j = 0; str2[j] != '\0'; j++)
			{
				str1[i + j + 1] = str2[j];	//str1 ���������� ����. str2 ó�� �ͺ��� ä���
			}
			break;
		}
	}
}

int main()
{
	char str1[10] = "Yoo";
	char str2[10] = "Jae";

	Strcat(str1, str2);
	printf("%s", str1);

	return 0;
}





//strcmp - Ǯ��3 - ������ ���길 �̿�
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

void Strcat(char * str1, const char * str2)
{
	while (*str1)
		*str1++;

	while (*str2)
		*str1++ = *str2++;

	*str1 = 0;
}

int main()
{
	char str1[10] = "YooJae";
	char str2[10] = "Jun";

	Strcat(str1, str2);
	printf("%s", str1);

	return 0;
}
