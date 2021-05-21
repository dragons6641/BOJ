from collections import deque;

ans = 0;

def bfs():
    cnt = 0;

    q = deque();

    q.append([s, cnt]);
    isVisited[s] = 1;

    if (s == g):
        return cnt;
    elif (s < g):
        if (u == 0 or u >= f):
            return -1;
    elif (s > g):
        if (d == 0 or d >= f):
            return -1;

    while(len(q) != 0):
        tmp = q.popleft();
        floor, cnt = tmp[0], tmp[1];

        """
        print(floor, cnt);
        print(isVisited);
        """

        if (floor == g):
            return cnt;

        if (floor < g and floor + (u * 2) <= g and isVisited[floor + u] == 0):
            q.append([floor + u, cnt + 1]);
            isVisited[floor + u] = 1;

            continue;

        if (floor > g and floor - (d * 2) >= g and isVisited[floor - d] == 0):
            q.append([floor - d, cnt + 1]);
            isVisited[floor - d] = 1;

            continue;

        if (floor + u <= f and isVisited[floor + u] == 0):
            q.append([floor + u, cnt + 1]);
            isVisited[floor + u] = 1;

        if (floor - d >= 1 and isVisited[floor - d] == 0):
            q.append([floor - d, cnt + 1]);
            isVisited[floor - d] = 1;

    return -1;

tmp = list(map(int, input().split()));
f, s, g, u, d = tmp[0], tmp[1], tmp[2], tmp[3], tmp[4];

# print(f, s, g, u, d);

isVisited = [0 for i in range(f + 1)];

ans = bfs();

if (ans == -1):
    print("use the stairs");
else:
    print(ans);
