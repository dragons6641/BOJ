import sys;

# sys.stdin = open("input1.txt", 'r');

rowAnswer = 0;
colAnswer = 0;
N, M = map(int, input().split());
castleArray = [input() for _ in range(N)];

# print(N, M);
# print(castleArray);

for curCastle in castleArray:
    rowAnswer += (1 if (curCastle.find('X') == -1) else 0);

for c in range(M):
    isNotSecured = True;

    for r in range(N):
        if (castleArray[r][c] == 'X'):
            isNotSecured = False;

            break;

    if (isNotSecured):
        colAnswer += 1;

print(max(rowAnswer, colAnswer));
