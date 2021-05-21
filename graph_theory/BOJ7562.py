from collections import deque;

testcase = int(input());

def bfs(startX, startY):
    ans = 0;

    q.append([startX, startY, ans]);

    while(len(q) > 0):
        tmp = q.popleft();
        curX, curY, ans = tmp[0], tmp[1], tmp[2];

        # print(curX, curY, ans);

        if (curX == finishX and curY == finishY):
            print(ans);

            return;

        if (curX + 1 <= length - 1 and curY + 2 <= length - 1 and isVisited[curX + 1][curY + 2] == 0):
            q.append([curX + 1, curY + 2, ans + 1]);
            isVisited[curX + 1][curY + 2] = 1;
        if (curX + 2 <= length - 1 and curY + 1 <= length - 1 and isVisited[curX + 2][curY + 1] == 0):
            q.append([curX + 2, curY + 1, ans + 1]);
            isVisited[curX + 2][curY + 1] = 1;
        if (curX + 1 <= length - 1 and curY - 2 >= 0 and isVisited[curX + 1][curY - 2] == 0):
            q.append([curX + 1, curY - 2, ans + 1]);
            isVisited[curX + 1][curY - 2] = 1;
        if (curX + 2 <= length - 1 and curY - 1 >= 0 and isVisited[curX + 2][curY - 1] == 0):
            q.append([curX + 2, curY - 1, ans + 1]);
            isVisited[curX + 2][curY - 1] = 1;
        if (curX - 1 >= 0 and curY + 2 <= length - 1 and isVisited[curX - 1][curY + 2] == 0):
            q.append([curX - 1, curY + 2, ans + 1]);
            isVisited[curX - 1][curY + 2] = 1;
        if (curX - 2 >= 0 and curY + 1 <= length - 1 and isVisited[curX - 2][curY + 1] == 0):
            q.append([curX - 2, curY + 1, ans + 1]);
            isVisited[curX - 2][curY + 1] = 1;
        if (curX - 1 >= 0 and curY - 2 >= 0 and isVisited[curX - 1][curY - 2] == 0):
            q.append([curX - 1, curY - 2, ans + 1]);
            isVisited[curX - 1][curY - 2] = 1;
        if (curX - 2 >= 0 and curY - 1 >= 0 and isVisited[curX - 2][curY - 1] == 0):
            q.append([curX - 2, curY - 1, ans + 1]);
            isVisited[curX - 2][curY - 1] = 1;

for i in range(testcase):
    q = deque();

    length = int(input());

    isVisited = [[0 for cols in range(length)] for rows in range(length)];

    tmpX, tmpY = input().split();
    startX, startY = int(tmpX), int(tmpY);

    tmpX, tmpY = input().split();
    finishX, finishY = int(tmpX), int(tmpY);

    # print(length, curX, curY, nextX, nextY);

    bfs(startX, startY);
