import sys;

a, b = sys.stdin.readline().split();
n, m = int(a), int(b);

# print(n, m);

maze = [[0 for cols in range(m + 1)] for rows in range(n + 1)];
isVisited = [[False for cols in range(m + 1)] for rows in range(n + 1)];
q = [];
ans = 0;
startY, startX = 1, 1;

def bfs_queue(y, x):
    # maze[y][x] = 1;

    # queue에 push
    q.append([y, x]);

    while(len(q) != 0):
        # print(q);

        # queue에서 pop
        temp = q.pop(0);
        y, x = temp[0], temp[1];
        # print(y, x);

        # 도착지에 도달했으면 break한다. 정답은 maze[m][n]에 저장되어 있다.
        if(y == n and x == m):
            return maze[n][m];

        # 4방향을 살펴보고 이동이 가능하면 maze배열을 갱신하고 큐에 넣는다.
        if(x < m and isVisited[y][x + 1] == False):
            isVisited[y][x + 1] = True;

            if(maze[y][x + 1] == 1):
                maze[y][x + 1] = maze[y][x] + 1;
                q.append([y, x + 1]);

        if(y < n and isVisited[y + 1][x] == False):
            isVisited[y + 1][x] = True;

            if(maze[y + 1][x] == 1):
                maze[y + 1][x] = maze[y][x] + 1;
                q.append([y + 1, x]);

        if(x > 1 and isVisited[y][x - 1] == False):
            isVisited[y][x - 1] = True;

            if(maze[y][x - 1]== 1):
                maze[y][x - 1] = maze[y][x] + 1;
                q.append([y, x - 1]);

        if(y > 1 and isVisited[y - 1][x] == False):
            isVisited[y - 1][x] = True;

            if(maze[y - 1][x] == 1):
                maze[y - 1][x]= maze[y][x] + 1;
                q.append([y - 1, x]);

for i in range(1, n + 1):
    ttt = sys.stdin.readline();
    tt = str(ttt);
    t = list(tt);
    t.pop();
    # print(t);

    for j in range(1, m + 1):
        maze[i][j] = int(t[j - 1]);

    # print(maze[i]);

# print(maze);

isVisited[startY][startX] = True;
ans = bfs_queue(startY, startX);
print(ans);
