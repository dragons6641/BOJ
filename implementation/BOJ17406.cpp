/*
17406 배열 돌리기 4
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MIN_R 3
#define MIN_C 3
#define MIN_K 1
#define MIN_A 1
#define MAX_R 50
#define MAX_C 50
#define MAX_K 6
#define MAX_A 100

struct Node
{
	int visit;
	int r;
	int c;
	int s;
};

int N;
int M;
int K;
// 최솟값을 가져야 함, 초기화는 최대로
int ans = 21e8;
// 1부터 시작
int orderList[MAX_K + 1] = { 0, };
// 1부터 시작
int map[MAX_R + 1][MAX_C + 1] = { 0, };
// 1부터 시작
Node rotateList[MAX_K + 1] = { {0, 0, 0, 0}, };

void input(void)
{
	scanf("%d %d %d", &N, &M, &K);

	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= M; c++)
		{
			scanf("%d", &map[r][c]);
		}
	}

	for (int i = 1; i <= K; i++)
	{
		scanf("%d %d %d", &rotateList[i].r, &rotateList[i].c, &rotateList[i].s);

		rotateList[i].visit = 0;
	}

	return;
}

int calc(void)
{
	int ret = 21e8;

	for (int r = 1; r <= N; r++)
	{
		int sum = 0;

		for (int c = 1; c <= M; c++)
		{
			sum += map[r][c];
		}

		if (ret > sum)
		{
			ret = sum;
		}
	}

	return ret;
}

void clockwise(int r, int c, int s)
{
	for (int k = s; k >= 1; k--)
	{
		int temp = map[r - k][c - k];

		// 1. 왼쪽
		for (int a = -k; a < k; a++)
		{
			map[r + a][c - k] = map[r + a + 1][c - k];
		}
		// 2. 아래쪽
		for (int b = -k; b < k; b++)
		{
			map[r + k][c + b] = map[r + k][c + b + 1];
		}
		// 3. 오른쪽
		for (int a = k; a > -k; a--)
		{
			map[r + a][c + k] = map[r + a - 1][c + k];
		}
		// 4. 위쪽
		for (int b = k; b > -k; b--)
		{
			map[r - k][c + b] = map[r - k][c + b - 1];
		}

		map[r - k][c - k + 1] = temp;
	}

	return;
}

void counterclockwise(int r, int c, int s)
{
	for (int k = s; k >= 1; k--)
	{
		int temp = map[r - k][c - k];

		// 1. 위쪽
		for (int b = -k; b < k; b++)
		{
			map[r - k][c + b] = map[r - k][c + b + 1];
		}
		// 2. 오른쪽
		for (int a = -k; a < k; a++)
		{
			map[r + a][c + k] = map[r + a + 1][c + k];
		}
		// 3. 아래쪽
		for (int b = k; b > -k; b--)
		{
			map[r + k][c + b] = map[r + k][c + b - 1];
		}
		// 4. 왼쪽
		for (int a = k; a > -k; a--)
		{
			map[r + a][c - k] = map[r + a - 1][c - k];
		}

		map[r - k + 1][c - k] = temp;
	}

	return;
}

void backtrack(int level)
{
	int result;
	int now;

	if (level == K)
	{
		int debug = 1;

		for (int i = 1; i <= K; i++)
		{
			now = orderList[i];

			clockwise(rotateList[now].r, rotateList[now].c, rotateList[now].s);
		}

		result = calc();

		if (ans > result)
		{
			ans = result;
		}

		for (int i = K; i >= 1; i--)
		{
			now = orderList[i];

			counterclockwise(rotateList[now].r, rotateList[now].c, rotateList[now].s);
		}

		return;
	}

	for (int i = 1; i <= K; i++)
	{
		if (rotateList[i].visit == 0)
		{
			rotateList[i].visit = 1;
			orderList[level + 1] = i;

			backtrack(level + 1);

			rotateList[i].visit = 0;
			orderList[level + 1] = 0;
		}
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);

	setbuf(stdout, NULL);

	input();

	// int x = calc();

	/*
	clockwise(3, 4, 2);
	counterclockwise(3, 4, 2);
	*/

	backtrack(0);

	// int debug = 1;

	printf("%d\n", ans);

	return 0;
}
