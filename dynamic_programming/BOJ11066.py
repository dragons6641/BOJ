import sys;

# sys.stdin = open("input1.txt", 'r');

T = int(sys.stdin.readline());

for testCase in range(T):
    fileSizeList = [0];

    K = int(sys.stdin.readline());
    fileSizeList.extend(list(map(int, sys.stdin.readline().split())));

    prefixSumList = [0 for _ in range(K + 1)];
    dp = [[0 for _ in range(K + 1)] for _ in range(K + 1)];

    for curIdx in range(1, K + 1):
        prefixSumList[curIdx] = prefixSumList[curIdx - 1] + fileSizeList[curIdx];

    # print(K);
    # print(fileSizeList);
    # print(prefixSumList);

    for i in range(2, K + 1):
        for j in range(1, K - i + 2):
            dp[j][j + i - 1] = min([dp[j][j + _] + dp[j + _ + 1][j + i - 1] for _ in range(i - 1)]) + (prefixSumList[j + i - 1] - prefixSumList[j - 1]);

    print(dp[1][K]);
