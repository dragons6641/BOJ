/*
10996 별 찍기 - 21
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main(void)
{
	int N;

	scanf("%d", &N);

	for (register int i = 1; i <= N * 2; i++)
	{
		for (register int j = 1; j <= N; j++)
		{
			if ((i + j) % 2 == 0)
			{
				printf("*");
			}
			else
			{
				printf(" ");
			}
		}

		printf("\n");
	}

	return 0;
}
