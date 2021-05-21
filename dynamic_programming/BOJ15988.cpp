/*
15988 1, 2, 3 더하기 3
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 1000000
#define MODULAR 1000000009

// dp[K] : K를 1, 2, 3으로 나타내는 방법의 갯수
int dp[MAX_N + 1] = { 0, };

// K를 1, 2, 3으로 나타내는 방법의 갯수 구하기
void solve()
{
	dp[1] = 1;
	dp[2] = 2;
	dp[3] = 4;

	for (int i = 4; i <= MAX_N; i++)
	{
		dp[i] = (((dp[i - 1] + dp[i - 2]) % MODULAR) + dp[i - 3]) % MODULAR;
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
		scanf("%d", &M);

		printf("%d\n", (dp[M] % MODULAR));
	}

	return 0;
}
