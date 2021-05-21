/*
Pro입문 4주차 Problem H 보물섬
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_R 50
#define MAX_C 50
#define MAX_DIR 4
#define MAX_QUEUE (MAX_R * MAX_C * MAX_DIR)

struct Node
{
	int r;
	int c;
	int level;
};

int height;
int width;
int directR[MAX_DIR] = {-1, 1, 0, 0};
int directC[MAX_DIR] = {0, 0, -1, 1};
char map[MAX_R][MAX_C + 1] = { 0, };
char visit[MAX_R][MAX_C + 1] = { 0, };

void input(void)
{
	scanf("%d %d", &height, &width);

	for (int r = 0; r < height; r++)
	{
		scanf("%s", &map[r]);
	}

	return;
}

int bfs(int startR, int startC)
{
	int head = 0;
	int tail = 1;
	// 처음 시작점 큐에 넣는다
	Node queue[MAX_QUEUE] = { {startR, startC, 0} };

	// 큐에 넣으면 반드시 방문 표시!
	visit[startR][startC] = 'Y';

	while (true)
	{
		if (head == tail)
		{
			return queue[tail - 1].level;
		}

		Node now = queue[head++];

		for (int d = 0; d < MAX_DIR; d++)
		{
			int dr = now.r + directR[d];
			int dc = now.c + directC[d];

			if ((dr < 0) || (dc < 0) || (dr >= height) || (dc >= width))
			{
				continue;
			}

			if ((map[dr][dc] == 'W') || (visit[dr][dc] == 'Y'))
			{
				continue;
			}

			visit[dr][dc] = 'Y';
			queue[tail++] = { dr, dc, now.level + 1 };
		}
	}

	return -1;
}

void init(void)
{
	for (int r = 0; r < height; r++)
	{
		for (int c = 0; c < width; c++)
		{
			visit[r][c] = 'N';
		}
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);
	// freopen("input3.txt", "r", stdin);
	// freopen("input4.txt", "r", stdin);
	// freopen("input5.txt", "r", stdin);
	// freopen("input6.txt", "r", stdin);

	setbuf(stdout, NULL);

	int ans = 0;
	int ret;

	input();

	for (int r = 0; r < height; r++)
	{
		for (int c = 0; c < width; c++)
		{
			if (map[r][c] == 'L')
			{
				init();

				ret = bfs(r, c);

				if (ans < ret)
				{
					ans = ret;
				}
			}
		}
	}

	printf("%d\n", ans);

	return 0;
}
