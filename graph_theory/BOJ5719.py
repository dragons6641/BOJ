import sys;
import heapq;
import math;

INF = math.inf;

"""
def traversePath(curNode) -> None:
    # print(curNode);
    minTime = INF;

    for (prevTime, prevNode) in prevNodeList[curNode]:
        minTime = min(minTime, prevTime);

    # print(minTime);

    for (prevTime, prevNode) in prevNodeList[curNode]:
        # print(prevTime, prevNode, curNode);
        # print(adjacencyList[prevNode]);

        if (prevTime != minTime):
            continue;

        for curIdx in range(len(adjacencyList[prevNode])):
            if (adjacencyList[prevNode][curIdx][1] == curNode):
                adjacencyList[prevNode][curIdx][0] = INF;
                break;

        traversePath(prevNode);

    return None;

def shortestBFS() -> bool:
    pq = [[0, S]];
    visitTimeList = [INF for _ in range(N)];
    visitTimeList[S] = 0;

    while (pq):
        (curTime, curNode) = heapq.heappop(pq);

        # print(pq);
        # print(visitTimeList);
        # print(curTime, curNode);
        # print();

        if (visitTimeList[curNode] < curTime):
            continue;

        for (moveTime, nextNode) in adjacencyList[curNode]:
            nextTime = curTime + moveTime;

            if (visitTimeList[nextNode] < nextTime):
                continue;

            visitTimeList[nextNode] = nextTime;
            prevNodeList[nextNode].append([nextTime, curNode]);
            heapq.heappush(pq, [nextTime, nextNode]);

    # print(visitTimeList);

    # for _ in prevNodeList:
    #     print(_);

    if (len(prevNodeList[D]) == 0):
        return False;

    traversePath(D);

    # for _ in adjacencyList:
    #     print(_);

    return True;

def almostShortestBFS() -> int:
    pq = [[0, S]];
    visitTimeList = [INF for _ in range(N)];
    visitTimeList[S] = 0;

    while (pq):
        (curTime, curNode) = heapq.heappop(pq);

        if (curNode == D):
            # print(visitTimeList);

            return visitTimeList[D];

        if (visitTimeList[curNode] < curTime):
            continue;

        for (moveTime, nextNode) in adjacencyList[curNode]:
            nextTime = curTime + moveTime;

            if (visitTimeList[nextNode] <= nextTime):
                continue;

            visitTimeList[nextNode] = nextTime;
            heapq.heappush(pq, [nextTime, nextNode]);

    return -1;
"""

def bfs() -> bool:
    pq = [[0, S]];
    distanceList[S] = 0;

    while (pq):
        (curDist, curNode) = heapq.heappop(pq);

        if (distanceList[curNode] < curDist):
            continue;

        for (remainDist, nextNode) in adjacencyList[curNode]:
            nextDist = curDist + remainDist;

            if (isDeletedList[curNode][nextNode]) or (distanceList[nextNode] <= nextDist):
                continue;

            distanceList[nextNode] = nextDist;
            heapq.heappush(pq, [nextDist, nextNode]);

    return (distanceList[D] != math.inf);

def dfs(curNode) -> None:
    if (curNode == S):
        return None;

    for (prevDist, prevNode) in reverseAdjacencyList[curNode]:
        if (isDeletedList[prevNode][curNode]):
            continue;

        if (distanceList[curNode] == distanceList[prevNode] + prevDist):
            isDeletedList[prevNode][curNode] = True;
            dfs(prevNode);

    return None;

# sys.stdin = open("input1.txt", 'r');
# sys.stdin = open("input2.txt", 'r');
# sys.stdin = open("input3.txt", 'r');
# sys.stdin = open("input4.txt", 'r');
# sys.stdin = open("input5.txt", 'r');
# sys.stdin = open("input6.txt", 'r');
# sys.stdin = open("input7.txt", 'r');
# sys.stdin = open("input8.txt", 'r');
# sys.stdin = open("input9.txt", 'r');
# sys.stdin = open("input10.txt", 'r');
# sys.stdin = open("input11.txt", 'r');
# sys.stdin = open("input12.txt", 'r');
# sys.stdin = open("input13.txt", 'r');

while (True):
    (N, M) = map(int, sys.stdin.readline().split());

    if ((N == 0) and (M == 0)):
        break;

    (S, D) = map(int, sys.stdin.readline().split());

    adjacencyList = [[] for _ in range(N)];
    reverseAdjacencyList = [[] for _ in range(N)];
    distanceList = [INF for _ in range(N)];
    isDeletedList = [[False for _ in range(N)] for _ in range(N)];
    isVisitedList = [False for _ in range(N)];
    isVisitedList[D] = True;
    # prevNodeList = [[] for _ in range(N)];

    for _ in range(M):
        U, V, P = map(int, sys.stdin.readline().split());
        adjacencyList[U].append([P, V]);
        reverseAdjacencyList[V].append([P, U]);

    # for _ in adjacencyList:
    #     print(_);

    """
    if (shortestBFS()):
        print(almostShortestBFS());
    else:
        print(-1);
    """

    if (bfs()):
        dfs(D);

        # for _ in isDeletedList:
        #     print(_);

        distanceList = [INF for _ in range(N)];

        if (bfs()):
            print(distanceList[D]);
        else:
            print(-1);
    else:
        print(-1);
