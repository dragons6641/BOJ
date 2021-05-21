/*
19237 어른 상어
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 20
#define MAX_M (MAX_N * MAX_N)
#define MAX_K 1000
#define MAX_DIR 4

struct Node
{
	// 상어 번호
	int num;
	// 남은 냄새 시간
	int time;
};

struct Shark
{
	// 번호
	// 나갔으면 0
	int num;
	// 위치
	int r;
	int c;
	// 방향
	int dir;
};

// 격자의 크기
int N;
// 상어가 들어있는 칸 수
int M;
// 냄새가 사라지는 데 걸리는 시간
int K;
// 현재 격자 안에 있는 상어 수
int cnt = 0;
// 방향 저장
// 상, 하, 좌, 우
// 1부터 사용
int directR[MAX_DIR + 1] = { 0, -1, 1, 0, 0 };
int directC[MAX_DIR + 1] = { 0, 0, 0, -1, 1 };
// 우선순위
// 1부터 사용
// 상어번호, 현재방향, 다음방향 우선순위
int priority[MAX_M + 1][MAX_DIR + 1][MAX_DIR + 1] = { 0, };
// Barrier!
// 1부터 N까지 사용
// 상어의 냄새 정보
Node map[MAX_N + 2][MAX_N + 2] = { {0, 0}, };
// 1부터 N까지 사용
// 상어 정보 저장
Shark sharkList[MAX_M + 1] = { {0, 0, 0, 0}, };

void inputData(void)
{
	scanf("%d %d %d", &N, &M, &K);

	for (register int r = 1; r <= N; r++)
	{
		for (register int c = 1; c <= N; c++)
		{
			scanf("%d", &map[r][c].num);

			if (map[r][c].num > 0)
			{
				// 상어 정보 저장
				// num, r, c, dir
				cnt++;
				sharkList[map[r][c].num] = { map[r][c].num, r, c, 0 };

				// 맨 처음에는 모든 상어가 자신의 위치에 자신의 냄새를 뿌린다.
				// 냄새는 상어가 k번 이동하고 나면 사라진다.
				map[r][c].time = K;
			}
		}
	}

	cnt = M;

	for (register int i = 1; i <= M; i++)
	{
		scanf("%d", &sharkList[i].dir);
	}

	for (register int i = 1; i <= M; i++)
	{
		for (register int r = 1; r <= MAX_DIR; r++)
		{
			for (register int c = 1; c <= MAX_DIR; c++)
			{
				scanf("%d", &priority[i][r][c]);
			}
		}
	}

	return;
}

void moveShark(void)
{
	// 1초마다 모든 상어가 동시에 상하좌우로 인접한 칸 중 하나로 이동하고, 자신의 냄새를 그 칸에 뿌린다.
	// 1의 번호를 가진 어른 상어는 가장 강력해서 나머지 모두를 쫓아낼 수 있다. 
	for (register int i = 1; i <= M; i++)
	{
		bool flag = false;

		// 각 상어가 이동 방향을 결정할 때는, 먼저 인접한 칸 중 아무 냄새가 없는 칸의 방향으로 잡는다. 
		for (register int d = 1; d <= MAX_DIR; d++)
		{
			// 해당 상어가 죽은 상어라면
			if (sharkList[i].num == 0)
			{
				// 더 하면 안된다
				flag = true;

				break;
			}

			// 상어번호, 현재방향, 다음방향 우선순위
			int nextDir = priority[i][sharkList[i].dir][d];
			int dr = sharkList[i].r + directR[nextDir];
			int dc = sharkList[i].c + directC[nextDir];

			// 지도 밖을 벗어나면 안됨
			if ((dr <= 0) || (dc <= 0) || (dr > N) || (dc > N))
			{
				continue;
			}

			/*
			// 모든 상어가 이동한 후 한 칸에 여러 마리의 상어가 남아 있으면, 가장 작은 번호를 가진 상어를 제외하고 모두 격자 밖으로 쫓겨난다. 
			// 다른 상어와 동시에 해당 칸으로 들어오는 경우
			// 그런데 거기에 들어가 있는 상어는 나보다 약하다
			// 즉, 쫓아낼 수 있는 상황이라면
			if ((map[dr][dc].num > i) && (map[dr][dc].time == K + 1))
			{
				// 이미 있던 상어를 쫓아내자
				// num, r, c, dir
				sharkList[map[dr][dc].num] = { 0, dr, dc, nextDir };
				// 냄새 없어진 것으로 해야 들어갈 수 있다. 
				map[dr][dc] = { 0, 0 };
				// 상어 마릿수는 감소
				cnt--;
			}
			*/

			/*
			// 모든 상어가 이동한 후 한 칸에 여러 마리의 상어가 남아 있으면, 가장 작은 번호를 가진 상어를 제외하고 모두 격자 밖으로 쫓겨난다. 
			// 다른 상어와 동시에 해당 칸으로 들어오는 경우
			// 그런데 거기에 들어가 있는 상어는 나보다 강하다
			// 즉, 내가 먹히는 상황이라면
			if (map[dr][dc].time == K + 1)
			{
				// 나는 쫓겨난다 이말이야~
				sharkList[i].num = 0;
				// 상어 마릿수는 감소
				cnt--;

				// 이미 이동했다면 더 하면 안된다
				flag = true;

				break;
			}
			*/
			// 이미 냄새가 있다면 안됨
			if (map[dr][dc].time > 0)
			{
				continue;
			}

			// 내가 죽지 않고 냄새가 없다면 이동 가능
			// 나중에 시간이 1 감소되므로 미리 1 증가시켜서 반영
			sharkList[i] = { i, dr, dc, nextDir };
			// map[dr][dc] = { i, K + 1 };

			// 이미 이동했다면 더 하면 안된다
			flag = true;

			break;
		}

		if (flag)
		{
			continue;
		}
		
		// 그런 칸이 없으면 자신의 냄새가 있는 칸의 방향으로 잡는다. 
		for (register int d = 1; d <= MAX_DIR; d++)
		{
			// 해당 상어가 죽은 상어라면
			if (sharkList[i].num == 0)
			{
				// 더 하면 안된다
				break;
			}

			// 상어번호, 현재방향, 다음방향 우선순위
			int nextDir = priority[i][sharkList[i].dir][d];
			int dr = sharkList[i].r + directR[nextDir];
			int dc = sharkList[i].c + directC[nextDir];

			// 지도 밖을 벗어나면 안됨
			if ((dr <= 0) || (dc <= 0) || (dr > N) || (dc > N))
			{
				continue;
			}

			// 다른 상어의 냄새가 있다면 안됨
			if (map[dr][dc].num != i)
			{
				continue;
			}

			// 내가 죽지 않고 냄새가 없다면 이동 가능
			// 나중에 시간이 1 감소되므로 미리 1 증가시켜서 반영
			sharkList[i] = { i, dr, dc, nextDir };
			// map[dr][dc] = { i, K + 1 };

			// 이미 이동했다면 더 하면 안된다
			break;
		}

		int debug = 1;
	}

	return;
}

void moveMap(void)
{
	for (register int i = 1; i <= M; i++)
	{
		// 죽은 상어는 이동하지 않는다
		if (sharkList[i].num == 0)
		{
			continue;
		}

		int nextR = sharkList[i].r;
		int nextC = sharkList[i].c;

		// 아무도 없으면 이동
		// 자신의 냄새여도 이동
		if ((map[nextR][nextC].num == 0) || (map[nextR][nextC].num == i))
		{
			map[sharkList[i].r][sharkList[i].c] = { i, K + 1 };
		}
		// 이미 다른 상어가 있다면
		else
		{
			// 나보다 더 센 상어가 이미 그쪽으로 이동했으므로
			// 나는 죽는다!
			sharkList[i].num = 0;
			// 상어 마릿수는 감소
			cnt--;
		}
	}

	return;
}

void decreaseSmell()
{
	for (register int r = 1; r <= N; r++)
	{
		for (register int c = 1; c <= N; c++)
		{
			if (map[r][c].time > 1)
			{
				map[r][c].time--;
			}
			else if (map[r][c].time == 1)
			{
				// 냄새가 사라지는 경우 번호도 초기화!
				map[r][c].num = 0;
				map[r][c].time--;
			}
		}
	}

	return;
}

int solve(void)
{
	register int time = 1;

	while (time <= MAX_K)
	{
		// 1초마다 모든 상어가 동시에 상하좌우로 인접한 칸 중 하나로 이동하고, 자신의 냄새를 그 칸에 뿌린다.
		moveShark();

		// 지도 상에서의 이동은 나중에 반영해줘야 한다!
		moveMap();

		// 냄새를 1초마다 감소시켜야 함
		decreaseSmell();

		if (cnt == 1)
		{
			return time;
		}

		time++;
	}

	// 1000초가 넘어도 다른 상어가 격자에 남아 있으면 -1을 출력한다
	return -1;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);
	// freopen("input3.txt", "r", stdin);
	// freopen("input4.txt", "r", stdin);
	// freopen("input5.txt", "r", stdin);

	inputData();

	int ans = solve();

	printf("%d\n", ans);

	return 0;
}
