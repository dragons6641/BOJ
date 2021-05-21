/*
2438 별 찍기 - 1
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main(void)
{
	int N;

	scanf("%d", &N);

	for (register int i = 0; i < N; i++)
	{
		for (register int j = 0; j <= i; j++)
		{
			printf("*");
		}

		printf("\n");
	}

	return 0;
}
