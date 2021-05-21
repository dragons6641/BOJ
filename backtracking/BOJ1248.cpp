#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 10
#define MAX_M (MAX_N + 1) * (MAX_N / 2)
#define MIN_K (-MAX_N)
#define MAX_K (MAX_N)
#define START_LEVEL 0

// 수열의 크기
int N;
// 수열
int A[MAX_N] = { 0, };
// 아무거나 출력하면 된다
bool isFinished = false;
// 구간 합 정보
char S[MAX_N][MAX_N + 1] = { 0, };

void inputData(void)
{
	scanf("%d", &N);

	for (register int r = 0; r < N; r++)
	{
		for (register int c = r; c < N; c++)
		{
			scanf(" %c", &S[r][c]);
		}
	}

	return;
}

void printAns(void)
{
	for (register int i = 0; i < N; i++)
	{
		printf("%d ", A[i]);
	}

	printf("\n");

	return;
}

bool checkPossible(int level)
{
	// 현재 값까지의 부분합 체크
	for (register int r = 0; r <= level; r++)
	{
		int prefixSum = 0;

		for (register int c = r; c <= level; c++)
		{
			prefixSum += A[c];
		}

		// 결과가 일치할 경우
		if (((prefixSum > 0) && (S[r][level] == '+')) || ((prefixSum < 0) && (S[r][level] == '-')) || ((prefixSum == 0) && (S[r][level] == '0')))
		{
			// 계속 체크 가능
			continue;
		}
		// 결과가 일치하지 않을 경우
		else
		{
			// 더 볼 필요 없음
			return false;
		}
	}

	// 여기까지 오면 조건에 부합하는 경우
	return true;
}

void dfs(int level)
{
	if (isFinished)
	{
		return;
	}

	if (level == N)
	{
		// int debug = 1;

		isFinished = true;

		printAns();

		return;
	}

	bool ret;

	// 양수일 경우
	if (S[level][level] == '+')
	{
		for (register int i = 1; i <= MAX_K; i++)
		{
			A[level] = i;

			ret = checkPossible(level);

			if (ret)
			{
				dfs(level + 1);
			}

			A[level] = 0;
		}
	}
	// 음수일 경우
	else if (S[level][level] == '-')
	{
		for (register int i = -1; i >= MIN_K; i--)
		{
			A[level] = i;

			ret = checkPossible(level);

			if (ret)
			{
				dfs(level + 1);
			}

			A[level] = 0;
		}
	}
	// 0일 경우
	else
	{
		dfs(level + 1);
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	inputData();

	dfs(START_LEVEL);

	return 0;
}
