/*
10950 A+B - 3
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_A 10
#define MAX_B 10

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
