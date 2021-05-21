ans = 0;
cnt = 0;

n = int(input());

matrix = [];
isVisited = [[0 for cols in range(n)] for rows in range(n)];
ans_list = [];

for i in range(n):
    tmp = list(input());
    matrix.append(tmp);

"""
print(matrix);
print(isVisited);
"""

def dfs(row, col):
    global cnt;
    cnt += 1;

    isVisited[row][col] = 1;

    if (row - 1 >= 0 and isVisited[row - 1][col] == 0 and matrix[row - 1][col] == '1'):
        dfs(row - 1, col);
    if (col - 1 >= 0 and isVisited[row][col - 1] == 0 and matrix[row][col - 1] == '1'):
        dfs(row, col - 1);
    if (row + 1 <= n - 1 and isVisited[row + 1][col] == 0 and matrix[row + 1][col] == '1'):
        dfs(row + 1, col);
    if (col + 1 <= n - 1 and isVisited[row][col + 1] == 0 and matrix[row][col + 1] == '1'):
        dfs(row, col + 1);

    # cnt -= 1;

    return;

for i in range(n):
    for j in range(n):
        if (isVisited[i][j] == 0):
            isVisited[i][j] = 1;

            if (matrix[i][j] == '1'):
                cnt = 0;

                dfs(i, j);

                ans += 1;
                ans_list.append(cnt);

ans_list.sort();

print(ans);

for i in ans_list:
    print(i);
