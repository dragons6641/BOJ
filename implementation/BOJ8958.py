import sys;

# sys.stdin = open("input1.txt", 'r');

T = int(input());

for testCase in range(T):
    resultList = input();

    # print(resultList);

    (answer, correctCnt) = (0, 0);

    for curResult in resultList:
        if (curResult == 'O'):
            correctCnt += 1;
            answer += correctCnt;
        else:
            correctCnt = 0;

    print(answer);
