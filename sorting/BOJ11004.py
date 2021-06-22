import sys;

# sys.stdin = open("input1.txt", 'r');

N, K = map(int, sys.stdin.readline().split());
print(sorted(list(map(int, sys.stdin.readline().split())))[K - 1]);
