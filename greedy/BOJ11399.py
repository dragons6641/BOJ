time_list = [];

ans = 0;

n = int(input());

tmp = input().split();

for i in tmp:
    time_list.append(int(i));

time_list.sort();

"""
print(n);
print(time_list);
"""

for i in range(len(time_list)):
    tmp = time_list[i] * (len(time_list) - i);

    # print(tmp);

    ans += tmp;

print(ans);
