import sys;

# sys.stdin = open("input1.txt", 'r');

volumeDiffList = [0];

N, S, M = map(int, sys.stdin.readline().split());
volumeDiffList.extend(list(map(int, sys.stdin.readline().split())));

# print(N, S, M);
# print(volumeDiffList);

dp = [[False for _ in range(M + 1)] for _ in range(N + 1)];
dp[0][S] = True;

for r in range(1, N + 1):
    isFinished = True;

    for c in range(M + 1):
        if (not dp[r - 1][c]):
            continue;

        isFinished = False;

        nextC = c - volumeDiffList[r]

        if (nextC >= 0):
            dp[r][nextC] = True;

        nextC = c + volumeDiffList[r];

        if (nextC <= M):
            dp[r][nextC] = True;

    if (isFinished):
        break;

try:
    print(M - list(reversed(dp[N])).index(True));
except ValueError:
    print(-1);
