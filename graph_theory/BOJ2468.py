import sys;

sys.setrecursionlimit(10000);

def dfs(row, col):
    isVisited[row][col] = 1;

    if (row - 1 >= 0 and isVisited[row - 1][col] == 0 and matrix[row - 1][col] > cur_height):
        dfs(row - 1, col);

    if (col - 1 >= 0 and isVisited[row][col - 1] == 0 and matrix[row][col - 1] > cur_height):
        dfs(row, col - 1);

    if (row + 1 <= n - 1 and isVisited[row + 1][col] == 0 and matrix[row + 1][col] > cur_height):
        dfs(row + 1, col);

    if (col + 1 <= n - 1 and isVisited[row][col + 1] == 0 and matrix[row][col + 1] > cur_height):
        dfs(row, col + 1);

    return;

max_height = 1;
min_height = 100;
cnt = 0;
ans = 1;

n = int(input());

# print(n);

matrix = [];
isVisited = [[0 for cols in range(n)] for rows in range(n)];

for i in range(n):
    tmp = list(map(int, input().split()));
    max_tmp = max(tmp);
    min_tmp = min(tmp);

    if (max_tmp > max_height):
        max_height = max_tmp;

    if (min_tmp < min_height):
        min_height = min_tmp;

    matrix.append(tmp);

"""
print(matrix);
print(isVisited);
print(min_height, max_height);
"""

for cur_height in range(min_height, max_height):
    cnt = 0;
    isVisited = [[0 for cols in range(n)] for rows in range(n)];

    for i in range(n):
        for j in range(n):
            if (isVisited[i][j] == 0 and matrix[i][j] > cur_height):
                cnt += 1;

                dfs(i, j);

    # print(cnt);

    if (cnt > ans):
        ans = cnt;

print(ans);
