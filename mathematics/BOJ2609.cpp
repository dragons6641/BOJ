/*
2609 최대공약수와 최소공배수
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

	scanf("%d %d", &A, &B);

	if (A < B)
	{
		int temp = A;
		A = B;
		B = temp;
	}

	int gcd = getGcd(A, B);
	int lca = getLca(A, B, gcd);

	// int debug = 1;

	printf("%d\n", gcd);
	printf("%d\n", lca);

	return 0;
}
