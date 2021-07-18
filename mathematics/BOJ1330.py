import sys;

# sys.stdin = open("input1.txt", 'r');
# sys.stdin = open("input2.txt", 'r');
# sys.stdin = open("input3.txt", 'r');

A, B = map(int, sys.stdin.readline().split());

if (A < B):
    print("<");
elif (A > B):
    print(">");
else:
    print("==");
