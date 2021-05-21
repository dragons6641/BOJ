import sys;
sys.setrecursionlimit(10000);

matrix_1 = [];
matrix_2 = [];

curColor = '';

ans_1 = 0;
ans_2 = 0;

n = int(input());

isVisited_1 = [[0 for cols in range(n)] for rows in range(n)];
isVisited_2 = [[0 for cols in range(n)] for rows in range(n)];

for i in range(n):
    tmp = input();

    matrix_1.append(list(tmp));
    matrix_2.append(list(tmp));

    for j in range(n):
        if (matrix_2[i][j] == 'G'):
            matrix_2[i][j] = 'R';

"""
print(matrix_1);
print(matrix_2);
"""

"""
for i in range(n):
    for j in range(n):
        print(matrix[i][j], i, j);
"""

def dfs_1(row, col):
    isVisited_1[row][col] = 1;

    if (row > 0 and isVisited_1[row - 1][col] == 0 and matrix_1[row - 1][col] == curColor):
        dfs_1(row - 1, col);

    if (col > 0 and isVisited_1[row][col - 1] == 0 and matrix_1[row][col - 1] == curColor):
        dfs_1(row, col - 1);

    if (row < n - 1 and isVisited_1[row + 1][col] == 0 and matrix_1[row + 1][col] == curColor):
        dfs_1(row + 1, col);

    if (col < n - 1 and isVisited_1[row][col + 1] == 0 and matrix_1[row][col + 1] == curColor):
        dfs_1(row, col + 1);

    return;

def dfs_2(row, col):
    isVisited_2[row][col] = 1;

    if (row > 0 and isVisited_2[row - 1][col] == 0 and matrix_2[row - 1][col] == curColor):
        dfs_2(row - 1, col);

    if (col > 0 and isVisited_2[row][col - 1] == 0 and matrix_2[row][col - 1] == curColor):
        dfs_2(row, col - 1);

    if (row < n - 1 and isVisited_2[row + 1][col] == 0 and matrix_2[row + 1][col] == curColor):
        dfs_2(row + 1, col);

    if (col < n - 1 and isVisited_2[row][col + 1] == 0 and matrix_2[row][col + 1] == curColor):
        dfs_2(row, col + 1);

    return;

for i in range(n):
    for j in range(n):
        if (isVisited_1[i][j] == 0):
            isVisited_1[i][j] = 1;
            curColor = matrix_1[i][j];
            ans_1 += 1;

            dfs_1(i, j);

for i in range(n):
    for j in range(n):
        if (isVisited_2[i][j] == 0):
            isVisited_2[i][j] = 1;
            curColor = matrix_2[i][j];
            ans_2 += 1;

            dfs_2(i, j);

print(ans_1, ans_2);
