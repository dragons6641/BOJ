import sys;
import collections;

# sys.stdin = open("input1.txt", 'r');

testCase = int(input());

for t in range(testCase):
    N, M = map(int, input().split());
    dq = collections.deque(zip([_ for _ in range(N)], list(map(int, input().split()))));
    answer = 0;

    # print(N, M);
    # print(dq);

    while (dq):
        isPrinted = True;
        curDocument, curPriority = dq.popleft();

        for (tmpDocument, tmpPriority) in dq:
            if (curPriority < tmpPriority):
                isPrinted = False;
                dq.append((curDocument, curPriority));

                break;

        if (not isPrinted):
            continue;

        answer += 1;

        if (curDocument == M):
            print(answer);

            break;
