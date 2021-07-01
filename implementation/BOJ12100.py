import sys;
import copy;

DIR_CNT = 4;

def convert(N : int, originalList : list) -> list:
    newList = [k for k in originalList if k];

    for k in range(1, len(newList)):
        if (newList[k - 1] == newList[k]):
            newList[k - 1] *= 2;
            newList[k] = 0;

    newList = [k for k in newList if k];

    return (newList + ([0] * (N - len(newList))));

def rotate90(N : int, boardArray : list) -> list:
    newList = copy.deepcopy(boardArray);

    for r in range(N):
        for c in range(N):
            newList[c][N - r - 1] = boardArray[r][c];

    return newList;

def dfs(N, boardArray, remainDepth):
    maxVal = max([max(k) for k in boardArray]);

    if (remainDepth == 0):
        return maxVal;

    for curDIR in range(DIR_CNT):
        convertResult = [convert(N, k) for k in boardArray];

        if (convertResult != boardArray):
            maxVal = max(maxVal, dfs(N, convertResult, remainDepth - 1));

        boardArray = rotate90(N, boardArray);

    return maxVal;

# sys.stdin = open("input1.txt", 'r');

N = int(sys.stdin.readline());
boardArray = [list(map(int, sys.stdin.readline().split())) for _ in range(N)];

# print(N);
# print(boardArray);

print(dfs(N, boardArray, 5));
