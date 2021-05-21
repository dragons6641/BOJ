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
	scanf("%d", &N);

	for (register int r = 1; r <= N; r++)
	{
		for (register int c = 1; c <= N; c++)
		{
			scanf("%d", &map[r][c]);
		}
	}

	return;
}

LL solve(void)
{
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

	return dp[N][N];
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	inputData();

	LL ans = solve();

	printf("%lld\n", ans);

	return 0;
}
