import sys;

# sys.stdin = open("input1.txt", 'r');

dp = [0, 1];

N = int(sys.stdin.readline());

for k in range(2, N + 1):
    # print(dp);

    dp.append(dp[-1] + dp[-2]);

print(dp[N]);
