/*
1934 최소공배수
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int getGcd(int x, int y)
{
	if (y == 0)
	{
		return x;
	}

	return getGcd(y, x % y);
}

int getLca(int x, int y, int z)
{
	return (x * y / z);
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	setbuf(stdout, NULL);

	int A;
	int B;
	int T;
	int gcd;
	int lca;

	scanf("%d", &T);

	for (int test_case = 1; test_case <= T; test_case++)
	{
		scanf("%d %d", &A, &B);

		if (A < B)
		{
			int temp = A;
			A = B;
			B = temp;
		}

		gcd = getGcd(A, B);
		lca = getLca(A, B, gcd);

		printf("%d\n", lca);
	}

	return 0;
}
