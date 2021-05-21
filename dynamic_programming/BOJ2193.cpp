/*
2193 이친수
*/

#define _CRT_SECURE_NO_WARNINGS
#define ll long long

#include <stdio.h>

#define MAX_N 90
#define MAX_DIGIT 1

int N;
ll ans = 0;
// dp[a][b] : 길이가 a인 이친수, 마지막 숫자는 b
ll dp[MAX_N + 1][MAX_DIGIT + 1] = { 0, };

void solve(void)
{
	// 초기 조건
	dp[1][0] = 0;
	dp[1][1] = 1;

	// 길이
	for (int r = 2; r <= N; r++)
	{
		dp[r][0] = dp[r - 1][0] + dp[r - 1][1];
		dp[r][1] = dp[r - 1][0];
	}

	for (int c = 0; c <= MAX_DIGIT; c++)
	{
		ans += dp[N][c];
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	setbuf(stdout, NULL);

	scanf("%d", &N);

	solve();

	printf("%lld\n", ans);

	return 0;
}
