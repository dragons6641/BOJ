import sys;
import collections;

MAX_C = 1000000000;

def bfs(curWeight):
    dq = collections.deque([startNode]);
    isVisitedList = [False for _ in range(N + 1)];
    isVisitedList[startNode] = True;

    while (dq):
        curNode = dq.popleft();

        for (nextNode, nextWeight) in adjacencyList[curNode]:
            if ((isVisitedList[nextNode]) or (nextWeight < curWeight)):
                continue;

            isVisitedList[nextNode] = True;
            dq.append(nextNode);

    return isVisitedList[endNode];

# sys.stdin = open("input1.txt", 'r');
# sys.stdin = open("input2.txt", 'r');
# sys.stdin = open("input3.txt", 'r');
# sys.stdin = open("input4.txt", 'r');
# sys.stdin = open("input5.txt", 'r');
# sys.stdin = open("input6.txt", 'r');
# sys.stdin = open("input7.txt", 'r');

N, M = map(int, input().split());
adjacencyList = [[] for _ in range(N + 1)];

left = MAX_C;
right = 1;

for bridgeIdx in range(M):
    src, dst, weight = map(int, input().split());
    adjacencyList[src].append((dst, weight));
    adjacencyList[dst].append((src, weight));
    left = min(left, weight);
    right = max(right, weight);

startNode, endNode = map(int, input().split());

answer = left;

while (left <= right):
    mid = (left + right) // 2;

    if (bfs(mid)):
        left = mid + 1;
        answer = mid;
    else:
        right = mid - 1;

print(answer);
