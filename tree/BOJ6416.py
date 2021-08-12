import sys;
import collections;

# sys.stdin = open("input1.txt");
# sys.stdin = open("input2.txt");
# sys.stdin = open("input3.txt");
# sys.stdin = open("input4.txt");

def bfs(startNode : int, nodeCnt : int, adjDict : list) -> bool:
    visitCnt = 0;
    dq = collections.deque([startNode]);
    isVisitedDict = collections.defaultdict(bool);
    isVisitedDict[startNode] = True;

    while (dq):
        curNode = dq.popleft();
        visitCnt += 1;

        for nextNode in adjDict[curNode]:
            if (isVisitedDict[nextNode]):
                return False;

            isVisitedDict[nextNode] = True;
            dq.append(nextNode);

    return (nodeCnt == visitCnt);

def checkTree(inputList : list) -> bool:
    if (inputList == [0, 0]):
        return True;

    edgeCnt = 0;
    vertexSet = set();
    (adjDict, indegreeDict) = (collections.defaultdict(set), collections.defaultdict(int));

    for curIdx in range(0, len(inputList) - 2, 2):
        (src, dst) = (inputList[curIdx], inputList[curIdx + 1]);
        edgeCnt += 1;
        vertexSet.update([src, dst]);
        adjDict[src].add(dst);

        if (indegreeDict[dst] > 0):
            return False;

        indegreeDict[dst] += 1;

        # print(src, dst);

    # print(testCase, edgeCnt);
    # print(inputList);
    # print(vertexSet);
    # print(adjDict);
    # print(indegreeDict);

    if (len(vertexSet) != edgeCnt + 1):
        return False;

    rootNode = sum(vertexSet) - sum(indegreeDict.keys());

    # print(rootNode);

    return bfs(rootNode, len(vertexSet), adjDict);

testCase = 0;
inputList = [];

while (True):
    inputList.extend(list(map(int, sys.stdin.readline().split())));

    if (inputList[-2 : ] == [-1, -1]):
        break;
    elif (inputList[-2 : ] != [0, 0]):
        continue;

    testCase += 1;

    print('Case %d is%sa tree.' % (testCase, ' ' if checkTree(inputList) else ' not '));

    inputList = [];
