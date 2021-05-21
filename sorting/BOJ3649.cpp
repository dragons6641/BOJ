# define _CRT_SECURE_NO_WARNINGS
# include <stdio.h>
# include <stdlib.h>

# define max_x 20
# define max_n 1000000
# define max_l 100000000
# define nano_to_cent 10000000

int temp = 0;
int t = 0;
int x = 0;
int n = 0;
int lego[max_n] = { 0 };
int ans = 0;

int compare(const void *a, const void *b)
{
	int num1 = *(int *)a;
	int num2 = *(int *)b;

	if (num1 < num2)
	{
		return -1;
	}
	else if (num1 > num2)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

// 쓰레기 버전
/*
int search(int lego[])
{
	for (int i = 0; i < n; i++)
	{
		for (int j = (i + 1); j < n; j++)
		{
			if (lego[i] + lego[j] == x)
			{
				return lego[i];
			}
		}
	}

	return -1;
}
*/

// 괜찮은 버전
int search_advanced(int lego[])
{
	int start = 0;
	int end = n - 1;
	int sum = 0;

	while (start < end)
	{
		sum = lego[start] + lego[end];

		if (sum < x)
		{
			start += 1;
		}
		else if (sum > x)
		{
			end -= 1;
		}
		else
		{
			if (start != end)
			{
				return lego[start];
			}
		}
	}

	return -1;
}

int main()
{
	while (scanf("%d %d", &x, &n) != EOF)
	{
		x *= nano_to_cent;

		// printf("%d %d\n", x, n);

		for (int i = 0; i < n; i++)
		{
			scanf("%d", &lego[i]);
		}

		// 정렬
		qsort(lego, n, sizeof(int), compare);

		/*
		for (int i = 0; i < n; i++)
		{
		printf("%d\n", lego[i]);
		}
		*/

		/*
		// 탐색 쓰레기 버전
		ans = search(lego);
		*/

		// 탐색 괜찮은 버전
		ans = search_advanced(lego);

		if (ans < 0)
		{
			printf("danger\n");
		}
		else
		{
			printf("yes %d %d\n", ans, x - ans);
		}
	}

	return 0;
}
