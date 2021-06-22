import sys;

# sys.stdin = open("input1.txt", 'r');

N = int(sys.stdin.readline());
print('\n'.join(map(str, sorted([int(sys.stdin.readline()) for _ in range(N)]))));
