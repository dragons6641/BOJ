/*
D5 방탈출
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 100
#define MIN_M 0
#define MAX_M 9
#define MAX_DIR 2
#define MAX_ROTATE 3
#define INF (MAX_N * (MAX_M + 1) + 1)
#define START_NOW 1
#define START_M 0

// 디스크의 갯수
int N;
// 시작 상태
// 1부터 사용
int startList[MAX_N + 1] = { 0, };
// 종료 상태
// 1부터 사용
int endList[MAX_N + 1] = { 0, };
// dp[now][a][b][c][d] : now번째 디스크를 보고 있고, d는 방향(시계 : 1, 반시계 : 2)
// a, b, c : now번째, (now + 1)번째, (now + 2)번째 디스크를 돌린 양
int dp[MAX_N + 1][MAX_M + 1][MAX_M + 1][MAX_M + 1][MAX_DIR + 1] = { 0, };

void inputData(void)
{
	scanf("%d", &N);

	for (register int i = 1; i <= N; i++)
	{
		scanf("%1d", &startList[i]);
	}

	for (register int i = 1; i <= N; i++)
	{
		scanf("%1d", &endList[i]);
	}

	return;
}

void init(void)
{
	for (register int now = START_NOW; now <= N; now++)
	{
		for (register int a = 0; a <= MAX_M; a++)
		{
			for (register int b = 0; b <= MAX_M; b++)
			{
				for (register int c = 0; c <= MAX_M; c++)
				{
					for (register int d = 1; d <= MAX_DIR; d++)
					{
						dp[now][a][b][c][d] = INF;
					}
				}
			}
		}
	}

	return;
}

int calcMod(int k)
{
	while (k < 0)
	{
		k += (MAX_M - MIN_M + 1);
	}

	return (k % (MAX_M - MIN_M + 1));
}

int calcMin(int x, int y)
{
	return ((x < y) ? x : y);
}

// dp + DFS
int solve(int now, int a, int b, int c, int d)
{
	// 모든 디스크를 다 봤다면 종료
	if (now == N + 1)
	{
		// 영향을 주지 않는 값 리턴
		return 0;
	}

	// int ret = dp[now][a][b][c][d];
	int& ret = dp[now][a][b][c][d];

	// 이미 한 번 봤던 곳이면 종료
	if (ret < INF)
	{
		// 영향을 주는 값 리턴
		return ret;
	}

	// 현재 디스크를 이미 맞춘 상태라면 다음 디스크로
	if (calcMod(a + startList[now]) == calcMod(endList[now]))
	{
		ret = calcMin(solve(now + 1, b, c, 0, 1), solve(now + 1, b, c, 0, 2));

		// 시계방향과 반시계방향 중 택 1
		return ret;
	}

	// 최솟값을 정확히 알 수 있도록 최댓값으로 초기화
	ret = INF;

	// 한 번에 최대 돌릴 수 있는 회전 수까지만 돌려봐야 한다
	for (register int i = 1; i <= MAX_ROTATE; i++)
	{
		// 시계 방향
		if (d == 1)
		{
			// now번째까지 돌리는 경우
			ret = calcMin(ret, solve(now, calcMod(a + i), b, c, d) + 1);
			// (now + 1)번째까지 돌리는 경우
			ret = calcMin(ret, solve(now, calcMod(a + i), calcMod(b + i), c, d) + 1);
			// (now + 2)번째까지 돌리는 경우
			ret = calcMin(ret, solve(now, calcMod(a + i), calcMod(b + i), calcMod(c + i), d) + 1);
		}
		// 반시계 방향
		else if (d == 2)
		{
			// now번째까지 돌리는 경우
			ret = calcMin(ret, solve(now, calcMod(a - i), b, c, d) + 1);
			// (now + 1)번째까지 돌리는 경우
			ret = calcMin(ret, solve(now, calcMod(a - i), calcMod(b - i), c, d) + 1);
			// (now + 2)번째까지 돌리는 경우
			ret = calcMin(ret, solve(now, calcMod(a - i), calcMod(b - i), calcMod(c - i), d) + 1);
		}
	}

	return ret;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);	// 2
	// freopen("input2.txt", "r", stdin);	// 2
	// freopen("input3.txt", "r", stdin);	// 3
	// freopen("input4.txt", "r", stdin);	// 2
	// freopen("input5.txt", "r", stdin);	// 1
	// freopen("input6.txt", "r", stdin);	// 3
	// freopen("input7.txt", "r", stdin);	// 8
	// freopen("input8.txt", "r", stdin);	// 72

	inputData();

	init();

	int ans = calcMin(solve(START_NOW, START_M, START_M, START_M, 1), solve(START_NOW, START_M, START_M, START_M, 2));

	printf("%d\n", ans);

	return 0;
}
