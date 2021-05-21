#define _CRT_SECURE_NO_WARNINGS
#define MAX_N 100000

#include <stdio.h>

int D[MAX_N];

int main()
{
	int n = 0;
	int s = 0;
	int lp = 0;
	int rp = 0;

	int sum = 0;
	int ans = 0;
	int len = MAX_N;

	scanf("%d %d", &n, &s);

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

		if (sum > s)
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

		if (sum >= s)
		{
			ans += 1;

			if ((rp - lp) < len)
			{
				len = (rp - lp);
			}
		}
	}

	if (ans == 0)
	{
		printf("%d\n", ans);
	}
	else
	{
		printf("%d\n", len);
	}

	return 0;
}
