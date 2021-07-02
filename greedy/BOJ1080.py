import sys;

CONVERT_ROW_CNT = 3;
CONVERT_COL_CNT = 3;

# sys.stdin = open("input1.txt", 'r');

(N, M) = map(int, input().split());
A = [list(input()) for _ in range(N)];
B = [list(input()) for _ in range(N)];

# print(A);
# print(B);

answer = 0;

for startR in range(N - CONVERT_ROW_CNT + 1):
    for startC in range(M - CONVERT_COL_CNT + 1):
        if (A[startR][startC] == B[startR][startC]):
            # print('A =', A[startR][startC], 'B =', B[startR][startC]);

            continue;

        # print('r =', startR, 'c =', startC);

        answer += 1;

        for curR in range(startR, startR + CONVERT_ROW_CNT):
            for curC in range(startC, startC + CONVERT_COL_CNT):
                A[curR][curC] = '1' if (A[curR][curC] == '0') else '0';

        # print(A);

print(answer if (A == B) else -1);
