/*
1037 약수
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <algorithm>

using namespace std;

#define MAX_N 50

int main(void)
{
	int N;
	int ans = 1;
	int inputList[MAX_N] = { 0, };

	scanf("%d", &N);

	for (register int i = 0; i < N; i++)
	{
		scanf("%d", &inputList[i]);
	}

	sort(inputList, inputList + N);

	ans = inputList[0] * inputList[N - 1];

	printf("%d\n", ans);

	return 0;
}
