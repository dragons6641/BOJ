#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 100
#define MAX_K 100
#define MAX_L 100
#define MAX_X 10000
#define MAX_DIR 4
#define START_R 1
#define START_C 1
#define START_DIR 3
#define START_IDX 1

struct Node
{
	int r;
	int c;
	int dir;
};

struct Command
{
	int time;
	int dir;
};

// 격자 크기
int N;
// 과일의 갯수
int K;
// 뱀 이동경로 갯수
int L;
// 다음 명령 위치
int cmdIdx = START_IDX;
int directR[MAX_DIR] = { -1, 1, 0, 0 };
int directC[MAX_DIR] = { 0, 0, -1, 1 };
// 왼쪽으로 90도 회전 시 다음 방향
int nextLeftDirList[MAX_DIR] = { 2, 3, 1, 0 };
// 오른쪽으로 90도 회전 시 다음 방향
int nextRightDirList[MAX_DIR] = { 3, 2, 0, 1 };
// Barrier!
// 1부터 N까지 사용
int map[MAX_N + 2][MAX_N + 2] = { 0, };
// Barrier!
// 1부터 N까지 사용
// 방향을 전환한 위치 기록
int visit[MAX_N + 2][MAX_N + 2] = { 0, };
// 머리 좌표
Node head = { START_R, START_C, START_DIR };
// 꼬리 좌표
Node tail = { START_R, START_C, START_DIR };
// 뱀의 방향 변화 기록
// 1부터 사용
Command cmdList[MAX_L + 1] = { {0, 0}, };

void inputData(void)
{
	int R;
	int C;
	char dir;

	scanf("%d", &N);
	scanf("%d", &K);

	for (register int i = 1; i <= K; i++)
	{
		scanf("%d %d", &R, &C);

		map[R][C] = 2;
	}

	scanf("%d", &L);

	for (register int i = 1; i <= L; i++)
	{
		scanf("%d %c", &cmdList[i].time, &dir);

		if (dir == 'L')
		{
			cmdList[i].dir = -1;
		}
		else if (dir == 'D')
		{
			cmdList[i].dir = 1;
		}
	}

	return;
}

void init(void)
{
	for (register int r = 0; r <= N + 1; r++)
	{
		map[r][0] = -1;
		map[r][N + 1] = -1;
	}

	for (register int c = 0; c <= N + 1; c++)
	{
		map[0][c] = -1;
		map[N + 1][c] = -1;
	}

	map[START_R][START_C] = 1;

	return;
}

bool simulate(int nowTime)
{
	// 1. 먼저 뱀은 몸길이를 늘려 머리를 다음 칸으로 이동한다.
	int nextHeadR = head.r + directR[head.dir];
	int nextHeadC = head.c + directC[head.dir];
	int nextTailR = tail.r + directR[tail.dir];
	int nextTailC = tail.c + directC[tail.dir];

	// 뱀이 상하좌우로 기어다니다가 벽 또는 자기자신과 부딪히면 게임이 끝난다.
	if ((map[nextHeadR][nextHeadC] == -1) || (map[nextHeadR][nextHeadC] == 1))
	{
		return false;
	}

	head.r = nextHeadR;
	head.c = nextHeadC;

	// 필요 시 방향 전환
	if (cmdIdx <= L)
	{
		// 방향을 전환해야 하는 시간이면
		if (cmdList[cmdIdx].time == nowTime)
		{
			// 머리 방향 전환이 필요한 경우
			// 왼쪽으로 90도
			if (cmdList[cmdIdx].dir == -1)
			{
				head.dir = nextLeftDirList[head.dir];
				visit[head.r][head.c] = -1;
			}
			// 오른쪽으로 90도
			else if (cmdList[cmdIdx].dir == 1)
			{
				head.dir = nextRightDirList[head.dir];
				visit[head.r][head.c] = 1;
			}

			cmdIdx++;
		}
	}

	// 2. 만약 이동한 칸에 과일이 있다면 이 상태가 유지된다. 즉, 몸길이가 1 증가한 것이다.
	// 3. 만약 이동한 칸에 과일이 없다면 몸길이가 원상태로 돌아와야 한다. 이때 꼬리가 위치한 칸을 비우게 된다.
	if (map[head.r][head.c] != 2)
	{
		map[tail.r][tail.c] = 0;
		tail.r = nextTailR;
		tail.c = nextTailC;

		// 꼬리 방향 전환이 필요한 경우
		// 왼쪽으로 90도
		if (visit[tail.r][tail.c] == -1)
		{
			tail.dir = nextLeftDirList[tail.dir];

			visit[tail.r][tail.c] = 0;
		}
		// 오른쪽으로 90도
		else if (visit[tail.r][tail.c] == 1)
		{
			tail.dir = nextRightDirList[tail.dir];

			visit[tail.r][tail.c] = 0;
		}
	}

	map[head.r][head.c] = 1;

	return true;
}

int solve(void)
{
	int result = 1;

	while (simulate(result))
	{
		if (result == 100)
		{
			int debug = 1;
		}

		result++;
	}

	return result;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);	// 9
	// freopen("input2.txt", "r", stdin);	// 21
	// freopen("input3.txt", "r", stdin);	// 13
	// freopen("input4.txt", "r", stdin);	// 110

	inputData();

	init();

	int ans = solve();

	printf("%d\n", ans);

	return 0;
}
