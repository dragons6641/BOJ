/*
1463 1로 만들기
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 1000000
#define TARGET 1

int N;
// dp[x] : x를 만드는 데 필요한 연산의 최솟값
// 1부터 사용
int dp[MAX_N + 1] = { 0, };

void solve()
{
	for (int i = N; i >= TARGET; i--)
	{
		// 1. 3의 배수면 3으로 나눈다
		if ((i % 3) == 0)
		{
			if (dp[i / 3] > dp[i] + 1)
			{
				dp[i / 3] = dp[i] + 1;
			}
		}

		// 2. 2의 배수면 2로 나눈다
		if ((i % 2) == 0)
		{
			if (dp[i / 2] > dp[i] + 1)
			{
				dp[i / 2] = dp[i] + 1;
			}
		}

		// 3. 모든 경우에 대해 1을 뺀다
		if (dp[i - 1] > dp[i] + 1)
		{
			dp[i - 1] = dp[i] + 1;
		}

		int debug = 1;
	}

	return;
}

void init(void)
{
	for (int i = TARGET; i < N; i++)
	{
		dp[i] = MAX_N;
	}

	dp[N] = 0;

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);

	setbuf(stdout, NULL);

	scanf("%d", &N);

	init();

	solve();

	printf("%d\n", dp[TARGET]);

	return 0;
}
