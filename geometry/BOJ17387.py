import sys;

def CCW(ax : int, ay : int, bx : int, by : int, cx : int, cy : int) -> int:
    return ((ax * by) + (bx * cy) + (cx * ay)) - ((ay * bx) + (by * cx) + (cy * ax));

def posCmp(ax : int, ay : int, bx : int, by : int) -> int:
    return ((ay - by) if (ax == bx) else (ax - bx));

# sys.stdin = open("input1.txt", 'r');    # 1
# sys.stdin = open("input2.txt", 'r');    # 0
# sys.stdin = open("input3.txt", 'r');    # 1
# sys.stdin = open("input4.txt", 'r');    # 1
# sys.stdin = open("input5.txt", 'r');    # 1
# sys.stdin = open("input6.txt", 'r');    # 1
# sys.stdin = open("input7.txt", 'r');    # 0
# sys.stdin = open("input8.txt", 'r');    # 1
# sys.stdin = open("input9.txt", 'r');    # 0
# sys.stdin = open("input10.txt", 'r');    # 1
# sys.stdin = open("input11.txt", 'r');    # 0
# sys.stdin = open("input12.txt", 'r');    # 1
# sys.stdin = open("input13.txt", 'r');    # 1
# sys.stdin = open("input14.txt", 'r');    # 1
# sys.stdin = open("input15.txt", 'r');    # 1
# sys.stdin = open("input16.txt", 'r');    # 1
# sys.stdin = open("input17.txt", 'r');    # 0
# sys.stdin = open("input18.txt", 'r');    # 0
# sys.stdin = open("input19.txt", 'r');    # 0
# sys.stdin = open("input20.txt", 'r');    # 1

(x1, y1, x2, y2) = map(int, sys.stdin.readline().split());
(x3, y3, x4, y4) = map(int, sys.stdin.readline().split());

L1 = (CCW(x1, y1, x2, y2, x3, y3) * CCW(x1, y1, x2, y2, x4, y4));
L2 = (CCW(x3, y3, x4, y4, x1, y1) * CCW(x3, y3, x4, y4, x2, y2));

if ((L1 == 0) and (L2 == 0)):
    if (posCmp(x1, y1, x2, y2) > 0):
        (x1, y1, x2, y2) = (x2, y2, x1, y1);

    if (posCmp(x3, y3, x4, y4) > 0):
        (x3, y3, x4, y4) = (x4, y4, x3, y3);

    print(int((posCmp(x3, y3, x2, y2) <= 0) and (posCmp(x1, y1, x4, y4) <= 0)));
else:
    print(int((L1 <= 0) and (L2 <= 0)));
