/*
15993 1, 2, 3 더하기 8
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 100000
#define MAX_M 2
#define MODULAR 1000000009

// dp[a][b] : a를 1, 2, 3으로 나타내는 방법의 갯수, 숫자의 갯수는 b
// b : 홀수면 1, 짝수면 2
int dp[MAX_N + 1][MAX_M + 1] = { 0, };

// K를 1, 2, 3으로 나타내는 방법의 갯수 구하기
void solve()
{
	dp[1][1] = 1;
	dp[1][2] = 0;
	dp[2][1] = 1;
	dp[2][2] = 1;
	dp[3][1] = 2;
	dp[3][2] = 2;

	for (int i = 4; i <= MAX_N; i++)
	{
		dp[i][1] = (((dp[i - 1][2] + dp[i - 2][2]) % MODULAR) + dp[i - 3][2]) % MODULAR;
		dp[i][2] = (((dp[i - 1][1] + dp[i - 2][1]) % MODULAR) + dp[i - 3][1]) % MODULAR;
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	setbuf(stdout, NULL);

	solve();

	int T;
	int N;

	scanf("%d", &T);

	for (int test_case = 1; test_case <= T; test_case++)
	{
		scanf("%d", &N);

		printf("%d %d\n", dp[N][1], dp[N][2]);
	}

	return 0;
}
