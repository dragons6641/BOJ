import sys;

def checkCandy() -> bool:
    for candyIdx in range(N):
        if (candyList[candyIdx] % 2 == 0):
            continue;

        candyList[candyIdx] += 1;

    # print(candyList.count(candyList[0]));

    return (candyList.count(candyList[0]) != N);

# sys.stdin = open("input1.txt", 'r');

T = int(sys.stdin.readline());

for testCase in range(T):
    N = int(sys.stdin.readline());
    candyList = list(map(int, sys.stdin.readline().split()));

    # print(N);
    # print(candyList);

    answer = 0;

    while (checkCandy()):
        answer += 1;

        tmpList = [(curCandy // 2) for curCandy in candyList];
        candyList = list(map(lambda k : (k // 2), candyList));

        # print(tmpList);
        # print(candyList);

        candyList[0] += tmpList[-1];

        for candyIdx in range(N - 1):
            candyList[candyIdx + 1] += tmpList[candyIdx];

        # print(candyList);
        # print();

    print(answer);
