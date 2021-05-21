#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_R 2
#define MAX_C 100000
#define MAX_QUEUE (MAX_R * MAX_C)
#define MAX_DIR 3
#define START_R 0
#define START_C 0
#define START_TIME 0

struct Node
{
	int r;
	int c;
	int time;
};

// cols
int N;
// 점프력
int K;
int directR[MAX_DIR] = { 0, 0, 1 };
int directC[MAX_DIR] = { 1, -1, 0 };
// 0 or 1
bool ans = false;
bool map[MAX_R][MAX_C] = { 0, };
bool visit[MAX_R][MAX_C] = { 0, };
Node queue[MAX_QUEUE] = { 0, };

void inputData(void)
{
	int M;

	scanf("%d %d", &N, &K);

	directC[MAX_DIR - 1] = K;

	for (register int r = 0; r < MAX_R; r++)
	{
		for (register int c = 0; c < N; c++)
		{
			scanf("%1d", &M);

			if (M == 1)
			{
				map[r][c] = true;
			}
		}
	}

	return;
}

void bfs(void)
{
	register int head = 0;
	register int tail = 0;

	visit[START_R][START_C] = true;
	queue[tail++] = { START_R, START_C, START_TIME };

	while (head != tail)
	{
		Node now = queue[head++];

		/*
		if (head == MAX_QUEUE)
		{
			head = 0;
		}
		*/

		if (now.c >= N)
		{
			ans = true;

			break;
		}

		// 1. 한 칸 앞으로 이동한다. 예를 들어, 현재 있는 칸이 i번 칸이면, i+1번 칸으로 이동한다.
		// 2. 한 칸 뒤로 이동한다. 예를 들어, 현재 있는 칸이 i번 칸이면, i-1번 칸으로 이동한다.
		// 3. 반대편 줄로 점프한다. 이때, 원래 있던 칸보다 k칸 앞의 칸으로 이동해야 한다. 예를 들어, 현재 있는 칸이 왼쪽 줄의 i번 칸이면, 오른쪽 줄의 i+k번 칸으로 이동해야 한다.
		for (register int d = 0; d < MAX_DIR; d++)
		{
			int dr = (now.r + directR[d]) % MAX_R;
			int dc = now.c + directC[d];

			if (dc <= now.time)
			{
				continue;
			}

			if (dc < N && (!map[dr][dc] || visit[dr][dc]))
			{
				continue;
			}

			visit[dr][dc] = true;
			queue[tail++] = { dr, dc, now.time + 1 };

			/*
			if (tail == MAX_QUEUE)
			{
				tail = 0;
			}
			*/
		}
	}

	return;
}

void printAns(void)
{
	if (ans)
	{
		printf("1\n");
	}
	else
	{
		printf("0\n");
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);

	inputData();

	bfs();

	// printAns();

	printf("%d\n", ans);

	return 0;
}
