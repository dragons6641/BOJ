/*
13549 숨바꼭질 3
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
// #include <queue>

// using namespace std;

#define MAX_POS 100000
#define MAX_QUEUE MAX_POS
#define START_TIME 0


struct Node
{
	int time;
	int pos;
};

/*
struct compare
{
	bool operator()(Node &x, Node &y)
	{
		if (x.time != y.time)
		{
			return x.time > y.time;
		}
		else
		{
			return x.pos > y.pos;
		}
	}
};
*/

// 수빈
int N;
// 동생
int K;
int head = 0;
int tail = 0;
int ans = MAX_POS;
bool visit[MAX_POS + 1] = { 0, };
Node queue[MAX_QUEUE] = { {0, 0} };

int bfs(int startPos, int target)
{
	visit[startPos] = true;
	queue[tail++] = { START_TIME, startPos };
	// deque <Node> dq;
	// priority_queue <Node, vector<Node>, compare> pq;

	// dq.push_back({ START_TIME, startPos });
	// pq.push({ START_TIME, startPos });

	while (head != tail)
	// while (!dq.empty())
	// while (!pq.empty())
	{
		Node now = queue[head++];
		// Node now = dq.front();
		// Node now = pq.top();
		// dq.pop_front();
		// pq.pop();

		visit[now.pos] = true;

		if (head == MAX_QUEUE)
		{
			head = 0;
		}

		if (now.pos == target)
		{
			return now.time;
		}

		/*
		if (now.pos == 3)
		{
			int debug = 1;
		}
		*/

		// 1. 2N
		if ((now.pos < K) && (now.pos * 2 <= MAX_POS))
		{
			/*
			if (now.pos * 2 == target)
			{
				return now.time;
			}

			if (!visit[now.pos * 2])
			{
				visit[now.pos * 2] = true;
				// queue[tail++] = { now.time, now.pos * 2 };
				queue[--head] = { now.time, now.pos * 2 };
				// dq.push_front({ now.time, now.pos * 2 });
				// pq.push({ now.time, now.pos * 2 });

				if (head == -1)
				{
					head = MAX_QUEUE - 1;
				}
			}
			*/

			if (!visit[now.pos * 2])
			{
				// visit[now.pos * 2] = true;
				// queue[tail++] = { now.time, now.pos * 2 };
				queue[--head] = { now.time, now.pos * 2 };
				// dq.push_front({ now.time, now.pos * 2 });
				// pq.push({ now.time, now.pos * 2 });

				if (head == -1)
				{
					head = MAX_QUEUE - 1;
				}
			}
		}

		// 2. N + 1
		if (now.pos < MAX_POS)
		{
			/*
			if (now.pos + 1 == target)
			{
				return now.time + 1;
			}

			if (!visit[now.pos + 1])
			{
				visit[now.pos + 1] = true;
				queue[tail++] = { now.time + 1, now.pos + 1 };
				// dq.push_back({ now.time + 1, now.pos + 1 });
				// pq.push({ now.time + 1, now.pos + 1 });

				if (tail == MAX_QUEUE)
				{
					tail = 0;
				}
			}
			*/

			if (!visit[now.pos + 1])
			{
				// visit[now.pos + 1] = true;
				queue[tail++] = { now.time + 1, now.pos + 1 };
				// dq.push_back({ now.time + 1, now.pos + 1 });
				// pq.push({ now.time + 1, now.pos + 1 });

				if (tail == MAX_QUEUE)
				{
					tail = 0;
				}
			}
		}

		// 3. N - 1
		if (now.pos > 0)
		{
			/*
			if (now.pos - 1 == target)
			{
				return now.time + 1;
			}

			if (!visit[now.pos - 1])
			{
				visit[now.pos - 1] = true;
				queue[tail++] = { now.time + 1, now.pos - 1 };
				// dq.push_back({ now.time + 1, now.pos - 1 });
				// pq.push({ now.time + 1, now.pos - 1 });

				if (tail == MAX_QUEUE)
				{
					tail = 0;
				}
			}
			*/

			if (!visit[now.pos - 1])
			{
				// visit[now.pos - 1] = true;
				queue[tail++] = { now.time + 1, now.pos - 1 };
				// dq.push_back({ now.time + 1, now.pos - 1 });
				// pq.push({ now.time + 1, now.pos - 1 });

				if (tail == MAX_QUEUE)
				{
					tail = 0;
				}
			}
		}
	}

	return -1;
}

/*
void dfs(int time, int pos)
{

	if (pos == K)
	{
		if (ans > time)
		{
			ans = time;
		}

		return;
	}

	// 1. 2N
	if ((pos < K) && (pos * 2 <= MAX_POS))
	{
		if (!visit[pos * 2])
		{
			visit[pos * 2] = true;

			dfs(time, pos * 2);

			visit[pos * 2] = false;
		}
	}

	// 2. N + 1
	if (pos < K)
	{
		if (!visit[pos + 1])
		{
			visit[pos + 1] = true;

			dfs(time + 1, pos + 1);

			visit[pos + 1] = false;
		}
	}

	// 3. N - 1
	if (pos > 0)
	{
		if (!visit[pos - 1])
		{
			visit[pos - 1] = true;

			dfs(time + 1, pos - 1);

			visit[pos - 1] = false;
		}
	}

	return;
}
*/

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);
	// freopen("input3.txt", "r", stdin);
	// freopen("input4.txt", "r", stdin);
	// freopen("input5.txt", "r", stdin);
	// freopen("input6.txt", "r", stdin);
	// freopen("input7.txt", "r", stdin);

	setbuf(stdout, NULL);

	scanf("%d %d", &N, &K);

	printf("%d\n", bfs(N, K));

	/*
	visit[N] = true;

	dfs(START_TIME, N);

	printf("%d\n", ans);
	*/

	return 0;
}
