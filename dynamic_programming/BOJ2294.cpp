#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 100
#define MAX_M 100000
#define MAX_K 10000
#define INF (MAX_M + 1)

int N;
int K;
// 동전의 가치 목록
// 1부터 사용
int valueList[MAX_N + 1] = { 0, };
// dp[K] : K원의 가치를 나타내는 최소 동전의 수
// 1부터 사용
int dp[MAX_K + 1] = { 0, };

int Min(const int a, const int b)
{
	return ((a < b) ? a : b);
}

void inputData(void)
{
	scanf("%d %d", &N, &K);

	for (register int i = 1; i <= N; i++)
	{
		scanf("%d", &valueList[i]);
	}

	return;
}

void init(void)
{
	// 아무 동전도 사용하지 않는 경우 0개!
	dp[0] = 0;

	for (register int i = 1; i <= K; i++)
	{
		dp[i] = INF;
	}

	return;
}

void solve(void)
{
	// 동전
	for (register int i = 1; i <= N; i++)
	{
		// 현재 동전의 가치
		int M = valueList[i];

		// 가치
		for (register int j = M; j <= K; j++)
		{
			dp[j] = Min(dp[j], dp[j - M] + 1);
		}

		int debug = 1;
	}

	return;
}

void outputData(void)
{
	if (dp[K] == INF)
	{
		printf("-1\n");
	}
	else
	{
		printf("%d\n", dp[K]);
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	inputData();

	init();

	solve();

	outputData();

	return 0;
}
