/*
10995 별 찍기 - 20
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main(void)
{
	int N;

	scanf("%d", &N);

	for (register int i = 1; i <= N; i++)
	{
		if (i % 2 == 0)
		{
			printf(" ");
		}

		for (register int j = 1; j <= N; j++)
		{
			printf("* ");
		}

		printf("\n");
	}

	return 0;
}
