import sys;

sys.setrecursionlimit(10000);

t = int(sys.stdin.readline());
# print(t);

for i in range(t):
    ans = 0;
    mm, nn, kk = sys.stdin.readline().split();
    m, n, k = int(mm), int(nn), int(kk);
    # print(m, n, k);

    field = [[0 for cols in range(n)] for rows in range(m)];
    isVisited = [[False for cols in range(n)] for rows in range(m)];

    def dfs_NEWS(x, y):
        if(x < m - 1):
            if(isVisited[x + 1][y] == False):
                isVisited[x + 1][y] = True;

                if(field[x + 1][y] == 1):
                    dfs_NEWS(x + 1, y);

        if(y < n - 1):
            if(isVisited[x][y + 1] == False):
                isVisited[x][y + 1] = True;

                if(field[x][y + 1] == 1):
                    dfs_NEWS(x, y + 1);

        if(x > 0):
            if(isVisited[x - 1][y] == False):
                isVisited[x - 1][y] = True;

                if(field[x - 1][y] == 1):
                    dfs_NEWS(x - 1, y);

        if(y > 0):
            if(isVisited[x][y - 1] == False):
                isVisited[x][y - 1] = True;

                if(field[x][y - 1] == 1):
                    dfs_NEWS(x, y - 1);

    # print(field);

    for j in range(k):
        xx, yy = sys.stdin.readline().split();
        x, y = int(xx), int(yy);
        # print(x, y);

        field[x][y] = 1;

    # print(field);

    for a in range(m):
        for b in range(n):
            if(isVisited[a][b] == False):
                isVisited[a][b] = True;

                if(field[a][b] == 1):
                    ans += 1;
                    dfs_NEWS(a, b);

    print(ans);
