import sys;

def zDivideAndConquer(curLen : int, startR : int, startC : int, answer : int) -> None:
    if (curLen == 1):
        if ((startR == R) and (startC == C)):
            print(answer);

            sys.exit(0);

        return None;

    nextLen = curLen // 2;
    nextArea = nextLen ** 2;
    nextR = startR + nextLen;
    nextC = startC + nextLen;

    if (R < nextR):
        if (C < nextC):
            zDivideAndConquer(nextLen, startR, startC, answer);
        else:
            zDivideAndConquer(nextLen, startR, startC + nextLen, answer + nextArea);
    else:
        if (C < nextC):
            zDivideAndConquer(nextLen, startR + nextLen, startC, answer + (nextArea * 2));
        else:
            zDivideAndConquer(nextLen, startR + nextLen, startC + nextLen, answer + (nextArea * 3));

    return None;

# sys.stdin = open("input1.txt", 'r');
# sys.stdin = open("input2.txt", 'r');

N, R, C = map(int, sys.stdin.readline().split());

# print(N, R, C);

zDivideAndConquer(2 ** N, 0, 0, 0);
