a = [];
b = [];

ans = 0;

n = int(input());

tmp = input().split();

for i in tmp:
    a.append(int(i));

a.sort();

tmp = input().split();

for i in tmp:
    b.append((int(i)));

b.sort(reverse = True);

"""
print(n);
print(a);
print(b);
"""

for i in range(n):
    ans += a[i] * b[i];

print(ans);
