/*
1009 분산처리
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_A 100
#define MAX_B 1000000
#define MODULAR 10

int main(void)
{
	int T;
	int A;
	int B;

	scanf("%d", &T);

	for (int i = 0; i < T; i++)
	{
		int ans = 1;

		scanf("%d %d", &A, &B);

		for (int j = 0; j < B; j++)
		{
			ans = ((ans * A) % MODULAR);
		}

		if (ans == 0)
		{
			ans = MODULAR;
		}

		printf("%d\n", ans);
	}

	return 0;
}
