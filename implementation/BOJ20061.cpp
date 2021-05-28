#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#define MAX_N 10000
#define MAX_T 3
#define BOARD_H 6
#define BOARD_W 4
#define SPECIAL_H 2
#define SPECIAL_W 4

struct BlockNode
{
	// 블록의 종류
	int t;
	// 기준 블록의 위치
	int r;
	int c;
};

// 핵심 아이디어 : 파란색 보드를 90도 회전시켜서 초록색 보드와 똑같은 원리로 사용!!!
// 블록을 놓은 횟수
int N;
// 블록을 모두 놓았을 때 얻은 점수
int score;
// 파란색 보드와 초록색 보드에서 타일이 들어있는 칸의 개수
int tileCnt;
// 파란색 보드에서 각 행에 타일이 채워진 갯수 기록
int blueRowTileCntArr[BOARD_H];
// 초록색 보드에서 각 행에 타일이 채워진 갯수 기록
int greenRowTileCntArr[BOARD_H];
// 파란색 보드로 놓을 때 타입 변경 시 사용
int typeConvertArr[MAX_T + 1] = { 0, 1, 3, 2 };
// 파란색 보드
int blueBoard[BOARD_H][BOARD_W];
// 초록색 보드
int greenBoard[BOARD_H][BOARD_W];
// 블록을 놓은 정보
BlockNode blockArr[MAX_N + 1];

void inputData(void)
{
	std::cin >> N;

	for (register int i = 1; i <= N; i++)
	{
		std::cin >> blockArr[i].t >> blockArr[i].r >> blockArr[i].c;
	}

	return;
}

BlockNode getConvertedBlock(BlockNode curBlock)
{
	BlockNode result = { typeConvertArr[curBlock.t], curBlock.c, BOARD_W - curBlock.r - 1 };

	if (curBlock.t == 3)
	{
		result.c--;
	}

	return result;
}

void moveBlock(int curBoard[BOARD_H][BOARD_W], int curRowTileCntArr[BOARD_W], int blockIdx, BlockNode& curBlock)
{
	int targetR = BOARD_H - 1;

	switch (curBlock.t)
	{
		case 1:
		{
			// 열은 이미 정해졌고, 위치할 행 찾기
			for (register int r = BOARD_H - 1; r >= SPECIAL_H; r--)
			{
				// 해당 칸에 블록이 있다면 그 아래로는 놓을 수 없음
				if (curBoard[r][curBlock.c] != 0)
				{
					targetR = r - 1;
				}
			}

			// 찾은 위치에 블록 놓기
			curBoard[targetR][curBlock.c] = blockIdx;

			// 블록 갯수 갱신
			curRowTileCntArr[targetR] += 1;

			break;
		}
		case 2:
		{
			// 열은 이미 정해졌고, 위치할 행 찾기
			for (register int r = BOARD_H - 1; r >= SPECIAL_H; r--)
			{
				// 해당 칸에 블록이 있다면 그 아래로는 놓을 수 없음
				// 두 칸 모두 확인해야 함
				if ((curBoard[r][curBlock.c] != 0) || (curBoard[r][curBlock.c + 1] != 0))
				{
					targetR = r - 1;
				}
			}

			// 찾은 위치에 블록 놓기
			curBoard[targetR][curBlock.c] = blockIdx;
			curBoard[targetR][curBlock.c + 1] = blockIdx;

			// 블록 갯수 갱신
			curRowTileCntArr[targetR] += 2;

			break;
		}
		case 3:
		{
			// 열은 이미 정해졌고, 위치할 행 찾기
			for (register int r = BOARD_H - 1; r >= SPECIAL_H; r--)
			{
				// 해당 칸에 블록이 있다면 그 아래로는 놓을 수 없음
				if (curBoard[r][curBlock.c] != 0)
				{
					targetR = r - 1;
				}
			}

			// 찾은 위치에 블록 놓기
			curBoard[targetR][curBlock.c] = blockIdx;
			curBoard[targetR - 1][curBlock.c] = blockIdx;

			// 블록 갯수 갱신
			curRowTileCntArr[targetR] += 1;
			curRowTileCntArr[targetR - 1] += 1;

			break;
		}
		default:
		{
			break;
		}
	}

	return;
}

void removeBlock(int curBoard[BOARD_H][BOARD_W], int curRowTileCntArr[BOARD_H])
{
	// 사라진 제일 아래 행
	int targetR = -1;
	// 사라진 행의 갯수
	int removeRowCnt = 0;

	// 특별한 구간은 제외
	for (register int r = BOARD_H - 1; r >= SPECIAL_H; r--)
	{
		// 제거할 필요 없다면 다음 행 확인
		if (curRowTileCntArr[r] < BOARD_W)
		{
			continue;
		}

		// 해당 행에 타일이 4개 차 있다면 제거
		for (register int c = 0; c < BOARD_W; c++)
		{
			curBoard[r][c] = 0;
		}

		targetR = r;
		curRowTileCntArr[r] = 0;

		// 그 윗 줄만 확인하면 됨
		if (curRowTileCntArr[r - 1] < BOARD_W)
		{
			removeRowCnt += 1;

			break;
		}

		// 해당 행에 타일이 4개 차 있다면 제거
		for (register int c = 0; c < BOARD_W; c++)
		{
			curBoard[r][c] = 0;
		}

		removeRowCnt += 2;
		curRowTileCntArr[r - 1] = 0;

		// 두 줄 이상 제거되지 않는다
		break;
	}

	// 제거된 행이 없으면 더 할 일 없음
	if (removeRowCnt == 0)
	{
		return;
	}

	// 제거된 만큼 아래로 내려주기
	for (register int r = targetR; r >= SPECIAL_H; r--)
	{
		for (register int c = 0; c < BOARD_W; c++)
		{
			curBoard[r][c] = curBoard[r - removeRowCnt][c];
		}

		curRowTileCntArr[r] = curRowTileCntArr[r - removeRowCnt];
	}

	// Garbage Clear
	for (register int r = SPECIAL_H - 1; r >= 0; r--)
	{
		for (register int c = 0; c < BOARD_W; c++)
		{
			curBoard[r][c] = 0;
		}

		curRowTileCntArr[r] = 0;
	}

	// 점수에 추가
	score += removeRowCnt;

	return;
}

void specialMoveBlock(int curBoard[BOARD_H][BOARD_W], int curRowTileCntArr[BOARD_H])
{
	// 사라진 행의 갯수
	int specialRowCnt = 0;

	// 특별한 구간은 제외
	for (register int r = SPECIAL_H - 1; r >= 0; r--)
	{
		// 타일이 하나라도 있으면 이동해야 함
		if (curRowTileCntArr[r] > 0)
		{
			specialRowCnt++;
		}
	}

	// 제거된 행이 없으면 더 할 일 없음
	if (specialRowCnt == 0)
	{
		return;
	}

	// 제거된 만큼 아래로 내려주기
	for (register int r = BOARD_H - 1; r >= specialRowCnt; r--)
	{
		for (register int c = 0; c < BOARD_W; c++)
		{
			curBoard[r][c] = curBoard[r - specialRowCnt][c];
		}

		curRowTileCntArr[r] = curRowTileCntArr[r - specialRowCnt];
	}

	// Garbage Clear
	for (register int r = specialRowCnt - 1; r >= 0; r--)
	{
		for (register int c = 0; c < BOARD_W; c++)
		{
			curBoard[r][c] = 0;
		}

		curRowTileCntArr[r] = 0;
	}

	return;
}

void solve(void)
{
	// 블록을 놓은 횟수만큼 진행
	for (register int i = 1; i <= N; i++)
	{
		// 파란색 보드에 놓는 위치를 바꿔주어야 한다!
		BlockNode convertedBlock = getConvertedBlock(blockArr[i]);

		// 1-G. 블록을 놓을 위치를 빨간색 보드에서 선택하면, 그 위치부터 초록색 보드로 블록이 이동하고, 
		// 블록의 이동은 다른 블록을 만나거나 보드의 경계를 만나기 전까지 계속해서 이동한다. 
		moveBlock(greenBoard, greenRowTileCntArr, i, blockArr[i]);

		// 1-B. 블록을 놓을 위치를 빨간색 보드에서 선택하면, 파란색 보드로 블록이 이동한다. 
		// 블록의 이동은 다른 블록을 만나거나 보드의 경계를 만나기 전까지 계속해서 이동한다. 
		moveBlock(blueBoard, blueRowTileCntArr, i, convertedBlock);

		// 2-G. 이렇게 초록색 보드에서 어떤 행이 타일로 가득 차 있다면, 그 행의 타일은 모두 사라진다. 
		// 사라진 이후에는 초록색 보드에서 사라진 행의 위에 있는 블록이 사라진 행의 수만큼 아래로 이동한다. 
		removeBlock(greenBoard, greenRowTileCntArr);

		// 2-B. 파란색의 경우는 열이 타일로 가득 차 있으면, 그 열의 타일이 모두 사라지며, 
		// 사라진 이후에는 파란색 보드에서 사라진 열의 왼쪽에 있는 블록이 사라진 열의 수만큼 오른쪽으로 이동한다. 
		removeBlock(blueBoard, blueRowTileCntArr);

		// 3-G. 초록색 보드의 0, 1번 행에 블록이 있으면, 블록이 있는 행의 수만큼 아래 행에 있는 타일이 사라지고, 
		// 초록색 보드의 모든 블록이 사라진 행의 수만큼 아래로 이동하고, 
		specialMoveBlock(greenBoard, greenRowTileCntArr);

		// 3-B. 파란색 보드의 0, 1번 열에 블록이 있으면, 블록이 있는 열의 수만큼 오른쪽 열에 있는 타일이 사라지고, 
		// 파란색 보드의 모든 블록이 사라진 열의 수만큼 이동하게 된다. 
		specialMoveBlock(blueBoard, blueRowTileCntArr);
	}

	return;
}

void outputAnswer(void)
{
	for (register int r = SPECIAL_H; r < BOARD_H; r++)
	{
		tileCnt += blueRowTileCntArr[r];
		tileCnt += greenRowTileCntArr[r];
	}

	std::cout << score << '\n';
	std::cout << tileCnt << '\n';

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);	// 0 2
	// freopen("input2.txt", "r", stdin);	// 0 6
	// freopen("input3.txt", "r", stdin);	// 1 10
	// freopen("input4.txt", "r", stdin);	// 1 12
	// freopen("input5.txt", "r", stdin);	// 1 16
	// freopen("input6.txt", "r", stdin);	// 1 18
	// freopen("input7.txt", "r", stdin);	// 2 15

	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	inputData();

	solve();

	outputAnswer();

	return 0;
}
