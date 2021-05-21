#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 32
#define MAX_DIR 3

typedef long long LL;

// 집의 크기
int N;
// Barrier!
// 1부터 N까지 사용
bool map[MAX_N + 2][MAX_N + 2] = { 0, };
// dp[r][c][d] : (r, c)칸까지 d방향을 바라보도록 이동시키는 방법의 수
LL dp[MAX_N + 2][MAX_N + 2][MAX_DIR] = { 0, };

void inputData(void)
{
	int M;

	scanf("%d", &N);

	for (register int r = 1; r <= N; r++)
	{
		for (register int c = 1; c <= N; c++)
		{
			scanf("%d", &M);

			if (M == 1)
			{
				map[r][c] = true;
			}
		}
	}

	return;
}

void init(void)
{
	for (register int r = 0; r <= N + 1; r++)
	{
		map[r][0] = true;
		map[r][N + 1] = true;
	}

	for (register int c = 0; c <= N + 1; c++)
	{
		map[0][c] = true;
		map[N + 1][c] = true;
	}

	dp[1][2][0] = 1;

	return;
}

LL solve(void)
{
	for (register int r = 1; r <= N; r++)
	{
		for (register int c = 3; c <= N; c++)
		{
			// 해당 칸이 빈 칸이 아니라면 이동 불가
			if (map[r][c])
			{
				continue;
			}

			// 0. 3시 방향
			dp[r][c][0] = dp[r][c - 1][0] + dp[r][c - 1][1];

			// 1. 5시 방향
			// 추가 빈 칸 확인 필요
			if ((!map[r - 1][c]) && (!map[r][c - 1]))
			{
				dp[r][c][1] = dp[r - 1][c - 1][0] + dp[r - 1][c - 1][1] + dp[r - 1][c - 1][2];
			}

			// 2. 6시 방향
			dp[r][c][2] = dp[r - 1][c][1] + dp[r - 1][c][2];
		}
	}

	LL result = dp[N][N][0] + dp[N][N][1] + dp[N][N][2];

	return result;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);	// 1
	// freopen("input2.txt", "r", stdin);	// 3
	// freopen("input3.txt", "r", stdin);	// 0
	// freopen("input4.txt", "r", stdin);	// 13
	// freopen("input5.txt", "r", stdin);	// 4345413252

	inputData();

	init();

	LL ans = solve();

	printf("%lld\n", ans);

	return 0;
}
