#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#define MAX_N 50
#define MAX_M 100
#define MAX_A 100
#define MAX_DIR 8
#define MAX_SHIFT 50
#define MAX_CLOUD_CNT (MAX_N * MAX_N)
#define WATER_INCREASE_AMOUNT 1
#define WATER_DECREASE_AMOUNT 2

struct CloudNode
{
	// 구름의 위치
	int r;
	int c;
};

struct MoveNode
{
	// 이동 방향
	int dir;
	// 이동 거리
	int shift;
};

// 격자의 크기
int N;
// 이동 횟수
int M;
// 바구니에 들어있는 물의 양의 합
int answer;
// 현재 구름의 갯수
int cloudCnt;
// 방향은 총 8개의 방향이 있으며, 8개의 정수로 표현한다. 
// 1부터 순서대로 ←, ↖, ↑, ↗, →, ↘, ↓, ↙ 이다. 
int dr[MAX_DIR + 1] = { 0, 0, -1, -1, -1, 0, 1, 1, 1 };
int dc[MAX_DIR + 1] = { 0, -1, -1, 0, 1, 1, 1, 0, -1 };
// 비바라기 격자판
int rainArr[MAX_N + 2][MAX_N + 2];
// 구름이 있는지 없는지 체크
bool isCloud[MAX_N + 2][MAX_N + 2];
// 구름 정보
CloudNode cloudArr[MAX_CLOUD_CNT];
// 이동 정보
MoveNode moveArr[MAX_M];

void inputData(void)
{
	std::cin >> N >> M;

	for (register int r = 1; r <= N; r++)
	{
		for (register int c = 1; c <= N; c++)
		{
			std::cin >> rainArr[r][c];
		}
	}

	for (register int i = 0; i < M; i++)
	{
		std::cin >> moveArr[i].dir >> moveArr[i].shift;
	}

	return;
}

void initCloud(void)
{
	for (register int r = N - 1; r <= N; r++)
	{
		for (register int c = 1; c <= 2; c++)
		{
			cloudArr[cloudCnt++] = { r, c };
		}
	}

	return;
}

int getNextPos(int curPos, int dir, int shift, int dPos[])
{
	// 격자가 무한히 클 경우를 가정한 위치 계산
	int nextPos = curPos + (dPos[dir] * shift);

	// 0 이하의 값을 가지는 경우 0 초과로 만들기
	while (nextPos <= 0)
	{
		nextPos += N;
	}

	// N 초과의 값을 가지는 경우 N 미만으로 만들기
	while (nextPos > N)
	{
		nextPos -= N;
	}

	return nextPos;
}

void moveCloud(int moveIdx)
{
	int dir = moveArr[moveIdx].dir;
	int shift = moveArr[moveIdx].shift;

	// 각 구름 모두 이동
	for (register int i = 0; i < cloudCnt; i++)
	{
		// 현재 구름의 위치
		int curR = cloudArr[i].r;
		int curC = cloudArr[i].c;

		// 다음 구름의 위치 계산
		int nextR = getNextPos(curR, dir, shift, dr);
		int nextC = getNextPos(curC, dir, shift, dc);

		// 다음 위치로 구름 이동
		cloudArr[i] = { nextR, nextC };
		isCloud[nextR][nextC] = true;

		// 비 내리기
		rainArr[nextR][nextC] += WATER_INCREASE_AMOUNT;
	}

	return;
}

void waterCopyBug(int moveIdx)
{
	// 비가 내린 칸 모두 확인
	for (register int i = 0; i < cloudCnt; i++)
	{
		// 현재 칸의 위치
		int curR = cloudArr[i].r;
		int curC = cloudArr[i].c;

		// 대각선 4방향 모두 확인
		for (register int dir = 2; dir <= MAX_DIR; dir += 2)
		{
			// 대각선 칸의 위치
			int nextR = curR + dr[dir];
			int nextC = curC + dc[dir];

			// 해당 대각선 칸에 물이 있으면 현재 칸에 물 증가
			if (rainArr[nextR][nextC] > 0)
			{
				rainArr[curR][curC] += WATER_INCREASE_AMOUNT;
			}
		}
	}

	return;
}

void resetCloud(int moveIdx)
{
	cloudCnt = 0;

	// 모든 칸 확인
	for (register int r = 1; r <= N; r++)
	{
		for (register int c = 1; c <= N; c++)
		{
			// 구름이 사라진 칸인 경우 구름 제거
			if (isCloud[r][c])
			{
				isCloud[r][c] = false;

				continue;
			}

			// 물의 양이 2 이상인 경우 구름 생성 후 물 감소
			if (rainArr[r][c] >= WATER_DECREASE_AMOUNT)
			{
				cloudArr[cloudCnt++] = { r, c };
				rainArr[r][c] -= WATER_DECREASE_AMOUNT;
			}
		}
	}

	return;
}

void getAnswer(void)
{
	for (register int r = 1; r <= N; r++)
	{
		for (register int c = 1; c <= N; c++)
		{
			answer += rainArr[r][c];
		}
	}

	return; 
}

void solve(void)
{
	// M번의 이동
	for (register int i = 0; i < M; i++)
	{
		// 1. 모든 구름이 di 방향으로 si칸 이동한다.
		// 2. 각 구름에서 비가 내려 구름이 있는 칸의 바구니에 저장된 물의 양이 1 증가한다.
		moveCloud(i);

		// 4. 2에서 물이 증가한 칸 (r, c)에 물복사버그 마법을 시전한다. 
		// 물복사버그 마법을 사용하면, 
		// 대각선 방향으로 거리가 1인 칸에 물이 있는 바구니의 수만큼 (r, c)에 있는 바구니의 물이 양이 증가한다. 
		waterCopyBug(i);

		// 3. 구름이 모두 사라진다. 
		// 5. 바구니에 저장된 물의 양이 2 이상인 모든 칸에 구름이 생기고, 
		// 물의 양이 2 줄어든다. 
		// 이때 구름이 생기는 칸은 3에서 구름이 사라진 칸이 아니어야 한다. 
		resetCloud(i);
	}

	getAnswer();

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);	// 77
	// freopen("input2.txt", "r", stdin);	// 41
	// freopen("input3.txt", "r", stdin);	// 2657

	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	inputData();

	initCloud();

	solve();

	std::cout << answer;

	return 0;
}
