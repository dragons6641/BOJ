#define _CRT_SECURE_NO_WARNINGS
#define MAX_N 10000

#include <stdio.h>

int D[MAX_N];

int main()
{
	int n = 0;
	long long m = 0;
	int lp = 0;
	int rp = 0;
	
	long long sum = 0;
	long long ans = 0;

	scanf("%d %lld", &n, &m);

	for (int i = 0; i < n; i++)
	{
		scanf("%d", &D[i]);
	}

	/*
	for (int i = 0; i < n; i++)
	{
		printf("%d ", D[i]);
	}
	*/

	// sum = D[0];

	while (1)
	{
		// printf("n = %d, m = %lld, sum = %lld, ans = %lld, low = %d, high = %d\n", n, m, sum, ans, lp, rp);

		/*
		if (sum > m)
		{
			sum -= D[lp];
			lp += 1;
		}
		else if (sum < m)
		{
			if (rp < n - 1)
			{
				rp += 1;
				sum += D[rp];
			}
			else
			{
				break;
			}
		}
		else
		{
			ans += 1;

			if (lp == rp)
			{
				rp += 1;
				sum += D[rp];
			}
			else
			{
				sum -= D[lp];
				lp += 1;
			}
		}
		*/

		if (sum > m)
		{
			sum -= D[lp];
			lp += 1;
		}
		else if (rp == n)
		{
			break;
		}
		else
		{
			sum += D[rp];
			rp += 1;
		}

		if (sum == m)
		{
			ans += 1;
		}
	}

	printf("%lld\n", ans);

	return 0;
}
