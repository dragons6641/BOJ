time_list = [];

cur_time = 0;
ans = 0;
index = 0;

n = int(input());

# print(n);

for i in range(n):
    tmp = input().split();

    start_time, end_time = int(tmp[0]), int(tmp[1]);

    time_list.append([start_time, end_time]);

time_list.sort();
time_list.sort(key = lambda x : x[1]);

# print(time_list);

while (True):
    start_time = time_list[index][0];
    end_time = time_list[index][1];

    # print(cur_time, start_time, end_time);

    if (start_time >= cur_time):
        ans += 1;
        cur_time = end_time;

        # print(index);

    index += 1;

    if (index == len(time_list)):
        break;

print(ans);
