#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 100
#define MAX_K 100000
#define MAX_W 100000
#define MAX_V 1000

// 물품의 수
int N;
// 버틸 수 있는 무게
int K;
// 각 물건의 무게
// 1부터 사용
int W[MAX_N + 1] = { 0, };
// 해당 물건의 가치
// 1부터 사용
int V[MAX_N + 1] = { 0, };
// dp[a][b] : a번째 물건까지 사용하여 b 무게의 가방에 담았을 때의 가치 최댓값
// 1부터 사용
int dp[MAX_N + 1][MAX_K + 1] = { 0, };

inline int Max(const int a, const int b)
{
	return ((a > b) ? a : b);
}

void inputData(void)
{
	scanf("%d %d", &N, &K);

	for (register int i = 1; i <= N; i++)
	{
		scanf("%d %d", &W[i], &V[i]);
	}

	return;
}

int solve(void)
{
	// 물건
	for (register int r = 1; r <= N; r++)
	{
		// 무게
		for (register int c = 1; c <= K; c++)
		{
			// 해당 물건을 담을 수 있는 경우
			if (c - W[r] >= 0)
			{
				// 담거나, 담지 않거나 -> 둘 중 선택
				dp[r][c] = Max(dp[r - 1][c - W[r]] + V[r], dp[r - 1][c]);
			}
			// 해당 물건을 담을 수 없는 경우
			else
			{
				// 경우의 수는 담지 않는 한 가지 뿐
				dp[r][c] = dp[r - 1][c];
			}
		}
	}

	return dp[N][K];
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);	// 14
	// freopen("input2.txt", "r", stdin);	// 14
	// freopen("input3.txt", "r", stdin);	// 1

	inputData();

	int ans = solve();

	printf("%d\n", ans);

	return 0;
}
