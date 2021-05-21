/*
1912 연속합
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 100000
#define MIN_M -1000
#define MAX_M 1000

int N;
int ans = (MAX_N * MIN_M) - 1;
// 1부터 시작
int inputList[MAX_N + 1] = { 0, };
// dp[K] : K번째까지의 연속합
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
	ans = inputList[1];

	for (int i = 2; i <= N; i++)
	{
		// 더할 수가 양수이거나 0인 경우
		if (inputList[i] >= 0)
		{
			// 지금까지의 합이 양수이거나 0인 경우
			if (dp[i - 1] >= 0)
			{
				// 기존 합에 추가
				dp[i] = dp[i - 1] + inputList[i];
			}
			// 지금까지의 합이 음수인 경우
			else
			{
				// 새로운 수부터 합 계산
				dp[i] = inputList[i];
			}
		}
		// 더할 수가 음수인 경우
		else
		{
			// 새로운 수가 지금까지의 합보다 더 크다면
			if (inputList[i] > dp[i - 1])
			{
				// 새로운 수부터 합 계산
				dp[i] = inputList[i];
			}
			// 새로운 수가 지금까지의 합보다 작거나 같다면
			else
			{
				// 기존 합에 추가
				dp[i] = dp[i - 1] + inputList[i];
			}
		}

		// 정답 갱신
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
	// freopen("input2.txt", "r", stdin);
	// freopen("input3.txt", "r", stdin);

	setbuf(stdout, NULL);

	input();

	solve();

	printf("%d\n", ans);

	return 0;
}
