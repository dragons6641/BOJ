import sys;

# sys.stdin = open("input1.txt", 'r');

N = int(input());
nextBirdCnt = 1;
answer = 0;

while (N > 0):
    # print(N, nextBirdCnt, answer);

    if (N < nextBirdCnt):
        nextBirdCnt = 1;
    else:
        N -= nextBirdCnt;
        nextBirdCnt += 1;
        answer += 1;

print(answer);
