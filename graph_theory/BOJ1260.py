import sys;

sys.setrecursionlimit(10000);

a, b, c = sys.stdin.readline().split();
n, m, v = int(a), int(b), int(c);

# print(n, m, v);

isVisited = [True] * (n + 1);
isConnected = [[0] * (n + 1) for i in range(n + 1)];
# queue = [];

for i in range(m):
    a, b = sys.stdin.readline().split();
    x, y = int(a), int(b);

    # print(x, y);

    isVisited[x] = False;
    isVisited[y] = False;

    isConnected[x][y] += 1;
    isConnected[y][x] += 1;

# print(isVisited);
# print(isConnected);

def dfs_recursion(now):
    for i in range(1, n + 1):
        # print(i, now, isVisited[i], isConnected[now][i]);

        if(isVisited[i] == False and isConnected[now][i] > 0):
            isVisited[i] = True;

            print(i, end = ' ');

            dfs_recursion(i);

def bfs_queue(start):
    # start를 queue에 push
    queue.append(start);
    print(start, end = ' ');

    while(len(queue) != 0):
        # queue에서 현재 위치를 pop
        now = queue.pop(0);
        # print(now);

        # print(len(queue));

        for i in range(1, n + 1):
            # 연결된 정점을 살펴보고 이동이 가능하면 isVisited배열을 갱신하고 queue에 넣는다.
            if(isVisited[i] == False and isConnected[now][i] > 0):
                # print(isVisited[i], isConnected[now][i]);

                isVisited[i] = True;

                queue.append(i);
                print(i, end = ' ');

        # print(queue);

# dfs start

isVisited[v] = True;

print(v, end = ' ');

dfs_recursion(v);

"""
# dfs else
for i in range(1, n + 1):
    for j in range(1, n + 1):
        if(isVisited[i] == False):
            isVisited[i] = True;

            print(i, end = ' ');

            dfs_recursion(i);
"""

isVisited = [False] * (n + 1);
# isConnected = [[0] * (n + 1) for i in range(n + 1)];
queue = [];

print();

# bfs start
isVisited[v] = True;

"""
for i in range(n + 1):
    isVisited[i] = True;

isVisited[x] = False;
isVisited[y] = False;
"""

# print(v, end = ' ');

# queue.append(v);
bfs_queue(v);
# queue.pop(0);

"""
# bfs else
for i in range(1, n + 1):
    for j in range(1, n + 1):
        if(isVisited[i] == False):
            isVisited[i] = True;

            # print(i, end = ' ');

            # queue.append(i);
            bfs_queue(i);
            # queue.pop(0);
"""
