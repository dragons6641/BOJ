/*
10953 A+B - 6
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
	char ch;

	scanf("%d", &T);

	for (int testCase = 1; testCase <= T; testCase++)
	{
		scanf("%d%c%d", &A, &ch, &B);

		int ans = A + B;

		printf("%d\n", ans);
	}

	return 0;
}
