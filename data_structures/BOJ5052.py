import sys;

sys.setrecursionlimit(10000);

t = int(input());

# print(t);

def quick_sort(ARRAY):
    ARRAY_LENGTH = len(ARRAY)
    if( ARRAY_LENGTH <= 1):
        return ARRAY
    else:
        PIVOT = ARRAY[0]
        GREATER = [ element for element in ARRAY[1:] if element > PIVOT ]
        LESSER = [ element for element in ARRAY[1:] if element <= PIVOT ]
        return quick_sort(LESSER) + [PIVOT] + quick_sort(GREATER)

def check(tel_list):
    for j in range(len(tel_list) - 1):
        # print(j);

        cur_tel = tel_list[j];
        next_tel = tel_list[j + 1];

        if (len(cur_tel) < len(next_tel)):
            tmp = next_tel[0 : len(cur_tel)];

            if (tmp == cur_tel):
                return 1;

    return 0;

"""
for i in range(t):
    isNo = 0;

    tel_list = [];

    n = int(input());

    # print(n);

    for j in range(n):
        tel = input();

        if (isNo == 1):
            tel_list.append(tel);

            continue;
        else:
            for k in tel_list:
                if (len(tel) > len(k)):
                    tmp = tel[0 : len(k)];

                    if (tmp == k):
                        isNo = 1;

                        break;
                elif (len(tel) < len(k)):
                    tmp = k[0 : len(tel)];

                    if (tmp == tel):
                        isNo = 1;

                        break;
                else:
                    if (tel == k):
                        isNo = 1;

                        break;

            tel_list.append(tel);

            continue;

    for j in range(n):
        tel_list.append(input());

    # print(tel_list);

    tel_list.sort();
    # tel_list = quick_sort(tel_list);

    # print(tel_list);

    for j in range(len(tel_list) - 1):
        # print(j);

        cur_tel = tel_list[j];
        next_tel = tel_list[j + 1];

        if (len(cur_tel) < len(next_tel)):
            tmp = next_tel[0 : len(cur_tel)];

            if (tmp == cur_tel):
                isNo = 1;

                break;

    if (isNo == 0):
        print('YES');
    else:
        print('NO');
"""

for i in range(t):
    isNo = 0;
    chk = 0;

    tel_list_0 = [];
    tel_list_1 = [];
    tel_list_2 = [];
    tel_list_3 = [];
    tel_list_4 = [];
    tel_list_5 = [];
    tel_list_6 = [];
    tel_list_7 = [];
    tel_list_8 = [];
    tel_list_9 = [];

    n = int(input());

    # print(new_tel_list);
    # print(n);

    for j in range(n):
        tel = input();
        first = int(tel[0]);

        # print(tel, first);

        if (first == 0):
            tel_list_0.append(tel);
        elif (first == 1):
            tel_list_1.append(tel);
        elif (first == 2):
            tel_list_2.append(tel);
        elif (first == 3):
            tel_list_3.append(tel);
        elif (first == 4):
            tel_list_4.append(tel);
        elif (first == 5):
            tel_list_5.append(tel);
        elif (first == 6):
            tel_list_6.append(tel);
        elif (first == 7):
            tel_list_7.append(tel);
        elif (first == 8):
            tel_list_8.append(tel);
        elif (first == 9):
            tel_list_9.append(tel);
        else:
            pass;

    new_tel_list = [tel_list_0, tel_list_1, tel_list_2, tel_list_3, tel_list_4, tel_list_5, tel_list_6, tel_list_7, tel_list_8, tel_list_9];

    for j in new_tel_list:
        j.sort();

        chk = check(j);

        if (chk == 1):
            isNo = 1;

            break;
        else:
            continue;

    if (isNo == 0):
        print('YES');
    else:
        print('NO');
