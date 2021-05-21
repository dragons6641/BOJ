/*
13015 별 찍기 - 23
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 100
#define MAX_R (MAX_N * 2) - 1
#define MAX_C (MAX_N * 4) - 3

int N;
int height;
int width;
int midR;
int midC;
char map[MAX_R + 1][MAX_C + 1] = { 0, };

void init(void)
{
	for (register int r = 0; r < midR; r++)
	{
		for (register int c = 0; c < width - r; c++)
		{
			map[r][c] = ' ';
		}
	}

	for (register int c = 0; c < width - midR; c++)
	{
		map[midR][c] = ' ';
	}

	for (register int r = midR + 1; r < height; r++)
	{
		for (register int c = 0; c <= midC + r; c++)
		{
			map[r][c] = ' ';
		}
	}

	return;
}

void solve(void)
{
	map[midR][midC - (N - 1)] = '*';
	map[midR][midC] = '*';
	map[midR][midC + (N - 1)] = '*';

	for (register int c = 0; c < N; c++)
	{
		map[0][c] = '*';
		map[0][width - c - 1] = '*';
		map[height - 1][c] = '*';
		map[height - 1][width - c - 1] = '*';
	}

	for (register int r = 1; r < midR; r++)
	{
		map[midR - r][midC - r] = '*';
		map[midR - r][midC + r] = '*';
		map[midR + r][midC - r] = '*';
		map[midR + r][midC + r] = '*';

		map[midR - r][midC - r - (N - 1)] = '*';
		map[midR - r][midC + r + (N - 1)] = '*';
		map[midR + r][midC - r - (N - 1)] = '*';
		map[midR + r][midC + r + (N - 1)] = '*';
	}

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

	height = (N * 2) - 1;
	width = (N * 4) - 3;
	midR = (height - 1) / 2;
	midC = (width - 1) / 2;

	init();

	solve();

	print();

	return 0;
}
