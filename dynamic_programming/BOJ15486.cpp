/*
15486 퇴사 2
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 1500000
#define MAX_T 50
#define MAX_P 1000

int N;
int T[MAX_N + 1] = { 0, };
int P[MAX_N + 1] = { 0, };
// dp[k] : k번째 날짜까지의 최대 이익
int dp[MAX_N + 1] = { 0, };

void inputData(void)
{
	scanf("%d", &N);

	for (int i = 1; i <= N; i++)
	{
		scanf("%d %d", &T[i], &P[i]);
	}

	return;
}

int solve(void)
{
	// 초기값
	if (T[N] > 1)
	{
		dp[N] = 0;
	}
	else
	{
		dp[N] = P[N];
	}

	for (int i = N - 1; i >= 1; i--)
	{
		// (현재 날짜 + 상담에 걸리는 날)이 퇴사 이후일 경우
		if (i + T[i] > N + 1)
		{
			// 해당 일자의 상담을 진행할 수 없음
			dp[i] = dp[i + 1];
		}
		// 해당 일자의 상담을 진행할 수 있는 경우
		else
		{
			// 상담을 진행한 경우와 진행하지 않은 경우 중 큰 값을 반영
			dp[i] = (dp[i + 1] > (P[i] + dp[i + T[i]])) ? dp[i + 1] : (P[i] + dp[i + T[i]]);
		}
	}

	return dp[1];
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);
	// freopen("input3.txt", "r", stdin);
	// freopen("input4.txt", "r", stdin);

	inputData();

	int ans = solve();

	printf("%d\n", ans);

	return 0;
}
