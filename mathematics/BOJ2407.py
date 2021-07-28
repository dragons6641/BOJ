import sys;
# import itertools;

# sys.stdin = open("input1.txt", 'r');

(N, M) = map(int, sys.stdin.readline().split());

# print(len(list(itertools.combinations([k for k in range(N)], M))));

dp = [[0 for c in range(M + 1)] for r in range(N + 1)];

for r in range(1, N + 1):
    dp[r][1] = r;

    if (r <= M):
        dp[r][r] = 1;

    for c in range(2, min(r, M + 1)):
        dp[r][c] = dp[r - 1][c] + dp[r - 1][c - 1];

print(dp[N][M]);
