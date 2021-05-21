ch_list = [];
kbs1_pos = 0;
kbs2_pos = 0;
cursor = 0;

n = int(input());

def button1():
    global cursor;

    cursor += 1;

    print('1', end = '');

def button2():
    global cursor;

    cursor -= 1;

    print('2', end='');

def button3():
    global cursor;
    global ch_list;

    ch_list[cursor], ch_list[cursor + 1] = ch_list[cursor + 1], ch_list[cursor];
    cursor += 1;

    print('3', end='');

def button4():
    global cursor;
    global ch_list;

    ch_list[cursor], ch_list[cursor - 1] = ch_list[cursor - 1], ch_list[cursor];
    cursor -= 1;

    print('4', end='');

for i in range(n):
    tmp = input();

    ch_list.append(tmp);

    if (tmp == 'KBS1'):
        kbs1_pos = i;

    if (tmp == 'KBS2'):
        kbs2_pos = i;

"""
print(ch_list);
print(kbs1_pos);
print(kbs2_pos);
"""

while (True):
    if (ch_list[cursor] != 'KBS1'):
        button1();
    else:
        break;

while (True):
    if (ch_list[0] != 'KBS1'):
        button4();
    else:
        break;

while (True):
    if (ch_list[cursor] != 'KBS2'):
        button1();
    else:
        break;

while (True):
    if (ch_list[1] != 'KBS2'):
        button4();
    else:
        break;

"""
while (True):
    if (ch_list[cursor + 1] == 'KBS1'):
        button3();

        break;

    else:
        button3();

if (ch_list[0] != 'KBS1'):
    button2();

    while (True):
        button4();

        if (ch_list[0] == 'KBS1'):
            break;

while (True):
    if (ch_list[cursor + 1] == 'KBS2'):
        button3();

        break;

    else:
        button3();

if (ch_list[1] != 'KBS2'):
    button2();

    while (True):
        button4();

        if (ch_list[1] == 'KBS2'):
            break;
"""
