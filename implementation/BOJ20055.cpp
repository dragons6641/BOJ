#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 100
#define MAX_K 200
#define MAX_A 1000
#define MAX_QUEUE ((MAX_A * MAX_A) + 1)

struct BeltNode
{
	// 해당 칸의 내구도
	int durability;
	// 해당 칸에 올라온 로봇 번호
	int robot;
};

// 컨베이어 벨트의 길이
int N;
// 내구도가 0인 칸의 제한
int K;
// 내구도가 0인 칸의 갯수
int zeroCnt = 0;
// 현재 단계
int step = 0;
// queue에 사용
int head = 1;
int tail = 1;
// 로봇의 위치 목록
// 1부터 사용
int queue[MAX_QUEUE];
// 컨베이어 벨트의 상태
// 1부터 사용
BeltNode A[MAX_K + 1] = { {0, 0}, };

void inputData(void)
{
	scanf("%d %d", &N, &K);

	for (register int i = 1; i <= N * 2; i++)
	{
		scanf("%d", &A[i].durability);
	}

	return;
}

void popRobot(void)
{
	BeltNode* end = &A[N];

	// 내려가는 위치에 로봇이 있는 경우 로봇은 반드시 땅으로 내려가야 한다.
	if (end->robot > 0)
	{
		queue[end->robot] = 0;
		end->robot = 0;
		head++;
	}

	return;
}

void rotateBelt(void)
{
	BeltNode tmp = A[N * 2];

	for (register int i = N * 2; i > 1; i--)
	{
		if (A[i - 1].robot > 0)
		{
			queue[A[i - 1].robot] = i;
		}

		A[i] = A[i - 1];
	}

	if (tmp.robot > 0)
	{
		queue[tmp.robot] = 1;
	}

	A[1] = tmp;

	popRobot();

	return;
}

void moveRobot(void)
{
	for (register int i = head; i <= tail; i++)
	{
		BeltNode* now = &A[queue[i]];
		BeltNode* next;

		if (queue[i] == 0)
		{
			continue;
		}
		else if (queue[i] == N * 2)
		{
			next = &A[1];
		}
		else
		{
			next = &A[queue[i] + 1];
		}

		// 로봇이 이동하기 위해서는 이동하려는 칸에 로봇이 없으며, 그 칸의 내구도가 1 이상 남아 있어야 한다.
		if ((next->durability > 0) && (next->robot == 0))
		{
			next->durability--;
			next->robot = now->robot;

			if (next->durability == 0)
			{
				zeroCnt++;
			}

			if (queue[i] == N * 2)
			{
				queue[i] = 1;
			}
			else
			{
				queue[i]++;
			}

			now->robot = 0;
		}

		popRobot();
	}

	return;
}

void pushRobot(void)
{
	BeltNode* start = &A[1];

	// 로봇이 이동하기 위해서는 이동하려는 칸에 로봇이 없으며, 그 칸의 내구도가 1 이상 남아 있어야 한다.
	if ((start->durability > 0) && (start->robot == 0))
	{
		queue[++tail] = 1;

		start->durability--;
		start->robot = tail;

		if (start->durability == 0)
		{
			zeroCnt++;
		}
	}

	return;
}

int solve(void)
{
	// 4. 내구도가 0인 칸의 개수가 K개 이상이라면 과정을 종료한다. 그렇지 않다면 1번으로 돌아간다.
	while (zeroCnt < K)
	{
		// 단계 수 증가
		step++;

		// 1. 벨트가 한 칸 회전한다. 
		rotateBelt();

		// 2. 가장 먼저 벨트에 올라간 로봇부터, 벨트가 회전하는 방향으로 한 칸 이동할 수 있다면 이동한다. 만약 이동할 수 없다면 가만히 있는다.
		moveRobot();

		// 3. 올라가는 위치에 로봇이 없다면 로봇을 하나 올린다.
		pushRobot();

		int debug = 1;
	}

	return step;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);	// 2
	// freopen("input2.txt", "r", stdin);	// 31
	// freopen("input3.txt", "r", stdin);	// 24
	// freopen("input4.txt", "r", stdin);	// 472

	inputData();

	int ans = solve();

	printf("%d\n", ans);

	return 0;
}
