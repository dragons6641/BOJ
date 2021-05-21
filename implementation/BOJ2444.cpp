/*
2444 별 찍기 - 7
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main(void)
{
	int N;

	scanf("%d", &N);

	for (register int i = 1; i < N; i++)
	{
		for (register int j = i + 1; j <= N; j++)
		{
			printf(" ");
		}

		for (register int j = 1; j < i * 2; j++)
		{
			printf("*");
		}

		printf("\n");
	}

	for (register int j = 1; j < N * 2; j++)
	{
		printf("*");
	}

	printf("\n");

	for (register int i = 2; i <= N; i++)
	{
		for (register int j = 1; j < i; j++)
		{
			printf(" ");
		}

		for (register int j = N * 2; j >= i * 2; j--)
		{
			printf("*");
		}

		printf("\n");
	}

	return 0;
}
