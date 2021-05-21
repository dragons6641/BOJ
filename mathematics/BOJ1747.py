import math;

n = int(input());
str_n = map(int, str(n));

max_num = 1000000;
max_ans = 1003001;
max_bound = 98689;

"""
if (n > max_bound):
    print(max_ans);
    exit(0);
"""

# print(str_n);

primenum_list = [];
ans_list = [];

# 1부터 1000000중 소수 찾기
def is_prime(n):
    primenum_list = [1 for _ in range(n + 1)]
    primenum_list[0], primenum_list[1] = 0, 0

    div = 2;

    while (div <= n // 2 + 1):
        for i in range(div * div, n + 1, div):
            if(primenum_list[i] == 0):
                continue;
            else:
                primenum_list[i] = 0;
        div += 1;

    return [i for i in range(len(primenum_list)) if primenum_list[i] == 1];

primenum_list = is_prime(max_ans);
#print(primenum_list);

# 회문인지 검사하는 함수
def is_palindrome(s):
    for i in range(0, len(s) // 2):
        if(s[i] == s[- i - 1]):
            continue;
        else:
            return False;

    return True;

# 소수이면서 회문인 list
for i in primenum_list:
    if(is_palindrome(str(i)) == True):
        ans_list.append(i);

"""
for i in ans_list:
    print(i);
"""

for i in ans_list:
    if(n > i):
        continue;
    else:
        print(i);
        break;
