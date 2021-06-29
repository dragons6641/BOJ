import sys;

# sys.stdin = open("input1.txt", 'r');
# sys.stdin = open("input2.txt", 'r');

N = int(sys.stdin.readline());
inputList = list(map(int, sys.stdin.readline().split()));

# print(N);
# print(inputList);

print(max(inputList) - min(inputList));
