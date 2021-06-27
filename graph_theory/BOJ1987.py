import sys;

ALPHABET_CNT = 26;
BIAS = ord("A");
DIR_VEC = ((-1, 0), (1, 0), (0, -1), (0, 1));

def backtrack(curR : int, curC : int, alphabetCnt : int) -> None:
    global answer;

    answer = max(answer, alphabetCnt);

    for (dr, dc) in DIR_VEC:
        nextR = curR + dr;
        nextC = curC + dc;

        if ((nextR < 0) or (nextR >= R) or (nextC < 0) or (nextC >= C)):
            continue;

        nextAlphabetIdx = ord(inputArray[nextR][nextC]) - BIAS;

        if ((alphabetVisitedList[nextAlphabetIdx]) or (locationVisitedArray[nextR][nextC])):
            continue;

        alphabetVisitedList[nextAlphabetIdx] = True;
        locationVisitedArray[nextR][nextC] = True;

        backtrack(nextR, nextC, alphabetCnt + 1);

        alphabetVisitedList[nextAlphabetIdx] = False;
        locationVisitedArray[nextR][nextC] = False;

    return None;

# sys.stdin = open("input1.txt", 'r');
# sys.stdin = open("input2.txt", 'r');
# sys.stdin = open("input3.txt", 'r');

R, C = map(int, input().split());
inputArray = [input() for _ in range(R)];

# print(R, C);
# print(inputArray);

answer = 0;
alphabetVisitedList = [False for _ in range(ALPHABET_CNT)];
locationVisitedArray = [[False for _ in range(C)] for _ in range(R)];

# print(alphabetVisitedList);
# print(locationVisitedArray);

alphabetVisitedList[ord(inputArray[0][0]) - BIAS] = True;
locationVisitedArray[0][0] = True;

backtrack(0, 0, 1);

print(answer);
