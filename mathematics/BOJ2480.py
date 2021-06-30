import sys;
import collections;

# sys.stdin = open("input1.txt", 'r');
# sys.stdin = open("input2.txt", 'r');
# sys.stdin = open("input3.txt", 'r');

numCounter = collections.Counter(list(map(int, sys.stdin.readline().split())));
mostCommonVal, mostCommonCnt = numCounter.most_common(1)[0];

# print(mostCommonVal, mostCommonCnt);

if (mostCommonCnt == 3):
    print(10000 + (mostCommonVal * 1000));
elif (mostCommonCnt == 2):
    print(1000 + (mostCommonVal * 100));
else:
    print(max(numCounter.keys()) * 100);
