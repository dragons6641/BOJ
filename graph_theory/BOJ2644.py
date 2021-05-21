def dfs(num, cnt):
    isVisited[num] = 1;

    if (num == b):
        print(cnt);

        exit(0);

    for i in range(n + 1):
        if (isVisited[i] == 0 and matrix[num][i] == 1):
            # print(num, i, cnt);

            isVisited[i] = 1;

            dfs(i, cnt + 1);

    return -1;

ans = 0;

n = int(input());

matrix = [[0 for cols in range(n + 1)] for rows in range(n + 1)];
isVisited = [0 for nums in range(n + 1)];

tmp = list(map(int, input().split()));
a, b = tmp[0], tmp[1];

m = int(input());

for i in range(m):
    tmp = list(map(int, input().split()));
    x, y = tmp[0], tmp[1];

    matrix[x][y] = 1;
    matrix[y][x] = 1;

"""
print(n);
print(a, b);
print(m);
print(matrix);
print(isVisited);
"""

ans = dfs(a, 0);

print(ans);
