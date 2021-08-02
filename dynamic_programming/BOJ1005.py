import sys;
import collections;
import copy;

def topologySort(N : int, W : int, indegreeList : list, buildtimeList : list, adjList : list):
    answerList = copy.deepcopy(buildtimeList);
    startNodeList = list(filter(lambda k : (indegreeList[k] == 0), range(1, N + 1)));
    dq = collections.deque(zip(startNodeList, [buildtimeList[k] for k in startNodeList]));

    # print(startNodeList);

    while (dq):
        # print('dq :', dq);
        # print('answerList :', answerList);
        # print('indegreeList :', indegreeList);
        # print('adjList :', adjList);

        (curNode, curTime) = dq.popleft();

        # print(curNode, curTime);

        if ((curNode == W) and (indegreeList[curNode] == 0)):
            break;

        for nextIdx in range(len(adjList[curNode])):
            if (adjList[curNode][nextIdx] == -1):
                continue;

            nextTime = curTime + buildtimeList[adjList[curNode][nextIdx]];
            indegreeList[adjList[curNode][nextIdx]] -= 1;
            answerList[adjList[curNode][nextIdx]] = max(answerList[adjList[curNode][nextIdx]], nextTime);

            if (indegreeList[adjList[curNode][nextIdx]] == 0):
                dq.append([adjList[curNode][nextIdx], answerList[adjList[curNode][nextIdx]]]);

            adjList[curNode][nextIdx] = -1;

    return answerList[W];

# sys.stdin = open("input1.txt", 'r');
# sys.stdin = open("input2.txt", 'r');
# sys.stdin = open("input3.txt", 'r');

T = int(sys.stdin.readline());

for testCase in range(T):
    (N, K) = map(int, sys.stdin.readline().split());

    (indegreeList, buildtimeList, adjList) = ([0 for _ in range(N + 1)], [0], [[] for _ in range(N + 1)]);

    buildtimeList.extend(list(map(int, sys.stdin.readline().split())));

    for edgeIdx in range(K):
        (src, dst) = map(int, sys.stdin.readline().split());
        indegreeList[dst] += 1;
        adjList[src].append(dst);

    W = int(sys.stdin.readline());

    # print(N, K, W);
    # print(indegreeList);
    # print(buildtimeList);
    # print(adjList);

    print(topologySort(N, W, indegreeList, buildtimeList, adjList));
