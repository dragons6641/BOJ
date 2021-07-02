import sys;

# sys.stdin = open("input1.txt", 'r');

N = int(sys.stdin.readline());
weightList = sorted(list(map(int, sys.stdin.readline().split())));

# print(N);
# print(weightList);

answer = 0;

for curWeight in weightList:
    if (answer >= curWeight - 1):
        answer += curWeight;
    else:
        break;

print(answer + 1);
