import sys;
import collections;
import math;

def bfs(nodeCnt : int, adjMatrix : list) -> int:
    answer = math.inf;
    dp = [[0 for _ in range((1 << nodeCnt))] for _ in range(nodeCnt)];
    dq = collections.deque([[0, 0, 0, 0]]);

    while (dq):
        (curNode, curRoute, curCost, visitCnt) = dq.popleft();

        # print(curNode, curRoute, curCost, cnt);
        # print(dp);
        # print(dq);

        if ((dp[curNode][curRoute] > 0) and (dp[curNode][curRoute] < curCost)):
            continue;

        if (visitCnt == nodeCnt):
            answer = min(answer, curCost);

        for nextNode in range(nodeCnt):
            nextRoute = curRoute | (1 << nextNode);
            nextCost = dp[curNode][curRoute] + adjMatrix[curNode][nextNode];

            if (((visitCnt < nodeCnt - 1) and (nextNode == 0)) or (adjMatrix[curNode][nextNode] == 0) or (curRoute & (1 << nextNode) or ((dp[nextNode][nextRoute] > 0) and (dp[nextNode][nextRoute] <= nextCost)))):
                continue;

            dp[nextNode][nextRoute] = nextCost;
            dq.append([nextNode, nextRoute, nextCost, visitCnt + 1]);

    return answer;

# sys.stdin = open("input1.txt", 'r');

N = int(sys.stdin.readline());
adjMatrix = [list(map(int, sys.stdin.readline().split())) for _ in range(N)];

# print(adjMatrix);

print(bfs(N, adjMatrix));
