/*
Pro입문 3주차 Problem K 벽장문의 이동
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_DOOR 20
#define MAX_CUST 20

int doorCnt;
int custCnt;
int min = 21e8;
// int limit;
int customer[MAX_CUST + 10] = { 0, };

/*
int enter(int now, int a, int b)
{
	int i;

	for (i = now; i < custCnt; i++)
	{
		if ((customer[i] == a) || (customer[i] == b))
		{
			continue;
		}

		break;
	}

	return i;
}

void run(int level, int a, int b, int now)
{
	if (min == level)
	{
		return;
	}

	if (limit < level)
	{
		return;
	}

	now = enter(now, a, b);

	if (now == custCnt)
	{
		if (min > level)
		{
			min = level;
		}

		return;
	}

	if (a + 1 < b)
	{
		run(level + 1, a + 1, b, now);
	}
	
	if (a - 1 > 0)
	{
		run(level + 1, a - 1, b, now);
	}
	
	if (b + 1 <= doorCnt)
	{
		run(level + 1, a, b + 1, now);
	}
	
	if (b - 1 > a)
	{
		run(level + 1, a, b - 1, now);
	}

	return;
}
*/

///*
// level : 열었던 벽장문 수, dist : 벽장문 이동 거리
void solve(int level, int a, int b, int dist)
{
	// 답이 될 가능성이 없는 경우
	if (min <= dist)
	{
		// 더 해볼 필요 없음
		return;
	}

	// 벽장문 모두 열었을 경우
	if (level == custCnt)
	{
		// 정답 갱신
		if (min > dist)
		{
			min = dist;
		}

		// 더 해볼 필요 없음
		return;
	}

	// int debug = 1;

	// (a < b)는 무조건 지켜져야 한다!
	// 1. cust < a < b
	if (customer[level] < a)
	{
		// a만 이동 가능
		solve(level + 1, customer[level], b, dist + a - customer[level]);
	}
	// 2. a < b < cust
	else if (customer[level] > b)
	{
		// b만 이동 가능
		solve(level + 1, a, customer[level], dist - b + customer[level]);
	}
	// 3. a < cust < b
	else
	{
		// 둘 다 이동 가능
		// 그래도 가까운 걸 먼저 이동
		// a가 더 가깝다면
		if (customer[level] - a < b - customer[level])
		{
			// a 먼저 이동
			solve(level + 1, customer[level], b, dist - a + customer[level]);
			// b 나중 이동
			solve(level + 1, a, customer[level], dist + b - customer[level]);
		}
		// b가 더 가깝다면
		else
		{
			// b 먼저 이동
			solve(level + 1, a, customer[level], dist + b - customer[level]);
			// a 나중 이동
			solve(level + 1, customer[level], b, dist - a + customer[level]);
		}
	}

	return;
}
//*/

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	setbuf(stdout, NULL);

	int a;
	int b;

	scanf("%d", &doorCnt);
	scanf("%d %d", &a, &b);
	scanf("%d", &custCnt);

	if (a > b)
	{
		int temp = a;
		a = b;
		b = temp;
	}

	for (int i = 0; i < custCnt; i++)
	{
		scanf("%d", &customer[i]);
	}

	// limit = custCnt * (doorCnt - 1);

	// run(0, a, b, 0);

	solve(0, a, b, 0);

	printf("%d\n", min);

	return 0;
}
