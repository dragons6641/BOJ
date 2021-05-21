#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_K 500
#define INF (int)2e9

int T;
int K;
// 파일의 크기 목록
// 1부터 시작
int inputList[MAX_K + 1] = { 0, };
// 부분합
// 1부터 시작
int prefixSum[MAX_K + 1] = { 0, };
// dp[a][b] : a~b번째 장을 합치는데 드는 최소 비용
// 1부터 시작
int dp[MAX_K + 1][MAX_K + 1] = { 0, };

int Min(const int a, const int b)
{
	return ((a < b) ? a : b);
}

void solve(void)
{
	scanf("%d", &T);

	for (register int testCase = 1; testCase <= T; testCase++)
	{
		scanf("%d", &K);

		for (register int i = 1; i <= K; i++)
		{
			scanf("%d", &inputList[i]);

			prefixSum[i] = prefixSum[i - 1] + inputList[i];
		}

		for (register int dist = 1; dist <= K; dist++)
		{
			for (register int start = 1; start + dist <= K; start++)
			{
				int end = start + dist;

				dp[start][end] = INF;

				for (register int mid = start; mid < end; mid++)
				{
					dp[start][end] = Min(dp[start][end], dp[start][mid] + dp[mid + 1][end] + prefixSum[end] - prefixSum[start - 1]);
				}
			}
		}

		printf("%d\n", dp[1][K]);
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	solve();

	return 0;
}
