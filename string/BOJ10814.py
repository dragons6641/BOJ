import sys;

# sys.stdin = open("input1.txt", 'r');

N = int(input());
memberList = sorted([input().split() for _ in range(N)], key = lambda k : int(k[0]));

# print(N);
# print(memberList);

for curMember in memberList:
    print(' '.join(curMember));
