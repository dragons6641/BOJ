import sys;

# sys.stdin = open("input1.txt", 'r');
# sys.stdin = open("input2.txt", 'r');
# sys.stdin = open("input3.txt", 'r');
# sys.stdin = open("input4.txt", 'r');
# sys.stdin = open("input5.txt", 'r');
# sys.stdin = open("input6.txt", 'r');
# sys.stdin = open("input7.txt", 'r');

S = input();

# print(S[-1]);

cntList = [0, 0];

for curIdx in range(len(S) - 1):
    curCh = S[curIdx];
    nextCh = S[curIdx + 1];

    if (curCh != nextCh):
        cntList[int(curCh)] += 1;

cntList[int(S[-1])] += 1;

print(min(cntList));
