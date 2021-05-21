#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_K 22
#define MAX_R 5
#define MAX_C 5
#define MAX_AREA (MAX_R * MAX_C)
#define MAX_DIR 4
#define START_R 1
#define START_C 1
#define START_LEVEL 1

// 거대한 바위의 갯수
int K;
// 가능한 경우의 수
int ans = 0;
int directR[MAX_DIR] = { -1, 1, 0, 0 };
int directC[MAX_DIR] = { 0, 0, -1, 1 };
// Barrier!
// 1부터 5까지 사용
char map[MAX_R + 2][MAX_C + 2] = { 0, };
// Barrier!
// 1부터 5까지 사용
bool visit[MAX_R + 2][MAX_C + 2] = { 0, };

void inputData(void)
{
	int R;
	int C;

	scanf("%d", &K);

	for (register int i = 0; i < K; i++)
	{
		scanf("%d %d", &R, &C);

		map[R][C] = 'x';
	}

	return;
}

void init(void)
{
	for (register int r = 0; r <= MAX_R + 1; r++)
	{
		map[r][0] = 'x';
		map[r][MAX_C + 1] = 'x';
	}

	for (register int c = 0; c <= MAX_C + 1; c++)
	{
		map[0][c] = 'x';
		map[MAX_R + 1][c] = 'x';
	}

	map[START_R][START_C] = 's';
	map[MAX_R][MAX_C] = 'e';

	return;
}

void dfs(int nowR, int nowC, int level)
{
	if (level == MAX_AREA - K)
	{
		ans++;
	}

	if (map[nowR][nowC] == 'e')
	{
		return;
	}

	// 상하좌우 탐색
	for (register int d = 0; d < MAX_DIR; d++)
	{
		int dr = nowR + directR[d];
		int dc = nowC + directC[d];

		if (map[dr][dc] == 'x')
		{
			continue;
		}

		if (visit[dr][dc])
		{
			continue;
		}

		visit[dr][dc] = true;

		dfs(dr, dc, level + 1);

		visit[dr][dc] = false;
	}

	return;
}

void solve(void)
{
	visit[START_R][START_C] = true;

	dfs(START_R, START_C, START_LEVEL);

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	inputData();

	init();

	solve();

	printf("%d\n", ans);

	return 0;
}
