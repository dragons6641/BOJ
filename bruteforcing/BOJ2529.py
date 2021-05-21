min_ans = [];
max_ans = [];
left_list = [];
right_list = [];
isUsed = [0 for i in range(10)];

min_index = 0;
max_index = 9;
num = 0;

k = int(input());
input_list = input().split();

"""
print(input_list);
print(isUsed);
"""

left_list.append(-1);
right_list.append(-1);

for i in range(len(input_list)):
    if (input_list[i] == '<'):
        left_list.append(i);
    else:
        right_list.append(i);

left_list.append(k);
right_list.append(k);

"""
print(left_list);
print(right_list);
"""

for i in range(len(right_list) - 1):
    tmp_ans = []
    length = right_list[i + 1] - right_list[i];
    cnt = 0;
    index = max_index;

    while (length > cnt):
        """
        print(right_list[i + 1], right_list[i], length, cnt, index);
        print(tmp_ans);
        print(isUsed);
        print();
        """

        if (isUsed[index] == 0):
            isUsed[index] = 1;
            tmp_ans.insert(0, index);
            cnt += 1;

        index -= 1;

    for i in tmp_ans:
        max_ans.append(i);

isUsed = [0 for i in range(10)];
num = 0;

for i in range(len(left_list) - 1):
    tmp_ans = []
    length = left_list[i + 1] - left_list[i];
    cnt = 0;
    index = min_index;

    while (length > cnt):
        """
        print(left_list[i + 1], left_list[i], length, cnt, index);
        print(tmp_ans);
        print(isUsed);
        print();
        """

        if (isUsed[index] == 0):
            isUsed[index] = 1;
            tmp_ans.insert(0, index);
            cnt += 1;

        index += 1;

    for i in tmp_ans:
        min_ans.append(i);

for i in max_ans:
    print(i, end = '');

print();

for i in min_ans:
    print(i, end='');
