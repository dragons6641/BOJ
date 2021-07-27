import sys;
import functools;

# sys.stdin = open("input1.txt", 'r');    # 1
# sys.stdin = open("input2.txt", 'r');    # 15
# sys.stdin = open("input3.txt", 'r');    # 7
# sys.stdin = open("input4.txt", 'r');    # 46

N = int(input());
numStr = input();

print(functools.reduce(lambda x, y : int(x) + int(y), numStr, 0));
