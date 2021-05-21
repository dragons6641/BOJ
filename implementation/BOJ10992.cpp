/*
10992 별 찍기 - 17
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main(void)
{
	int N;

	scanf("%d", &N);

	if (N == 1)
	{
		printf("*\n");

		return 0;
	}

	for (register int j = 1; j < N; j++)
	{
		printf(" ");
	}

	printf("*\n");

	for (register int i = 2; i < N; i++)
	{
		for (register int j = i; j < N; j++)
		{
			printf(" ");
		}

		printf("*");

		for (register int j = 3; j < i * 2; j++)
		{
			printf(" ");
		}

		printf("*\n");
	}

	for (register int j = 1; j < N * 2; j++)
	{
		printf("*");
	}

	return 0;
}
