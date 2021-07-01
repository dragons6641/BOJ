import sys;

# sys.stdin = open("input1.txt", 'r');

(N, M) = map(int, sys.stdin.readline().split());

inputArray = [[0 for _ in range(M + 1)] for _ in range(N + 1)];
dp = [[0 for _ in range(M + 1)] for _ in range(N + 1)];

for r in range(1, N + 1):
    inputArray[r][1 : ] = map(int, sys.stdin.readline().split());

# print(N, M);
# print(inputArray);

for r in range(1, N + 1):
    for c in range(1, M + 1):
        dp[r][c] = dp[r][c - 1] + dp[r - 1][c] - dp[r - 1][c - 1] + inputArray[r][c];

# print(dp);

K = int(sys.stdin.readline());

for _ in range(K):
    (startR, startC, endR, endC) = map(int, sys.stdin.readline().split());
    print(dp[endR][endC] - dp[endR][startC - 1] - dp[startR - 1][endC] + dp[startR - 1][startC - 1]);
