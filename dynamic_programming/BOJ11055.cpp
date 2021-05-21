/*
11055 가장 큰 증가 부분 수열
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 1000
#define MAX_M 1000

int N;
int ans = 0;
// 1부터 시작
int inputList[MAX_N + 1] = { 0, };
// dp[k] : k번째 요소를 포함했을 경우, 가장 큰 증가 부분 수열의 합
// 정답을 찾기 위해서는 최댓값을 갱신해 줘야 한다
int dp[MAX_N + 1] = { 0, };

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
	// 초기값
	dp[1] = inputList[1];
	ans = dp[1];

	for (int i = 2; i <= N; i++)
	{
		int maxValue = 0;
		int maxIndex = 0;

		for (int j = 1; j < i; j++)
		{
			// i번째 요소가 j번째 요소보다 커야 함
			// 최대값 갱신 가능하다면
			if ((inputList[i] > inputList[j]) && (maxValue < dp[j]))
			{
				maxValue = dp[j];
			}
		}

		dp[i] = maxValue + inputList[i];

		if (ans < dp[i])
		{
			ans = dp[i];
		}
	}

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
