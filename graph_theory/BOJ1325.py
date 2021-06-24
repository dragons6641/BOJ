import sys;
import collections;

def bfs(startNode : int) -> int:
    hackingCnt = 1;
    dq = collections.deque([startNode]);
    isVisitedList = [False for _ in range(N + 1)];
    isVisitedList[startNode] = True;

    while (dq):
        curNode = dq.popleft();

        for nextNode in adjacencyDict[curNode]:
            if (isVisitedList[nextNode]):
                continue;

            isVisitedList[nextNode] = True;
            dq.append(nextNode);
            hackingCnt += 1;

    return hackingCnt;

# sys.stdin = open("input1.txt", 'r');
# sys.stdin = open("input2.txt", 'r');
# sys.stdin = open("input3.txt", 'r');
# sys.stdin = open("input4.txt", 'r');
# sys.stdin = open("input5.txt", 'r');
# sys.stdin = open("input6.txt", 'r');
# sys.stdin = open("input7.txt", 'r');
# sys.stdin = open("input8.txt", 'r');

N, M = map(int, sys.stdin.readline().split());

maxHackingCnt = 0;
answerList = [];
adjacencyDict = collections.defaultdict(list);

for _ in range(M):
    (dst, src) = map(int, sys.stdin.readline().split());
    adjacencyDict[src].append(dst);

# print(N, M);
# print(adjacencyDict);

for curNode in range(1, N + 1):
    curHackingCnt = bfs(curNode);

    if (maxHackingCnt == curHackingCnt):
        maxHackingCnt = curHackingCnt;
        answerList.append(str(curNode));
    elif (maxHackingCnt < curHackingCnt):
        maxHackingCnt = curHackingCnt;
        answerList = [str(curNode)];

print(' '.join(answerList));
