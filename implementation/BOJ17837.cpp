/*
17837 새로운 게임 2
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 12
#define MAX_K 10
#define MAX_DIR 4
#define MAX_ANS 1000
#define MIN_N 4
#define MIN_HORSE 4

struct Node
{
	int pos;
	int r;
	int c;
	int dir;
};

int N;
int K;
// 이게 K값이면 정답
// 같은 칸에 말이 두 개 이상 있는 경우는 입력으로 주어지지 않는다
// int maxCnt = 1;
// 1부터 사용
// X, 우, 좌, 상, 하
int directR[MAX_DIR + 1] = { 0, 0, 0, -1, 1 };
int directC[MAX_DIR + 1] = { 0, 1, -1, 0, 0 };
// 1부터 사용
// 방향 바뀌는 것 표시
int changeDir[MAX_DIR + 1] = { 0, 2, 1, 4, 3 };
// 1부터 N까지 사용
// Barrier
int map[MAX_N + 2][MAX_N + 2] = { 0, };
int cntMap[MAX_N + 2][MAX_N + 2] = { 0, };
// 1부터 사용
Node horseList[MAX_K + 1] = { {0, 0, 0, 0}, };

void init(void)
{
	for (int r = 0; r < MAX_N + 2; r++)
	{
		for (int c = 0; c < MAX_N + 2; c++)
		{
			map[r][c] = 2;
		}
	}

	return;
}

void input(void)
{
	scanf("%d %d", &N, &K);

	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			scanf("%d", &map[r][c]);
		}
	}

	for (int i = 1; i <= K; i++)
	{
		scanf("%d %d %d", &horseList[i].r, &horseList[i].c, &horseList[i].dir);

		// 같은 칸에 말이 두 개 이상 있는 경우는 입력으로 주어지지 않는다
		horseList[i].pos = 1;

		cntMap[horseList[i].r][horseList[i].c]++;
	}

	return;
}

// now번째 말을 (nowR, nowC) -> (nextR, nextC)로 이동
bool moveWhite(int now, int nowR, int nowC, int nowPos, int nextR, int nextC)
{
	int posCnt = 0;

	// 1. 일단 다음 칸으로 이동 
	// 해당 말 위에 있는 말까지 함께 이동
	// 2. 원래 있던 칸에서 없애준다 
	// 해당 말 위에 있는 말까지 함께 삭제
	while (true)
	{
		int flag = 0;

		for (int i = 1; i <= K; i++)
		{
			// 자신 포함, 좌표가 같고 위치가 자신보다 높거나 같다면
			if ((horseList[i].r == nowR) && (horseList[i].c == nowC) && (horseList[i].pos == (nowPos + posCnt)))
			{
				// 이동 후 삭제
				horseList[i].r = nextR;
				horseList[i].c = nextC;
				horseList[i].pos = ++cntMap[nextR][nextC];
				cntMap[nowR][nowC]--;
				posCnt++;
				flag = 1;

				if (cntMap[nextR][nextC] == MIN_HORSE)
				{
					return true;
				}

				break;
			}
		}

		if (flag == 0)
		{
			break;
		}
	}

	return false;
}

void reverseOrder(int now, int nowR, int nowC, int nowPos)
{
	int reverseCnt = 0;

	for (int i = 1; i <= K; i++)
	{
		// 자신 포함, 좌표가 같고 자신보다 높거나 같은 위치에 있는 말들 갯수 세기
		if ((horseList[i].r == nowR) && (horseList[i].c == nowC) && (horseList[i].pos >= nowPos))
		{
			reverseCnt++;
		}
	}

	for (int i = 1; i <= K; i++)
	{
		// 자신 포함, 좌표가 같고 자신보다 높거나 같은 위치에 있는 말들 위치 바꾸기
		if ((horseList[i].r == nowR) && (horseList[i].c == nowC) && (horseList[i].pos >= nowPos))
		{
			horseList[i].pos = (nowPos * 2) + reverseCnt - horseList[i].pos - 1;
		}
	}

	return;
}

bool simulate(void)
{
	bool ret = false;

	// 1번 말부터 K번 말까지 움직인다
	// cntMap과 horseList에 집중
	for (int i = 1; i <= K; i++)
	{
		int dr = horseList[i].r + directR[horseList[i].dir];
		int dc = horseList[i].c + directC[horseList[i].dir];

		// 흰색이라면
		if (map[dr][dc] == 0)
		{
			// 기본 이동
			ret = moveWhite(i, horseList[i].r, horseList[i].c, horseList[i].pos, dr, dc);
		}
		// 빨간색이라면
		else if (map[dr][dc] == 1)
		{
			// 기본 이동
			ret = moveWhite(i, horseList[i].r, horseList[i].c, horseList[i].pos, dr, dc);

			// 위치 뒤집기
			reverseOrder(i, horseList[i].r, horseList[i].c, horseList[i].pos);
		}
		// 파란색이라면
		else if (map[dr][dc] == 2)
		{
			// 이동 방향을 반대로 하고 다음 이동 위치 다시 계산
			horseList[i].dir = changeDir[horseList[i].dir];
			dr = horseList[i].r + directR[horseList[i].dir];
			dc = horseList[i].c + directC[horseList[i].dir];

			// 흰색이라면
			if (map[dr][dc] == 0)
			{
				// 기본 이동
				ret = moveWhite(i, horseList[i].r, horseList[i].c, horseList[i].pos, dr, dc);
			}
			// 빨간색이라면
			else if (map[dr][dc] == 1)
			{
				// 기본 이동
				ret = moveWhite(i, horseList[i].r, horseList[i].c, horseList[i].pos, dr, dc);

				// 위치 뒤집기
				reverseOrder(i, horseList[i].r, horseList[i].c, horseList[i].pos);
			}
			// 파란색이라면
			else if (map[dr][dc] == 2)
			{
				// 가만히 있는다
				continue;
			}
		}

		if (ret)
		{
			return true;
		}
	}

	return false;
}

bool ansCheck()
{
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			if (cntMap[r][c] == MIN_HORSE)
			{
				return true;
			}
		}
	}

	return false;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);
	// freopen("input3.txt", "r", stdin);
	// freopen("input4.txt", "r", stdin);
	// freopen("input5.txt", "r", stdin);

	setbuf(stdout, NULL);

	int ans = 0;
	bool ret = false;

	// Barrier 초기화
	init();

	input();

	while (true)
	{
		// 불가능한 경우
		if (ans > MAX_ANS)
		{
			ans = -1;

			break;
		}

		/*
		// 정답 나온 경우
		ret = ansCheck();

		if (ret)
		{
			break;
		}
		*/

		// 다음 턴으로
		ans++;

		// 한 턴 실행
		ret = simulate();

		int debug = 1;

		if (ret)
		{
			break;
		}
	}

	printf("%d\n", ans);

	return 0;
}
