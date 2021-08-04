import sys;
import collections;

# sys.stdin = open("input1.txt", 'r');

N = int(sys.stdin.readline());
numCounter = collections.Counter(list(map(int, sys.stdin.readline().split())));
M = int(sys.stdin.readline());
targetList = list(map(int, sys.stdin.readline().split()));

for curTarget in targetList:
    print(numCounter[curTarget], end = ' ');

print();
