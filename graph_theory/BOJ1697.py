import sys;
import collections;

MAX_POINT = 100000;

# sys.stdin = open("input1.txt", 'r');

N, K = map(int, sys.stdin.readline().split());

dq = collections.deque([[N, 0]]);
isVisitedList = [False for _ in range(MAX_POINT + 1)];
isVisitedList[N] = True;

while (dq):
    (curNode, curTime) = dq.popleft();

    # print(curNode, curTime);

    if (curNode == K):
        print(curTime);

        break;

    if ((curNode - 1 >= 0) and (not isVisitedList[curNode - 1])):
        isVisitedList[curNode - 1] = True;
        dq.append([curNode - 1, curTime + 1]);

    if ((curNode + 1 <= MAX_POINT) and (not isVisitedList[curNode + 1])):
        isVisitedList[curNode + 1] = True;
        dq.append([curNode + 1, curTime + 1]);

    if ((curNode * 2 <= MAX_POINT) and (not isVisitedList[curNode * 2])):
        isVisitedList[curNode * 2] = True;
        dq.append([curNode * 2, curTime + 1]);
