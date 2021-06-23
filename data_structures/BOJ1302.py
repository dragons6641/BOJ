import sys;
import collections;

# sys.stdin = open("input1.txt", 'r');

N = int(input());
bookCounter = collections.Counter([input() for _ in range(N)]);

# print(N);
# print(bookCounter);
# print(bookCounter.most_common(1)[0][0]);

print(sorted(list(zip(bookCounter.keys(), bookCounter.values())), key = lambda k : (-k[1], k[0]))[0][0]);
