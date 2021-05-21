/*
A1 연속부분최대곱
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

/*
#define MAX_N 10000

int N;
double ans = 0.0;
// 1부터 사용
double prefixMul[MAX_N + 1] = { 0.0, };

void input(void) 
{
	prefixMul[0] = 1.0;

	scanf("%d", &N);

	for (int i = 1; i <= N; i++)
	{
		scanf("%lf", &prefixMul[i]);

		prefixMul[i] *= prefixMul[i - 1];
	}

	return;
}

void solve(void)
{
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= i; j++)
		{
			double temp = (prefixMul[i] / prefixMul[j - 1]);

			if (ans < temp)
			{
				ans = temp;
			}
		}
	}

	printf("%.3lf\n", ans);

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	input();

	solve();

	return 0;
}
*/

#define MAX_N ((int)1e4)

int N;
double A[MAX_N + 10] = { 0.0, };

void inputData(void)
{
	scanf("%d", &N);

	for (register int i = 1; i <= N; i++)
	{
		scanf("%lf", &A[i]);
	}
}

double solveN3(void) // O(N^3)
{
	double maxv = 0;

	for (register int s = 1; s <= N; s++) // 시작 요소번호
	{
		for (register int e = s; e <= N; e++) // 끝 요소번호
		{
			double mul = 1;

			for (register int k = s; k <= e; k++) // 시작~끝 까지 곱하기
			{
				mul *= A[k];

				if (maxv < mul)
				{
					maxv = mul;
				}
			}
		}
	}

	return maxv;
}

double solveN2(void) // O(N^2)
{
	double maxv = 0;

	for (register int s = 1; s <= N; s++) // 시작 요소번호
	{
		double mul = 1;

		for (register int k = s; k <= N; k++) // 시작~끝 까지 곱하기
		{
			mul *= A[k];

			if (maxv < mul)
			{
				maxv = mul;
			}
		}
	}

	return maxv;
}

double solveN1(void) // O(N), 필요한 최소한의 경우만 해봄(그리디)
{
	double mul = 1;
	double maxv = 0;

	for (register int i = 1; i <= N; i++)
	{
		if (mul > 1)
		{
			mul *= A[i];
		}
		else
		{
			mul = A[i];
		}

		if (maxv < mul)
		{
			maxv = mul;
		}
	}

	return maxv;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	inputData();

	// double ans = solveN3();
	// double ans = solveN2();
	double ans = solveN1();

	printf("%.3lf\n", ans);

	return 0;
}
