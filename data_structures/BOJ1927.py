import sys;
import heapq;

# sys.stdin = open("input1.txt", 'r');

N = int(sys.stdin.readline());

minHeap = [];

for _ in range(N):
    X = int(sys.stdin.readline());

    if (X == 0):
        if (minHeap):
            print(heapq.heappop(minHeap));
        else:
            print(0);
    else:
        heapq.heappush(minHeap, X);
