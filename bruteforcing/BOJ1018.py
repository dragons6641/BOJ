import sys;
import math;

CHESS_ROW_CNT = 8;
CHESS_COL_CNT = 8;

def checkBoard(boardArray : int, startR : int, startC : int) -> int:
    diffCnt = 0;
    startSquareList = [boardArray[startR][startC], 'W' if (boardArray[startR][startC] == 'B') else 'B'];

    # print(startSquareList);

    for curR in range(startR, startR + CHESS_ROW_CNT):
        for curC in range(startC, startC + CHESS_COL_CNT):
            if (boardArray[curR][curC] != startSquareList[(curR + curC) % 2]):
                diffCnt += 1;

    # print(diffCnt, (CHESS_ROW_CNT * CHESS_COL_CNT) - diffCnt);

    return min(diffCnt, (CHESS_ROW_CNT * CHESS_COL_CNT) - diffCnt);

# sys.stdin = open("input1.txt", 'r');
# sys.stdin = open("input2.txt", 'r');

(N, M) = map(int, input().split());
boardArray = [input() for _ in range(N)];

# print(N, M);
# print(boardArray);

answer = math.inf;

for startR in range(N - CHESS_ROW_CNT + 1):
    for startC in range(M - CHESS_COL_CNT + 1):
        # print(startR, startC);
        # print(checkBoard(boardArray, startR, startC));

        answer = min(answer, checkBoard(boardArray, startR, startC));

print(answer);
