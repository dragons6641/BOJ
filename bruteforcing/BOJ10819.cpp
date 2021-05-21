# define _CRT_SECURE_NO_WARNINGS
# include <stdio.h>
# include <math.h>

# define max_size 8
# define start 0

int n = 0;
int num_list[max_size + 1] = { 0 };
int isUsed[max_size + 1] = { 0 };
int dif = 0;
int ans = 0;
int cnt = 0;

// now는 배열의 index값!
void backTrack(int prev, int now)
{
	// 변수 세팅
	isUsed[now] = 1;

	for (int i = 0; i < n; i++)
	{
		if (isUsed[i] == 0)
		{
			dif += abs(num_list[now] - num_list[i]);
			cnt += 1;

			if (dif > ans)
			{
				ans = dif;

				// printf("%d\n", ans);
			}

			// printf("%d %d %d\n", dif, now, i);

			backTrack(now, i);
		}
	}

	// 변수 초기화
	isUsed[now] = 0;
	dif -= abs(num_list[prev] - num_list[now]);
	cnt -= 1;
}

int main()
{
	scanf("%d", &n);

	// printf("%d\n", n);

	for (int i = 0; i < n; i++)
	{
		getchar();

		scanf("%d", &num_list[i]);
	}

	/*
	for (int i = 0; i < n; i++)
	{
		printf("%d ", num_list[i]);
	}
	*/

	for (int i = 0; i < n; i++)
	{
		backTrack(i, i);

		// printf("%dth iteration\n", i);
	}

	printf("%d", ans);

	return 0;
}
