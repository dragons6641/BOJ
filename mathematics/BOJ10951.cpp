/*
10951 A+B - 4
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_A 10
#define MAX_B 10

int main(void)
{
	int A;
	int B;

	while (scanf("%d %d", &A, &B) != EOF)
	{
		int ans = A + B;

		printf("%d\n", ans);
	}

	return 0;
}
