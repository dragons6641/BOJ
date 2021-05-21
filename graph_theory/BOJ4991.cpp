#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_R 20
#define MAX_C 20
#define MAX_DIRTY 10
#define MAX_DIR 4
#define MAX_QUEUE (MAX_R * MAX_C)
#define INF ((MAX_R + MAX_C) * MAX_DIRTY)
#define START_POS 0
#define START_DIST 0
#define START_LEVEL 0

// 거리를 구하기 위해 필요한 좌표
// queue에 넣을 정보
struct Node
{
	int r;
	int c;
	// 현재 위치까지의 거리
	int dist;
};

// 방의 가로 크기 : cols
int W;
// 방의 세로 크기 : rows
int H;
// 최소 이동 거리이므로 최댓값으로 초기화
int ans = INF;
// 더러운 칸의 갯수
int dirtyCnt = 0;
int directR[MAX_DIR] = { -1, 1, 0, 0 };
int directC[MAX_DIR] = { 0, 0, -1, 1 };
// 각 칸 사이의 거리 기록
// 1부터 사용
int distMap[MAX_DIRTY + 1][MAX_DIRTY + 1] = { 0, };
// Barrier!
// 1부터 N까지 사용
char map[MAX_R + 2][MAX_C + 2] = { 0, };
// 더러운 칸을 청소했는지 여부
// 1부터 사용
bool isCleaned[MAX_DIRTY + 1] = { 0, };
// 더러운 칸의 위치 저장
// 0번 칸은 로봇의 시작 위치
// 더러운 칸은 1부터 시작
Node dirtyList[MAX_DIRTY + 1] = { {0, 0, 0}, };
// queue는 head와 tail만 초기화하면 되므로 전역으로 선언
Node queue[MAX_QUEUE] = { {0, 0, 0}, };

void initBefore(void)
{
	ans = INF;
	dirtyCnt = 0;

	for (register int i = 1; i <= MAX_DIRTY; i++)
	{
		isCleaned[i] = false;
	}

	return;
}

// 경계를 가구로 채워넣는다
void initAfter(void)
{
	for (register int r = 0; r <= H + 1; r++)
	{
		map[r][0] = 'x';
		map[r][W + 1] = 'x';
	}

	for (register int c = 0; c <= W + 1; c++)
	{
		map[0][c] = 'x';
		map[H + 1][c] = 'x';
	}

	return;
}

// a번째 칸과 b번째 칸의 거리 구하기
// 즉, a가 출발지이고 b가 도착지인 bfs!
int bfs(int a, int b)
{
	register int head = 0;
	register int tail = 0;
	// visit을 여기에 잡아야 초기화할 필요 없음
	bool visit[MAX_R + 2][MAX_C + 2] = { 0, };
	Node start = dirtyList[a];
	Node end = dirtyList[b];

	visit[start.r][start.c] = true;
	queue[tail++] = start;

	while (head != tail)
	{
		Node now = queue[head++];

		if (head == MAX_QUEUE)
		{
			head = 0;
		}

		if ((now.r == end.r) && (now.c == end.c))
		{
			return now.dist;
		}

		// 4방향 탐색
		for (register int d = 0; d < MAX_DIR; d++)
		{
			int dr = now.r + directR[d];
			int dc = now.c + directC[d];

			// 가구일 경우 이동 불가
			if (map[dr][dc] == 'x')
			{
				continue;
			}

			// 이미 방문했을 경우 이동 불가
			if (visit[dr][dc])
			{
				continue;
			}

			visit[dr][dc] = true;
			queue[tail++] = { dr, dc, now.dist + 1 };

			if (tail == MAX_QUEUE)
			{
				tail = 0;
			}
		}
	}

	return INF;
}

void dfs(int pos, int dist, int level)
{
	// 이미 정답의 가능성이 없는 경우
	if (ans <= dist)
	{
		return;
	}

	// 모든 더러운 칸을 방문했을 경우
	if (level == dirtyCnt)
	{
		ans = dist;

		return;
	}

	// 가능한 칸 방문
	for (register int i = 1; i <= dirtyCnt; i++)
	{
		// 이미 청소한 칸은 방문할 필요 없음
		if (isCleaned[i])
		{
			continue;
		}

		isCleaned[i] = true;

		dfs(i, dist + distMap[pos][i], level + 1);

		isCleaned[i] = false;
	}

	return;
}

void solve(void)
{
	while (true)
	{
		initBefore();

		scanf("%d %d", &W, &H);

		if ((W == 0) && (H == 0))
		{
			break;
		}

		for (register int r = 1; r <= H; r++)
		{
			for (register int c = 1; c <= W; c++)
			{
				scanf(" %c", &map[r][c]);

				// 로봇의 시작 위치 기록
				if (map[r][c] == 'o')
				{
					dirtyList[START_POS] = { r, c, START_DIST };
				}
				// 더러운 칸일 경우 위치 기록
				else if (map[r][c] == '*')
				{
					dirtyList[++dirtyCnt] = { r, c, START_DIST };
				}
			}
		}

		initAfter();

		// 1. 각 칸 사이의 거리를 모두 계산 : BFS
		for (register int r = 0; r <= dirtyCnt; r++)
		{
			// 중복되는 경우는 제외
			for (register int c = r + 1; c <= dirtyCnt; c++)
			{
				// 각 칸의 거리 구하기
				int ret = bfs(r, c);

				// 양쪽 모두에 거리 기록
				// INF일 경우에도 그대로 기록
				distMap[r][c] = ret;
				distMap[c][r] = ret;
			}
		}

		// 2. 거리 정보로 가능한 모든 경우 탐색 : DFS
		dfs(START_POS, START_DIST, START_LEVEL);

		// int debug = 1;

		if (ans == INF)
		{
			ans = -1;
		}

		printf("%d\n", ans);
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	solve();

	return 0;
}
