#define _CRT_SECURE_NO_WARNINGS
#define MAX_N 100

#include <stdio.h>

long long D[MAX_N];

int main()
{
	int n = 0;

	scanf("%d", &n);

	D[1] = 1;
	D[2] = 1;

	for (int i = 3; i <= n; i++)
	{
		D[i] = D[i - 1] + D[i - 2];
	}

	printf("%lld\n", D[n]);

	return 0;
}
