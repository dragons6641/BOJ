/*
Pro입문 2주차 Problem G 곱셈
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	int first;
	char a;
	char b;
	char c;

	setbuf(stdout, NULL);

	scanf("%d", &first);
	scanf("\n%c%c%c", &a, &b, &c);

	a -= '0';
	b -= '0';
	c -= '0';

	printf("%d\n", first * c);
	printf("%d\n", first * b);
	printf("%d\n", first * a);
	printf("%d\n", first * a * 100 + first * b * 10 + first * c);

	return 0;
}
