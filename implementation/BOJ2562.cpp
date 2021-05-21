/*
A2 최대값
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 9
#define MAX_M 100

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	setbuf(stdout, NULL);

	int maxValue = 0;
	int maxIndex = 0;
	// 1부터 사용
	int inputList[MAX_N + 1] = { 0, };

	for (int i = 1; i <= MAX_N; i++)
	{
		scanf("%d", &inputList[i]);

		if (maxValue < inputList[i])
		{
			maxValue = inputList[i];
			maxIndex = i;
		}
	}

	printf("%d\n", maxValue);
	printf("%d\n", maxIndex);

	return 0;
}
