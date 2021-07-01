import sys;

# sys.stdin = open("input1.txt", 'r');

N = int(sys.stdin.readline());
triangleArray = [list(map(int, sys.stdin.readline().split())) for _ in range(N)];

dp = [[0 for c in range(r + 1)] for r in range(N)];
dp[0][0] = triangleArray[0][0];

# print(N);
# print(triangleArray);
# print(dp);

for r in range(1, N):
    curLen = len(triangleArray[r]);

    for c in range(curLen):
        if (c == 0):
            dp[r][c] = dp[r - 1][c] + triangleArray[r][c];
        elif (c == curLen - 1):
            dp[r][c] = dp[r - 1][c - 1] + triangleArray[r][c];
        else:
            dp[r][c] = max(dp[r - 1][c], dp[r - 1][c - 1]) + triangleArray[r][c];

print(max(dp[-1]));
