import sys;

# sys.stdin = open("input1.txt", 'r');

N = int(sys.stdin.readline());
inputStr = 'X' + sys.stdin.readline();

# print(N);
# print(inputStr);

answer = 0;
bonusScore = 0;

for curIdx in range(1, N + 1):
    if (inputStr[curIdx] == 'O'):
        answer += (curIdx + bonusScore);
        bonusScore += 1;
    else:
        bonusScore = 0;

print(answer);
