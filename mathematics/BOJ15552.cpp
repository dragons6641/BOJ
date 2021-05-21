/*
15552 빠른 A+B
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_A 1000
#define MAX_B 1000
#define MAX_T 1000000

int main(void)
{
	int A;
	int B;
	int T;

	scanf("%d", &T);

	for (int testCase = 1; testCase <= T; testCase++)
	{
		scanf("%d %d", &A, &B);

		int ans = A + B;

		printf("%d\n", ans);
	}

	return 0;
}
