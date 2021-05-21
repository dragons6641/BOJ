ans = 0;

using = 0;

tmp = input().split();

n, k = int(tmp[0]), int(tmp[1]);

if (n >= k):
    print(ans);

    exit(0);

# print(n, k);

multi_tap = [0 for i in range(n)];
check_list = [0 for i in range(n)];
goods_list = [];

tmp = input().split();

for i in tmp:
    goods_list.append(int(i));

"""
print(multi_tap);
print(check_list);
print(goods_list);
"""

for i in range(len(goods_list)):
    """
    print('i =', i);
    print('goods_list[i] =', goods_list[i]);
    print('ans =', ans);
    """

    if (goods_list[i] in multi_tap):
        """
        print(multi_tap);
        print(check_list);
        print();
        """

        continue;

    elif (using < n):
        for j in range(len(multi_tap)):
            if (multi_tap[j] == 0):
                multi_tap[j] = goods_list[i];
                using += 1;

                break;
    else:
        check_list = [0 for i in range(n)];
        cnt = 0;

        for j in range(i, len(goods_list)):
            for k in range(len(multi_tap)):
                if (goods_list[j] == multi_tap[k] and check_list[k] == 0):
                    check_list[k] = j;
                    cnt += 1;

                    #"""
                    if (cnt == n):
                        break;
                    #"""

            #"""
            if (cnt == n):
                break;
            #"""

        if (cnt == n):
            max = 0;
            max_index = 0;

            for k in range(len(check_list)):
                if (check_list[k] > max):
                    max = check_list[k];
                    max_index = k;

            multi_tap[max_index] = goods_list[i];
            ans += 1;

        else:
            for k in range(len(check_list)):
                if (check_list[k] == 0):
                    multi_tap[k] = goods_list[i];
                    ans += 1;

                    break;

    """
    print(multi_tap);
    print(check_list);
    print();
    """

print(ans);
