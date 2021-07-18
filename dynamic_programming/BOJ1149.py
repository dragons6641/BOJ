import sys;

# sys.stdin = open("input1.txt", 'r');

N = int(sys.stdin.readline());

homeList = [];

for homeIdx in range(N):
    homeList.append(list(map(int, sys.stdin.readline().split())));

# print(homeList);

dp = [homeList[0]];

for k in range(1, N):
    tmpList = [];
    tmpList.append(min(dp[-1][1], dp[-1][2]) + homeList[k][0]);
    tmpList.append(min(dp[-1][0], dp[-1][2]) + homeList[k][1]);
    tmpList.append(min(dp[-1][0], dp[-1][1]) + homeList[k][2]);
    dp.append(tmpList);

    # print(dp);

print(min(dp[-1]));
