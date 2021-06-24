import sys;

# sys.stdin = open("input1.txt", 'r');

N, K = map(int, input().split());
inputList = [map(int, input().split()) for _ in range(N)];

dp = [0 for _ in range(K + 1)];

# print(N, K);
# print(inputList);

for (W, V) in inputList:
    for curIdx in range(K, W - 1, -1):
        dp[curIdx] = max(dp[curIdx], dp[curIdx - W] + V);

print(dp[K]);
