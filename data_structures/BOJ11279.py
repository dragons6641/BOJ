import sys;
import heapq;

# sys.stdin = open("input1.txt", 'r');

N = int(sys.stdin.readline());

maxHeap = [];

for cmdIdx in range(N):
    X = int(sys.stdin.readline());

    if (X > 0):
        heapq.heappush(maxHeap, -X);
    elif (X == 0):
        print(-heapq.heappop(maxHeap) if (maxHeap) else 0);
