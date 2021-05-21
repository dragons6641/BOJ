/*
19236 청소년 상어
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_R 4
#define MAX_C 4
#define MAX_FISH (MAX_R * MAX_C)
#define MAX_LEVEL (MAX_R * MAX_C)
#define MAX_DIR 8
#define MAX_MOVE 3
#define START_R 0
#define START_C 0
#define START_LEVEL 0
#define SHARK 0

struct Pos
{
	// 물고기 위치 표시
	int r;
	int c;
};

struct Fish
{
	// 물고기 번호
	// 죽었으면 -1
	int a;
	// 물고기 방향
	// 죽었으면 -1
	int b;
};

// 최댓값을 가져야 한다
// 최솟값으로 초기화
int ans = 0;
// 8방향, 반시계 순서
// 12, 11, 9, 7, 6, 5, 3, 1
// 1부터 사용
// 나머지 연산자 말고 더하기와 if문으로 방향 처리!
int directR[MAX_DIR + 1] = { 0, -1, -1, 0, 1, 1, 1, 0, -1 };
int directC[MAX_DIR + 1] = { 0, 0, -1, -1, -1, 0, 1, 1, 1 };
// 함수의 parameter로 넘겨줘야 할 수도 있다
// 상어의 위치는 0번째, 물고기의 위치는 1부터 사용
Pos fishList[MAX_LEVEL][MAX_FISH + 1] = { {0, 0} };
// 함수의 parameter로 넘겨줘야 할 수도 있다
// 0부터 사용해서 최대한 공간 아끼자!
Fish map[MAX_LEVEL][MAX_R][MAX_C] = { {0, 0}, };

void inputData(void)
{
	for (register int r = 0; r < MAX_R; r++)
	{
		for (register int c = 0; c < MAX_C; c++)
		{
			scanf("%d %d", &map[START_LEVEL][r][c].a, &map[START_LEVEL][r][c].b);

			fishList[START_LEVEL][map[START_LEVEL][r][c].a] = {r, c};
		}
	}

	return;
}

void copyInfo(int src, int dst)
{
	for (register int i = 0; i <= MAX_FISH; i++) 
	{
		fishList[src][i] = fishList[dst][i];
	}

	for (register int r = 0; r < MAX_R; r++)
	{
		for (register int c = 0; c < MAX_C; c++)
		{
			map[src][r][c] = map[dst][r][c];
		}
	}

	return;
}

void dfs(int point, int level)
{
	// 모든 물고기를 다 먹은 경우 끝
	if (level == MAX_LEVEL)
	{


		return;
	}

	int nowR = -1;
	int nowC = -1;
	int nowNum = -1;
	int nowDir = -1;

	// 정보 복사
	copyInfo(level + 1, level);

	// 물고기는 번호가 작은 물고기부터 순서대로 이동한다. 
	for (register int i = 1; i <= MAX_FISH; i++)
	{
		nowR = fishList[level + 1][i].r;
		nowC = fishList[level + 1][i].c;
		nowNum = map[level + 1][nowR][nowC].a;
		nowDir = map[level + 1][nowR][nowC].b;

		// 죽은 물고기는 이동하지 않는다.
		if (nowNum != i)
		{
			continue;
		}

		// 각 물고기는 방향이 이동할 수 있는 칸을 향할 때까지 방향을 45도 반시계 회전시킨다. 
		// 만약, 이동할 수 있는 칸이 없으면 이동을 하지 않는다. 
		for (register int j = 0; j < MAX_DIR; j++)
		{
			int nextDir = nowDir + j;

			if (nextDir > MAX_DIR)
			{
				nextDir -= MAX_DIR;
			}

			// 물고기는 한 칸을 이동할 수 있다.
			int dr = nowR + directR[nextDir];
			int dc = nowC + directC[nextDir];

			// 공간의 경계를 넘는 칸은 이동할 수 없는 칸이다. 
			if ((dr < 0) || (dc < 0) || (dr >= MAX_R) || (dc >= MAX_C))
			{
				continue;
			}

			// 상어가 있는 칸은 이동할 수 없는 칸이다. 
			if (map[level + 1][dr][dc].a == SHARK)
			{
				continue;
			}

			// 그 외의 경우에는 그 칸으로 이동을 한다. 
			// 이동할 수 있는 칸은 빈 칸(-1)과 다른 물고기가 있는 칸(>0)이다. 
			// 물고기가 다른 물고기가 있는 칸으로 이동할 때는 서로의 위치를 바꾸는 방식으로 이동한다.

			// 바뀐 방향을 반영해 준다. 
			map[level + 1][nowR][nowC].b = nextDir;

			// 자신과 바꿀 물고기의 번호를 저장한다. 
			int target = map[level + 1][dr][dc].a;

			// 빈 곳과 바꾸는 경우
			if (target == -1)
			{
				/*
				// fishList swap
				fishList[i] = { dr, dc };

				// map swap
				map[dr][dc] = map[nowR][nowC];
				map[nowR][nowC].a = -1;
				*/

				// fishList swap
				fishList[level + 1][i] = { dr,dc };

				// map swap
				map[level + 1][dr][dc] = map[level + 1][nowR][nowC];
				map[level + 1][nowR][nowC].a = -1;
			}
			// 다른 물고기와 바뀌는 경우
			else
			{
				/*
				// fishList swap
				Pos fishListTmp = fishList[i];
				fishList[i] = fishList[target];
				fishList[target] = fishListTmp;

				// map swap
				Fish mapTmp = map[nowR][nowC];
				map[nowR][nowC] = map[dr][dc];
				map[dr][dc] = mapTmp;
				*/

				// fishList swap
				Pos fishListTmp = fishList[level + 1][i];
				fishList[level + 1][i] = fishList[level + 1][target];
				fishList[level + 1][target] = fishListTmp;

				// map swap
				Fish mapTmp = map[level + 1][nowR][nowC];
				map[level + 1][nowR][nowC] = map[level + 1][dr][dc];
				map[level + 1][dr][dc] = mapTmp;
			}

			// int debug = 1;

			// 한 번 이동하면 추가로 이동할 필요 없다. 
			break;
		}
	}

	nowR = fishList[level + 1][SHARK].r;
	nowC = fishList[level + 1][SHARK].c;
	nowNum = map[level + 1][nowR][nowC].a;
	nowDir = map[level + 1][nowR][nowC].b;

	// 물고기의 이동이 모두 끝나면 상어가 이동한다. 
	// 상어는 방향에 있는 칸으로 이동할 수 있는데, 한 번에 여러 개의 칸을 이동할 수 있다. 
	// 이동하는 중에 지나가는 칸에 있는 물고기는 먹지 않는다. 
	// 상어가 이동할 수 있는 칸이 없으면 공간에서 벗어나 집으로 간다. 
	for (register int i = 1; i <= MAX_MOVE; i++)
	{
		int dr = nowR + (directR[nowDir]) * i;
		int dc = nowC + (directC[nowDir]) * i;

		// 공간의 경계를 넘는 칸은 이동할 수 없는 칸이다. 
		if ((dr < 0) || (dc < 0) || (dr >= MAX_R) || (dc >= MAX_C))
		{
			continue;
		}

		// 물고기가 없는 칸으로는 이동할 수 없다. 
		if (map[level + 1][dr][dc].a == -1)
		{
			continue;
		}

		int nextNum = map[level + 1][dr][dc].a;
		int nextPoint = point + nextNum;

		// 여기부터는 원래 상태 복구 필요
		// 상어가 물고기가 있는 칸으로 이동했다면, 그 칸에 있는 물고기를 먹고, 그 물고기의 방향을 가지게 된다. 
		/*
		fishList[SHARK] = { dr, dc };
		map[nowR][nowC].a = -1;
		map[dr][dc].a = SHARK;
		*/

		fishList[level + 1][SHARK] = { dr, dc };
		map[level + 1][nowR][nowC].a = -1;
		map[level + 1][dr][dc].a = SHARK;

		// 정답 갱신
		if (ans < nextPoint)
		{
			ans = nextPoint;
		}

		// 상어가 이동한 후에는 다시 물고기가 이동하며, 이후 이 과정이 계속해서 반복된다. 
		dfs(nextPoint, level + 1);

		// 원래 상태 복구
		// map 전체를 복구해야 함!
		/*
		fishList[SHARK] = { nowR, nowC };
		map[nowR][nowC].a = SHARK;
		map[dr][dc].a = nextNum;
		*/

		fishList[level + 1][SHARK] = { nowR, nowC };
		map[level + 1][nowR][nowC].a = SHARK;
		map[level + 1][dr][dc].a = nextNum;
	}

	return;
}

void solve(void)
{
	// 청소년 상어는 (0, 0)에 있는 물고기를 먹고 (0, 0)에 들어가게 된다.
	// 상어의 방향은 (0, 0)에 있던 물고기의 방향과 같다.
	int startPoint = map[START_LEVEL][START_R][START_C].a;
	fishList[START_LEVEL][SHARK] = { START_R, START_C };
	map[START_LEVEL][START_R][START_C].a = SHARK;

	// 정답 갱신
	if (ans < startPoint)
	{
		ans = startPoint;
	}

	// 상어가 이동한 후에는 다시 물고기가 이동하며, 이후 이 과정이 계속해서 반복된다. 
	dfs(startPoint, START_LEVEL);

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);
	// freopen("input3.txt", "r", stdin);
	// freopen("input4.txt", "r", stdin);

	inputData();

	solve();

	printf("%d\n", ans);

	return 0;
}
