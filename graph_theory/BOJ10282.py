import sys;
import heapq;

INF = 10 ** 10;

def bfs(startTime : int, startNode : int) -> None:
    infestCnt = 0;
    maxInfestTime = 0;
    pq = [[startTime, startNode]];
    infestTimeList = [INF for _ in range(N + 1)];
    infestTimeList[startNode] = 0;

    while (pq):
        (curTime, curNode) = heapq.heappop(pq);

        if (curTime > infestTimeList[curNode]):
            continue;

        # print(curTime, curNode);

        for (infestTime, nextNode) in adjacencyList[curNode]:
            nextTime = curTime + infestTime;

            if (nextTime >= infestTimeList[nextNode]):
                continue;

            infestTimeList[nextNode] = nextTime;
            heapq.heappush(pq, [nextTime, nextNode]);

    # print(infestTimeList);

    for curInfestTime in infestTimeList:
        if (curInfestTime == INF):
            continue;

        # print(maxInfestTime, curInfestTime);

        infestCnt += 1;
        maxInfestTime = max(maxInfestTime, curInfestTime);

    print(infestCnt, maxInfestTime);

    return None;

# sys.stdin = open("input1.txt",'r');
# sys.stdin = open("input2.txt",'r');

testCase = int(sys.stdin.readline());

for t in range(testCase):
    (N, D, C) = map(int, sys.stdin.readline().split());

    adjacencyList = [[] for _ in range(N + 1)];

    for _ in range(D):
        (A, B, S) = map(int, sys.stdin.readline().split());
        adjacencyList[B].append([S, A]);

    # print(adjacencyList);

    bfs(0, C);
