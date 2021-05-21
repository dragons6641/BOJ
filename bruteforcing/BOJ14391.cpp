#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_R 4
#define MAX_C 4
#define MAX_DIR 2
#define DIGIT 10
#define START_R 0
#define START_C 0
#define START_SUM 0
#define START_CNT 0
#define START_LEVEL 0

struct Node
{
	int r;
	int c;
};

// rows
int N;
// cols
int M;
// 최댓값을 가져야 하므로 최솟값으로 초기화
int ans = 0;
int map[MAX_R][MAX_C] = { 0, };
int visit[MAX_R][MAX_C] = { 0, };

void inputData(void)
{
	scanf("%d %d", &N, &M);

	for (register int r = 0; r < N; r++)
	{
		for (register int c = 0; c < M; c++)
		{
			scanf("%1d", &map[r][c]);
		}
	}

	return;
}

Node calcNext(int nowR, int nowC)
{
	for (register int r = nowR; r < N; r++)
	{
		for (register int c = (r == nowR ? nowC : 0); c < M; c++)
		{
			if (visit[r][c] == 0)
			{
				return { r, c };
			}
		}
	}

	return { -1, -1 };
}

void dfs(int nowR, int nowC, int nowSum, int cnt, int level)
{
	if ((nowR == -1) && (nowC == -1))
	{
		if ((level == N * M) && (ans < nowSum))
		{
			ans = nowSum;
		}

		return;
	}

	if ((nowR == -1) && (nowC == -1))
	{
		int debug = 1;
	}

	for (register int r = nowR; r < N; r++)
	{
		for (register int c = (r == nowR ? nowC : 0); c < M; c++)
		{
			int val = 0;
			bool isPossible = true;
			Node ret;

			// 조각의 크기 결정
			// 1조각 -> 따로 처리
			// 가능하다면 해당 범위를 한 조각으로 만든다
			if (visit[r][c] > 0)
			{
				isPossible = false;
			}

			if (isPossible)
			{
				visit[r][c] = cnt + 1;
				val = map[r][c];

				// 다음 위치를 계산
				ret = calcNext(r, c);

				// 다음 위치에서 탐색
				dfs(ret.r, ret.c, nowSum + val, cnt + 1, level + 1);

				// 초기화
				visit[r][c] = false;
				val = 0;
			}

			// 아래쪽이면 row방향 -> N
			for (register int k = 1; k < N; k++)
			// for (register int k = N - 1; k >= 1; k--)
			{
				int dr = r + k;

				// 범위를 벗어나면 안됨
				if (dr >= N)
				{
					continue;
				}

				isPossible = true;

				// 가능한지 확인
				for (register int nextR = r; nextR <= dr; nextR++)
				{
					if (visit[nextR][c] > 0)
					{
						isPossible = false;

						break;
					}
				}

				if (isPossible)
				{
					// 가능하다면 해당 범위를 한 조각으로 만든다
					for (register int nextR = r; nextR <= dr; nextR++)
					{
						visit[nextR][c] = cnt + 1;
						val = (val * DIGIT) + map[nextR][c];
					}

					// 다음 위치를 계산
					ret = calcNext(r, c);

					// 다음 위치에서 탐색
					dfs(ret.r, ret.c, nowSum + val, cnt + 1, level + dr - r + 1);

					// 초기화
					for (register int nextR = r; nextR <= dr; nextR++)
					{
						visit[nextR][c] = 0;
					}

					val = 0;
				}
			}

			// 오른쪽이면 col방향 -> M
			for (register int k = 1; k < M; k++)
			// for (register int k = M - 1; k >= 1; k--)
			{
				int dc = c + k;

				// 범위를 벗어나면 안됨
				if (dc >= M)
				{
					continue;
				}

				isPossible = true;

				// 가능한지 확인
				for (register int nextC = c; nextC <= dc; nextC++)
				{
					if (visit[r][nextC] > 0)
					{
						isPossible = false;

						break;
					}
				}

				if (isPossible)
				{
					// 가능하다면 해당 범위를 한 조각으로 만든다
					for (register int nextC = c; nextC <= dc; nextC++)
					{
						visit[r][nextC] = cnt + 1;
						val = (val * DIGIT) + map[r][nextC];
					}

					// 다음 위치를 계산
					ret = calcNext(r, c);

					// 다음 위치에서 탐색
					dfs(ret.r, ret.c, nowSum + val, cnt + 1, level + dc - c + 1);

					// 초기화
					for (register int nextC = c; nextC <= dc; nextC++)
					{
						visit[r][nextC] = 0;
					}

					val = 0;
				}
			}

			c++;
		}
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);	// 435
	// freopen("input2.txt", "r", stdin);	// 182
	// freopen("input3.txt", "r", stdin);	// 1131
	// freopen("input4.txt", "r", stdin);	// 8
	// freopen("input5.txt", "r", stdin);	// 24925

	inputData();

	dfs(START_R, START_C, START_SUM, START_CNT, START_LEVEL);

	printf("%d\n", ans);

	return 0;
}
