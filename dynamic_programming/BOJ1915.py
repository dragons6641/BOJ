import sys;

# sys.stdin = open("input1.txt", 'r');

(N, M) = map(int, input().split());
inputArray = [[0 for _ in range(M + 1)] for _ in range(N + 1)];
dp = [[0 for _ in range(M + 1)] for _ in range(N + 1)];

for r in range(1, N + 1):
    inputArray[r][1 : ] = map(int, list(input()));

# print(N, M);
# print(inputArray);

for r in range(1, N + 1):
    for c in range(1, M + 1):
        dp[r][c] = (0 if (inputArray[r][c] == 0) else (min(dp[r - 1][c - 1], dp[r - 1][c], dp[r][c - 1]) + 1));

print(max([max(k) for k in dp]) ** 2);
