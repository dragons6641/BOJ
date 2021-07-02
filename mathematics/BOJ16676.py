import sys;
# import collections;

DIGIT = 10;

# sys.stdin = open("input1.txt", 'r');
# sys.stdin = open("input2.txt", 'r');
# sys.stdin = open("input3.txt", 'r');
# sys.stdin = open("input4.txt", 'r');
# sys.stdin = open("input5.txt", 'r');

N = int(sys.stdin.readline());

"""
answer = 0;

for curSalary in range(N):
    answer = max(answer, collections.Counter(list(str(curSalary))).most_common(1)[0][1]);

print(answer);
"""

minusNum = 0;

for digitIdx in range(len(str(N)) - 1):
    minusNum = (minusNum * DIGIT) + 1;

# print(N - minusNum);

print(len(str(N - minusNum)));
