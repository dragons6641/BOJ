/*
10844 쉬운 계단 수
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 100
#define MAX_DIGIT 9
#define MODULAR 1000000000

int N;
int ans = 0;
// dp[a][b] : 길이가 a인 계단 수, 마지막 숫자는 b
int dp[MAX_N + 1][MAX_DIGIT + 1] = { 0, };

void solve(void)
{
	dp[1][0] = 0;

	// 초기 조건
	for (int c = 1; c <= MAX_DIGIT; c++)
	{
		dp[1][c] = 1;
	}

	// 길이
	for (int r = 2; r <= N; r++)
	{
		// 0일 경우
		dp[r][0] = dp[r - 1][1];

		// 나머지 경우
		// 자릿수
		for (int c = 1; c < MAX_DIGIT; c++)
		{
			dp[r][c] = (dp[r - 1][c - 1] + dp[r - 1][c + 1]) % MODULAR;
		}

		// 9일 경우
		dp[r][MAX_DIGIT] = dp[r - 1][MAX_DIGIT - 1];
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

	setbuf(stdout, NULL);

	scanf("%d", &N);

	solve();

	printf("%d\n", ans);

	return 0;
}
