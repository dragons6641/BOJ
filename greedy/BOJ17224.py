import sys;

EASY_POINT = 100;
HARD_POINT = 140;

# sys.stdin = open("input1.txt", 'r');
# sys.stdin = open("input2.txt", 'r');
# sys.stdin = open("input3.txt", 'r');

(N, L, K) = map(int, sys.stdin.readline().split());

# print(N, L, K);

answer = 0;
easySolveAvailableCnt = 0;
hardSolveAvailableCnt = 0;

for _ in range(N):
    (sub1, sub2) = map(int, sys.stdin.readline().split());

    if (sub2 <= L):
        hardSolveAvailableCnt += 1;
    elif (sub1 <= L):
        easySolveAvailableCnt += 1;

# print(easySolveAvailableCnt, hardSolveAvailableCnt);

answer += (min(K, hardSolveAvailableCnt) * HARD_POINT);

if (K > hardSolveAvailableCnt):
    answer += (min(K - hardSolveAvailableCnt, easySolveAvailableCnt) * EASY_POINT);

print(answer);
