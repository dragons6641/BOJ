import sys;

# sys.stdin = open("input1.txt", 'r');
# sys.stdin = open("input2.txt", 'r');
# sys.stdin = open("input3.txt", 'r');

inputList = [0];

N = int(sys.stdin.readline());
inputList.extend(list(map(int, sys.stdin.readline().split())));

# print(N);
# print(inputList);

curSum = 0;
answer = [];

for curIdx in range(1, N + 1):
    nextNum = (inputList[curIdx] * curIdx) - curSum;
    answer.append(str(nextNum));
    curSum += nextNum;

print(' '.join(answer));
