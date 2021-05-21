#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 100
#define MAX_K 10
#define START_R 1
#define START_C 1

typedef long long LL;

int N;
// 1부터 사용
int map[MAX_N + 1][MAX_N + 1] = { 0, };
// 1부터 사용
// dp[r][c] : (r, c) 좌표까지 이동할 수 있는 경우의 수
LL dp[MAX_N + 1][MAX_N + 1] = { 0, };

void inputData(void)
{
	for (register int r = 1; r <= N; r++)
	{
		for (register int c = 1; c <= N; c++)
		{
			scanf("%1d", &map[r][c]);

			dp[r][c] = 0;
		}
	}

	return;
}

void solve(void)
{
	while (true)
	{
		scanf("%d", &N);

		if (N == -1)
		{
			break;
		}

		inputData();

		dp[START_R][START_C] = 1;

		for (register int r = 1; r <= N; r++)
		{
			for (register int c = 1; c <= N; c++)
			{
				if ((dp[r][c] > 0) && (map[r][c] > 0))
				{
					if (r + map[r][c] <= N)
					{
						dp[r + map[r][c]][c] += dp[r][c];
					}

					if (c + map[r][c] <= N)
					{
						dp[r][c + map[r][c]] += dp[r][c];
					}
				}
			}
		}

		printf("%lld\n", dp[N][N]);
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	solve();

	return 0;
}
