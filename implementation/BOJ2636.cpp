/*
Pro입문 4주차 Problem G 치즈
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_R 100
#define MAX_C 100
#define MAX_DIR 4
#define MAX_QUEUE (MAX_R * MAX_C)

struct Node
{
	int r;
	int c;
};

int width;
int height;
int tn = 0;
int leftCnt = 0;
int map[(int)(MAX_R * 1.1)][(int)(MAX_C * 1.1)];
Node teduri[(int)(MAX_QUEUE * 1.1)];

void init(void)
{
	scanf("%d %d", &height, &width);

	for (int r = 0; r < height; r++)
	{
		for (int c = 0; c < width; c++)
		{
			scanf("%d", &map[r][c]);

			if (map[r][c] == 1)
			{
				leftCnt++;
			}
		}
	}

	return;
}

void bfs(void)
{
	int head = 0;
	int tail = 1;
	int visit[(int)(MAX_R * 1.1)][(int)(MAX_C * 1.1)] = { 0, };
	// teduri에 값 채우기
	Node queue[(int)(MAX_QUEUE * 1.1)] = { {0, 0}, };

	int direct[MAX_DIR][2] =
	{
		-1, 0,
		1, 0,
		0, -1,
		0, 1
	};

	while (head != tail)
	{
		Node now = queue[head++];
		{
			for (int t = 0; t < MAX_DIR; t++)
			{
				int dr = now.r + direct[t][0];
				int dc = now.c + direct[t][1];

				if ((dr < 0) || (dc < 0) || (dr >= height) || (dc >= width))
				{
					continue;
				}

				if (visit[dr][dc] == 1)
				{
					continue;
				}

				visit[dr][dc] = 1;

				if ((map[dr][dc] == 1))
				{
					teduri[tn++] = { dr, dc };

					continue;
				}

				queue[tail++] = { dr, dc };
			}
		}
	}
}

void removeTeduri(void)
{
	// 테두리를 모두 제거
	for (int t = 0; t < tn; t++)
	{
		int dr = teduri[t].r;
		int dc = teduri[t].c;

		map[dr][dc] = 0;
		leftCnt--;
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	setbuf(stdout, NULL);

	init();

	int days = 0;

	while (true)
	{
		days++;
		tn = 0;

		// 1. 테두리 구하기
		bfs();

		// 2. 테두리 제거
		removeTeduri();

		// 3. 남아있는 치즈 확인
		if (leftCnt == 0)
		{
			printf("%d\n", days);
			printf("%d\n", tn);

			break;
		}
	}

	return 0;
}
