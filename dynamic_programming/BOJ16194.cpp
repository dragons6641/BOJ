/*
16194 카드 구매하기 2
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 1000
#define MAX_P 10000
#define MAX_DP (MAX_N * MAX_P)

int N;
// P[i] : 카드가 i개 포함된 카드팩의 가격
// 1부터 사용
int P[MAX_N + 1] = { 0, };
// dp[i] : 카드를 i개 구매하는데 지불한 금액의 최댓값
int dp[MAX_N + 1] = { 0, };

void input(void)
{
	scanf("%d", &N);

	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &P[i]);
	}

	return;
}

void init(void)
{
	for (int i = 1; i <= N; i++)
	{
		dp[i] = MAX_DP;
	}

	return;
}

int solve(void)
{
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= i; j++)
		{
			if (dp[i] > dp[i - j] + P[j])
			{
				dp[i] = dp[i - j] + P[j];
			}
		}
	}

	return dp[N];
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);
	// freopen("input3.txt", "r", stdin);
	// freopen("input4.txt", "r", stdin);
	// freopen("input5.txt", "r", stdin);
	// freopen("input6.txt", "r", stdin);

	setbuf(stdout, NULL);

	input();

	init();

	printf("%d\n", solve());

	return 0;
}
