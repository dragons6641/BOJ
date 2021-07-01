import sys;
import collections;

COL_CNT = 10;
DIR_VEC = [[-1, 0], [1, 0], [0, -1], [0, 1]];

def bfs(startR : int, startC : int) -> int:
    curDisappearCnt = 0;
    regionList = [[startR, startC]];
    dq = collections.deque([[startR, startC, 1]]);

    while (dq):
        (curR, curC, curCnt) = dq.popleft();

        for (dr, dc) in DIR_VEC:
            nextR = curR + dr;
            nextC = curC + dc;

            if ((nextR < 0) or (nextR >= N) or (nextC < 0) or (nextC >= COL_CNT) or (isVisitedArray[nextR][nextC]) or (boardArray[curR][curC] != boardArray[nextR][nextC])):
                continue;

            isVisitedArray[nextR][nextC] = True;
            regionList.append([nextR, nextC]);
            dq.append([nextR, nextC, curCnt + 1]);

    if (len(regionList) >= K):
        for (curR, curC) in regionList:
            curDisappearCnt += 1;
            boardArray[curR][curC] = '0';

    return curDisappearCnt;

# sys.stdin = open("input1.txt", 'r');

boardArray = [];

(N, K) = map(int, input().split());

for curR in range(N):
    boardArray.append(list(input()));

# print(N, K);
# print(boardArray);

while (True):
    totalDisappearCnt = 0;
    isVisitedArray = [[False for _ in range(COL_CNT)] for _ in range(N)];

    for curR in range(N):
        for curC in range(COL_CNT):
            if (isVisitedArray[curR][curC] or (boardArray[curR][curC] == '0')):
                continue;

            # print(curR, curC);

            # for _ in isVisitedArray:
            #     print(_);

            isVisitedArray[curR][curC] = True;
            totalDisappearCnt += bfs(curR, curC);

    # for _ in boardArray:
    #     print(_);

    for curC in range(COL_CNT):
        nonZeroList = [];

        for curR in range(N):
            if (boardArray[curR][curC] == '0'):
                continue;

            nonZeroList.append([curR, boardArray[curR][curC]]);

        # print(nonZeroList);

        for curIdx in range(len(nonZeroList) - 1, -1, -1):
            srcR = nonZeroList[curIdx][0];
            dstR = N - len(nonZeroList) + curIdx;

            # print(srcR, dstR, curC);

            if (srcR == dstR):
                continue;

            boardArray[dstR][curC] = boardArray[srcR][curC];
            boardArray[srcR][curC] = '0';

    # for _ in boardArray:
    #     print(_);

    # print();

    if (totalDisappearCnt == 0):
        break;

for curBoard in boardArray:
    print(''.join(curBoard));
