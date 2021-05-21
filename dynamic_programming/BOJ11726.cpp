/*
11726 2×n 타일링
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 1000
#define MODULAR 10007

int N;
// dp[k] : 2 * k 타일을 채우는 방법의 개수
// 10007로 나눈 나머지를 저장
int dp[MAX_N + 1] = { 0, };

void solve(void)
{
	dp[1] = 1;
	dp[2] = 2;

	for (int i = 3; i <= N; i++)
	{
		dp[i] = ((dp[i - 1] + dp[i - 2]) % MODULAR);

		// int debug = 1;
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);

	setbuf(stdout, NULL);

	scanf("%d", &N);

	solve();

	// 10007로 나눈 나머지 출력
	printf("%d\n", dp[N] % MODULAR);

	return 0;
}
