#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>
#include <queue>

#define MAX_N 20
#define MAX_M 5
#define MAX_DIR 4
#define MIN_BLOCK_CNT 2
#define EMPTY_BLOCK -2
#define BLACK_BLOCK -1
#define RAINBOW_BLOCK 0

struct BlockNode
{
	// 블록의 위치
	int r;
	int c;
};

struct StandardBlockNode
{
	// 블록의 위치
	int r;
	int c;
	// 해당 블록 그룹 전체 블록의 갯수
	int blockCnt;
	// 해당 블록 그룹 무지개 블록의 갯수
	int rainbowBlockCnt;

	bool operator < (const StandardBlockNode& cmpStandardBlock)
	{
		// 크기가 가장 큰 블록 그룹을 찾는다.
		if (this->blockCnt == cmpStandardBlock.blockCnt)
		{
			// 그러한 블록 그룹이 여러 개라면 포함된 무지개 블록의 수가 가장 많은 블록 그룹, 
			if (this->rainbowBlockCnt == cmpStandardBlock.rainbowBlockCnt)
			{
				// 그러한 블록도 여러개라면 기준 블록의 행이 가장 큰 것을, 
				// 그 것도 여러개이면 열이 가장 큰 것을 찾는다. 
				return (((this->r * MAX_N) + this->c) > ((cmpStandardBlock.r * MAX_N) + cmpStandardBlock.c));
			}

			return (this->rainbowBlockCnt > cmpStandardBlock.rainbowBlockCnt);
		}

		return (this->blockCnt > cmpStandardBlock.blockCnt);
	}
};

// 격자 한 변의 크기
int N;
// 색상의 개수
int M;
// 획득한 점수의 합
int answer;
// 전체 블록의 갯수
// 블록이 제거되면 변경
int totalBlockCnt;
// 검정 블록의 갯수
// 블록이 제거되어도 변경되지 않음
int totalBlackBlockCnt;
// 무지개 블록의 갯수
// 블록이 제거되면 변경
int totalRainbowBlockCnt = MIN_BLOCK_CNT;
// 인접한 4방향 확인
int dr[MAX_DIR] = { -1, 1, 0, 0 };
int dc[MAX_DIR] = { 0, 0, -1, 1 };
// 게임 격자판
int gameArr[MAX_N + 2][MAX_N + 2];
// 방문 여부 표시
bool isVisitedArr[MAX_N + 2][MAX_N + 2];
// 무지개 블록 정보
BlockNode rainbowBlockArr[MAX_N * MAX_N];

void inputData(void)
{
	std::cin >> N >> M;

	totalBlockCnt = N * N;

	for (register int r = 1; r <= N; r++)
	{
		for (register int c = 1; c <= N; c++)
		{
			std::cin >> gameArr[r][c];

			if (gameArr[r][c] == BLACK_BLOCK)
			{
				totalBlackBlockCnt++;
			}
		}
	}

	return;
}

void initGameArr(void)
{
	for (register int r = 0; r <= N + 1; r++)
	{
		gameArr[r][0] = BLACK_BLOCK;
		gameArr[r][N + 1] = BLACK_BLOCK;
	}

	for (register int c = 0; c <= N + 1; c++)
	{
		gameArr[0][c] = BLACK_BLOCK;
		gameArr[N + 1][c] = BLACK_BLOCK;
	}

	return;
}

void initIsVisitedArr(void)
{
	for (register int r = 1; r <= N; r++)
	{
		for (register int c = 1; c <= N; c++)
		{
			isVisitedArr[r][c] = false;
		}
	}

	return;
}

void setRainbowBlockArr(void)
{
	totalRainbowBlockCnt = 0;

	for (register int r = 1; r <= N; r++)
	{
		for (register int c = 1; c <= N; c++)
		{
			if (gameArr[r][c] == RAINBOW_BLOCK)
			{
				rainbowBlockArr[totalRainbowBlockCnt++] = { r, c };
			}
		}
	}

	return; 
}

bool isStandardPossible(int r, int c)
{
	// 일반 블록인 경우에만 기준 블록이 될 수 있음
	if ((gameArr[r][c] <= 0) || (gameArr[r][c] > M))
	{
		return false;
	}

	// 아직 방문하지 않은 경우에만 기준 블록이 될 수 있음
	if (isVisitedArr[r][c])
	{
		return false;
	}

	return true;
}

bool isBFSPossible(int r, int c, int standardColor)
{
	// 기준 블록과 같은 블록이거나 무지개 블록인 경우에만 진행 가능
	if ((gameArr[r][c] != standardColor) && (gameArr[r][c] != RAINBOW_BLOCK))
	{
		return false;
	}

	// 아직 방문하지 않은 경우에만 진행 가능
	if (isVisitedArr[r][c])
	{
		return false;
	}

	return true;
}

StandardBlockNode groupBFS(int standardR, int standardC)
{
	// 기준 블록의 색깔
	int standardColor = gameArr[standardR][standardC];
	// 기준 블록 정보
	StandardBlockNode result = {standardR, standardC, 1, 0};
	// bfs에 사용할 큐
	std::queue<StandardBlockNode> bfsQueue;

	// 시작점 방문 표시 후 큐에 넣기
	isVisitedArr[standardR][standardC] = true;
	bfsQueue.push({ standardR, standardC });

	// 큐
	while (!bfsQueue.empty())
	{
		StandardBlockNode curBlock = bfsQueue.front();
		bfsQueue.pop();

		// 인접한 4개 방향 확인
		for (register int dir = 0; dir < MAX_DIR; dir++)
		{
			int nextR = curBlock.r + dr[dir];
			int nextC = curBlock.c + dc[dir];

			// 진행이 불가능한 경우 체크
			if (!isBFSPossible(nextR, nextC, standardColor))
			{
				continue;
			}

			result.blockCnt++;

			// 무지개 블록인 경우 갯수 추가
			if (gameArr[nextR][nextC] == RAINBOW_BLOCK)
			{
				result.rainbowBlockCnt++;
			}

			// 다음 진행 지점 방문 표시 후 큐에 넣기
			isVisitedArr[nextR][nextC] = true;
			bfsQueue.push({ nextR, nextC });
		}
	}

	return result;
}

void removeBFS(StandardBlockNode curStandardBlock)
{
	// 기준 블록의 위치
	int standardR = curStandardBlock.r;
	int standardC = curStandardBlock.c;
	// 기준 블록의 색깔
	int standardColor = gameArr[standardR][standardC];
	// bfs에 사용할 큐
	std::queue<StandardBlockNode> bfsQueue;

	// 시작점 블록 삭제
	gameArr[standardR][standardC] = EMPTY_BLOCK;

	// 시작점 방문 표시 후 큐에 넣기
	isVisitedArr[standardR][standardC] = true;
	bfsQueue.push({ standardR, standardC });

	// 큐
	while (!bfsQueue.empty())
	{
		StandardBlockNode curBlock = bfsQueue.front();
		bfsQueue.pop();

		// 인접한 4개 방향 확인
		for (register int dir = 0; dir < MAX_DIR; dir++)
		{
			int nextR = curBlock.r + dr[dir];
			int nextC = curBlock.c + dc[dir];

			// 진행이 불가능한 경우 체크
			if (!isBFSPossible(nextR, nextC, standardColor))
			{
				continue;
			}

			// 다음 블록 삭제
			gameArr[nextR][nextC] = EMPTY_BLOCK;

			// 다음 진행 지점 방문 표시 후 큐에 넣기
			isVisitedArr[nextR][nextC] = true;
			bfsQueue.push({ nextR, nextC });
		}
	}

	return;
}

void applyGravity(void)
{
	for (register int c = N; c > 0; c--)
	{
		for (register int r = N - 1; r > 0; r--)
		{
			register int nextR = r + 1;

			// 현재 칸이 빈 칸이거나 검은색 블록이면 낙하 불가
			if ((gameArr[r][c] == EMPTY_BLOCK) || (gameArr[r][c] == BLACK_BLOCK))
			{
				continue;
			}

			while (nextR <= N + 1)
			{
				// 빈 칸인 경우에만 해당 칸에 낙하 가능
				if (gameArr[nextR][c] != EMPTY_BLOCK)
				{
					nextR--;

					break;
				}

				nextR++;
			}

			// 낙하가 필요없는 경우 다음 반복문으로
			if (nextR == r)
			{
				continue;
			}

			// 해당 칸으로 낙하
			gameArr[nextR][c] = gameArr[r][c];
			gameArr[r][c] = EMPTY_BLOCK;
		}
	}

	return;
}

void rotate90DegreesCounterclockwise(void)
{
	int tmpGameArr[MAX_N + 2][MAX_N + 2];

	// 임시 배열에 백업
	for (register int r = 1; r <= N; r++)
	{
		for (register int c = 1; c <= N; c++)
		{
			tmpGameArr[N + 1 - c][r] = gameArr[r][c];
		}
	}

	// 원본 배열에 복구
	for (register int r = 1; r <= N; r++)
	{
		for (register int c = 1; c <= N; c++)
		{
			gameArr[r][c] = tmpGameArr[r][c];
		}
	}

	return;
}

void solve(void)
{
	// 검정 블록을 제외한 모든 블록이 사라질 때까지 진행
	while (totalBlockCnt > totalBlackBlockCnt)
	{
		// 블록 그룹 기준 블록의 갯수
		int standardBlockCnt = 0;
		// 블록 그룹 기준 블록의 정보
		StandardBlockNode standardBlockArr[MAX_N * MAX_N];

		// 방문 여부 초기화
		initIsVisitedArr();

		// 무지개 블록 정보 갱신
		if (totalRainbowBlockCnt > 0)
		{
			setRainbowBlockArr();
		}

		// 1. 크기가 가장 큰 블록 그룹을 찾는다. 
		// 그러한 블록 그룹이 여러 개라면 포함된 무지개 블록의 수가 가장 많은 블록 그룹, 
		// 그러한 블록도 여러개라면 기준 블록의 행이 가장 큰 것을, 
		// 그 것도 여러개이면 열이 가장 큰 것을 찾는다. 
		for (register int r = 1; r <= N; r++)
		{
			for (register int c = 1; c <= N; c++)
			{
				// 블록 그룹의 기준 블록이 될 수 있다면 블록 그룹 찾기
				if (!isStandardPossible(r, c))
				{
					continue;
				}

				StandardBlockNode curStandardBlock = groupBFS(r, c);

				standardBlockArr[standardBlockCnt++] = curStandardBlock;

				// 제거되지 않은 무지개 블록은 방문 여부 초기화
				for (register int i = 0; i < totalRainbowBlockCnt; i++)
				{
					isVisitedArr[rainbowBlockArr[i].r][rainbowBlockArr[i].c] = false;
				}
			}
		}

		// 문제의 기준에 맞게 정렬
		std::sort(standardBlockArr, standardBlockArr + standardBlockCnt);

		// 블록 그룹이 없을 경우 종료
		if (standardBlockCnt == 0)
		{
			break;
		}

		// 그룹에 속한 블록의 개수는 2보다 크거나 같아야 하며
		if (standardBlockArr[0].blockCnt < MIN_BLOCK_CNT)
		{
			break;
		}

		// 방문 여부 초기화
		initIsVisitedArr();

		// 2. 1에서 찾은 블록 그룹의 모든 블록을 제거한다. 
		removeBFS(standardBlockArr[0]);

		// 블록 갯수 갱신
		totalBlockCnt -= standardBlockArr[0].blockCnt;

		// 블록 그룹에 포함된 블록의 수를 B라고 했을 때, B2점을 획득한다. 
		answer += standardBlockArr[0].blockCnt * standardBlockArr[0].blockCnt;

		// 3. 격자에 중력이 작용한다. 
		applyGravity();

		// 4. 격자가 90도 반시계 방향으로 회전한다. 
		rotate90DegreesCounterclockwise();

		// 5. 다시 격자에 중력이 작용한다. 
		applyGravity();
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);	// 77
	// freopen("input2.txt", "r", stdin);	// 125
	// freopen("input3.txt", "r", stdin);	// 33
	// freopen("input4.txt", "r", stdin);	// 0
	// freopen("input5.txt", "r", stdin);	// 160000
	// freopen("input6.txt", "r", stdin);	// 0

	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	inputData();

	initGameArr();

	solve();

	std::cout << answer;

	return 0;
}
