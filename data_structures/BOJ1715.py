import sys;
import heapq;

# sys.stdin = open("input1.txt", 'r');

N = int(sys.stdin.readline());

answer = 0;
minHeap = [int(sys.stdin.readline()) for _ in range(N)];
heapq.heapify(minHeap);

# print(minHeap);

while (len(minHeap) > 1):
    compCnt = (heapq.heappop(minHeap) + heapq.heappop(minHeap));
    answer += compCnt;
    heapq.heappush(minHeap, compCnt);

print(answer);
