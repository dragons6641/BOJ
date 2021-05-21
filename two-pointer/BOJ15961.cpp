/*
Problem D 회전 초밥(중)
1. Naive : O(N * K)
2. Counting : O(N + K)
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

struct Data
{
	int id, cnt;
};

const int LM = 3005;
int N;
int D;
int K;
int C;
// int ans;
int ans = 1;
// int len;
int len = 1;
// int sushi[LM * 11];
int sushi[LM * 1000];
int cnt[LM];
Data plate[LM];

void push(int id)
{
	register int i;

	for (i = 1; i <= len; i++)
	{
		if (plate[i].id == id)
		{
			break;
		}
	}

	if (i > len)
	{
		plate[++len] = { id, 1 };
	}
	else
	{
		plate[i].cnt++;
	}

	if (ans < len)
	{
		ans = len;
	}

	return;
}

void pop(int id)
{
	register int i;

	for (i = 1; i <= len; i++)
	{
		if (plate[i].id == id)
		{
			break;
		}
	}

	plate[i].cnt--;

	if (plate[i].cnt == 0)
	{
		plate[i] = plate[len];
		len--;
	}

	return;
}

void solveNaive(void)
{
	scanf("%d %d %d %d", &N, &D, &K, &C);

	for (register int i = 0; i < N; i++)
	{
		scanf("%d", sushi + i);
	}

	for (register int i = 0; i < K; i++)
	{
		sushi[N + i] = sushi[i];
	}

	plate[++len] = { C, 1 };

	for (register int i = 0; i < K; i++)
	{
		push(sushi[i]);
	}

	for (register int i = K; i < N + K; i++)
	{
		pop(sushi[i - K]);
		push(sushi[i]);
	}

	printf("%d\n", ans);

	return;
}

void solveCounting(void)
{
	scanf("%d %d %d %d", &N, &D, &K, &C);

	cnt[C]++;

	for (register int i = 0; i < N; i++)
	{
		scanf("%d", sushi + i);
	}

	for (register int i = 0; i < N + K; i++)
	{
		if (i >= K)
		{
			cnt[sushi[i - K]]--;

			if (cnt[sushi[i - K]] == 0)
			{
				len--;
			}
		}

		cnt[sushi[i % N]]++;

		if (cnt[sushi[i % N]] == 1)
		{
			len++;
		}

		if (ans < len)
		{
			ans = len;
		}
	}

	printf("%d\n", ans);

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);

	// solveNaive();
	solveCounting();

	return 0;
}
