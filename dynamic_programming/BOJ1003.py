import sys;

MAX_N = 40;

# sys.stdin = open("input1.txt", 'r');

answerList0 = [1, 0];
answerList1 = [0, 1];

for answerIdx in range(2, MAX_N + 1):
    answerList0.append(answerList0[answerIdx - 1] + answerList0[answerIdx - 2]);
    answerList1.append(answerList1[answerIdx - 1] + answerList1[answerIdx - 2]);

T = int(sys.stdin.readline());

for testCase in range(T):
    N = int(sys.stdin.readline());

    print(answerList0[N], answerList1[N]);
