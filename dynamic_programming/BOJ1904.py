import sys;

MOD = 15746;

# sys.stdin = open("input1.txt", 'r');

N = int(input());

dp = [0, 1, 2];

for _ in range(3, N + 1):
    dp.append((dp[-1] + dp[-2]) % MOD);

# print(dp);
print(dp[N]);
