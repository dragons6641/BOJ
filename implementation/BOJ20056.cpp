#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 50
#define MAX_M (MAX_N * MAX_N)
#define MAX_K 1000
#define MAX_MASS 1000
#define MAX_SPEED 1000
#define MAX_DIR 8
#define MAX_DIVIDE 4

struct FireballNode
{
	int mass;
	int speed;
	int dir;
};

struct VectorNode
{
	// 선 증가 후 대입
	int inCnt;
	int outCnt;
	// 0번째는 in, 1 ~ 4번째는 out
	FireballNode fireballList[MAX_DIVIDE + 1];
};

int N;
int M;
int K;
int dr[MAX_DIR] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dc[MAX_DIR] = { 0, 1, 1, 1, 0, -1, -1, -1 };
VectorNode map[MAX_N + 2][MAX_N + 2] = { 0, };

void inputData(void)
{
	int row;
	int col;
	int mass;
	int speed;
	int dir;

	scanf("%d %d %d", &N, &M, &K);

	for (register int i = 1; i <= M; i++)
	{
		scanf("%d %d %d %d %d", &row, &col, &mass, &speed, &dir);

		map[row][col].fireballList[++(map[row][col].outCnt)] = { mass, speed, dir };
	}

	return;
}

int calcNextPos(int nowPos, int size, int dirList[MAX_DIR], FireballNode* nowOut)
{
	int nextPos = nowPos + (nowOut->speed * dirList[nowOut->dir]);

	while (nextPos <= 0)
	{
		nextPos += size;
	}

	while (nextPos > N)
	{
		nextPos -= size;
	}

	return nextPos;
}

void moveFireball(void)
{
	// 1. 모든 파이어볼이 자신의 방향 di로 속력 si칸 만큼 이동한다.
	for (register int r = 1; r <= N; r++)
	{
		for (register int c = 1; c <= N; c++)
		{
			for (register int i = 1; i <= map[r][c].outCnt; i++)
			{
				// 1-1. 이동하는 중에는 같은 칸에 여러 개의 파이어볼이 있을 수도 있다.
				FireballNode* nowOut = &map[r][c].fireballList[i];
				int nextR = calcNextPos(r, N, dr, nowOut);
				int nextC = calcNextPos(c, N, dc, nowOut);
				FireballNode* nextIn = &map[nextR][nextC].fireballList[0];

				// 2-1. 같은 칸에 있는 파이어볼은 모두 하나로 합쳐진다. 
				map[nextR][nextC].inCnt++;

				// 2-3-3. 합쳐지는 파이어볼의 방향이 모두 홀수이거나 모두 짝수이면, 방향은 0, 2, 4, 6이 되고, 그렇지 않으면 1, 3, 5, 7이 된다.
				if (nextIn->mass == 0)
				{
					nextIn->dir = nowOut->dir;
				}
				else
				{
					if ((nextIn->dir != -1) && ((nextIn->dir % 2) != (nowOut->dir % 2)))
					{
						nextIn->dir = -1;
					}
				}

				// 2-3-1. 질량은 ⌊(합쳐진 파이어볼 질량의 합) / 5⌋이다. 
				nextIn->mass += nowOut->mass;
				// 2-3-2. 속력은 ⌊(합쳐진 파이어볼 속력의 합) / (합쳐진 파이어볼의 개수)⌋이다.
				nextIn->speed += nowOut->speed;
			}

			map[r][c].outCnt = 0;
		}
	}

	// 2. 이동이 모두 끝난 뒤, 2개 이상의 파이어볼이 있는 칸에서는 다음과 같은 일이 일어난다.
	for (register int r = 1; r <= N; r++)
	{
		for (register int c = 1; c <= N; c++)
		{
			int nextMass;
			int nextSpeed;
			FireballNode* nowIn = &map[r][c].fireballList[0];

			if (map[r][c].inCnt == 0)
			{
				map[r][c].outCnt = map[r][c].inCnt;
			}
			else if (map[r][c].inCnt == 1)
			{
				map[r][c].outCnt = map[r][c].inCnt;
				map[r][c].fireballList[1] = *nowIn;
			}
			else
			{
				// 2-3. 나누어진 파이어볼의 질량, 속력, 방향은 다음과 같다.
				// 2-3-1. 질량은 ⌊(합쳐진 파이어볼 질량의 합) / 5⌋이다.
				nextMass = nowIn->mass / 5;

				// 2-4. 질량이 0인 파이어볼은 소멸되어 없어진다.
				if (nextMass > 0)
				{
					// 2-2. 파이어볼은 4개의 파이어볼로 나누어진다.
					map[r][c].outCnt = MAX_DIVIDE;

					// 2-3-2. 속력은 ⌊(합쳐진 파이어볼 속력의 합) / (합쳐진 파이어볼의 개수)⌋이다.
					nextSpeed = nowIn->speed / map[r][c].inCnt;

					for (register int i = 1; i <= map[r][c].outCnt; i++)
					{
						// 2-3-3. 합쳐지는 파이어볼의 방향이 모두 홀수이거나 모두 짝수이면, 방향은 0, 2, 4, 6이 되고, 그렇지 않으면 1, 3, 5, 7이 된다.
						if (nowIn->dir == -1)
						{
							map[r][c].fireballList[i] = { nextMass, nextSpeed, (i * 2) - 1 };
						}
						else
						{
							map[r][c].fireballList[i] = { nextMass, nextSpeed, (i - 1) * 2 };
						}
					}
				}
			}

			map[r][c].inCnt = 0;
			*nowIn = { 0, 0, -1 };
		}
	}

	return;
}

int solve(void)
{
	int result = 0;

	for (register int i = 1; i <= K; i++)
	{
		moveFireball();
	}

	for (register int r = 1; r <= N; r++)
	{
		for (register int c = 1; c <= N; c++)
		{
			for (register int i = 1; i <= map[r][c].outCnt; i++)
			{
				result += map[r][c].fireballList[i].mass;
			}	
		}
	}

	return result;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);	// 8
	// freopen("input2.txt", "r", stdin);	// 8
	// freopen("input3.txt", "r", stdin);	// 0
	// freopen("input4.txt", "r", stdin);	// 9

	inputData();

	int ans = solve();

	printf("%d\n", ans);

	return 0;
}
