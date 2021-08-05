import sys;
import collections;

# sys.stdin = open("input1.txt", 'r');
# sys.stdin = open("input2.txt", 'r');

N = int(sys.stdin.readline());

dq = collections.deque();

for cmdIdx in range(N):
    cmdList = sys.stdin.readline().split();

    if (cmdList[0] == 'push_front'):
        dq.appendleft(int(cmdList[1]));
    elif (cmdList[0] == 'push_back'):
        dq.append(int(cmdList[1]));
    elif (cmdList[0] == 'pop_front'):
        print(dq.popleft() if dq else -1);
    elif (cmdList[0] == 'pop_back'):
        print(dq.pop() if dq else -1);
    elif (cmdList[0] == 'size'):
        print(len(dq));
    elif (cmdList[0] == 'empty'):
        print(int(bool(not dq)));
    elif (cmdList[0] == 'front'):
        print(dq[0] if dq else -1);
    elif (cmdList[0] == 'back'):
        print(dq[-1] if dq else -1);

    # print(cmdList);
    # print(dq);
