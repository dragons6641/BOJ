/*
9465 스티커
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_M 2
#define MAX_N 100000

int N;
int ans = 0;
int map[MAX_M + 1][MAX_N + 1] = { 0, };
// dp[r][c] : c번째 열까지 진행했을 때 최대 점수
// 0 : 선택 X, 1 : 위쪽 스티커 선택, 2 : 아랫쪽 스티커 선택
int dp[MAX_M + 1][MAX_N + 1] = { 0, };

void input(void)
{
	scanf("%d", &N);

	for (int r = 1; r <= MAX_M; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			scanf("%d", &map[r][c]);
		}
	}

	return;
}

void solve(void)
{
	int maxValue = -1;
	int maxIndex = -1;

	// 초기값 설정
	dp[0][1] = 0;
	dp[1][1] = map[1][1];
	dp[2][1] = map[2][1];

	for (int c = 2; c <= N; c++)
	{
		/*
		if (dp[0][c - 1] > dp[1][c - 1])
		{
			// 0이 최대
			dp[2][c] = dp[0][c - 1] + map[2][c];

			if (dp[0][c - 1] > dp[2][c - 1])
			{
				// 0이 최대
				dp[0][c] = dp[0][c - 1];
				dp[1][c] = dp[0][c - 1] + map[1][c];
			}
			else
			{
				// 2가 최대
				dp[0][c] = dp[2][c - 1];
				dp[1][c] = dp[2][c - 1] + map[1][c];
			}
		}
		else
		{
			// 1이 최대
			dp[2][c] = dp[1][c - 1] + map[2][c];

			if (dp[0][c - 1] > dp[2][c - 1])
			{
				// 1이 최대
				dp[0][c - 1] = dp[1][c - 1];
				// 0이 최대
				dp[1][c] = dp[0][c - 1] + map[1][c];
			}
			else
			{
				// 2가 최대
				dp[1][c] = dp[2][c - 1] + map[1][c];

				if (dp[1][c - 1] > dp[2][c - 1])
				{
					// 1이 최대
					dp[0][c - 1] = dp[1][c - 1];
				}
				else
				{
					// 2가 최대
					dp[0][c - 1] = dp[2][c - 1];
				}
			}
		}
		*/

		// 0
		maxValue = -1;
		maxIndex = -1;

		for (int r = 0; r <= MAX_M; r++)
		{
			if (maxValue < dp[r][c - 1])
			{
				maxValue = dp[r][c - 1];
				maxIndex = r;
			}
		}

		dp[0][c] = dp[maxIndex][c - 1];

		// 1
		if (dp[0][c - 1] > dp[2][c - 1])
		{
			dp[1][c] = dp[0][c - 1] + map[1][c];
		}
		else
		{
			dp[1][c] = dp[2][c - 1] + map[1][c];
		}

		// 2
		if (dp[0][c - 1] > dp[1][c - 1])
		{
			dp[2][c] = dp[0][c - 1] + map[2][c];
		}
		else
		{
			dp[2][c] = dp[1][c - 1] + map[2][c];
		}
	}

	maxValue = -1;
	maxIndex = -1;

	for (int r = 0; r <= MAX_M; r++)
	{
		if (maxValue < dp[r][N])
		{
			maxValue = dp[r][N];
			maxIndex = r;
		}
	}

	ans = maxValue;

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);

	setbuf(stdout, NULL);

	int T;

	scanf("%d", &T);

	for (int testCase = 1; testCase <= T; testCase++)
	{
		ans = 0;

		input();

		solve();

		printf("%d\n", ans);

		// int debug = 1;
	}

	return 0;
}
