import sys;

# sys.stdin = open("input1.txt", 'r');

T = int(sys.stdin.readline());

for testCase in range(T):
    (R, S) = sys.stdin.readline().split();

    print(''.join([(curCh * int(R)) for curCh in S]));
