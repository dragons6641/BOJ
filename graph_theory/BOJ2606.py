import sys;

a = sys.stdin.readline();
b = sys.stdin.readline();
v, e = int(a), int(b);

isVisited = [False] * (v + 1);
isConnected = [[0] * (v + 1) for i in range(v + 1)];

global ans;
ans = 0;

for i in range(e):
    a, b = sys.stdin.readline().split(' ');
    x, y = int(a), int(b);

    isConnected[x][y] += 1;
    isConnected[y][x] += 1;

# print(isVisited);
# print(isConnected);

def dfs_recursive(now):
    for i in range(1, v + 1):
        if(isVisited[i] == False and isConnected[now][i] > 0):
            global ans;
            ans += 1;

            isVisited[i] = True;
            dfs_recursive(i);

isVisited[1] = True;
dfs_recursive(1);

print(ans);
