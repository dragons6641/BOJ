/*
A2 토마토(고)
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_R 1000
#define MAX_C 1000
#define MAX_QUEUE (MAX_R * MAX_C)
#define MAX_DIR 4

struct Node
{
	int r;
	int c;
	int day;
};

int M;
int N;
int head = 0;
int tail = 0;
// 아직 익지 않은 토마토의 수
int cnt = 0;
int ans = 0;
int directR[MAX_DIR] = { -1 ,1, 0, 0 };
int directC[MAX_DIR] = { 0, 0, -1, 1 };
int map[MAX_R][MAX_C] = { 0, };
Node queue[MAX_QUEUE] = { {0, 0, 0}, };

void input(void)
{
	scanf("%d %d", &M, &N);

	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < M; c++)
		{
			scanf("%d", &map[r][c]);

			if (map[r][c] == 0)
			{
				cnt++;
			}
			else if (map[r][c] == 1)
			{
				queue[tail++] = { r, c, 0 };
			}
		}
	}

	return;
}

void bfs(void)
{
	while (head != tail)
	{
		Node now = queue[head++];

		if (ans < now.day)
		{
			ans = now.day;
		}

		for (int d = 0; d < MAX_DIR; d++)
		{
			int dr = now.r + directR[d];
			int dc = now.c + directC[d];

			if ((dr < 0) || (dc < 0) || (dr >= N) || (dc >= M))
			{
				continue;
			}

			if (map[dr][dc] != 0)
			{
				continue;
			}

			cnt--;
			map[dr][dc] = now.day + 1;
			queue[tail++] = { dr, dc, now.day + 1 };
		}
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);
	// freopen("input3.txt", "r", stdin);

	// setbuf(stdout, NULL);

	input();

	if (cnt == 0)
	{
		printf("0\n");

		return 0;
	}

	bfs();

	if (cnt == 0)
	{
		printf("%d\n", ans);
	}
	else
	{
		printf("-1\n");
	}

	return 0;
}
