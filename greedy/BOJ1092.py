import sys;

# sys.stdin = open("input1.txt", 'r');
# sys.stdin = open("input2.txt", 'r');
# sys.stdin = open("input3.txt", 'r');
# sys.stdin = open("input4.txt", 'r');
# sys.stdin = open("input5.txt", 'r');
# sys.stdin = open("input6.txt", 'r');
# sys.stdin = open("input7.txt", 'r');
# sys.stdin = open("input8.txt", 'r');
# sys.stdin = open("input9.txt", 'r');
# sys.stdin = open("input10.txt", 'r');

N = int(sys.stdin.readline());
craneWeightList = sorted(list(map(int, sys.stdin.readline().split())), reverse = True);
M = int(sys.stdin.readline());
boxWeightList = sorted(list(map(int, sys.stdin.readline().split())), reverse = True);

"""
if (max(craneWeightList) < max(boxWeightList)):
    print(-1);

    exit(0);

# print(N, M);
# print(craneWeightList);
# print(boxWeightList);

craneIdx = 0;
boxFinishCnt = 0;
craneTargetList = [[] for _ in range(N)];
craneFinishedList = [False for _ in range(N)];
boxFinishedList = [False for _ in range(M)];

for boxIdx in range(M):
    if (boxWeightList[boxIdx] > craneWeightList[craneIdx]):
        continue;

    craneTargetList[craneIdx].append(boxIdx);
    boxFinishedList[boxIdx] = True;
    craneIdx += 1;
    boxFinishCnt += 1;

    if (craneIdx == N):
        break;

craneIdx = 0;

while (craneIdx < N):
    if (len(craneTargetList[craneIdx]) == 0):
        craneFinishedList[craneIdx] = True;

    craneIdx += 1;

# print(craneTargetList);

while (boxFinishCnt < M):
    craneIdx = 0;

    while (craneIdx < N):
        # print(boxFinishCnt, craneIdx);
        # print(craneTargetList);
        # print(craneFinishedList);
        # print(boxFinishedList);

        if (not craneFinishedList[craneIdx]):
            try:
                nextTargetIdx = boxFinishedList.index(False);
                craneTargetList[craneIdx].append(nextTargetIdx);
                boxFinishedList[nextTargetIdx] = True;
                boxFinishCnt += 1;
            except ValueError:
                craneFinishedList[craneIdx] = True;

        craneIdx += 1;

# print(craneTargetList);

print(len(max(craneTargetList, key = lambda k : len(k))));
"""

answer = 0;
boxFinishedCnt = 0;
craneFinishedList = [False for _ in range(N)];
boxFinishedList = [False for _ in range(M)];

while (boxFinishedCnt < M):
    answer += 1;
    boxFinished = True;

    for craneIdx in range(N):
        if (craneFinishedList[craneIdx]):
            continue;

        craneFinished = True;

        for boxIdx in range(M):
            if ((boxFinishedList[boxIdx]) or (boxWeightList[boxIdx] > craneWeightList[craneIdx])):
                continue;

            boxFinished = False;
            craneFinished = False;
            boxFinishedCnt += 1;
            boxFinishedList[boxIdx] = True;

            break;

        if (craneFinished):
            craneFinishedList[craneIdx] = True;

    if (boxFinished):
        print(-1);

        sys.exit(0);

print(answer);
