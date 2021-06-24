import sys;

# sys.stdin = open("input1.txt", 'r');

N = int(sys.stdin.readline());
A = list(map(int, sys.stdin.readline().split()));

# print(N);
# print(A);

dp = [1 for _ in range(N)];

for i in range(N):
    for j in range(i):
        if A[i] > A[j]:
            dp[i] = max(dp[i], dp[j] + 1);

print(max(dp));
