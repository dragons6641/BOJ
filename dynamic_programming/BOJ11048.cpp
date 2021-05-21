#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_R 1000
#define MAX_C 1000
#define MAX_K 100

// rows
int N;
// cols
int M;
// 1부터 사용
int map[MAX_R + 1][MAX_C + 1] = { 0, };
// dp[r][c] : (r, c) 위치까지 이동했을 때 얻을 수 있는 최대 사탕 갯수
// 1부터 사용
int dp[MAX_R + 1][MAX_C + 1] = { 0, };

int Max(const int a, const int b)
{
	return ((a > b) ? a : b);
}

void inputData(void)
{
	scanf("%d %d", &N, &M);

	for (register int r = 1; r <= N; r++)
	{
		for (register int c = 1; c <= M; c++)
		{
			scanf("%d", &map[r][c]);
		}
	}

	return;
}

int solve(void)
{
	for (register int r = 1; r <= N; r++)
	{
		for (register int c = 1; c <= M; c++)
		{
			dp[r][c] = Max(Max(dp[r - 1][c], dp[r][c - 1]), dp[r - 1][c - 1]) + map[r][c];
		}
	}

	return dp[N][M];
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);	// 31
	// freopen("input2.txt", "r", stdin);	// 3
	// freopen("input3.txt", "r", stdin);	// 47

	inputData();

	int ans = solve();

	printf("%d\n", ans);

	return 0;
}
