import sys;

# sys.stdin = open("input1.txt", 'r');
# sys.stdin = open("input2.txt", 'r');
# sys.stdin = open("input3.txt", 'r');

N = int(sys.stdin.readline());
K = int(sys.stdin.readline());
sensorList = sorted(list(map(int, sys.stdin.readline().split())));

if (N <= K):
    print(0);

    sys.exit(0);

# print(N, K);
# print(sensorList);

answer = sensorList[-1] - sensorList[0];
diffList = [];

for sensorIdx in range(N - 1):
    curSensor = sensorList[sensorIdx];
    nextSensor = sensorList[sensorIdx + 1];
    diffList.append(nextSensor - curSensor);

diffList.sort(reverse = True);

for diffIdx in range(K - 1):
    answer -= diffList[diffIdx];

print(answer);
