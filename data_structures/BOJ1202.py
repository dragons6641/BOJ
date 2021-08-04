import sys;
import heapq;

# sys.stdin = open("input1.txt", 'r');    # 10
# sys.stdin = open("input2.txt", 'r');    # 164

(N, K) = map(int, sys.stdin.readline().split());
jewelHeap = [list(map(int, sys.stdin.readline().split())) for _ in range(N)];
bagHeap = [int(sys.stdin.readline()) for _ in range(K)];
tmpHeap = [];
answer = 0;

heapq.heapify(jewelHeap);
heapq.heapify(bagHeap);

# print(jewelList);
# print(bagList);

while (bagHeap):
    C = heapq.heappop(bagHeap);

    while ((jewelHeap) and (jewelHeap[0][0] <= C)):
        heapq.heappush(tmpHeap, -heapq.heappop(jewelHeap)[1]);

    if (tmpHeap):
        answer -= heapq.heappop(tmpHeap);
    elif (not jewelHeap):
        break;

print(answer);
