import sys;

# sys.stdin = open("input1.txt", 'r');

print(''.join(map(str, sorted(map(int, list(input())), reverse = True))));
