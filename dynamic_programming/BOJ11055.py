import sys;
import copy;

# sys.stdin = open("input1.txt", 'r');

N = int(sys.stdin.readline());
A = list(map(int, sys.stdin.readline().split()));

# print(N);
# print(A);

dp = copy.deepcopy(A);

for i in range(1, N):
    for j in range(i):
        if (A[i] > A[j]):
            dp[i] = max(A[i] + dp[j], dp[i]);

print(max(dp));
