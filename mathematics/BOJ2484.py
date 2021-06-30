import sys;
import collections;

# sys.stdin = open("input1.txt", 'r');

N = int(sys.stdin.readline());

answerList = [];

for _ in range(N):
    numCounter = collections.Counter(list(map(int, sys.stdin.readline().split())));
    mostCommonList = numCounter.most_common(2);

    # print(mostCommonList);

    if (mostCommonList[0][1] == 4):
        answerList.append(50000 + (mostCommonList[0][0] * 5000));
    elif (mostCommonList[0][1] == 3):
        answerList.append(10000 + (mostCommonList[0][0] * 1000));
    elif (mostCommonList[0][1] == 2):
        if (mostCommonList[1][1] == 2):
            answerList.append(2000 + ((mostCommonList[0][0] + mostCommonList[1][0]) * 500));
        else:
            answerList.append(1000 + mostCommonList[0][0] * 100);
    else:
        answerList.append(max(numCounter.keys()) * 100);

print(max(answerList));
