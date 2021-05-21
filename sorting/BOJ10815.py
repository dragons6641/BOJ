def binary_search(num, data):
    start = 0;
    end = n - 1;

    while (start <= end):
        mid = (start + end) // 2;

        if (data[mid] == num):
            return 1;
        elif (data[mid] < num):
            start = mid + 1;
        else:
            end = mid - 1;

    return 0;

n = int(input());
n_list = list(map(int, input().split(' ')));
m = int(input());
m_list = list(map(int, input().split(' ')));

"""
print(n);
print(n_list);
print(m);
print(m_list);
"""

"""
for i in range(m - 1):
    if m_list[i] in n_list:
        print('1', end = ' ');
    else:
        print('0', end = ' ');

if m_list[-1] in n_list:
    print('1');
else:
    print('0');
"""

n_list.sort();

# print(n_list);

for i in range(m - 1):
    ans = binary_search(m_list[i], n_list);

    print(ans, end = ' ');

ans = binary_search(m_list[-1], n_list);

print(ans);
