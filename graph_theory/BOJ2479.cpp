/*
Pro입문 4주차 Problem D 경로 찾기
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 1000
#define MAX_K 30
#define MAX_QUEUE (MAX_N * MAX_N)

struct Node
{
	int num;
	int level;
	int parent;
} queue[MAX_QUEUE];

int N;
int K;
int start;
int end;
int head = 0;
int tail = 0;
int visit[MAX_QUEUE + 1] = { 0, };
char map[(int)(MAX_N * 1.1)][(int)(MAX_N * 1.1)] = { 0, }; // 1.15 MB 메모리 사용

void init(void)
{
	int code[(int)(MAX_N * 1.1)] = { 0, };
	char line[MAX_K + 10] = { 0, };

	scanf("%d %d", &N, &K);

	for (int i = 1; i <= N; i++)
	{
		scanf("%s", &line);

		int num = 0;

		// 호너의 메소드
		for (int x = 0; line[x]; x++)
		{
			num = num * 2 + (line[x] - '0');
		}

		code[i] = num;
	}

	scanf("%d %d", &start, &end);

	// 해밍 거리
	for (int a = 1; a <= N; a++)
	{
		for (int b = a + 1; b <= N; b++)
		{
			int ret = code[a] ^ code[b];
			int gret = (ret - 1) & ret;

			if (gret == 0)
			{
				map[a][b] = 1;
				map[b][a] = 1;
			}
		}
	}

	return;
}

void persuit(int now)
{
	if (now == -1)
	{
		return;
	}

	persuit(queue[now].parent);

	printf("%d ", queue[now].num);

	return;
}

void bfs(void)
{
	queue[tail++] = { start, 0, -1 };
	visit[start] = 1;

	while (head != tail)
	{
		Node now = queue[head++];

		if (head == MAX_QUEUE)
		{
			head = 0;
		}

		for (int i = 1; i <= N; i++)
		{
			if (map[now.num][i] == 0)
			{
				continue;
			}

			if (visit[i] == 0)
			{
				queue[tail++] = { i, now.level + 1, head - 1 };
				visit[i] = 1;

				if (tail == MAX_QUEUE)
				{
					tail = 0;
				}
			}

			if (i == end)
			{
				persuit(tail - 1);

				printf("\n");

				return;
			}
		}
	}

	printf("-1\n");

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);
	// freopen("input3.txt", "r", stdin);

	setbuf(stdout, NULL);

	init();

	bfs();

	return 0;
}
