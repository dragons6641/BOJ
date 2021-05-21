/*
10994 별 찍기 19
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 100
#define MAX_R (MAX_N * 4) - 3
#define MAX_C (MAX_N * 4) - 3
#define START_R 0
#define START_C 0
#define MIN_K 1

int N;
int height;
int width;
char map[MAX_R + 1][MAX_C + 1] = { 0, };

void init(void)
{
	for (register int r = 0; r < height; r++)
	{
		for (register int c = 0; c < width; c++)
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

		return;
	}

	int nowHeight = (k * 4) - 3;
	int nowWidth = (k * 4) - 3;

	for (register int r = nowR; r < nowR + nowHeight; r++)
	{
		map[r][nowC] = '*';
		map[r][nowC + nowWidth - 1] = '*';
	}

	for (register int c = nowC; c < nowC + nowWidth; c++)
	{
		map[nowR][c] = '*';
		map[nowR + nowHeight - 1][c] = '*';
	}

	solve(nowR + 2, nowC + 2, k - 1);

	return;
}

void print(void)
{
	for (register int r = 0; r < height; r++)
	{
		printf("%s\n", map[r]);
	}

	return;
}

int main(void)
{
	scanf("%d", &N);

	height = (N * 4) - 3;
	width = (N * 4) - 3;

	init();

	solve(START_R, START_C, N);

	print();

	return 0;
}
