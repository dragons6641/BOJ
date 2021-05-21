/*
2523 별 찍기 - 13
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main(void)
{
	int N;

	scanf("%d", &N);

	for (register int i = 1; i < N; i++)
	{
		for (register int j = 1; j <= i; j++)
		{
			printf("*");
		}

		printf("\n");
	}

	for (register int j = 1; j <= N; j++)
	{
		printf("*");
	}

	printf("\n");

	for (register int i = 1; i < N; i++)
	{
		for (register int j = i; j < N; j++)
		{
			printf("*");
		}

		printf("\n");
	}

	return 0;
}
