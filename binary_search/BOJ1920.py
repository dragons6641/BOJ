import sys;
import collections;

# sys.stdin = open("input1.txt", 'r');

N = int(input());
A = list(map(int, input().split()));
M = int(input());
X = list(map(int, input().split()));
numDict = collections.defaultdict(int);

# print(N, A);
# print(M, X);

"""
for curNum in X:
    print(1 if curNum in A else 0);
"""

for curNum in A:
    numDict[curNum] = 1;

# print(numDict);

for curNum in X:
    print(numDict[curNum]);
