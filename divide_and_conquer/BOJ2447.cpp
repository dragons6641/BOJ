/*
2447 별 찍기 - 10
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 7
#define MAX_R 2187
#define MAX_C 2187
#define START_R 0
#define START_C 0
#define MIN_K 3

char map[MAX_R][MAX_C] = { 0, };

void init(void)
{
	for (register int r = 0; r < MAX_R; r++)
	{
		for (register int c = 0; c < MAX_C; c++)
		{
			map[r][c] = '*';
		}
	}

	return;
}

void solve(int nowR, int nowC, int k)
{
	if (k == MIN_K)
	{
		map[nowR + 1][nowC + 1] = ' ';

		return;
	}

	for (register int r = 0; r < MIN_K; r++)
	{
		for (register int c = 0; c < MIN_K; c++)
		{
			if ((r == 1) && (c == 1))
			{
				for (register int a = (k / 3 + nowR); a < (2 * k / 3) + nowR; a++)
				{
					for (register int b = (k / 3 + nowC); b < (2 * k / 3) + nowC; b++)
					{
						map[a][b] = ' ';
					}
				}
			}
			else
			{
				solve((r * k / 3) + nowR, (c * k / 3) + nowC, k / 3);
			}
		}
	}

	return;
}

void print(int N)
{
	for (register int r = 0; r < N; r++)
	{
		for (register int c = 0; c < N; c++)
		{
			printf("%c", map[r][c]);
		}

		printf("\n");
	}

	return;
}

int main(void)
{
	int N;

	scanf("%d", &N);

	init();

	solve(START_R, START_C, N);

	print(N);

	return 0;
}
