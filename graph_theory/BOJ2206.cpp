/*
2206 벽 부수고 이동하기
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_R 1000
#define MAX_C 1000
#define MAX_K 1
#define MAX_DIR 4
#define MAX_QUEUE (MAX_R * MAX_C)
#define START_R 1
#define START_C 1
#define START_K 0
#define START_DIST 1

struct Node
{
	int r;
	int c;
	// 벽을 부순 횟수
	int k;
	// 이동 거리
	int dist;
};

int N;
int M;
int directR[MAX_DIR] = { -1, 1, 0, 0 };
int directC[MAX_DIR] = { 0, 0, -1, 1 };
// Barrier
// 1부터 1000까지 사용
int map[MAX_R + 2][MAX_C + 2] = { 0, };
// Barrier
// 1부터 1000까지 사용
int visit[MAX_R + 2][MAX_C + 2][MAX_K + 2] = { 0, };
Node queue[MAX_QUEUE] = { {0, 0, 0, 0}, };

void input(void)
{
	scanf("%d %d", &N, &M);

	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= M; c++)
		{
			scanf("%1d", &map[r][c]);
		}
	}

	return;
}

void init(void)
{
	for (int r = 0; r <= N + 1; r++)
	{
		map[r][0] = -1;
		map[r][M + 1] = -1;
	}

	for (int c = 0; c <= M + 1; c++)
	{
		map[0][c] = -1;
		map[N + 1][c] = -1;
	}

	return;
}

int bfs(void)
{
	int head = 0;
	int tail = 0;

	queue[tail++] = { START_R, START_C, START_K, START_DIST };

	while (head != tail)
	{
		Node now = queue[head++];

		if (head == MAX_QUEUE)
		{
			head = 0;
		}

		// 가중치가 다를 때는 큐에서 빼면서 방문 표시!
		

		// 도착했다면
		if ((now.r == N) && (now.c == M))
		{
			return now.dist;
		}

		for (int d = 0; d < MAX_DIR; d++)
		{
			int dr = now.r + directR[d];
			int dc = now.c + directC[d];

			if ((dr <= 0) || (dc <= 0) || (dr > N) || (dc > M))
			{
				continue;
			}

			// 벽을 부쉈는지까지 고려해야 함
			if (visit[dr][dc][now.k] == 1)
			{
				continue;
			}

			// 일반 공간이라면
			if (map[dr][dc] == 0)
			{
				// enqueue 전에 방문 표시
				visit[dr][dc][now.k] = 1;

				// 그냥 이동
				queue[tail++] = { dr, dc, now.k, now.dist + 1 };

				if (tail == MAX_QUEUE)
				{
					tail = 0;
				}
			}
			// 벽이라면
			else if (map[dr][dc] == 1)
			{
				// 부술 수 있을 경우
				if (now.k == 0)
				{
					// enqueue 전에 방문 표시
					visit[dr][dc][now.k + 1] = 1;

					// 부수고 이동
					queue[tail++] = { dr, dc, now.k + 1, now.dist + 1 };

					if (tail == MAX_QUEUE)
					{
						tail = 0;
					}
				}
				// 부술 수 없을 경우
				else if (now.k == 1)
				{
					// 이동 불가
					continue;
				}
			}
		}
	}

	return -1;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);

	setbuf(stdout, NULL);

	input();

	init();

	printf("%d\n", bfs());

	return 0;
}
