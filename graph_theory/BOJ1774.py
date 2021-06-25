import sys;
import math;

def find(curNode : int) -> int:
    if (parentList[curNode] != curNode):
        parentList[curNode] = find(parentList[curNode]);

    return parentList[curNode];

def union(node1 : int, node2 : int) -> None:
    root1 = find(node1);
    root2 = find(node2);

    if (rankList[root1] < rankList[root2]):
        parentList[root1] = root2;
    else:
        parentList[root2] = root1;

        if (rankList[root1] == rankList[root2]):
            rankList[root1] += 1;

    return None;

# sys.stdin = open("input1.txt", 'r');

answer = 0.00;
connectIdx = 0;
locationList = [[0, 0]];

N, M = map(int, sys.stdin.readline().split());
locationList.extend(list(map(int, sys.stdin.readline().split())) for _ in range(N));
connectList = sorted([sorted(list(map(int, sys.stdin.readline().split()))) for _ in range(M)]);

# print(N, M);
# print(locationList);
# print(mst);

parentList = [k for k in range(N + 1)];
rankList = [0 for k in range(N + 1)];
edgeList = [];

for i in range(1, N + 1):
    (x1, y1) = locationList[i];

    for j in range(i + 1, N + 1):
        # print(i, j);

        if (connectIdx < M) and ([i, j] == connectList[connectIdx]):
            connectIdx += 1;

            if (find(i) != find(j)):
                union(i, j);
        else:
            (x2, y2) = locationList[j];
            edgeList.append([i, j, math.sqrt(((y2 - y1) ** 2) + ((x2 - x1) ** 2))]);

edgeList.sort(key = lambda k : k[2]);

# print(parentList);
# print(rankList);
# print(edgeList);

for (i, j, k) in edgeList:
    if (find(i) != find(j)):
        union(i, j);
        connectList.append([i, j]);
        answer += k;

print("{:.2f}".format(round(answer, 2)));
