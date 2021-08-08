import sys;

ZONE_LEN = 3;
NUM_CNT = ZONE_LEN ** 2;
POS_CNT = NUM_CNT ** 2;

def getZone(curR : int, curC : int):
    return (((curR // ZONE_LEN) * ZONE_LEN) + (curC // ZONE_LEN));

def init() -> None:
    for r in range(NUM_CNT):
        for c in range(NUM_CNT):
            if (sudokuList[r][c] == 0):
                continue;

            rowVisitedList[r][sudokuList[r][c]] = True;
            colVisitedList[c][sudokuList[r][c]] = True;
            zoneVisitedList[getZone(r, c)][sudokuList[r][c]] = True;

def printSudokuList() -> None:
    for r in range(NUM_CNT):
        for c in range(NUM_CNT):
            print(sudokuList[r][c], end = '');

        print();

    return;

def backtrack(curPos : int) -> None:
    if (curPos == POS_CNT):
        printSudokuList();
        sys.exit(0);

    (curR, curC) = (divmod(curPos, NUM_CNT));
    curZone = getZone(curR, curC);

    # print(curR, curC, curZone);

    if (sudokuList[curR][curC] > 0):
        backtrack(curPos + 1);
        return;

    for curNum in range(1, NUM_CNT + 1):
        if ((rowVisitedList[curR][curNum]) or (colVisitedList[curC][curNum]) or (zoneVisitedList[curZone][curNum])):
            continue;

        (rowVisitedList[curR][curNum], colVisitedList[curC][curNum], zoneVisitedList[curZone][curNum]) = (True, True, True);
        sudokuList[curR][curC] = curNum;

        backtrack(curPos + 1);

        (rowVisitedList[curR][curNum], colVisitedList[curC][curNum], zoneVisitedList[curZone][curNum]) = (False, False, False);
        sudokuList[curR][curC] = 0;

    return;

# sys.stdin = open("input1.txt", 'r');

sudokuList = [list(map(int, list(input()))) for _ in range(NUM_CNT)];

rowVisitedList = [[False for _ in range(NUM_CNT + 1)] for _ in range(NUM_CNT)];
colVisitedList = [[False for _ in range(NUM_CNT + 1)] for _ in range(NUM_CNT)];
zoneVisitedList = [[False for _ in range(NUM_CNT + 1)] for _ in range(NUM_CNT)];

init();
backtrack(0);
