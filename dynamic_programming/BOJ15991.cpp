/*
15991 1, 2, 3 더하기 6
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 1000000
#define MAX_M 3
#define MODULAR 1000000009

// dp[k] : k를 1, 2, 3으로 나타내는 방법의 갯수
int dp[MAX_N + 1] = { 0, };

// K를 1, 2, 3으로 나타내는 방법의 갯수 구하기
void solve()
{
	/*
	dp[1] = 1;
	dp[2] = 2;
	dp[3] = 2;
	dp[4] = 3;
	dp[5] = 3;
	dp[6] = 7;

	for (int i = 7; i <= MAX_N; i++)
	{
		dp[i] = (((dp[i - 2] + dp[i - 4]) % MODULAR) + dp[i - 6]) % MODULAR;
	}
	*/

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

		// printf("%d\n", dp[M]);

		// 1, 2, 3은 예외처리
		if ((M == 1) || (M == 2))
		{
			printf("%d\n", dp[M]);
		}
		else if (M == 3)
		{
			printf("%d\n", dp[M] - 2);
		}
		// 홀수
		else if (M % 2 == 1)
		{
			printf("%d\n", (dp[(M - 1) / 2] + dp[(M - 1) / 2 - 1]) % MODULAR);
		}
		// 짝수
		else
		{
			printf("%d\n", (dp[M / 2] + dp[M / 2 - 1]) % MODULAR);
		}
	}

	return 0;
}
