import sys;
import collections;

def dfs(startNode : int) -> None:
    for curVal in adjacencyDict.values():
        curVal.sort(reverse=True);

    stack = [startNode];
    visitSet = set();

    while (stack):
        curNode = stack.pop();

        if (curNode in visitSet):
            continue;

        print(curNode, end=' ');

        visitSet.add(curNode);
        stack.extend(adjacencyDict[curNode]);

    print();

    return None;

def bfs(startNode : int) -> None:
    for curVal in adjacencyDict.values():
        curVal.sort();

    dq = collections.deque([startNode]);
    visitSet = set();

    while (dq):
        curNode = dq.popleft();

        if (curNode in visitSet):
            continue;

        print(curNode, end=' ');

        visitSet.add(curNode);
        dq.extend(adjacencyDict[curNode]);

    print();

    return None;

# sys.stdin = open("input1.txt", 'r');
# sys.stdin = open("input2.txt", 'r');
# sys.stdin = open("input3.txt", 'r');

adjacencyDict = collections.defaultdict(list);

N, M, V = map(int, sys.stdin.readline().split());

for _ in range(M):
    src, dst = map(int, sys.stdin.readline().split());
    adjacencyDict[src].append(dst);
    adjacencyDict[dst].append(src);

# print(N, M, V);
# print(adjacencyDict);

dfs(V);
bfs(V);
