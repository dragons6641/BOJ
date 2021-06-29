import sys;
import collections;

# sys.stdin = open("input1.txt", 'r');

(N, M) = map(int, input().split());

girlGroupDict = collections.defaultdict(list);
memberDict = collections.defaultdict(str);

for girlGroupIdx in range(N):
    girlGroupName = input();
    memberCnt = int(input());

    for memberIdx in range(memberCnt):
        memberName = input();
        girlGroupDict[girlGroupName].append(memberName);
        memberDict[memberName] = girlGroupName;

for (curKey, curVal) in girlGroupDict.items():
    curVal.sort();

# print(girlGroupDict);
# print(memberDict);

for quizIdx in range(M):
    quizQuestion = input();
    quizCategory = int(input());

    if (quizCategory == 0):
        print('\n'.join(girlGroupDict[quizQuestion]));
    else:
        print(memberDict[quizQuestion]);
