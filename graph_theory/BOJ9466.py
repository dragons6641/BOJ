import sys;

# sys.stdin = open("input1.txt", 'r');

T = int(sys.stdin.readline());

for testCase in range(T):
    N = int(sys.stdin.readline());
    adjList = [0] + list(map(int, sys.stdin.readline().split()));

    groupIdx = 1;
    groupList = [0 for _ in range(N + 1)];

    # print(adjList);
    # print(groupList);

    for startNode in range(1, N + 1):
        curNode = startNode;

        while (groupList[curNode] == 0):
            groupList[curNode] = groupIdx;
            curNode = adjList[curNode];

        while (groupList[curNode] == groupIdx):
            groupList[curNode] = -1;
            curNode = adjList[curNode];

        groupIdx += 1;

    print(len(list(filter(lambda k : (k > 0), groupList))));
