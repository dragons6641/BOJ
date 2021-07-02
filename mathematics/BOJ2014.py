import sys;
import copy;
import heapq;

# sys.stdin = open("input1.txt", 'r');

(K, N) = map(int, sys.stdin.readline().split());
primeList = list(map(int, sys.stdin.readline().split()));

# print(K, N);
# print(primeList);

productSet = set();
pq = copy.deepcopy(primeList);
heapq.heapify(pq);

while (len(productSet) < N):
    curProduct = heapq.heappop(pq);

    if ((len(productSet) > 0) and (curProduct in productSet)):
        continue;

    productSet.add(curProduct);

    # print(curProduct);
    # print(productList);
    # print(pq);
    # print(primeList);

    for curPrime in primeList:
        heapq.heappush(pq, curProduct * curPrime);

        # print(pq);

print(max(productSet));
