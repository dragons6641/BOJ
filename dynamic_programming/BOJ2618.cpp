/*
F2 경찰차
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 1000
#define MAX_W 1000
#define INF ((int)2e9)
#define MAX_QUEUE ((MAX_W + 1) * (MAX_W + 1))
#define START_DIST 0
#define START_LEVEL 0

struct Node
{
	int r;
	int c;
	// 현재까지의 거리
	int dist;
	// 사건을 해결한 경찰차 번호
	// 1번 혹은 2번
	int num;
};

// 동서방향 도로의 갯수
int N;
// 처리해야 하는 사건의 갯수
int W;
// 최소 거리를 가져야 하므로 최댓값으로 초기화
Node ans = { 0, 0, INF, 0 };
// 어떤 경찰차가 사건 해결했는지
// 1부터 사용
// int visit[MAX_W + 1] = { 0, };
// 1번 경찰차 위치
Node police1 = { 1, 1, START_DIST, -1 };
// 2번 경찰차 위치
Node police2 = { MAX_N, MAX_N, START_DIST, -2 };
// 1부터 사용
Node inputList[MAX_W + 1] = { { 0, 0, 0, 0 }, };
// DP[a][b] : 1번 경찰차가 a번 사건, 2번 경찰차가 b번 사건을 각각 마지막으로 해결했을 때의 정보
// 0부터 사용
Node DP[MAX_W + 1][MAX_W + 1] = { {0, 0, 0, 0}, };
// BFS
Node queue[MAX_QUEUE] = { {0, 0, 0, 0}, };

void inputData(void)
{
	scanf("%d", &N);
	scanf("%d", &W);

	police2 = { N, N };

	for (register int i = 1; i <= W; i++)
	{
		scanf("%d %d", &inputList[i].r, &inputList[i].c);
	}

	return;
}

void init(void)
{
	for (register int r = 0; r <= W; r++)
	{
		for (register int c = 0; c <= W; c++)
		{
			DP[r][c].dist = INF;
		}
	}

	return;
}

int abs(int k)
{
	return ((k > 0) ? k : -k);
}

int calcDist(Node x, Node y)
{
	return (abs(x.r - y.r) + abs(x.c - y.c));
}

/*
// DFS : Time Limit Exceed
void run(int nowDist, int level, Node p1, Node p2)
{
	// 이미 정답이 더 좋아질 수 없다면
	if (ans <= nowDist)
	{
		// 더 할 필요가 없다
		return;
	}

	// 모든 사건을 다 처리했다면
	if (level == W)
	{
		// 정답 갱신
		ans = nowDist;

		return;
	}

	int nextDist;

	// 1번 경찰차가 처리
	visit[level + 1] = 1;

	nextDist = calcDist(inputList[level + 1], p1);

	run(nowDist + nextDist, level + 1, inputList[level + 1], p2);

	// 2번 경찰차가 처리
	visit[level + 1] = 2;

	nextDist = calcDist(inputList[level + 1], p2);

	run(nowDist + nextDist, level + 1, p1, inputList[level + 1]);

	// 초기화
	visit[level + 1] = 0;

	return;
}
*/

/*
// DP + BFS
// BFS의 목적 : DP Table을 완성하는 것!
// DP배열엔 이전 경로의 정보 저장
int solve(void)
{
	register int head = 0;
	register int tail = 0;

	// 초기값
	DP[0][0].dist = 0;

	queue[tail++] = DP[0][0];

	while (head != tail)
	{
		Node now = queue[head++];
		// Node now = queue[head];
		// head = ((head + 1) % MAX_QUEUE);

		if (head == MAX_QUEUE - 1)
		{
			head = 0;
		}

		// 모든 사건을 처리했다면
		if ((now.r == W) || (now.c == W))
		{
			// 해당 사건은 볼 필요 없다
			continue;
		}

		int nextDist;
		// 다음 사건 번호 : 두 사건 번호 중 큰 것 + 1
		int nextCrime = ((now.r > now.c) ? (now.r + 1) : (now.c + 1));

		// 1번 경찰차가 사건을 처리하는 경우
		// 단, 최소 거리일때만!
		// 현재 거리가 아닌, 다음 거리와 비교
		if (now.r == 0)
		{
			nextDist = calcDist(inputList[nextCrime], police1);
		}
		else
		{
			nextDist = calcDist(inputList[nextCrime], inputList[now.r]);
		}

		if (DP[nextCrime][now.c].dist > now.dist + nextDist)
		{
			DP[nextCrime][now.c] = { now.r, now.c, now.dist + nextDist, 1 };
			queue[tail++] = { nextCrime, now.c, now.dist + nextDist, 1 };
			// queue[tail] = { nextCrime, now.c, now.dist + nextDist, 1 };
			// tail = (tail + 1) % MAX_QUEUE;

			if (tail == MAX_QUEUE)
			{
				tail = 0;
			}
		}

		// 2번 경찰차가 사건을 처리하는 경우
		// 단, 최소 거리일때만!
		// 현재 거리가 아닌, 다음 거리와 비교
		if (now.c == 0)
		{
			nextDist = calcDist(inputList[nextCrime], police2);
		}
		else
		{
			nextDist = calcDist(inputList[nextCrime], inputList[now.c]);
		}

		if (DP[now.r][nextCrime].dist > now.dist + nextDist)
		{
			DP[now.r][nextCrime] = { now.r, now.c, now.dist + nextDist, 2 };
			queue[tail++] = { now.r, nextCrime, now.dist + nextDist, 2 };
			// queue[tail] = { now.r, nextCrime, now.dist + nextDist, 2 };
			// tail = (tail + 1) % MAX_QUEUE;

			if (tail == MAX_QUEUE)
			{
				tail = 0;
			}
		}
	}

	for (register int r = 0; r < W; r++)
	{
		if (ans.dist > DP[r][W].dist)
		{
			ans = { r, W, DP[r][W].dist, DP[r][W].num };
		}
	}

	for (register int c = 0; c < W; c++)
	{
		if (ans.dist > DP[W][c].dist)
		{
			ans = { W, c, DP[W][c].dist, DP[W][c].num };
		}
	}

	return 0;
}
*/

void traverse(int nowR, int nowC)
{
	/*
	if ((nowR == 0) && (nowC == 0))
	{
		return;
	}

	traverse(DP[nowR][nowC].r, DP[nowR][nowC].c);
	*/

	if (DP[nowR][nowC].num == 0)
	{
		return;
	}

	printf("%d\n", DP[nowR][nowC].num);

	traverse(DP[nowR][nowC].r, DP[nowR][nowC].c);

	return;
}

void print(void)
{
	printf("%d\n", ans.dist);
	printf("%d\n", ans.num);

	traverse(ans.r, ans.c);

	return;
}

// DP + DFS
// DFS의 목적 : DP Table을 완성하는 것!
// DP배열엔 다음 경로의 정보 저장
Node run(int a, int b)
{
	// 모든 사건을 처리한 경우 종료
	if ((a == W) || (b == W))
	{
		return {a, b, 0, 0};
	}

	// 이 코드의 의미는...?
	/*
	int& ret = DP[a][b].dist;

	if (ret != INF)
	{
		return DP[a][b];
	}
	*/

	if (DP[a][b].dist < INF)
	{
		return DP[a][b];
	}

	int nextDist1;
	int nextDist2;
	int nextCrime = ((a > b) ? (a + 1) : (b + 1));
	Node ret1;
	Node ret2;

	// 1번 경찰차가 사건을 처리하는 경우
	// 단, 최소 거리일때만!
	// 현재 거리가 아닌, 다음 거리와 비교
	if (a == 0)
	{
		nextDist1 = calcDist(inputList[nextCrime], police1);
	}
	else
	{
		nextDist1 = calcDist(inputList[nextCrime], inputList[a]);
	}

	ret1 = run(nextCrime, b);

	// 2번 경찰차가 사건을 처리하는 경우
	if (b == 0)
	{
		nextDist2 = calcDist(inputList[nextCrime], police2);
	}
	else
	{
		nextDist2 = calcDist(inputList[nextCrime], inputList[b]);
	}

	ret2 = run(a, nextCrime);

	// 두 경우 중 거리가 작은 경우로 결정
	// Node ret = ((ret1.dist < ret2.dist) ? ret1 : ret2);
	// 1번 경찰자가 사건을 처리하는 경우
	if (ret1.dist + nextDist1 < ret2.dist + nextDist2)
	{
		DP[a][b] = { nextCrime, b, ret1.dist + nextDist1, 1 };
	}
	// 2번 경찰차가 사건을 처리하는 경우
	else
	{
		DP[a][b] = { a, nextCrime, ret2.dist + nextDist2, 2 };
	}

	return DP[a][b];
}

int main(void)
{
	// freopen("input.txt", "r", stdin);
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);
	// freopen("input3.txt", "r", stdin);
	// freopen("input4.txt", "r", stdin);
	// freopen("input5.txt", "r", stdin);
	// freopen("input6.txt", "r", stdin);
	// freopen("input7.txt", "r", stdin);
	// freopen("input8.txt", "r", stdin);

	inputData();

	init();

	// run(START_DIST, START_LEVEL, police1, police2);

	// solve();

	ans = run(0, 0);

	// printf("%d\n", ans);

	print();

	return 0;
}

// 랜덤 Test Case 생성 방법
/*
#define _CRT_SECURE_NO_WARNINGS

#include <bits.h>
#include <time.h>
#include <stdio.h>
using namespace std;

int main() {
	FILE *fp = fopen("input.txt", "w");

	srand(time(0));
	// puts("1000\n1000");
	fprintf(fp, "1000\n1000\n");
	for (int i = 0; i < 1000; i++)
		// printf("%d %d\n", rand() % 1000 + 1, rand() % 1000 + 1);
		fprintf(fp, "%d %d\n", rand() % 1000 + 1, rand() % 1000 + 1);
	fclose(fp);
	return 0;
}
*/
