import sys;

MOD = 1000000007;
VERTEX_CNT = 8;
ADJACENCY_LIST = [[1, 7], [0, 2, 6, 7], [1, 3, 5, 6], [2, 4], [3, 5], [2, 4, 6], [1, 2, 5, 7], [0, 1, 6]];

# sys.stdin = open("input1.txt", 'r');

D = int(sys.stdin.readline());

dp = ([[0 for _ in range(VERTEX_CNT)] for _ in range(D + 1)]);
dp[0][0] = 1;

# print(dp);

for curTime in range(D):
    for curVertex in range(VERTEX_CNT):
        for nextVertex in ADJACENCY_LIST[curVertex]:
            # print(curTime, curVertex, nextVertex);

            dp[curTime + 1][nextVertex] = (dp[curTime + 1][nextVertex] + dp[curTime][curVertex]) % MOD;

# for _ in dp:
#     print(_);

print(dp[D][0]);
