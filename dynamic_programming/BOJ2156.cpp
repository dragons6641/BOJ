/*
2156 포도주 시식
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 10000
#define MAX_M 3

int N;
int ans = 0;
// 1부터 사용
int inputList[MAX_N + 1] = { 0, };
// dp[a][b] : a번째 포도주까지의 답, 연속 b개째 마시는 중
int dp[MAX_N + 1][MAX_M + 1] = { 0, };

void input(void)
{
	scanf("%d", &N);

	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &inputList[i]);
	}

	return;
}

void solve(void)
{
	int maxValue = -1;
	int maxIndex = -1;

	// 초기값 설정
	dp[1][0] = 0;
	dp[1][1] = inputList[1];

	for (int r = 2; r <= N; r++)
	{
		maxValue = -1;
		maxIndex = -1;

		for (int c = 0; c < MAX_M; c++)
		{
			if (maxValue < dp[r - 1][c])
			{
				maxValue = dp[r - 1][c];
				maxIndex = c;
			}
		}

		// 0
		dp[r][0] = dp[r - 1][maxIndex];
		// 1
		dp[r][1] = dp[r - 1][0] + inputList[r];
		// 2
		dp[r][2] = dp[r - 1][1] + inputList[r];
	}

	maxValue = -1;
	maxIndex = -1;

	for (int c = 0; c < MAX_M; c++)
	{
		if (maxValue < dp[N][c])
		{
			maxValue = dp[N][c];
			maxIndex = c;
		}
	}

	ans = maxValue;

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	setbuf(stdout, NULL);

	input();

	solve();

	printf("%d\n", ans);

	return 0;
}
