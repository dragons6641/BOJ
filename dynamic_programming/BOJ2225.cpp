/*
2225 합분해
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 200
#define MAX_K 200
#define MODULAR 1000000000

int N;
int K;
// dp[a][b] : 정수 b개를 더해서 합이 a가 되는 경우의 수
// 1부터 시작
int dp[MAX_N + 1][MAX_K + 1] = { 0, };

void init(void)
{
	for (int r = 0; r <= N; r++)
	{
		dp[r][0] = 0;
		dp[r][1] = 1;
	}

	for (int c = 0; c <= K; c++)
	{
		dp[0][c] = 1;
		dp[1][c] = c;
	}
}

int solve(void)
{
	// 초기화
	init();

	for (int r = 2; r <= N; r++)
	{
		for (int c = 2; c <= K; c++)
		{
			for (int i = 0; i <= r; i++)
			{
				// dp[r][c] = (dp[r][c] + dp[r - i][c - 1] + c) % MODULAR;
				dp[r][c] = (dp[r][c] + dp[r - i][c - 1]) % MODULAR;
			}
		}
	}

	return dp[N][K] % MODULAR;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	setbuf(stdout, NULL);

	scanf("%d %d", &N, &K);

	printf("%d\n", solve());

	return 0;
}
