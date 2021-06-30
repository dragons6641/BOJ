import sys;

DIR_VEC = [[-1, 0], [1, 0], [0, -1], [0, 1]];

# sys.stdin = open("input1.txt", 'r');
# sys.stdin = open("input2.txt", 'r');
# sys.stdin = open("input3.txt", 'r');

pastureArray = [];

(R, C) = map(int, input().split());

for curR in range(R):
    pastureArray.append(input());

# print(pastureArray);

for curR in range(R):
    curC = 0;

    while (curC < C):
        curC = pastureArray[curR].find('W', curC);

        if (curC == -1):
            break;

        for (dr, dc) in DIR_VEC:
            nextR = curR + dr;
            nextC = curC + dc;

            if ((nextR < 0) or (nextR >= R) or (nextC < 0) or (nextC >= C)):
                continue;

            if (pastureArray[nextR][nextC] == 'S'):
                print(0);

                sys.exit(0);

        curC += 1;

print(1);

for curPasture in pastureArray:
    print(curPasture.replace('.', 'D'));
