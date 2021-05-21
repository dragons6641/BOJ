#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 100
#define MAX_M 100000
#define MAX_K 10000

int N;
int K;
// 가장 높은 동전의 가치
// 단, 나타낼 가치의 합보다는 작거나 같아야 함
// 최댓값을 가져야 하므로 최솟값으로 초기화
int maxValue = 0;
// 동전의 가치 목록
// 1부터 사용
int valueList[MAX_N + 1] = { 0, };
// dp[K] : K원의 가치를 나타내는 방법의 수
// 1부터 사용
int dp[MAX_K + 1] = { 0, };

void inputData(void)
{
	scanf("%d %d", &N, &K);

	for (register int i = 1; i <= N; i++)
	{
		scanf("%d", &valueList[i]);

		if (valueList[i] <= K)
		{
			// dp[valueList[i]] = 1;

			if (maxValue < valueList[i])
			{
				maxValue = valueList[i];
			}
		}
	}

	return;
}

int solve(void)
{
	// 아무 동전도 사용하지 않는 경우 1가지!
	dp[0] = 1;

	// 동전
	for (register int i = 1; i <= N; i++)
	{
		// 현재 동전의 가치
		int M = valueList[i];

		// 가치
		for (register int j = M; j <= K; j++)
		{
			dp[j] += dp[j - M];
		}

		int debug = 1;
	}

	return dp[K];
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	inputData();

	int ans = solve();

	printf("%d\n", ans);

	return 0;
}
