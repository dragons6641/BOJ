import sys;
import collections;

START_NODE = 1;

# sys.stdin = open("input1.txt", 'r');

adjacencyDict = collections.defaultdict(list);

vertexCnt = int(sys.stdin.readline());
edgeCnt = int(sys.stdin.readline());

for _ in range(edgeCnt):
    (src, dst) = map(int, sys.stdin.readline().split());
    adjacencyDict[src].append(dst);
    adjacencyDict[dst].append(src);

# print(vertexCnt, edgeCnt);
# print(adjacencyDict);

dq = collections.deque([START_NODE]);
visitSet = set();

while (dq):
    curNode = dq.popleft();

    if (curNode in visitSet):
        continue;

    visitSet.add(curNode);
    dq.extend(adjacencyDict[curNode]);

# print(visitSet);
print(len(visitSet) - 1);
