import sys;

# sys.stdin = open("input1.txt", 'r');

str1 = ' ' + input();
str2 = ' ' + input();
str1Len = len(str1);
str2Len = len(str2);

dp = [[0 for _ in range(str2Len)] for _ in range(str1Len)];

for r in range(1, str1Len):
    for c in range(1, str2Len):
        if (str1[r] == str2[c]):
            dp[r][c] = dp[r - 1][c - 1] + 1;
        else:
            dp[r][c] = max(dp[r - 1][c], dp[r][c - 1]);

print(dp[str1Len - 1][str2Len - 1]);
