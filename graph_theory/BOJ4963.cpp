/*
4963 섬의 개수
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_R 50
#define MAX_C 50
#define MAX_DIR 8

int W;
int H;
int ans = 0;
int directR[MAX_DIR] = { -1, 1, 0, 0, -1, -1, 1, 1 };
int directC[MAX_DIR] = { 0, 0, -1, 1, -1, 1, 1, -1 };
int map[MAX_R][MAX_C] = { 0, };

void init(void)
{
	ans = 0;

	for (int r = 0; r < MAX_R; r++)
	{
		for (int c = 0; c < MAX_C; c++)
		{
			map[r][c] = -1;
		}
	}

	return;
}

void input(void)
{
	for (int r = 0; r < H; r++)
	{
		for (int c = 0; c < W; c++)
		{
			scanf("%d", &map[r][c]);
		}
	}

	return;
}

void dfs(int nowR, int nowC)
{
	for (int d = 0; d < MAX_DIR; d++)
	{
		int dr = nowR + directR[d];
		int dc = nowC + directC[d];

		if ((dr < 0) || (dc < 0) || (dr >= H) || (dc >= W))
		{
			continue;
		}

		if (map[dr][dc] != 1)
		{
			continue;
		}

		map[dr][dc] = (ans + 1);

		dfs(dr, dc);
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);

	setbuf(stdout, NULL);

	while (true)
	{
		scanf("%d %d", &W, &H);

		if ((W == 0) && (H == 0))
		{
			break;
		}

		init();

		input();

		for (int r = 0; r < H; r++)
		{
			for (int c = 0; c < W; c++)
			{
				if (map[r][c] == 1)
				{
					ans++;

					dfs(r, c);
				}
			}
		}

		printf("%d\n", ans);

		// int debug = 1;
	}

	return 0;
}
