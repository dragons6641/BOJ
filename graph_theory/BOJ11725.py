import sys;
import collections;

def bfs(startNode : int, nodeCnt : int, adjList : list) -> None:
    dq = collections.deque([startNode]);
    (isVisitedList, parentNodeList) = ([False for _ in range(nodeCnt + 1)], [0 for _ in range(nodeCnt + 1)]);
    isVisitedList[startNode] = True;

    while (dq):
        curNode = dq.popleft();

        for nextNode in adjList[curNode]:
            if (isVisitedList[nextNode]):
                continue;

            dq.append(nextNode);
            isVisitedList[nextNode] = True;
            parentNodeList[nextNode] = curNode;

    for curNode in range(startNode + 1, nodeCnt + 1):
        print(parentNodeList[curNode]);

    return;

# sys.stdin = open("input1.txt", 'r');
# sys.stdin = open("input2.txt", 'r');

N = int(sys.stdin.readline());

adjList = [[] for _ in range(N + 1)];

for edgeIdx in range(N - 1):
    (src, dst) = map(int, sys.stdin.readline().split());
    adjList[src].append(dst);
    adjList[dst].append(src);

# print(adjList);

bfs(1, N, adjList);
