import sys;
import collections;

def topologySort(singerCnt : int, adjList : list, indegreeList : list) -> list:
    answerList = [];
    dq = collections.deque(list(filter(lambda k : (indegreeList[k] == 0), range(1, singerCnt + 1))));

    # print(dq);

    while (dq):
        curSinger = dq.popleft();
        answerList.append(str(curSinger));

        for nextSinger in adjList[curSinger]:
            indegreeList[nextSinger] -= 1;

            if (indegreeList[nextSinger] == 0):
                dq.append(nextSinger);

    return (answerList if (len(answerList) == singerCnt) else ['0']);

# sys.stdin = open("input1.txt", 'r');
# sys.stdin = open("input2.txt", 'r');
# sys.stdin = open("input3.txt", 'r');

(N, M) = map(int, sys.stdin.readline().split());

orderList = [list(map(int, sys.stdin.readline().split()))[1 : ] for _ in range(M)];

(adjList, indegreeList) = ([set() for _ in range(N + 1)], [0 for _ in range(N + 1)]);

for pdIdx in range(M):
    for singerIdx in range(len(orderList[pdIdx]) - 1):
        (src, dst) = (orderList[pdIdx][singerIdx], orderList[pdIdx][singerIdx + 1]);

        if (dst in adjList[src]):
            continue;

        adjList[src].add(dst);
        indegreeList[dst] += 1;

# print(orderList);
# print(adjList);
# print(indegreeList);

print('\n'.join(topologySort(N, adjList, indegreeList)) + '\n');
