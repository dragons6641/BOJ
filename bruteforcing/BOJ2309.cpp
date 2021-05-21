/*
2309 일곱 난쟁이
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MIN_N 7
#define MAX_N 9
#define MAX_HEIGHT 100
#define TARGET_HEIGHT 100
#define START_LEVEL 0
#define START_NOW 0
#define MAX_LEVEL (MAX_N - MIN_N)
/*
#define SWAP(a, b, type) do { \
    type temp; \
    temp = a;  \
    a = b;     \
    b = temp;  \
} while (true)
*/

int flag = 0;
// 1부터 사용
int heights[MAX_N + 1] = { 0, };
// 1부터 사용
int dat[MAX_HEIGHT + 1] = { 0, };

void print()
{
	for (int i = 1; i <= MAX_HEIGHT; i++)
	{
		if (dat[i] > 0)
		{
			for (int j = 0; j < dat[i]; j++)
			{
				printf("%d\n", i);
			}
		}
	}

	return;
}

void run(int level, int now, int sum)
{
	if (flag == 1)
	{
		return;
	}

	if (level == MAX_LEVEL)
	{
		if (sum == TARGET_HEIGHT)
		{
			print();

			flag = 1;
		}

		return;
	}

	for (int i = now + 1; i <= MAX_N; i++)
	{
		dat[heights[i]]--;

		run(level + 1, i, sum - heights[i]);

		dat[heights[i]]++;
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);
	// freopen("input3.txt", "r", stdin);
	// freopen("input4.txt", "r", stdin);
	// freopen("input5.txt", "r", stdin);
	// freopen("input6.txt", "r", stdin);

	setbuf(stdout, NULL);

	// 7명 총합 키
	int start_sum = 0;

	for (int i = 1; i <= MAX_N; i++)
	{
		scanf("%d", &heights[i]);

		dat[heights[i]]++;
		start_sum += heights[i];
	}

	// int debug = 1;

	run(START_LEVEL, START_NOW, start_sum);

	return 0;
}
