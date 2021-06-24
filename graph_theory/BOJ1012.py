import sys;
import collections;

def bfs(startR : int, startC : int) -> None:
    dq = collections.deque([[startR, startC]]);

    while (dq):
        (curR, curC) = dq.popleft();

        for (dr, dc) in dirVec:
            nextR = curR + dr;
            nextC = curC + dc;

            # print(nextR, nextC);

            if ((nextR < 0) or (nextR >= N) or (nextC < 0) or (nextC >= M)):
                continue;

            if ((not landArray[nextR][nextC]) or (isVisitedArray[nextR][nextC])):
                continue;

            isVisitedArray[nextR][nextC] = True;
            dq.append([nextR, nextC]);

    return;

# sys.stdin = open("input1.txt", 'r');

testCase = int(sys.stdin.readline());

for t in range(testCase):
    M, N, K = map(int, sys.stdin.readline().split());

    cabbageList = [];
    isVisitedArray = [[False for _ in range(M)] for _ in range(N)];
    landArray = [[False for _ in range(M)] for _ in range(N)];

    for _ in range(K):
        X, Y = map(int, sys.stdin.readline().split());
        cabbageList.append([Y, X]);
        landArray[Y][X] = True;

    # print(cabbageList);

    answer = 0;
    dirVec = [(-1, 0), (1, 0), (0, -1), (0, 1)];

    for (r, c) in cabbageList:
        # print(r, c);

        if (isVisitedArray[r][c]):
            continue;

        isVisitedArray[r][c] = True;
        answer += 1;
        bfs(r, c);

    print(answer);
