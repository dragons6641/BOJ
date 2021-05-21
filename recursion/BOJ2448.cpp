/*
2448 별 찍기 - 11
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 3072
#define MAX_R MAX_N
#define MAX_C (MAX_N * 2) - 1
#define MIN_K 3

char map[MAX_R][MAX_C] = { 0, };

void init(void)
{
	for (register int r = 0; r < MAX_R; r++)
	{
		for (register int c = 0; c < MAX_C; c++)
		{
			map[r][c] = ' ';
		}
	}

	return;
}

void solve(int nowR, int nowC, int k)
{
	if (k == MIN_K)
	{
		map[nowR][nowC] = '*';
		map[nowR + 1][nowC - 1] = '*';
		map[nowR + 1][nowC + 1] = '*';

		for (register int c = nowC - (MIN_K - 1); c <= nowC + (MIN_K - 1); c++)
		{
			map[nowR + (MIN_K - 1)][c] = '*';
		}

		return;
	}

	solve(nowR, nowC, k / 2);
	solve(nowR + (k / 2), nowC - (k / 2), k / 2);
	solve(nowR + (k / 2), nowC + (k / 2), k / 2);

	return;
}

void print(int N)
{
	for (register int r = 0; r < N; r++)
	{
		for (register int c = 0; c < (N * 2) - 1; c++)
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

	solve(0, N - 1, N);

	print(N);

	return 0;
}
