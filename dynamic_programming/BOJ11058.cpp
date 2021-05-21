#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 100

typedef long long LL;

int N;
// dp[K] : 크리보드를 K번 눌러서 만들 수 있는 A 갯수의 최댓값 
LL dp[MAX_N + 1] = { 0, };

LL Max(LL a, LL b)
{
	return ((a > b) ? a : b);
}

LL solve(void)
{
	for (register int i = 1; i <= 6; i++)
	{
		dp[i] = i;
	}

	for (register int i = 7; i <= N; i++)
	{
		dp[i] = Max(dp[i], dp[i - 1] + 1);

		for (register int j = 2; j <= i - 2; j++)
		{
			dp[i] = Max(dp[i], dp[i - j - 1] * j);
		}
	}

	return dp[N];
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);	// 3
	// freopen("input2.txt", "r", stdin);	// 9
	// freopen("input3.txt", "r", stdin);	// 27

	scanf("%d", &N);

	LL ans = solve();

	printf("%lld\n", ans);

	return 0;
}
