import sys;

# sys.stdin = open("input1.txt", 'r');

(N, K) = map(int, sys.stdin.readline().split());

josephusIdx = 0;
(answerList, josephusList) = ([], [str(m) for m in range(1, N + 1)]);

while (josephusList):
    josephusIdx = (josephusIdx + K - 1) % len(josephusList);
    answerList.append(josephusList.pop(josephusIdx));

print('<' + ', '.join(answerList) + '>');
