#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 10000
#define MAX_A MAX_N
#define MAX_B MAX_N
#define MAX_QUEUE MAX_N
#define DIGIT 10

struct Node
{
	int num;
	int time;
	int prev;
	char cmd;
};

int T;
int A;
int B;
bool visit[MAX_N] = { 0, };
Node queue[MAX_QUEUE] = { 0, 0, 0, 0 };

void traverse(int now)
{
	if (now == 0)
	{
		return;
	}

	traverse(queue[now].prev);

	printf("%c", queue[now].cmd);

	return;
}

void printAns(int now)
{
	traverse(now);

	printf("\n");

	return;
}

void bfs(void)
{
	register int head = 0;
	register int tail = 0;

	visit[A] = true;
	queue[tail++] = { A, 0, -1, '\0' };

	while (head != tail)
	{
		int tmpNum;
		int nextNum;
		Node now = queue[head];

		if (now.num == B)
		{
			// int debug = 1;

			printAns(head);

			break;
		}

		// 4가지 명령 수행
		// 1. D
		nextNum = (now.num * 2) % MAX_N;

		if (!visit[nextNum])
		{
			visit[nextNum] = true;
			queue[tail++] = { nextNum, now.time + 1, head, 'D' };

			if (tail == MAX_QUEUE)
			{
				tail = 0;
			}
		}

		// 2. S
		nextNum = now.num - 1;

		if (nextNum == -1)
		{
			nextNum = MAX_N - 1;
		}

		if (!visit[nextNum])
		{
			visit[nextNum] = true;
			queue[tail++] = { nextNum, now.time + 1, head, 'S' };

			if (tail == MAX_QUEUE)
			{
				tail = 0;
			}
		}

		// 3. L
		tmpNum = (int)(now.num / (MAX_N / DIGIT));
		nextNum = (((now.num * DIGIT) + tmpNum) % MAX_N);

		if (!visit[nextNum])
		{
			visit[nextNum] = true;
			queue[tail++] = { nextNum, now.time + 1, head, 'L' };

			if (tail == MAX_QUEUE)
			{
				tail = 0;
			}
		}

		// 4. R
		tmpNum = now.num % DIGIT;
		nextNum = ((int)(now.num / DIGIT) + (tmpNum * (MAX_N / DIGIT)));

		if (!visit[nextNum])
		{
			visit[nextNum] = true;
			queue[tail++] = { nextNum, now.time + 1, head, 'R' };

			if (tail == MAX_QUEUE)
			{
				tail = 0;
			}
		}

		head++;

		if (head == MAX_QUEUE)
		{
			head = 0;
		}
	}

	return;
}

void init(void)
{
	for (register int i = 0; i < MAX_N; i++)
	{
		visit[i] = false;
	}

	return;
}

void solve(void)
{
	scanf("%d", &T);

	for (register int testCase = 1; testCase <= T; testCase++)
	{
		scanf("%d %d", &A, &B);

		bfs();

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
