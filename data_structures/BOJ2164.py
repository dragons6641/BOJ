import sys;
import collections;

# sys.stdin = open("input1.txt", 'r');

N = int(sys.stdin.readline());

loopCnt = 0;
dq = collections.deque([k for k in range(1, N + 1)]);

while (len(dq) > 1):
    # print(dq);

    dq.popleft() if (loopCnt % 2 == 0) else dq.rotate(-1);
    loopCnt += 1;

print(dq[0]);
