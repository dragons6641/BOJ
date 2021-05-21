/*
11055 가장 긴 바이토닉 부분 수열
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 1000
#define MAX_M 1000

int N;
int ans = 0;
// 1부터 시작
int inputList[MAX_N + 1] = { 0, };
// dp[k] : k번째 요소를 포함했을 경우, 가장 긴 증가하는 부분 수열
// 정답을 찾기 위해서는 최댓값을 갱신해 줘야 한다
int dp1[MAX_N + 1] = { 0, };
int dp2[MAX_N + 1] = { 0, };

void input(void)
{
	scanf("%d", &N);

	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &inputList[i]);
	}

	return;
}

void solve1(void)
{
	// 초기값
	dp1[1] = 1;

	for (int i = 2; i <= N; i++)
	{
		int maxValue = 0;
		int maxIndex = 0;

		for (int j = 1; j < i; j++)
		{
			// i번째 요소가 j번째 요소보다 커야 함
			// 최대값 갱신 가능하다면
			if ((inputList[i] > inputList[j]) && (maxValue < dp1[j]))
			{
				maxValue = dp1[j];
			}
		}

		dp1[i] = maxValue + 1;
	}

	return;
}

void solve2(void)
{
	// 초기값
	dp2[N] = 1;

	for (int i = N - 1; i >= 1; i--)
	{
		int maxValue = 0;
		int maxIndex = 0;

		for (int j = N; j > i; j--)
		{
			// i번째 요소가 j번째 요소보다 커야 함
			// 최대값 갱신 가능하다면
			if ((inputList[i] > inputList[j]) && (maxValue < dp2[j]))
			{
				maxValue = dp2[j];
			}
		}

		dp2[i] += maxValue + 1;

		if (ans < dp1[i] + dp2[i] - 1)
		{
			ans = dp1[i] + dp2[i] - 1;
		}
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	setbuf(stdout, NULL);

	input();

	if (N == 1)
	{
		ans = 1;
	}
	else
	{
		solve1();
		solve2();
	}

	printf("%d\n", ans);

	return 0;
}
