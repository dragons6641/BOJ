import sys;
import collections;

def bfs(startNode : int, nodeCnt : int, adjList : list[[int, int]]) -> list[int]:
    (maxNode, maxDiameter) = (startNode, 0);
    dq = collections.deque([[startNode, 0]]);
    isVisitedList = [False for _ in range(nodeCnt + 1)];
    isVisitedList[startNode] = True;

    while (dq):
        (curNode, curDiameter) = dq.popleft();

        if (maxDiameter < curDiameter):
            (maxNode, maxDiameter) = (curNode, curDiameter);

        # print(curNode, curDiameter);

        for (nextNode, nextDist) in adjList[curNode]:
            if (isVisitedList[nextNode]):
                continue;

            isVisitedList[nextNode] = True;
            dq.append([nextNode, curDiameter + nextDist]);

    # print();

    return [maxNode, maxDiameter];

# sys.stdin = open("input1.txt", 'r');    # 11
# sys.stdin = open("input2.txt", 'r');    # 22
# sys.stdin = open("input3.txt", 'r');    # 20
# sys.stdin = open("input4.txt", 'r');    # 12
# sys.stdin = open("input5.txt", 'r');    # 17
# sys.stdin = open("input6.txt", 'r');    # 8

V = int(sys.stdin.readline());

answer = 0;
adjList = [[] for _ in range(V + 1)];

for vertexIdx in range(1, V + 1):
    inputList = list(map(int, sys.stdin.readline().split()));

    for inputIdx in range(1, len(inputList) - 1, 2):
        adjList[inputList[0]].append([inputList[inputIdx], inputList[inputIdx + 1]]);

# print(adjList);

startNode = bfs(1, V, adjList)[0];
print(bfs(startNode, V, adjList)[1]);
