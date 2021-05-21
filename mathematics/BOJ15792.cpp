/*
15792 A/B - 2
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_A 10000
#define MAX_B 10000
#define MAX_LENGTH 1000
#define MUL 10

int main(void)
{
	int A;
	int B;
	int outputList[MAX_LENGTH + 1] = { 0, };

	scanf("%d %d", &A, &B);

	outputList[0] = A / B;
	int N = A % B;

	register int cnt = 1;

	while ((N != 0) && (cnt <= MAX_LENGTH))
	{
		while (N < B)
		{
			N *= MUL;
			outputList[cnt] = N / B;
			cnt++;
		}

		N %= B;

		int debug = 1;
	}

	cnt--;

	if ((A % B) == 0)
	{
		printf("%d\n", outputList[0]);
	}
	else
	{
		printf("%d.", outputList[0]);

		for (int i = 1; i <= cnt; i++)
		{
			printf("%d", outputList[i]);
		}

		printf("\n");
	}

	return 0;
}
