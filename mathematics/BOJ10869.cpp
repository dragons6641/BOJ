/*
10869 사칙연산
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main(void)
{
	int A;
	int B;

	scanf("%d %d", &A, &B);

	printf("%d\n", A + B);
	printf("%d\n", A - B);
	printf("%d\n", A * B);
	printf("%d\n", A / B);
	printf("%d\n", A % B);

	return 0;
}
