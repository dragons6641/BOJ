import sys;

# sys.stdin = open("input1.txt", 'r');
# sys.stdin = open("input2.txt", 'r');

T = int(sys.stdin.readline());

for testCase in range(T):
    (H, W, N) = map(int, sys.stdin.readline().split());
    (quotient, remainder) = divmod(N, H);
    print((str(H) + str(quotient).zfill(2)) if (remainder == 0) else (str(remainder) + str(quotient + 1).zfill(2)));
