/*
1920 수 찾기
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <algorithm>

using namespace std;

#define MAX_N 100000
#define MAX_M 100000

int main(void)
{
	int N;
	int M;
	int K;
	int inputList[MAX_N] = { 0, };

	scanf("%d", &N);

	for (int i = 0; i < N; i++)
	{
		scanf("%d", &inputList[i]);
	}

	sort(inputList, inputList + N);

	scanf("%d", &M);

	for (int i = 0; i < M; i++)
	{
		scanf("%d", &K);

		bool ret = binary_search(inputList, inputList + N, K);

		if (ret)
		{
			printf("1\n");
		}
		else
		{
			printf("0\n");
		}
	}

	return 0;
}
