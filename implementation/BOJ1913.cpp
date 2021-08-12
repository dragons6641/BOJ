/*
1913 달팽이
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 1000
#define MAX_DIR 4

int map[MAX_N + 1][MAX_N + 1] = { 0, };

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);

	int N;
	int M;
	int dir = 0;
	int directR[MAX_DIR] = { -1, 0, 1, 0 };
	int directC[MAX_DIR] = { 0, 1, 0, -1 };

	scanf("%d", &N);
	scanf("%d", &M);

	int nowR = (N + 1) / 2;
	int nowC = (N + 1) / 2;
	int targetR = nowR;
	int targetC = nowC;

	register int i = 1;
	register int maxMove = 1;

	map[nowR][nowC] = i;

	while (i < (N * N))
	{
		for (register int j = 1; j <= maxMove; j++)
		{
			i++;

			int dr = nowR + directR[dir];
			int dc = nowC + directC[dir];

			map[dr][dc] = i;

			if (i == M)
			{
				targetR = dr;
				targetC = dc;
			}

			nowR = dr;
			nowC = dc;

			if (i == N * N)
			{
				break;
			}
		}

		dir = (dir + 1) % MAX_DIR;

		if (dir % 2 == 0)
		{
			maxMove++;
		}
	}

	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			printf("%d ", map[r][c]);
		}

		printf("\n");
	}

	printf("%d %d\n", targetR, targetC);

	return 0;
}
