import sys;
import heapq;

# sys.stdin = open("input1.txt", 'r');

N, M = map(int, sys.stdin.readline().split());

adjacencyList = [[] for _ in range(N + 1)];
inCnt = [0 for _ in range(N + 1)];
minHeap = [];

for _ in range(M):
    (src, dst) = map(int, sys.stdin.readline().split());
    adjacencyList[src].append(dst);
    inCnt[dst] += 1;

# print(adjacencyList);
# print(inCnt);

for curIdx in range(1, N + 1):
    if (inCnt[curIdx] == 0):
        heapq.heappush(minHeap, curIdx);

# print(minHeap);

while (minHeap):
    curNode = heapq.heappop(minHeap);
    print(curNode, end = ' ');

    for nextNode in adjacencyList[curNode]:
        inCnt[nextNode] -= 1;

        if (inCnt[nextNode] == 0):
            heapq.heappush(minHeap, nextNode);

print();
