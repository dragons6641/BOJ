/*
2556 별 찍기 - 14
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 100

int main(void)
{
	int N;

	scanf("%d", &N);

	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			printf("*");
		}

		printf("\n");
	}

	return 0;
}
