n = int(input());

n1, n2 = n // 10, n % 10;

# print(n1);
# print(n2);

def cycle(n, n1, n2):
    cnt = 0;

    while(True):
        num = n1 + n2;
        new_num = n2 * 10 + num % 10

        n1, n2 = new_num // 10, new_num % 10
        cnt += 1;

        # print(n, n1, n2, new_num, cnt);

        if(int(n) == new_num):
            return cnt;

ans = cycle(n, n1, n2);
print(ans);
