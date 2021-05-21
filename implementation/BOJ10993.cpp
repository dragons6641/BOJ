/*
10993 별 찍기 - 18
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 10
#define MAX_R (1 << MAX_N) - 1
#define MAX_C (1 << (MAX_N + 1)) - 3

int N;
int height;
int width;
char map[MAX_R + 1][MAX_C + 1] = { 0, };

void init()
{
	for (register int r = 0; r < height; r++)
	{
		if (N % 2 == 1)
		{
			for (register int c = 0; c < height + r; c++)
			{
				map[r][c] = ' ';
			}

			map[r][height + r] = '\0';
		}
		else
		{
			for (register int c = 0; c < width - r; c++)
			{
				map[r][c] = ' ';
			}

			map[r][width - r] = '\0';
		}
	}

	return;
}

void solve(int nowR, int nowC, int k)
{
	if (k == 1)
	{
		map[nowR][nowC] = '*';

		return;
	}

	int nowHeight = (1 << k) - 1;
	int nowWidth = (1 << (k + 1)) - 3;

	if (k % 2 == 1)
	{
		map[nowR][nowC] = '*';

		for (register int r = 1; r < nowHeight - 1; r++)
		{
			map[nowR + r][nowC - r] = '*';
			map[nowR + r][nowC + r] = '*';
		}

		for (register int c = nowC - (nowWidth - 1) / 2; c <= nowC + (nowWidth - 1) / 2; c++)
		{
			map[nowR + (nowHeight - 1)][c] = '*';
		}

		solve(nowR + (nowHeight - 2), nowC, k - 1);
	}
	else
	{
		map[nowR][nowC] = '*';

		for (register int r = 1; r < nowHeight - 1; r++)
		{
			map[nowR - r][nowC - r] = '*';
			map[nowR - r][nowC + r] = '*';
		}

		for (register int c = nowC - (nowWidth - 1) / 2; c <= nowC + (nowWidth - 1) / 2; c++)
		{
			map[nowR - (nowHeight - 1)][c] = '*';
		}

		solve(nowR - (nowHeight - 2), nowC, k - 1);
	}

	return;
}

void print()
{
	for (register int r = 0; r < height; r++)
	{
		/*
		for (register int c = 0; c < width; c++)
		{
			printf("%c", map[r][c]);
		}

		printf("\n");
		*/

		printf("%s\n", map[r]);
	}

	return;
}

int main(void)
{
	scanf("%d", &N);

	height = (1 << N) - 1;
	width = (1 << (N + 1)) - 3;

	init();

	if (N % 2 == 1)
	{
		solve(0, (width - 1) / 2, N);
	}
	else
	{
		solve(height - 1, (width - 1) / 2, N);
	}

	print();

	return 0;
}
