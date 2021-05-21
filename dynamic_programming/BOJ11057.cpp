/*
11507 오르막 수
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 1000
#define MAX_DIGIT 9
#define MODULAR 10007

int N;
int ans = 0;
// dp[a][b] : 길이가 a인 오르막 수, 마지막 숫자는 b
int dp[MAX_N + 1][MAX_DIGIT + 1] = { 0, };

void solve(void)
{
	// 초기 조건
	for (int c = 0; c <= MAX_DIGIT; c++)
	{
		dp[1][c] = 1;
	}

	// 길이
	for (int r = 2; r <= N; r++)
	{
		for (int c = 0; c <= MAX_DIGIT; c++)
		{
			for (int k = 0; k <= c; k++)
			{
				dp[r][c] = (dp[r][c] + dp[r - 1][k]) % MODULAR;
			}
		}
	}

	for (int c = 0; c <= MAX_DIGIT; c++)
	{
		ans = (ans + dp[N][c]) % MODULAR;
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);
	// freopen("input3.txt", "r", stdin);

	setbuf(stdout, NULL);

	scanf("%d", &N);

	solve();

	printf("%d\n", ans);

	return 0;
}
