pos_list = [];

ans = 1;
index = 0;
start = 0;
end = 0;

tmp = input().split();
n, l = int(tmp[0]), int(tmp[1]);

# print(n, l);

if (n == 0):
    print(0);

    exit(0);

else:
    tmp = input().split();

for i in tmp:
    pos_list.append(int(i));

pos_list.sort();

# print(pos_list);

start = pos_list[index];
end = pos_list[index] + l;

while (True):
    if (index == len(pos_list)):
        break;

    # print(ans, pos_list[index], start, end);

    if (pos_list[index] >= end):
        start = pos_list[index];
        end = pos_list[index] + l;
        ans += 1;
        index += 1;
    else:
        index += 1;

        continue;

print(ans);
