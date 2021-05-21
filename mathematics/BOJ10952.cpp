/*
10952 A+B - 5
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_A 10
#define MAX_B 10

int main(void)
{
	int A;
	int B;

	while (true)
	{
		scanf("%d %d", &A, &B);

		if ((A == 0) && (B == 0))
		{
			break;
		}

		int ans = A + B;

		printf("%d\n", ans);
	}

	return 0;
}
