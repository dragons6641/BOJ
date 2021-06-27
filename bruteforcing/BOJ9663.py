import sys;

def nQueen(r : int) -> None:
    if (r == N):
        global answer;

        answer += 1;

        return None;

    for c in range(N):
        if ((colVisitedList[c]) or (diagonalVisitedList1[r + c]) or (diagonalVisitedList2[r - c + N - 1])):
            continue;

        colVisitedList[c] = True;
        diagonalVisitedList1[r + c] = True;
        diagonalVisitedList2[r - c + N - 1] = True;

        nQueen(r + 1);

        colVisitedList[c] = False;
        diagonalVisitedList1[r + c] = False;
        diagonalVisitedList2[r - c + N - 1] = False;

    return None;

# sys.stdin = open("input1.txt", 'r');

N = int(sys.stdin.readline());

answer = 0;
colVisitedList = [False for _ in range(N)];
diagonalVisitedList1 = [False for _ in range((2 * N) + 1)];
diagonalVisitedList2 = [False for _ in range((2 * N) + 1)];

nQueen(0);

print(answer);
