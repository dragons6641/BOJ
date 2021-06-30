import sys;
import itertools;
import math;

DIR_VEC = [[0, 0], [-1, 0], [1, 0], [0, -1], [0, 1]];
DIR_CNT = 5;

def checkFlower(curR : int, curC : int, idxList = list[int]) -> int:
    curPrice = 0;

    for dirIdx in range(DIR_CNT):
        nextR = curR + DIR_VEC[dirIdx][0];
        nextC = curC + DIR_VEC[dirIdx][1];

        if (isVisitedArray[nextR][nextC]):
            return -1;

        isVisitedArray[nextR][nextC] = True;
        curPrice += flowerArray[nextR][nextC];
        idxList.append(dirIdx);

    return curPrice;

def initFlower(curR : int, curC : int, idxList = list[int]) -> None:
    for dirIdx in idxList:
        isVisitedArray[curR + DIR_VEC[dirIdx][0]][curC + DIR_VEC[dirIdx][1]] = False;

    return None;

# sys.stdin = open("input1.txt", 'r');

flowerArray = [];

N = int(input());

for curR in range(N):
    flowerArray.append(list(map(int, input().split())));

answer = math.inf;
isVisitedArray = [[False for _ in range(N)] for _ in range(N)];
tmpList = [k for k in range(1, N - 1)];
locationList = (list(itertools.product(tmpList, tmpList)));

# print(N);
# print(flowerArray);
# print(isVisitedArray);
# print(locationList);

for idx1 in range(len(locationList)):
    totalPrice = 0;
    idxList1 = [];
    (r1, c1) = locationList[idx1];
    totalPrice += checkFlower(r1, c1, idxList1);

    # print('r1 =', r1, 'c1 =', c1, 'totalPrice =', totalPrice);

    for idx2 in range(idx1 + 1, len(locationList)):
        idxList2 = [];
        (r2, c2) = locationList[idx2];
        result2 = checkFlower(r2, c2, idxList2);

        # print('r2 =', r2, 'c2 =', c2, 'result2 =', result2);

        if (result2 == -1):
            initFlower(r2, c2, idxList2);

            continue;

        totalPrice += result2;

        for idx3 in range(idx2 + 1, len(locationList)):
            idxList3 = [];
            (r3, c3) = locationList[idx3];
            result3 = checkFlower(r3, c3, idxList3);

            # print('r3 =', r3, 'c3 =', c3, 'result3 =', result3);

            if (result3 != -1):
                answer = min(answer, totalPrice + result3);
                # print(answer, [r1, c1], [r2, c2], [r3, c3]);
                # print(isVisitedArray);

            initFlower(r3, c3, idxList3);

        totalPrice -= result2;
        initFlower(r2, c2, idxList2);

    initFlower(r1, c1, idxList1);

print(answer);
