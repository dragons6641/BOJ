#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_R 100
#define MAX_C 100
#define MAX_DIR 4
#define HEAP_SIZE (MAX_R * MAX_C * MAX_DIR)
#define INF (MAX_R * MAX_C * MAX_DIR)

struct Node
{
	int r;
	int c;
	// 빛의 방향
	int dir;
	// 현재까지 사용한 거울의 갯수
	int cnt;
};

// cols
int W;
// rows
int H;
int lastnode = 0;
bool flag = false;
int directR[MAX_DIR] = { -1, 1, 0, 0 };
int directC[MAX_DIR] = { 0, 0, -1, 1 };
// Barrier!
// 1부터 N까지 사용
char map[MAX_R + 2][MAX_C + 2] = { 0, };
// Barrier!
// 1부터 N까지 사용
int visit[MAX_R + 2][MAX_C + 2][MAX_DIR] = { 0, };
Node start = {0, 0, 0, 0};
Node end = {0, 0, 0, 0};
// Min Heap
Node heap[HEAP_SIZE];

bool comp(Node a, Node b)
{
	return (a.cnt < b.cnt);
}

int Heap_Push_Minheap(Node *heap, int size, int *lastnode, Node d)
{
	int n, p;
	Node temp;

	if (*lastnode == size) return 0;

	heap[++(*lastnode)] = d;

	n = *lastnode; p = n / 2;

	while (p > 0)
	{
		if (comp(heap[n], heap[p]))
		{
			temp = heap[n];
			heap[n] = heap[p];
			heap[p] = temp;
			n = p; p = n / 2;
		}
		else break;
	}

	return 1;
}

int Heap_Pop_Minheap(Node *heap, int *lastnode, Node *d)
{
	int n, c, lc, rc;
	Node temp;

	if (*lastnode == 0) return 0;

	*d = heap[1];
	heap[1] = heap[(*lastnode)--];

	n = 1; lc = 2; rc = 3;
	while (lc <= *lastnode)
	{
		if (*lastnode == lc) c = lc;
		else c = (comp(heap[lc], heap[rc])) ? (lc) : (rc);

		if (comp(heap[c], heap[n]))
		{
			temp = heap[c];
			heap[c] = heap[n];
			heap[n] = temp;
			n = c; lc = n * 2; rc = lc + 1;
		}
		else break;
	}

	return 1;
}

void inputData(void)
{
	scanf("%d %d", &W, &H);

	for (register int r = 1; r <= H; r++)
	{
		for (register int c = 1; c <= W; c++)
		{
			scanf(" %c", &map[r][c]);

			if (map[r][c] == 'C')
			{
				if (!flag)
				{
					flag = true;

					start = { r, c, 0, 0 };
				}
				else
				{
					end = { r, c, 0, 0 };
				}
			}
		}
	}

	return;
}

void init(void)
{
	for (register int r = 0; r <= H + 1; r++)
	{
		map[r][0] = '*';
		map[r][W + 1] = '*';
	}

	for (register int c = 0; c <= W + 1; c++)
	{
		map[0][c] = '*';
		map[H + 1][c] = '*';
	}

	for (register int r = 1; r <= H; r++)
	{
		for (register int c = 1; c <= W; c++)
		{
			for (register int d = 0; d < MAX_DIR; d++)
			{
				visit[r][c][d] = INF;
			}
		}
	}

	return;
}

bool checkPossible(int dir1, int dir2)
{
	if (dir1 + dir2 == 1)
	{
		return false;
	}
	else if (dir1 + dir2 == MAX_DIR + 1)
	{
		return false;
	}

	return true;
}

int bfs(void)
{
	Node now;

	// 4방향 모두 시작 상태로 heap push
	for (register int d = 0; d < MAX_DIR; d++)
	{
		start.dir = d;

		visit[start.r][start.c][start.dir] = start.cnt;
		Heap_Push_Minheap(heap, HEAP_SIZE, &lastnode, start);
	}

	// int Heap_Push_Minheap(Node *heap, int size, int *lastnode, Node d)

	while (lastnode > 0)
	{
		// int Heap_Pop_Minheap(Node *heap, int *lastnode, Node *d)
		Heap_Pop_Minheap(heap, &lastnode, &now);

		/*
		if ((now.r == 8) && (now.c == 2) && (now.dir == 2))
		{
			int debug = 1;
		}
		*/

		if ((now.r == end.r) && (now.c == end.c))
		{
			return now.cnt;
		}

		// 4방향 탐색
		for (register int d = 0; d < MAX_DIR; d++)
		{
			int dr = now.r + directR[d];
			int dc = now.c + directC[d];
			// 방향이 같으면 그대로, 달라지면 1 증가
			int nextCnt = ((now.dir == d) ? now.cnt : now.cnt + 1);
			bool ret = checkPossible(now.dir, d);

			// 정 반대 방향으로는 이동 불가
			if (!ret)
			{
				continue;
			}

			if (map[dr][dc] == '*')
			{
				continue;
			}

			if (visit[dr][dc][d] <= nextCnt)
			{
				continue;
			}

			visit[dr][dc][d] = nextCnt;
			Heap_Push_Minheap(heap, HEAP_SIZE, &lastnode, {dr, dc, d, nextCnt});
		}
	}

	return -1;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);	// 3
	// freopen("input2.txt", "r", stdin);	// 1
	// freopen("input3.txt", "r", stdin);	// 1
	// freopen("input4.txt", "r", stdin);	// 1
	// freopen("input5.txt", "r", stdin);	// 1
	// freopen("input6.txt", "r", stdin);	// 2
	// freopen("input7.txt", "r", stdin);	// 2
	// freopen("input8.txt", "r", stdin);	// 2
	// freopen("input9.txt", "r", stdin);	// 3
	// freopen("input10.txt", "r", stdin);	// 6
	// freopen("input11.txt", "r", stdin);	// 4
	// freopen("input12.txt", "r", stdin);	// 2
	// freopen("input13.txt", "r", stdin);	// 1
	// freopen("input14.txt", "r", stdin);	// 27
	// freopen("input15.txt", "r", stdin);	// 10
	// freopen("input16.txt", "r", stdin);	// 8
	// freopen("input17.txt", "r", stdin);	// 24
	// freopen("input18.txt", "r", stdin);	// 9

	inputData();

	init();

	int ans = bfs();

	printf("%d\n", ans);

	return 0;
}
