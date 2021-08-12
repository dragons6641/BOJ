import sys;
import collections;

def pushNextNode(nextNode : int, curNode : int, nextOperationCnt : int, dq : list, prevNodeList : list) -> None:
    if (prevNodeList[nextNode] > 0):
        return;

    prevNodeList[nextNode] = curNode;
    dq.append([nextNode, curNode, nextOperationCnt]);
    return;

def bfs(startNode : int, prevNodeList : list) -> int:
    dq = collections.deque([[startNode, 0, 0]]);

    while (dq):
        (curNode, prevNode, curOperationCnt) = dq.popleft();

        if (curNode == 1):
            # print(prevNodeList);
            return curOperationCnt;

        if (curNode % 3 == 0):
            pushNextNode(curNode // 3, curNode, curOperationCnt + 1, dq, prevNodeList);

        if (curNode % 2 == 0):
            pushNextNode(curNode // 2, curNode, curOperationCnt + 1, dq, prevNodeList);

        if (curNode > 1):
            pushNextNode(curNode - 1, curNode, curOperationCnt + 1, dq, prevNodeList);

    return -1;

def traverse(curNode : int, startNode : int, prevNodeList : list) -> list:
    if (curNode == startNode):
        return [str(curNode)];

    return traverse(prevNodeList[curNode], startNode, prevNodeList) + [str(curNode)];

# sys.stdin = open("input1.txt", 'r');
# sys.stdin = open("input2.txt", 'r');

N = int(sys.stdin.readline());

prevNodeList = [0 for _ in range(N + 1)];

print(bfs(N, prevNodeList));
print(' '.join(traverse(1, N, prevNodeList)));
