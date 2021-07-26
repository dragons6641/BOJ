import sys;
import collections;

def bfs(startNode : int, nodeCnt : int, adjList : list[[int, int]]) -> list[int]:
    (dq, isVisitedList) = (collections.deque([[startNode, 0]]), [False for _ in range(nodeCnt + 1)]);
    (endNode, endDiameter, isVisitedList[startNode]) = (0, 0, True);

    while (dq):
        (curNode, curDiameter) = dq.popleft();

        if (endDiameter < curDiameter):
            (endNode, endDiameter) = (curNode, curDiameter);

        for (nextNode, nextDist) in adjList[curNode]:
            if (isVisitedList[nextNode]):
                continue;

            isVisitedList[nextNode] = True;
            dq.append([nextNode, nextDist + curDiameter]);

    return [endNode, endDiameter];

# sys.stdin = open("input1.txt", 'r');

N = int(sys.stdin.readline());

adjList = [[] for _ in range(N + 1)];

for edgeIdx in range(N - 1):
    (parent, child, weight) = map(int, sys.stdin.readline().split());
    adjList[parent].append([child, weight]);
    adjList[child].append([parent, weight]);

# print(adjList);

startNode = bfs(1, N, adjList)[0];
print(bfs(startNode, N, adjList)[1]);
