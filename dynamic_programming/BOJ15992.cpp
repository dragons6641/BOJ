/*
15992 1, 2, 3 더하기 7
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 1000
#define MAX_M 1000
#define MODULAR 1000000009

// dp[a][b] : a를 1, 2, 3으로 나타내는 방법의 갯수, 숫자의 갯수는 b
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
	dp[3][2] = 2;
	dp[3][3] = 1;

	for (int r = 4; r <= MAX_N; r++)
	{
		for (int c = 1; c <= r; c++)
		{
			dp[r][c] = (((dp[r - 1][c - 1] + dp[r - 2][c - 1]) % MODULAR) + dp[r - 3][c - 1]) % MODULAR;
		}
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);

	setbuf(stdout, NULL);

	solve();

	int T;
	int N;
	int M;

	scanf("%d", &T);

	for (int test_case = 1; test_case <= T; test_case++)
	{
		scanf("%d %d", &N, &M);

		printf("%d\n", dp[N][M]);
	}

	return 0;
}
