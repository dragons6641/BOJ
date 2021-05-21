/*
A6 히스토그램에서 가장 큰 직사각형
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

/*
#define MAX_N 100000
#define ll long long

int N;
// 가장 위에 있는 원소를 가리키고 있음
int sp = 0;
// 1부터 사용
int H[MAX_N + 1] = { 0, };
// 1부터 사용
ll stack[MAX_N + 1] = { 0, };

void push(int data)
{
	stack[++sp] = data;

	return;
}

void pop(void)
{
	sp--;

	return;
}

ll top(void)
{
	return stack[sp];
}

int size(void)
{
	return sp;
}

bool isEmpty(void)
{
	return (sp == 0);
}

void init(void)
{
	sp = 0;

	return;
}

ll solve(void)
{
	ll maxArea = 0;
	ll width = 0;

	for (int i = 1; i <= N; i++)
	{
		// 비어있거나, 내가 더 크다면
		if ((isEmpty()) || (H[i] >= top()))
		{
			// 스택에 push
			push(H[i]);
		}
		// 내가 더 작다면
		else
		{
			width = 0;

			while ((!isEmpty()) && (H[i] < top()))
			{
				width++;

				ll height = top();

				pop();

				ll area = width * height;

				if (maxArea < area)
				{
					maxArea = area;
				}
			}

			// 스택에 push
			push(H[i]);
		}
	}

	width = 0;

	while (!isEmpty())
	{
		width++;

		ll height = top();

		pop();

		ll area = width * height;

		if (maxArea < area)
		{
			maxArea = area;
		}
	}

	return maxArea;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);

	while (true)
	{
		scanf("%d", &N);

		if (N == 0)
		{
			break;
		}

		init();

		for (int i = 1; i <= N; i++)
		{
			scanf("%d", &H[i]);
		}

		ll ans = solve();

		printf("%lld\n", ans);
	}

	return 0;
}
*/

#define MAX_N ((int)1e5)
#define MAX_H ((int)1e9)

typedef signed long long S64;

typedef struct
{
	int h; // 높이
	int n; // 인덱스
}STK;

int N;
int sp = 0;
int H[MAX_N + 10] = { 0, };
STK stack[MAX_N + 10] = { {0, 0}, };

void initStk(void)
{
	sp = 0;

	return;
}

void push(int h, int n)
{
	stack[++sp] = { h, n };

	return;
}

void pop(void)
{
	sp--;

	return;
}

STK top(void)
{
	return stack[sp];
}

int size(void)
{
	return sp;
}

bool empty(void)
{
	return (sp == 0);
}

int inputData(void)
{
	scanf("%d", &N);

	if (N == 0)
	{
		return 0;
	}

	for (register int i = 0; i < N; i++)
	{
		scanf("%d", &H[i]);
	}

	return 1;
}

S64 solveN2(void)
{
	S64 maxArea = 0;

	for (int s = 0; s < N; s++)
	{
		int h = MAX_H;

		for (int k = s; k < N; k++)
		{
			if (h > H[k])
			{
				h = H[k]; // s ~ k까지 중 낮은 높이 찾기
			}

			if (h == 0)
			{
				break;
			}

			S64 area = (S64)h * (k - s + 1);

			if (maxArea < area)
			{
				maxArea = area;
			}
		}
	}

	return maxArea;
}

S64 solveN1(void)
{
	S64 maxArea = 0;
	S64 area = 0;

	initStk(); // 스택 초기화

	for (int i = 0; i < N; i++)
	{
		int n = i;

		while ((!empty()) && (top().h >= H[i]))
		{
			n = top().n;

			area = (S64)top().h * (i - n);

			pop();

			if (maxArea < area)
			{
				maxArea = area;
			}
		}

		push(H[i], n);
	}

	while (!empty())
	{
		area = (S64)top().h * (N - top().n);

		pop();

		if (maxArea < area)
		{
			maxArea = area;
		}
	}

	return maxArea;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	for ( ; ; )
	{
		if (inputData() == 0)
		{
			break;
		}

		// S64 ans = solveN2();
		S64 ans = solveN1();

		printf("%lld\n", ans);
	}
}
