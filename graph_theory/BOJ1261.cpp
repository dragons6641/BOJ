/*
1261 알고스팟
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_R 100
#define MAX_C 100
#define START_R 1
#define START_C 1
#define MAX_DIR 4
#define MAX_DIST (MAX_R + MAX_C)
#define MAX_AREA ((MAX_R / 2) * (MAX_C / 2))
#define MAX_QUEUE (MAX_R * MAX_C)

struct Node
{
	int r;
	int c;
	int dist;
};

int M;
int N;
// 영역 갯수
int areaCnt = 0;
int head = 0;
int tail = 1;
int directR[MAX_DIR] = { -1, 1, 0, 0 };
int directC[MAX_DIR] = { 0, 0, -1, 1 };
// (1, 1)에서 다른 영역으로 가는 거리
// 1부터 시작
int distList[MAX_AREA + 1] = { 0, };
// Barrier
// 1부터 100까지 사용
// 양수 : 해당 번호 영역
// -1 : 벽
// -2 : 테두리
int map[MAX_R + 2][MAX_C + 2] = { 0, };
// 각 영역별 거리
// 1부터 시작
int distMap[MAX_AREA + 1][MAX_AREA + 1] = { 0, };
// 각 영역 탐색 시작점 저장
// 1부터 시작
Node startPos[MAX_AREA + 1] = { {0, 0, 0}, };
Node queue[MAX_QUEUE] = { {0, 0, 0}, };

void input(void)
{
	scanf("%d %d", &M, &N);

	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= M; c++)
		{
			scanf("%1d", &map[r][c]);

			// 벽은 -1로 치환
			if (map[r][c] == 1)
			{
				map[r][c] = -1;
			}
		}
	}

	return;
}

void initMap(void)
{
	for (int r = 0; r <= N + 1; r++)
	{
		map[r][0] = -2;
		map[r][M + 1] = -2;
	}

	for (int c = 0; c <= M + 1; c++)
	{
		map[0][c] = -2;
		map[N + 1][c] = -2;
	}

	return;
}

void initDist(void)
{
	for (int i = 2; i <= areaCnt; i++)
	{
		distList[i] = MAX_DIST;
	}

	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= M; c++)
		{
			distMap[r][c] = MAX_DIST;
		}
	}

	distMap[START_R][START_C] = 0;

	return;
}

/*
void divideArea(int nowR, int nowC)
{
	// 4방향 탐색
	for (int d = 0; d < MAX_DIR; d++)
	{
		int dr = nowR + directR[d];
		int dc = nowC + directC[d];

		if ((dr <= 0) || (dc <= 0) || (dr > N) || (dc > M))
		{
			continue;
		}

		// 벽이거나 지도 바깥이면 이동 불가
		// 이미 영역 할당된 곳이어도 이동 불가
		if (map[dr][dc] != 0)
		{
			continue;
		}

		map[dr][dc] = areaCnt;

		divideArea(dr, dc);
	}

	return;
}

// index번째 계산
// 자신의 번호 뒤부터 계산하면 된다!
void calcDist(int index)
{
	// 같은 영역에 있다면
	if (map[START_R][START_C] == map[N][M])
	{
		// 계산할 필요 없다!
		return;
	}

	int head = 0;
	int tail = 0;

	queue[tail++] = {startPos[index].r, startPos[index].c, 0};

	while (head != tail)
	{
		Node now = queue[head++];

		if (head == MAX_QUEUE)
		{
			head = 0;
		}

		// 4방향 탐색
		for (int d = 0; d < MAX_DIR; d++)
		{
			int dr = now.r + directR[d];
			int dc = now.c + directC[d];

			if ((dr <= 0) || (dc <= 0) || (dr > N) || (dc > M))
			{
				continue;
			}

			// 지도 바깥이면 이동 불가
			if (map[dr][dc] == -2)
			{
				continue;
			}
			// 벽이면
			else if (map[dr][dc] == -1)
			{
				// 이동하고 거리 1 추가
				queue[tail++] = { dr, dc, now.dist + 1 };
			}
			// 이미 탐색한 지역도 이동 불가
			// 자신보다 번호가 낮은 영역이면 이동 불가
			else if (map[dr][dc] < index)
			{
				continue;
			}
			// 같은 영역이면
			else if (map[dr][dc] == index)
			{
				// 이동은 하되 거리는 그대로
				queue[tail++] = { dr, dc, now.dist };
			}
			// 자신보다 번호가 높은 영역이면
			else if (map[dr][dc] > index)
			{
				// 최단거리 기록
				if (distMap[index][map[dr][dc]] > now.dist)
				{
					// 양쪽에 모두 기록
					distMap[index][map[dr][dc]] = now.dist;
					distMap[map[dr][dc]][index] = now.dist;
				}

				continue;
			}

			if (tail == MAX_QUEUE)
			{
				tail = 0;
			}
		}
	}

	return;
}

int dijkstra(void)
{
	// 같은 영역에 있다면
	if (map[START_R][START_C] == map[N][M])
	{
		// 벽 부술 필요 없다!
		return 0;
	}

	int visitCnt = 0;
	// 1부터 사용
	bool visit[MAX_AREA + 1] = { false, };

	while (true)
	{
		int minDist = MAX_DIST + 1;
		int minIndex = 0;

		// 아직 방문하지 않은 곳 중에서
		// 가장 거리가 짧은 곳 방문
		for (int i = 1; i <= areaCnt; i++)
		{
			if ((!visit[i]) && (minDist > distList[i]))
			{
				minDist = distList[i];
				minIndex = i;
			}
		}

		visit[minIndex] = true;
		visitCnt++;

		// 해당 인덱스와 연결되어 있는 영역의 거리 갱신
		// 기존 거리 VS 현재까지의 거리 + 목적지까지의 가중치
		for (int i = 1; i <= areaCnt; i++)
		{
			// 이동할 수 있고 거리 갱신이 가능하다면
			if ((distMap[minIndex][i] < MAX_DIST) && (distList[i] > distList[minIndex] + distMap[minIndex][i]))
			{
				distList[i] = distList[minIndex] + distMap[minIndex][i];
			}
		}

		// 모두 방문했다면
		if (visitCnt == areaCnt)
		{
			// 알고리즘 종료
			break;
		}
	}

	return distList[map[N][M]];
}
*/

int solve(void)
{
	bool visit[MAX_R + 2][MAX_C + 2] = { false, };

	while (true)
	{
		int minDist = MAX_DIST + 1;
		int minR = 0;
		int minC = 0;

		// 아직 방문하지 않은 곳 중에서
		// 가장 거리가 짧은 곳 방문
		for (int r = 1; r <= N; r++)
		{
			for (int c = 1; c <= M; c++)
			{
				if ((!visit[r][c]) && (minDist > distMap[r][c]))
				{
					minDist = distMap[r][c];
					minR = r;
					minC = c;
				}
			}
		}

		// 모두 방문했다면
		if (minDist == MAX_DIST + 1)
		{
			// 알고리즘 종료
			break;
		}

		visit[minR][minC] = true;

		// 해당 인덱스와 연결되어 있는 영역의 거리 갱신
		// 기존 거리 VS 현재까지의 거리 + 목적지까지의 가중치
		for (int d = 0; d < MAX_DIR; d++)
		{
			int dr = minR + directR[d];
			int dc = minC + directC[d];

			// 이동할 수 없다면 더 볼 필요 없다
			if ((dr <= 0) || (dc <= 0) || (dr > N) || (dc > M))
			{
				continue;
			}

			// 해당 칸으로 이동 가능하다면
			if (map[dr][dc] == 0)
			{
				// 거리 갱신이 가능하다면
				// 가중치는 0
				if (distMap[dr][dc] > distMap[minR][minC])
				{
					distMap[dr][dc] = distMap[minR][minC];
				}
			}
			// 해당 칸이 벽이라면
			else if (map[dr][dc] == -1)
			{
				// 거리 갱신이 가능하다면
				// 가중치는 1
				if (distMap[dr][dc] > distMap[minR][minC] + 1)
				{
					distMap[dr][dc] = distMap[minR][minC] + 1;
				}
			}
		}
	}

	return distMap[N][M];
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);
	// freopen("input3.txt", "r", stdin);

	setbuf(stdout, NULL);

	input();

	initMap();

	/*
	// 1. 영역 나누기
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= M; c++)
		{
			if (map[r][c] == 0)
			{
				areaCnt++;
				startPos[areaCnt].r = r;
				startPos[areaCnt].c = c;
				map[r][c] = areaCnt;

				divideArea(r, c);
			}
		}
	}

	initDist();

	// 2. 거리 구하기
	for (int i = 1; i <= areaCnt; i++)
	{
		calcDist(i);
	}

	// 3. 다익스트라
	printf("%d\n", dijkstra());
	*/

	initDist();

	// 바로 다익스트라
	printf("%d\n", solve());

	return 0;
}
