import sys;
import heapq;

# sys.stdin = open("input1.txt", 'r');
# sys.stdin = open("input2.txt", 'r');
# sys.stdin = open("input3.txt", 'r');
# sys.stdin = open("input4.txt", 'r');
# sys.stdin = open("input5.txt", 'r');

N = int(sys.stdin.readline());
problemList = sorted([list(map(int, sys.stdin.readline().split())) for _ in range(N)], key = lambda k : k[0]);

"""
answer = 0;
curTime = 0;
problemList = [];

for _ in range(N):
    (deadLine, cupRamen) = map(int, sys.stdin.readline().split());
    heapq.heappush(problemList, [deadLine, -cupRamen]);

while (problemList):
    (deadLine, cupRamen) = heapq.heappop(problemList);

    print(answer, curTime, deadLine, cupRamen);

    if (deadLine > curTime):
        answer += (-cupRamen);
        curTime += 1;

print(answer);
"""

# print(problemList);

pq = [];

for (curDeadLine, curRamenCnt) in problemList:
    heapq.heappush(pq, curRamenCnt);

    if (curDeadLine < len(pq)):
        heapq.heappop(pq);

print(sum(pq));
