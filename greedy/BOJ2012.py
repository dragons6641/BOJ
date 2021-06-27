import sys;

# sys.stdin = open("input1.txt", 'r');

N = int(sys.stdin.readline());
rankList = sorted([int(sys.stdin.readline()) for _ in range(N)]);

# print(N);
# print(rankList);

answer = 0;

for rankIdx in range(N):
    # print(rankIdx, rankList[rankIdx]);

    answer += abs(rankIdx - rankList[rankIdx] + 1);

print(answer);
