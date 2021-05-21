/*
15989 1, 2, 3 더하기 4
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 10000
#define MAX_M 3

// dp[a][b] : a를 1, 2, 3으로 나타내는 방법의 갯수, 마지막 수는 b
int dp[MAX_N + 1][MAX_M + 1] = { 0, };

// K를 1, 2, 3으로 나타내는 방법의 갯수 구하기
void solve()
{
	dp[1][1] = 1;
	dp[1][2] = 0;
	dp[1][3] = 0;
	dp[2][1] = 1;
	dp[2][2] = 1;
	dp[2][3] = 0;
	dp[3][1] = 1;
	dp[3][2] = 1;
	dp[3][3] = 1;

	for (int i = 4; i <= MAX_N; i++)
	{
		dp[i][1] = dp[i - 1][1];
		dp[i][2] = dp[i - 2][1] + dp[i - 2][2];
		dp[i][3] = dp[i - 3][1] + dp[i - 3][2] + dp[i - 3][3];
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	setbuf(stdout, NULL);

	solve();

	int N;
	int M;

	scanf("%d", &N);

	for (int i = 0; i < N; i++)
	{
		int ans = 0;

		scanf("%d", &M);

		for (int j = 1; j <= MAX_M; j++)
		{
			ans = ans + dp[M][j];
		}

		printf("%d\n", ans);
	}

	return 0;
}
