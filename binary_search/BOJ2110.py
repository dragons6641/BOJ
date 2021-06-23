import sys;

# sys.stdin = open("input1.txt", 'r');

N, C = list(map(int, input().split()));
inputList = sorted([int(input()) for _ in range(N)]);

# print(N, C);
# print(inputList);

answer = 0;
left = 1;
right = inputList[-1] - inputList[0];

while (left <= right):
    mid = (left + right) // 2;
    curVal = inputList[0];
    curCnt = 1;

    for curIdx in range(1, N):
        if (inputList[curIdx] >= curVal + mid):
            curVal = inputList[curIdx];
            curCnt += 1;

    if (curCnt < C):
        right = mid - 1;
    else:
        left = mid + 1;
        answer = mid;

print(answer);
