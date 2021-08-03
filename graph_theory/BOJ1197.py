import sys;

# sys.stdin = open("input1.txt", 'r');

def find(curNode : int, parentList : list) -> int:
    if (parentList[curNode] != curNode):
        parentList[curNode] = find(parentList[curNode], parentList);
    return parentList[curNode];

def union(node1 : int, node2 : int, parentList : list, rankList : list) -> None:
    (root1, root2) = (find(node1, parentList), find(node2, parentList));

    if (rankList[root1] < rankList[root2]):
        parentList[root1] = root2;
    else:
        parentList[root2] = root1;

        if (rankList[root1] == rankList[root2]):
            rankList[root1] += 1;

    return;

def kruskal(edgeList : list, parentList : list, rankList : list) -> int:
    answer = 0;

    for (src, dst, weight) in edgeList:
        if (find(src, parentList) == find(dst, parentList)):
            continue;

        union(src, dst, parentList, rankList);
        answer += weight;

    return answer;

(V, E) = map(int, sys.stdin.readline().split());
(edgeList, parentList, rankList) = ([], [k for k in range(V + 1)], [0 for _ in range(V + 1)]);

for edgeIdx in range(E):
    edgeList.append(list(map(int, sys.stdin.readline().split())));

# print(edgeList);
# print(parentList);
# print(rankList);

print(kruskal(sorted(edgeList, key = lambda k : k[2]), parentList, rankList));
