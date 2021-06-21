import sys;
import collections;

def find(curNode : int) -> int:
    if (curNode == parentDict[curNode]):
        return curNode;

    curParent = find(parentDict[curNode]);
    parentDict[curNode] = curParent;

    return parentDict[curNode];

def union(src : int, dst : int) -> None:
    src = find(src);
    dst = find(dst);

    if (src != dst):
        parentDict[dst] = src;
        answerDict[src] += answerDict[dst];

    return None;

# sys.stdin = open("input1.txt", 'r');

testCase = int(input());

for t in range(testCase):
    """
    F = int(input());
    friendDict = collections.defaultdict(set);

    for k in range(F):
        src, dst = input().split();
        friendDict[src].add(dst);
        friendDict[dst].add(src);
        networkSet = set();
        dq = collections.deque([src, dst]);

        while (dq):
            curFriend = dq.popleft();

            if (curFriend not in networkSet):
                networkSet.add(curFriend);
                dq.extend(friendDict[curFriend]);

        print(len(networkSet));
    """

    F = int(input());
    parentDict = dict();
    answerDict = dict();

    for k in range(F):
        src, dst = input().split();

        if (src not in parentDict):
            parentDict[src] = src;
            answerDict[src] = 1;

        if (dst not in parentDict):
            parentDict[dst] = dst;
            answerDict[dst] = 1;

        union(src, dst);

        print(answerDict[find(src)]);
