import sys;

INF = 1e10;

"""
def floydWarshall(N : int, adjArr : list) -> bool:
    for startNode in range(1, N + 1):
        for endNode in range(1, N + 1):
            for waypointNode in range(1, N + 1):
                adjArr[startNode][endNode] = min(adjArr[startNode][endNode], adjArr[startNode][waypointNode] + adjArr[waypointNode][endNode]);

            if ((startNode == endNode) and (adjArr[startNode][endNode] < 0)):
                return True;

    return False;

# sys.stdin = open("input1.txt", 'r');
# sys.stdin = open("input2.txt", 'r');
# sys.stdin = open("input3.txt", 'r');

TC = int(sys.stdin.readline());

for testCase in range(TC):
    (N, M, W) = map(int, sys.stdin.readline().split());

    adjArr = [[math.inf for _ in range(N + 1)] for _ in range(N + 1)];

    for roadIdx in range(M):
        (S, E, T) = map(int, sys.stdin.readline().split());

        (adjArr[S][E], adjArr[E][S]) = (min(adjArr[S][E], T), min(adjArr[E][S], T));

    for wormholeIdx in range(W):
        (S, E, T) = map(int, sys.stdin.readline().split());

        adjArr[S][E] = min(adjArr[S][E], -T);

    print("YES" if floydWarshall(N, adjArr) else "NO");
    # print(adjArr);
"""

def bellmanFord(startNode : int, N : int, adjList : list) -> bool:
    distList = [INF for _ in range(N + 1)];
    distList[startNode] = 0;

    for curIdx in range(1, N):
        for curNode in range(1, N + 1):
            for nextNode in adjList[curNode].keys():
                # print(curNode, nextNode);
                # print(distList);

                distList[nextNode] = min(distList[nextNode], distList[curNode] + adjList[curNode][nextNode]);

    for curNode in range(1, N + 1):
        for nextNode in adjList[curNode].keys():
            if (distList[nextNode] > distList[curNode] + adjList[curNode][nextNode]):
                return True;

    return False;

# sys.stdin = open("input1.txt", 'r');
# sys.stdin = open("input2.txt", 'r');
# sys.stdin = open("input3.txt", 'r');

TC = int(sys.stdin.readline());

for testCase in range(TC):
    (N, M, W) = map(int, sys.stdin.readline().split());

    adjList = [dict() for _ in range(N + 1)];

    for roadIdx in range(M):
        (S, E, T) = map(int, sys.stdin.readline().split());

        adjList[S][E] = (min(adjList[S][E], T) if (E in adjList[S].keys()) else T);
        adjList[E][S] = (min(adjList[E][S], T) if (S in adjList[E].keys()) else T);

    for wormholeIdx in range(W):
        (S, E, T) = map(int, sys.stdin.readline().split());

        adjList[S][E] = (min(adjList[S][E], -T) if (E in adjList[S].keys()) else -T);

    print("YES" if bellmanFord(1, N, adjList) else "NO");
    
    # print(adjList);
