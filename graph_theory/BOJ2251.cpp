#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_A 200
#define MAX_B 200
#define MAX_C 200
#define MAX_QUEUE (MAX_A * MAX_B)
#define START_A 0
#define START_B 0
#define TARGET 0

struct Node
{
	int a;
	int b;
};

int A;
int B;
int C;
int arr[MAX_C + 1] = { 0, };
int trr[MAX_C + 1] = { 0, };
// 가능한 물의 양 기록
bool check[MAX_C + 1] = { 0, };
// A와 B에 따라 C는 자동으로 정해짐!
bool visit[MAX_A + 1][MAX_B + 1] = { 0, };
Node queue[MAX_QUEUE] = { 0, 0, 0 };

void mergeSort(int s, int e)
{
	if (s >= e)
	{
		return;
	}

	int m = (s + e) / 2;

	mergeSort(s, m);
	mergeSort(m + 1, e);

	int i = s;
	int j = m + 1;

	for (register int k = s; k <= e; k++)
	{
		if (j > e)
		{
			trr[k] = arr[i++];
		}
		else if (i > m)
		{
			trr[k] = arr[j++];
		}
		else if (arr[i] < arr[j])
		{
			trr[k] = arr[i++];
		}
		else
		{
			trr[k] = arr[j++];
		}
	}

	for (register int k = s; k <= e; k++)
	{
		arr[k] = trr[k];
	}

	return;
}

void bfs(void)
{
	int total = START_A + START_B + C;
	register int head = 0;
	register int tail = 0;

	visit[START_A][START_B] = true;
	queue[tail++] = {START_A, START_B};

	while (head != tail)
	{
		int curSum;
		int nextA;
		int nextB;
		Node now = queue[head++];

		if (head == MAX_QUEUE)
		{
			head = 0;
		}

		if (now.a == TARGET)
		{
			check[total - TARGET - now.b] = true;
		}

		// 한 물통이 비거나, 다른 한 물통이 가득 찰 때까지 물을 부을 수 있다.
		// 6가지 경우의 수
		// 1. A -> B
		curSum = now.a + now.b;

		// 넘치는 경우
		if (curSum > B)
		{
			nextA = curSum - B;
			nextB = B;
		}
		// 비는 경우
		else
		{
			nextA = 0;
			nextB = curSum;
		}

		// 아직 해당 상태 도달하지 않았을 경우 다음 탐색 가능
		if (!visit[nextA][nextB])
		{
			visit[nextA][nextB] = true;
			queue[tail++] = { nextA, nextB };

			if (tail == MAX_QUEUE)
			{
				tail = 0;
			}
		}

		// 2. B -> A
		// 넘치는 경우
		if (curSum > A)
		{
			nextA = A;
			nextB = curSum - A;
		}
		// 비는 경우
		else
		{
			nextA = curSum;
			nextB = 0;
		}

		// 아직 해당 상태 도달하지 않았을 경우 다음 탐색 가능
		if (!visit[nextA][nextB])
		{
			visit[nextA][nextB] = true;
			queue[tail++] = { nextA, nextB };

			if (tail == MAX_QUEUE)
			{
				tail = 0;
			}
		}

		// 3. A -> C
		curSum = total - now.b;
		nextB = now.b;

		// 넘치는 경우
		if (curSum > C)
		{
			nextA = curSum - C;
		}
		// 비는 경우
		else
		{
			nextA = 0;
		}

		// 아직 해당 상태 도달하지 않았을 경우 다음 탐색 가능
		if (!visit[nextA][nextB])
		{
			visit[nextA][nextB] = true;
			queue[tail++] = { nextA, nextB };

			if (tail == MAX_QUEUE)
			{
				tail = 0;
			}
		}

		// 4. C -> A
		// 넘치는 경우
		if (curSum > A)
		{
			nextA = A;
		}
		// 비는 경우
		else
		{
			nextA = curSum;
		}

		// 아직 해당 상태 도달하지 않았을 경우 다음 탐색 가능
		if (!visit[nextA][nextB])
		{
			visit[nextA][nextB] = true;
			queue[tail++] = { nextA, nextB };

			if (tail == MAX_QUEUE)
			{
				tail = 0;
			}
		}

		// 5. B -> C
		curSum = total - now.a;
		nextA = now.a;

		// 넘치는 경우
		if (curSum > C)
		{
			nextB = curSum - C;
		}
		// 비는 경우
		else
		{
			nextB = 0;
		}

		// 아직 해당 상태 도달하지 않았을 경우 다음 탐색 가능
		if (!visit[nextA][nextB])
		{
			visit[nextA][nextB] = true;
			queue[tail++] = { nextA, nextB };

			if (tail == MAX_QUEUE)
			{
				tail = 0;
			}
		}

		// 6. C -> B
		// 넘치는 경우
		if (curSum > B)
		{
			nextB = B;
		}
		// 비는 경우
		else
		{
			nextB = curSum;
		}

		// 아직 해당 상태 도달하지 않았을 경우 다음 탐색 가능
		if (!visit[nextA][nextB])
		{
			visit[nextA][nextB] = true;
			queue[tail++] = { nextA, nextB };

			if (tail == MAX_QUEUE)
			{
				tail = 0;
			}
		}
	}

	return;
}

void printAns(void)
{
	for (register int i = 0; i <= C; i++)
	{
		if (check[i])
		{
			printf("%d ", i);
		}
	}

	printf("\n");

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);
	// freopen("input3.txt", "r", stdin);

	scanf("%d %d %d", &A, &B, &C);

	bfs();

	printAns();

	return 0;
}
