import sys;

# sys.stdin = open("input1.txt", 'r');

while (True):
    N = input();

    if (N == '0'):
        break;

    print("yes" if (N == N[ : : -1]) else "no");
