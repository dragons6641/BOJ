/*
14226 이모티콘
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_S 1000
#define MAX_TIME (MAX_S * MAX_S)
#define MAX_QUEUE (MAX_S * 10)
#define START_TIME 0
#define START_CLIPBOARD 0
#define START_SCREEN 1

struct Node
{
	int time;
	int clipboard;
	int screen;
};

int head = 0;
int tail = 1;
// 해당 상태에 도달하는 최소 시간 표시
// R : clipboard, C : screen
bool visit[MAX_S * 2 + 1][MAX_S * 2 + 1] = { 0, };
Node queue[MAX_QUEUE] = { {START_TIME, START_CLIPBOARD, START_SCREEN}, };

void init(void)
{
	/*
	for (int r = 0; r <= MAX_S; r++)
	{
		for (int c = 0; c <= MAX_S; c++)
		{
			visit[r][c] = MAX_TIME;
		}
	}

	// visit[START_CLIPBOARD][START_SCREEN] = START_TIME;
	*/

	visit[START_CLIPBOARD][START_SCREEN] = true;

	return;
}

int bfs(int target)
{
	while (head != tail)
	{
		Node now = queue[head++];

		if (head == MAX_QUEUE)
		{
			head = 0;
		}

		// 1. 화면에 있는 이모티콘을 모두 복사해서 클립보드에 저장한다.
		if (now.screen > 0)
		{
			if (visit[now.screen][now.screen] == false)
			{
				visit[now.screen][now.screen] = true;

				queue[tail++] = { now.time + 1, now.screen, now.screen };
			}
		}

		// 2. 클립보드에 있는 모든 이모티콘을 화면에 붙여넣기 한다.
		if ((now.clipboard > 0) && (now.screen + now.clipboard < target * 2))
		{
			if (now.screen + now.clipboard == target)
			{
				return now.time + 1;
			}

			if (visit[now.clipboard][now.screen + now.clipboard] == false)
			{
				visit[now.clipboard][now.screen + now.clipboard] = true;

				queue[tail++] = { now.time + 1, now.clipboard, now.screen + now.clipboard };

				if (tail == MAX_QUEUE)
				{
					tail = 0;
				}
			}
		}

		// 3. 화면에 있는 이모티콘 중 하나를 삭제한다.
		if (now.screen > 0)
		{
			if (now.screen - 1 == target)
			{
				return now.time + 1;
			}

			if (visit[now.clipboard][now.screen - 1] == false)
			{
				visit[now.clipboard][now.screen - 1] = true;

				queue[tail++] = { now.time + 1, now.clipboard, now.screen - 1 };

				if (tail == MAX_QUEUE)
				{
					tail = 0;
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
	// freopen("input3.txt", "r", stdin);
	// freopen("input4.txt", "r", stdin);

	// setbuf(stdout, NULL);

	int S;
	int ans;

	scanf("%d", &S);

	init();

	ans = bfs(S);

	printf("%d\n", ans);

	return 0;
}
