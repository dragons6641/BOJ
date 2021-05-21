hear_list = [];
see_list = [];
ans_list = [];

hear_list_index = 0;
see_list_index = 0;
cnt = 0;

tmp = input().split();

n, m = int(tmp[0]), int(tmp[1]);

for i in range(n):
    tmp = input();
    hear_list.append(tmp);

for i in range(m):
    tmp = input();
    see_list.append(tmp);

hear_list.sort();
see_list.sort();

"""
print(hear_list);
print(see_list);
"""

while (hear_list_index < len(hear_list) and see_list_index < len(see_list)):
    # print(hear_list[hear_list_index], see_list[see_list_index]);

    if (hear_list[hear_list_index] < see_list[see_list_index]):
        hear_list_index += 1;
    elif (hear_list[hear_list_index] > see_list[see_list_index]):
        see_list_index += 1;
    else:
        ans_list.append(hear_list[hear_list_index]);

        cnt += 1;
        hear_list_index += 1;
        see_list_index += 1;

print(cnt);

for i in ans_list:
    print(i);
