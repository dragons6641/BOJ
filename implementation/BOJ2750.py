import sys;

# sys.stdin = open("input1.txt", 'r');

N = int(input());
print('\n'.join(map(str, sorted([int(input()) for _ in range(N)]))));
