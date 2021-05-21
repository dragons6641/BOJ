/*
1699 제곱수의 합
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 100000

int N;
// dp[k] : k를 제곱수로 나타내는 방법들 중 최소 항의 갯수
// dp[k] = k로 초기화 필요
// 1부터 사용
int dp[MAX_N + 1] = { 0, };

void init(void)
{
	for (int i = 0; i <= N; i++)
	{
		dp[i] = i;
	}

	return;
}

int solve(void)
{
	// 초기화
	init();

	for (int i = 2; i <= N; i++)
	{
		for (int j = 2; (j * j) <= i; j++)
		{
			if (dp[i] > dp[i - (j * j)] + 1)
			{
				dp[i] = dp[i - (j * j)] + 1;
			}
		}
	}

	return dp[N];
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	setbuf(stdout, NULL);

	scanf("%d", &N);

	printf("%d\n", solve());

	return 0;
}
