/*
10997 별 찍기 22
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 100
#define MAX_R (MAX_N * 4) - 1
#define MAX_C (MAX_N * 4) - 3
#define MIN_K 1
#define MAX_DIR 4
#define START_DIR 0
#define START_CNT 2

int N;
int height;
int width;
int directR[MAX_DIR] = { -1, 0, 1, 0 };
int directC[MAX_DIR] = { 0, 1, 0, -1 };
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

	map[1][1] = '\0';

	return;
}

void solve(int nowR, int nowC, int k)
{
	int nowDir = START_DIR;
	int nowCnt = START_CNT;

	map[nowR][nowC] = '*';

	while (true)
	{
		for (register int i = 0; i < nowCnt; i++)
		{
			nowR += directR[nowDir];
			nowC += directC[nowDir];

			if (nowC >= width)
			{
				return;
			}

			map[nowR][nowC] = '*';
		}

		nowDir++;

		if (nowDir == 2)
		{
			nowCnt += 2;
		}
		else if (nowDir == MAX_DIR)
		{
			nowCnt += 2;
			nowDir = START_DIR;
		}
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

	if (N == 1)
	{
		printf("*\n");

		return 0;
	}

	height = (N * 4) - 1;
	width = (N * 4) - 3;

	init();

	solve((height + 1) / 2, (width - 1) / 2, N);

	print();

	return 0;
}
