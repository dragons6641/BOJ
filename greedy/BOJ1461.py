import sys;

def bringBook(locationList : list[int]) -> int:
    dist = 0;
    bookList = [];

    for curLocation in locationList:
        bookList.append(curLocation);

        if (len(bookList) == M):
            dist += abs(bookList[0]) * 2;
            bookList.clear();

    if (bookList):
        dist += abs(bookList[0]) * 2;

    return dist;

# sys.stdin = open("input1.txt");
# sys.stdin = open("input2.txt");

N, M = map(int, sys.stdin.readline().split());
locationList = list(map(int, sys.stdin.readline().split()));

# print(N, M);
# print(locationList);

answer = 0;
leftLocationList = sorted([k for k in locationList if (k < 0)]);
rightLocationList = sorted([k for k in locationList if (k > 0)], reverse = True);

# print(leftLocationList);
# print(rightLocationList);

answer += bringBook(leftLocationList);
answer += bringBook(rightLocationList);

if ((leftLocationList) and (rightLocationList)):
    answer -= max(-leftLocationList[0], rightLocationList[0]);
elif (leftLocationList):
    answer += leftLocationList[0];
elif (rightLocationList):
    answer -= rightLocationList[0];

print(answer);
