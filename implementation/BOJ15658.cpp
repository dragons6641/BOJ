/*
15658 연산자 끼워넣기
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 11
#define MAX_M 100
#define MAX_OPERATOR 4
#define START_NOW 0
#define START_LEVEL 1
#define MIN_INT -21e8
#define MAX_INT 21e8

int N;
int minAns = MAX_INT;
int maxAns = MIN_INT;
int operandList[MAX_N] = { 0, };
int operatorList[MAX_OPERATOR] = { 0, };

void input(void)
{
	scanf("%d", &N);

	for (int i = 0; i < N; i++)
	{
		scanf("%d", &operandList[i]);
	}

	for (int i = 0; i < MAX_OPERATOR; i++)
	{
		scanf("%d", &operatorList[i]);
	}

	return;
}

void run(int now, int level)
{
	if (level == N)
	{
		if (minAns > now)
		{
			minAns = now;
		}

		if (maxAns < now)
		{
			maxAns = now;
		}

		return;
	}

	// 1. 덧셈
	if (operatorList[0] > 0)
	{
		operatorList[0]--;

		run(now + operandList[level], level + 1);

		operatorList[0]++;
	}

	// 2. 뺄셈
	if (operatorList[1] > 0)
	{
		operatorList[1]--;

		run(now - operandList[level], level + 1);

		operatorList[1]++;
	}

	// 3. 곱셈
	if (operatorList[2] > 0)
	{
		operatorList[2]--;

		run(now * operandList[level], level + 1);

		operatorList[2]++;
	}

	// 4. 나눗셈
	if (operatorList[3] > 0)
	{
		operatorList[3]--;

		run(now / operandList[level], level + 1);

		operatorList[3]++;
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);
	// freopen("input3.txt", "r", stdin);

	setbuf(stdout, NULL);

	input();

	run(operandList[START_NOW], START_LEVEL);

	printf("%d\n", maxAns);
	printf("%d\n", minAns);

	return 0;
}
