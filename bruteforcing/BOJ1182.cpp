/*
1182 부분수열의 합
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 20
#define START_LEVEL 0

int N;
int S;
int ans = 0;
int cnt = 0;
// 1부터 시작
int inputList[MAX_N + 1] = { 0, };
// 1부터 시작
int visit[MAX_N + 1] = { 0, };
// 1부터 시작
// dp[start][end] : start번째 ~ end번째 수로 이루어진 부분수열의 합
// int dp[MAX_N + 1][MAX_N + 1] = { 0, };

void run(int level)
{
	if (level == N)
	{
		int sum = 0;

		for (int i = 1; i <= N; i++)
		{
			if (visit[i] == 2)
			{
				sum += inputList[i];
			}
		}

		if ((sum == S) && (cnt > 0))
		{
			ans++;
		}

		return;
	}

	// 1. 선택하지 않음
	visit[level + 1] = 1;

	run(level + 1);

	visit[level + 1] = 0;

	// 2. 선택
	visit[level + 1] = 2;
	cnt++;

	run(level + 1);

	visit[level + 1] = 0;
	cnt--;

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);
	// freopen("input3.txt", "r", stdin);
	// freopen("input4.txt", "r", stdin);

	setbuf(stdout, NULL);

	scanf("%d %d", &N, &S);

	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &inputList[i]);
	}

	/*
	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &dp[i][i]);

		if (dp[i][i] == S)
		{
			ans++;
		}
	}

	for (int c = 1; c <= N; c++)
	{
		for (int r = 1; r < c; r++)
		{
			dp[r][c] = dp[r][c - 1] + dp[c][c];

			if (dp[r][c] == S)
			{
				ans++;
			}
		}
	}
	*/

	run(START_LEVEL);

	printf("%d\n", ans);

	return 0;
}
