import sys;
import math;
import copy;

DIR_VEC = [[1, 0], [0, -1], [-1, 0], [0, 1]];

def value(array : list) -> int:
    return min([sum(k) for k in array]);

def convert(array : list, query : list) -> list:
    (queryR, queryC, queryS) = query;
    (queryR, queryC) = (queryR - 1, queryC - 1);
    newArray = copy.deepcopy(array);

    for s in range(1, queryS + 1):
        (curR, curC) = (queryR - s, queryC + s);

        for (dr, dc) in DIR_VEC:
            for k in range(s * 2):
                (nextR, nextC) = (curR + dr, curC + dc);
                newArray[nextR][nextC] = array[curR][curC];
                (curR, curC) = (nextR, nextC);

    return newArray;

def dfs(array : list, query : list) -> None:
    global answer;

    if (sum(query) == K):
        answer = min(answer, value(array));

        return None;

    for queryIdx in range(K):
        if (query[queryIdx]):
            continue;

        newArray = convert(array, Q[queryIdx]);

        query[queryIdx] = True;

        dfs(newArray, query);

        query[queryIdx] = False;

    return None;


# sys.stdin = open("input1.txt", 'r');

(N, M, K) = map(int, sys.stdin.readline().split());
A = [list(map(int, sys.stdin.readline().split())) for _ in range(N)];
Q = [list(map(int, sys.stdin.readline().split())) for _ in range(K)];

# print(N, M, K);
# print(A);
# print(Q);

answer = math.inf;

dfs(A, [False for queryIdx in range(K)]);

print(answer);
