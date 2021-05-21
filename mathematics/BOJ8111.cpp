#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_T 1000
#define MAX_N 20000
#define START_N 1
#define END_N 0
#define DIGIT 10
#define MAX_QUEUE MAX_N

struct Node
{
	int num;
	int prev;
	// 0이면 false, 1이면 true
	bool isOne;
};

int T;
int N;
bool visit[MAX_N] = { 0, };
Node queue[MAX_QUEUE] = { 0, };

void init(void)
{
	for (register int i = 0; i < N; i++)
	{
		visit[i] = false;
	}

	return;
}

void traverse(int pos)
{
	if (pos == -1)
	{
		return;
	}

	traverse(queue[pos].prev);

	if (queue[pos].isOne)
	{
		printf("1");
	}
	else
	{
		printf("0");
	}

	return;
}

void printAns(int pos)
{
	traverse(pos);

	printf("\n");

	return;
}

void bfs(void)
{
	// 1은 예외처리
	if (N == START_N)
	{
		printf("%d\n", START_N);

		return;
	}

	register int head = 0;
	register int tail = 0;

	visit[START_N] = true;
	queue[tail++] = { START_N, -1, true };

	while (head != tail)
	{
		int nextNum;
		Node now = queue[head];

		if (now.num == END_N)
		{
			printAns(head);
		}

		// 1. 뒤에 0 붙이기
		nextNum = (now.num * DIGIT) % N;

		if (!visit[nextNum])
		{
			visit[nextNum] = true;
			queue[tail++] = { nextNum, head, false };

			if (tail == MAX_QUEUE)
			{
				tail = 0;
			}
		}

		// 2. 뒤에 1 붙이기
		nextNum = (nextNum + 1) % N;

		if (!visit[nextNum])
		{
			visit[nextNum] = true;
			queue[tail++] = { nextNum, head, true };

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

void solve(void)
{
	scanf("%d", &T);

	for (register int testCase = 1; testCase <= T; testCase++)
	{
		scanf("%d", &N);

		init();

		bfs();
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	solve();

	return 0;
}
