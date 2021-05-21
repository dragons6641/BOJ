/*
A2 용액
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

/*
#define MAX_N 100000
#define MIN_M -1000000000
#define MAX_M 1000000000

int N;
int ans = (MAX_M - MIN_M) + 1;
int inputList[MAX_N] = { 0, };

void input(void)
{
	scanf("%d", &N);

	for (int i = 0; i <= N; i++)
	{
		scanf("%d", &inputList[i]);
	}

	return;
}

void solve(void)
{
	int lp = 0;
	int rp = N - 1;
	int lv = inputList[lp];
	int rv = inputList[rp];

	while (lp < rp)
	{
		int sumValue = inputList[lp] + inputList[rp];
		int absValue = ((sumValue > 0) ? sumValue : (-sumValue));

		if (ans > absValue)
		{
			ans = absValue;
			lv = inputList[lp];
			rv = inputList[rp];
		}

		if (sumValue < 0)
		{
			lp++;
		}
		else if (sumValue > 0)
		{
			rp--;
		}
		else
		{
			break;
		}
	}

	printf("%d %d\n", lv, rv);

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);

	input();

	solve();

	return 0;
}
*/

#define MAX_N ((int)1e5)
#define INF ((int)2e9 + 1)

// 용액 수
int N;
int A[MAX_N + 10] = { 0, };

void inputData(void)
{
	scanf("%d", &N);

	for (register int i = 1; i <= N; i++)
	{
		scanf("%d", &A[i]);
	}

	return;
}

int ABS(int x)
{
	return ((x > 0) ? x : (-x));
}

void solveN2(void) // O(N^2)
{
	int sol = INF;
	int a;
	int b;

	for (register int i = 1; i <= N; i++)
	{
		for (register int j = i + 1; j <= N; j++)
		{
			int sum = ABS(A[i] + A[j]);

			if (sol > sum)
			{
				sol = sum;
				a = A[i];
				b = A[j];
			}
		}
	}

	printf("%d %d\n", a, b);

	return;
}

int binarySearch(int s, int e, int data) // data와 합이 0에 가장 가까운 인덱스
{
	int sol = e;
	int minSum = INF;

	while (s <= e)
	{
		int m = (s + e) / 2;
		int sum = data + A[m];

		if (minSum > ABS(sum))
		{
			sol = m;
			minSum = ABS(sum);
		}

		if (sum < 0)
		{
			s = m + 1;
		}
		else if (sum > 0)
		{
			e = m - 1;
		}
		else
		{
			break;
		}
	}
}

void solveNlogN(void)
{
	int sol = INF;
	int a = 0;
	int b = 0;

	for (register int i = 1; i <= N; i++)
	{
		int idx = binarySearch(i + 1, N, A[i]);
		int sum = A[i] + A[idx];

		if (sol > ABS(sum))
		{
			sol = sum;
			a = A[i];
			b = A[idx];
		}
	}

	printf("%d %d\n", &a, &b);

	return;
}

void solveN1(void) // O(N)
{
	int sol = INF;
	int a = 0;
	int b = 0;
	int i = 1;
	int j = N;

	while (i < j)
	{
		int sum = A[i] + A[j];

		if (sol > ABS(sum))
		{
			sol = ABS(sum);
			a = A[i];
			b = A[j];
		}

		if (sum < 0)
		{
			i++;
		}
		else if (sum > 0)
		{
			j--;
		}
		else
		{
			break;
		}
	}

	printf("%d %d\n", a, b);

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	inputData();

	// solveN2();
	// solveNlogN();
	solveN1();

	return 0;
}
