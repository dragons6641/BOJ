#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MIN_N 3
#define MAX_N 9
#define MIN_R MIN_N
#define MIN_C MIN_N
#define MAX_R MAX_N
#define MAX_C MAX_N
#define MAX_K (MAX_R * MAX_C)
#define START_LEVEL 0

struct Node
{
	int r;
	int c;
};

// 풀어야 할 칸 갯수
int cnt = 0;
// 아무거나 출력하면 된다
bool isFinished = false;
int map[MAX_R][MAX_C] = { 0, };
// 풀어야 할 칸 목록
Node zeroList[MAX_K] = { 0, 0 };

void inputData(void)
{
	for (register int r = 0; r < MAX_R; r++)
	{
		for (register int c = 0; c < MAX_C; c++)
		{
			scanf("%d", &map[r][c]);

			if (map[r][c] == 0)
			{
				zeroList[cnt++] = { r, c };
			}
		}
	}

	return;
}

void printAns(void)
{
	for (register int r = 0; r < MAX_R; r++)
	{
		for (register int c = 0; c < MAX_C; c++)
		{
			printf("%d ", map[r][c]);
		}

		printf("\n");
	}

	return;
}

void dfs(int level)
{
	if (isFinished)
	{
		return;
	}

	if (level == cnt)
	{
		// int debug = 1;

		isFinished = true;

		printAns();

		return;
	}

	int nowR = zeroList[level].r;
	int nowC = zeroList[level].c;
	int startR = ((int)(nowR / MIN_N) * MIN_N);
	int startC = ((int)(nowC / MIN_N) * MIN_N);
	int endR = startR + MIN_N - 1;
	int endC = startC + MIN_N - 1;
	bool isUsed[MAX_N + 1] = { false, };

	// 검사를 먼저 하자
	// 1. row방향 검사
	for (register int r = 0; r < MAX_R; r++)
	{
		isUsed[map[r][nowC]] = true;
	}

	// 2. col방향 검사
	for (register int c = 0; c < MAX_C; c++)
	{
		isUsed[map[nowR][c]] = true;
	}

	// 3. 3 * 3 정사각형 검사
	for (register int r = startR; r <= endR; r++)
	{
		for (register int c = startC; c <= endC; c++)
		{
			isUsed[map[r][c]] = true;
		}
	}

	// 가능한 경우 모두 탐색
	for (register int i = 1; i <= MAX_N; i++)
	{
		// 사용되지 않은 경우에만 숫자를 써넣는다
		if (!isUsed[i])
		{
			map[nowR][nowC] = i;

			dfs(level + 1);

			map[nowR][nowC] = 0;
		}
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	inputData();

	dfs(START_LEVEL);

	return 0;
}
