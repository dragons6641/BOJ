import sys;

# sys.stdin = open("input1.txt", 'r');

N = int(sys.stdin.readline());
numList = list(map(int, sys.stdin.readline().split()));

# print(numList);
print(min(numList), max(numList));
