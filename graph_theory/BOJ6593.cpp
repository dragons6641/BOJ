#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_L 30
#define MAX_R 30
#define MAX_C 30
#define MAX_DIR 6
#define MAX_QUEUE (MAX_L * MAX_R * MAX_C)

struct Node
{
	int l;
	int r;
	int c;
	int time;
};

int L;
int R;
int C;
int directL[MAX_DIR] = { -1, 1, 0, 0, 0, 0 };
int directR[MAX_DIR] = { 0, 0, -1 ,1 ,0 ,0 };
int directC[MAX_DIR] = { 0, 0, 0 ,0, -1, 1 };
// Barrier!
// 1부터 30까지 사용
char map[MAX_L + 2][MAX_R + 2][MAX_C + 2] = { 0, };
// Barrier!
// 1부터 30까지 사용
bool visit[MAX_L + 2][MAX_R + 2][MAX_C + 2] = { 0, };
Node start = { 0, 0, 0, 0 };
Node end = { 0, 0, 0, 0 };
Node queue[MAX_QUEUE + 1] = { {0, 0, 0, 0}, };

bool inputData(void)
{
	scanf("%d %d %d", &L, &R, &C);

	if ((L == 0) && (R == 0) && (C == 0))
	{
		// 입력 그만
		return false;
	}

	for (register int l = 1; l <= L; l++)
	{
		for (register int r = 1; r <= R; r++)
		{
			for (register int c = 1; c <= C; c++)
			{
				scanf(" %c", &map[l][r][c]);

				if (map[l][r][c] == 'S')
				{
					start = { l, r, c, 0 };
				}
				else if (map[l][r][c] == 'E')
				{
					end = { l, r, c, 0 };
				}
			}
		}
	}

	// 입력 계속
	return true;
}

int bfs(void)
{
	register int head = 0;
	register int tail = 0;

	visit[start.l][start.r][start.c] = true;
	queue[tail++] = start;

	while (head != tail)
	{
		Node now = queue[head++];

		if (head == MAX_QUEUE)
		{
			head = 0;
		}

		if ((now.l == end.l) && (now.r == end.r) && (now.c == end.c))
		{
			return now.time;
		}

		for (register int d = 0; d < MAX_DIR; d++)
		{
			int dl = now.l + directL[d];
			int dr = now.r + directR[d];
			int dc = now.c + directC[d];

			// 정육면체 밖이거나 이동 불가능한 칸일 경우
			if ((map[dl][dr][dc] == '\0') || (map[dl][dr][dc] == '#'))
			{
				continue;
			}

			// 이미 방문한 곳일 경우
			if (visit[dl][dr][dc])
			{
				continue;
			}

			visit[dl][dr][dc] = true;
			queue[tail++] = { dl, dr, dc, now.time + 1 };
		}
	}

	return -1;
}

void print(int n)
{
	if (n == -1)
	{
		printf("Trapped!\n");
	}
	else
	{
		printf("Escaped in %d minute(s).\n", n);
	}

	return;
}

void init(void)
{
	for (register int l = 1; l <= L; l++)
	{
		for (register int r = 1; r <= R; r++)
		{
			for (register int c = 1; c <= C; c++)
			{
				map[l][r][c] = '\0';
				visit[l][r][c] = false;
			}
		}
	}

	return;
}

void solve(void)
{
	while (inputData())
	{
		// int debug = 1;

		int ans = bfs();

		print(ans);

		init();
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	solve();

	return 0;
}
