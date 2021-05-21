/*
1000 A+B
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_A 10
#define MAX_B 10

int main(void)
{
	int A;
	int B;

	scanf("%d %d", &A, &B);

	int ans = A + B;

	printf("%d\n", ans);

	return 0;
}
