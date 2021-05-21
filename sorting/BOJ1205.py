score_list = [];
rank = 1;
min_score = -1;

tmp = input().split();
n, score, p = int(tmp[0]), int(tmp[1]), int(tmp[2]);

if (n != 0):
    tmp = input().split();

    for i in range(n):
        if (i == 0):
            min_score = int(tmp[i]);

        score_list.append(int(tmp[i]));
else:
    if (p == 0):
        rank = -1;
    else:
        rank = 1;

    print(rank);
    exit(0);

"""
print(n, score, p);
print(score_list);
"""

for i in score_list:
    if (score < i):
        rank += 1;

    if (min_score > i):
        min_score = i;

    # print(min_score);

if (n == p and score <= min_score):
    rank = -1;

print(rank);
