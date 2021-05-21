n = int(input());

row = 0;
column = 0;

room = [];
row_room = [];
column_room = [];
x_room = [];
y_room = [];

# input 받기
for i in range(n):
    s = str(input());
    room.append(list(s));
    row_room.append(s.split('X'));

# print(room);

for i in range(n):
    for j in range(i):
        room[i][j], room[j][i] = room[j][i], room[i][j];

for i in range(n):
    s = ("".join(room[i]));
    column_room.append(s.split('X'));

for i in row_room:
    for j in i:
        x_room.append(j);

for i in column_room:
    for j in i:
        y_room.append(j);

# print(room);
# print(row_room);
# print(column_room);
# print(x_room);
# print(y_room);

for i in x_room:
    if(i.count('.') >= 2):
        row += 1;

for i in y_room:
    if(i.count('.') >= 2):
        column += 1;

print(row, column);
