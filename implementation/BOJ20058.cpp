#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 6
#define MAX_Q 1000
#define MAX_A 100
#define MAX_DIR 4
#define MIN_ADJ 3
#define MAX_L MAX_N
#define MAX_SIZE (1 << MAX_N)
#define MAX_AREA (MAX_SIZE * MAX_SIZE)
#define MAX_QUEUE (MAX_SIZE * MAX_SIZE)

struct QueueNode
{
	int r;
	int c;
	int cnt;
};

int N;
int Q;
int L;
int sizeN;
int sizeL;
int iceSum = 0;
int iceMax = 0;
int dr[MAX_DIR] = { -1, 1, 0, 0 };
int dc[MAX_DIR] = { 0, 0, -1, 1 };
int A[MAX_SIZE + 2][MAX_SIZE + 2] = { 0, };
int B[MAX_SIZE + 2][MAX_SIZE + 2] = { 0, };
bool visit[MAX_SIZE + 2][MAX_SIZE + 2] = { 0, };
QueueNode queue[MAX_QUEUE] = { {0, 0, 0}, };

void push(int r, int c, int& cnt, int& tail)
{
	visit[r][c] = true;
	queue[tail++] = { r, c, ++cnt };

	if (tail == MAX_QUEUE)
	{
		tail = 0;
	}

	return;
}

QueueNode pop(int& head)
{
	QueueNode data = queue[head++];

	if (head == MAX_QUEUE)
	{
		head = 0;
	}

	return data;
}

void rotateIce(int sr, int sc)
{
	for (register int r = 0; r < sizeL; r++)
	{
		for (register int c = 0; c < sizeL; c++)
		{
			B[sr + c][sc + sizeL - r - 1] = A[sr + r][sc + c];
		}
	}

	for (register int r = 0; r < sizeL; r++)
	{
		for (register int c = 0; c < sizeL; c++)
		{
			A[sr + r][sc + c] = B[sr + r][sc + c];
		}
	}

	return;
}

bool checkPossible(int nowR, int nowC)
{
	// 범위를 벗어나는 경우
	if ((nowR <= 0) || (nowC <= 0) || (nowR > sizeN) || (nowC > sizeN))
	{
		return false;
	}

	// 얼음이 없는 경우
	if (A[nowR][nowC] == 0)
	{
		return false;
	}

	// 이미 방문한 경우
	if (visit[nowR][nowC])
	{
		return false;
	}

	// 얼음이 있는 경우
	return true;
}

bool decreaseIce(int nowR, int nowC)
{
	int cnt = 0;

	for (register int dir = 0; dir < MAX_DIR; dir++)
	{
		int nextR = nowR + dr[dir];
		int nextC = nowC + dc[dir];

		if (checkPossible(nextR, nextC))
		{
			cnt++;
		}
	}

	return (cnt < MIN_ADJ);
}

void firestorm(void)
{
	// 선 증가 후 대입
	int cnt = 0;
	// 1부터 사용
	int rowList[MAX_AREA + 1] = { 0, };
	// 1부터 사용
	int colList[MAX_AREA + 1] = { 0, };

	// 그 후, 모든 부분 격자를 시계 방향으로 90도 회전시킨다. 
	for (register int r = 1; r <= sizeN; r += sizeL)
	{
		for (register int c = 1; c <= sizeN; c += sizeL)
		{
			rotateIce(r, c);
		}
	}

	// 이후 얼음이 있는 칸 3개 또는 그 이상과 인접해있지 않은 칸은 얼음의 양이 1 줄어든다. 
	// (r, c)와 인접한 칸은 (r-1, c), (r+1, c), (r, c-1), (r, c+1)이다. 
	for (register int r = 1; r <= sizeN; r++)
	{
		for (register int c = 1; c <= sizeN; c++)
		{
			if (A[r][c] == 0)
			{
				continue;
			}

			if (decreaseIce(r, c))
			{
				iceSum--;
				cnt++;
				rowList[cnt] = r;
				colList[cnt] = c;
				B[r][c] = -1;
			}
		}
	}

	for (register int i = 1; i <= cnt; i++)
	{
		int nowR = rowList[i];
		int nowC = colList[i];

		A[nowR][nowC] += B[nowR][nowC];
		B[nowR][nowC] = 0;
	}

	return;
}

void bfs(int startR, int startC)
{
	int cnt = 0;
	int head = 0;
	int tail = 0;

	push(startR, startC, cnt, tail);

	while (head != tail)
	{
		QueueNode now = pop(head);

		for (register int dir = 0; dir < MAX_DIR; dir++)
		{
			int nextR = now.r + dr[dir];
			int nextC = now.c + dc[dir];

			if ((checkPossible(nextR, nextC)) && (!visit[nextR][nextC]))
			{
				push(nextR, nextC, cnt, tail);
			}
		}
	}

	if (iceMax < cnt)
	{
		iceMax = cnt;
	}

	return;
}

void solve(void)
{
	scanf("%d %d", &N, &Q);

	sizeN = (1 << N);

	for (register int r = 1; r <= sizeN; r++)
	{
		for (register int c = 1; c <= sizeN; c++)
		{
			scanf("%d", &A[r][c]);

			iceSum += A[r][c];
		}
	}

	for (register int i = 1; i <= Q; i++)
	{
		// 파이어스톰을 시전하려면 시전할 때마다 단계 L을 결정해야 한다. 
		scanf("%d", &L);

		// 파이어스톰은 먼저 격자를 2L × 2L 크기의 부분 격자로 나눈다. 
		sizeL = (1 << L);

		// 마법사 상어는 파이어스톰을 총 Q번 시전하려고 한다.
		firestorm();

		int debug = 1;
	}

	// 가장 큰 덩어리 찾기
	for (register int r = 1; r <= sizeN; r++)
	{
		for (register int c = 1; c <= sizeN; c++)
		{
			if (checkPossible(r, c))
			{
				bfs(r, c);
			}
		}
	}

	return;
}

void outputData(void)
{
	// 첫째 줄에 남아있는 얼음 A[r][c]의 합을 출력하고, 
	printf("%d\n", iceSum);
	// 둘째 줄에 가장 큰 덩어리가 차지하는 칸의 개수를 출력한다. 
	printf("%d\n", iceMax);

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);	// 284 64
	// freopen("input2.txt", "r", stdin);	// 280 64
	// freopen("input3.txt", "r", stdin);	// 268 64
	// freopen("input4.txt", "r", stdin);	// 248 62
	// freopen("input5.txt", "r", stdin);	// 246 60
	// freopen("input6.txt", "r", stdin);	// 37 9

	solve();

	outputData();

	return 0;
}
