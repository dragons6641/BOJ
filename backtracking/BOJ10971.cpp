/*
10971 외판원 순회
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 10
#define MAX_INT 21e8
#define START_NOW 1
#define START_LEVEL 1
#define START_COST 0

int N;
int ans = MAX_INT;
int visit[MAX_N + 1] = { 0, };
// 1부터 시작
int W[MAX_N + 1][MAX_N + 1] = { 0, };

void input(void)
{
	scanf("%d", &N);

	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			scanf("%d", &W[r][c]);
		}
	}

	return;
}

void run(int start, int now, int level, int cost)
{
	if (level == N)
	{
		if (W[now][start] > 0)
		{
			cost += W[now][start];

			if (ans > cost)
			{
				ans = cost;
			}
		}

		return;
	}

	for (int j = 1; j <= N; j++)
	{
		if ((W[now][j] > 0) && (visit[j] == 0))
		{
			visit[j] = level + 1;

			run(start, j, level + 1, cost + W[now][j]);

			visit[j] = 0;
		}
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	setbuf(stdout, NULL);

	input();

	for (int i = 1; i <= N; i++)
	{
		visit[i] = 1;

		run(i, i, START_LEVEL, START_COST);

		visit[i] = 0;
	}

	printf("%d\n", ans);

	return 0;
}
