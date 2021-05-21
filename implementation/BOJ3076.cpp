/*
B3 체스판
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_R 10
#define MAX_C 10
#define MAX_A 10
#define MAX_B 10

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);

	setbuf(stdout, NULL);

	int R;
	int C;
	int A;
	int B;
	int flag = 1;

	scanf("%d %d", &R, &C);
	scanf("%d %d", &A, &B);

	for (int p = 1; p <= R * A; p++)
	{
		for (int q = 1; q <= C * B; q++)
		{
			if (flag)
			{
				printf("X");
			}
			else
			{
				printf(".");
			}

			if (q % B == 0)
			{
				flag = !flag;
			}

			if ((q == C * B) && (C % 2 == 1))
			{
				flag = !flag;
			}
		}

		if (p % A == 0)
		{
			flag = !flag;
		}

		printf("\n");
	}

	return 0;
}
