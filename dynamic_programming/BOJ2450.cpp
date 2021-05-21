#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int N;
int ans = 200000;
int A[100001];
int B[100001];
int cnt[4];
int order[4];
bool chk[4];

int Min(int x, int y)
{
	return ((x < y) ? x : y);
}

int calc(void)
{
	int cnt1 = 0;
	int cnt2 = 0;
	int arr[4][4] = { {0} };

	for (register int i = 1, k = 1; i <= 3; i++)
	{
		for (register int j = 1; j <= cnt[order[i]]; j++)
		{
			B[k++] = order[i];
		}
	}

	for (register int i = 1; i <= N; i++)
	{
		arr[B[i]][A[i]]++;
	}

	for (register int i = 1; i < 3; i++)
	{
		for (register int j = i + 1; j <= 3; j++)
		{
			int k = Min(arr[i][j], arr[j][i]);

			cnt1 += k;
			arr[i][j] -= k;
			arr[j][i] -= k;
			cnt2 += (arr[i][j] + arr[j][i]);
		}
	}

	return (cnt1 + (cnt2 / 3 * 2));
}

void inputData(void)
{
	scanf("%d", &N);

	for (register int i = 1; i <= N; i++)
	{
		scanf("%d", &A[i]);

		cnt[A[i]]++;
	}

	return;
}

void dfs(int step)
{
	if (step > 3)
	{
		ans = Min(ans, calc());

		return;
	}

	for (register int i = 1; i <= 3; i++)
	{
		if (chk[i])
		{
			continue;
		}

		chk[i] = true;

		order[step] = i;

		dfs(step + 1);

		chk[i] = false;
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	inputData();

	dfs(1);

	printf("%d\n", ans);

	return 0;
}
