import sys;
# import collections;

# sys.stdin = open("input1.txt", 'r');

"""
N = int(sys.stdin.readline());
numDict = collections.defaultdict(int);

for k in range(N):
    numDict[int(sys.stdin.readline())] += 1;

# print(N);
# print(numCounter);

numList = sorted(list(zip(numDict.keys(), numDict.values())), key = lambda k : k[0]);

# print(numList);

for (curNum, curCnt) in numList:
    print((str(curNum) + '\n') * curCnt, end = '');
"""

MAX_NUM = 10000;
numCntList = [0 for _ in range(MAX_NUM + 1)];

N = int(sys.stdin.readline());

for numIdx in range(N):
    numCntList[int(sys.stdin.readline())] += 1;

for curNum in range(1, MAX_NUM + 1):
    for loopIdx in range(numCntList[curNum]):
        print(curNum);
