/*
9095 1, 2, 3 더하기
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 10
#define START_LEVEL 0

int ans;
int N;

void run(int level)
{
	if (level == N)
	{
		ans++;

		return;
	}
	else if (level > N)
	{
		return;
	}

	run(level + 1);
	run(level + 2);
	run(level + 3);

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	setbuf(stdout, NULL);

	int T;

	scanf("%d", &T);

	for (int test_case = 1; test_case <= T; test_case++)
	{
		ans = 0;

		scanf("%d", &N);

		run(START_LEVEL);

		printf("%d\n", ans);
	}

	return 0;
}
