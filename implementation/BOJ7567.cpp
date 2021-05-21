/*
Pro입문 3일차 Problem J 그릇
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>

#define MIN_N 3
#define MAX_N 50
#define HEIGHT_1 5
#define HEIGHT_2 10

char str[MAX_N + 5];

int strlen(char* s)
{
	/*
	for (int i = 0; i < MAX_N + 5; i++)
	{
		if (s[i] == '\0')
		{
			return i;
		}
	}
	*/

	for (int i = 0; str[i] != '\0'; i++)
	{
		return i;
	}

	return -1;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);

	scanf("%s", str);

	int height = HEIGHT_2;

	// int n = strlen(str);

	for (int i = 1; str[i]; i++)
	{
		int old = str[i - 1];
		int now = str[i];

		if (old == now)
		{
			height += HEIGHT_1;
		}
		else
		{
			height += HEIGHT_2;
		}
	}

	printf("%d\n", height);

	return 0;
}
