import sys;

MAX_ITERATION_CNT = 9;

# sys.stdin = open("input1.txt", 'r');

N = int(sys.stdin.readline());

print('\n'.join([(str(N) + " * " + str(k) + " = " + str(N * k)) for k in range(1, MAX_ITERATION_CNT + 1)]));
