import sys;

max_value = 200000;

a, b = sys.stdin.readline().split();
n, k = int(a), int(b);

# print(n, k);
queue = [];
ans = 0;
ans_list = [];
isVisited = [False] * (max_value + 1);

def bfs_move(n, k):
    ans = 0;
    isVisited[n] = True;
    queue.append([n, 0]);

    while(len(queue) != 0):
        temp = queue.pop(0);
        now, ans = temp[0], temp[1];

        # print(now, ans);

        if(now == k):
            ans_list.append(ans);

        ans += 1;

        # x - 1
        if(now > 0 and isVisited[now - 1] == False):
            isVisited[now - 1] = True;
            queue.append([now - 1, ans]);

        # x + 1
        if(now < k and isVisited[now + 1] == False):
            isVisited[now + 1] = True;
            queue.append([now + 1, ans]);

            # 2x
        if(now < k and not ((2 * now) - k) > (k - now) and isVisited[2 * now] == False):
            isVisited[2 * now] = True;
            queue.append([2 * now, ans]);

        # print(queue);

    return min(ans_list);

ans = bfs_move(n, k);
print(ans);
