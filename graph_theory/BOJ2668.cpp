/*
Pro입문 3주차 Problem I 숫자고르기
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 100

int N;
int M;
int zeroCnt;
int maxi = 0;
int map[2][(int)(MAX_N * 1.1)] = { 0, };
int check[(int)(MAX_N * 1.1)] = { 0, };
int select[(int)(MAX_N * 1.1)] = { 0, };
int path[(int)(MAX_N * 1.1)] = { 0, };
int maxiPath[(int)(MAX_N * 1.1)] = { 0, };

/*
void input()
{
	scanf("%d", &N);

	for (int i = 0; i < N; i++)
	{
		map[0][i] = i + 1;

		scanf("%d", &M);

		map[1][i] = M;
	}

	zeroCnt = N;

	return;
}
*/

void input(void)
{
	scanf("%d", &N);

	for (int i = 1; i <= N; i++)
	{
		map[0][i] = i;

		scanf("%d", &M);

		map[1][i] = M;
	}

	return;
}

void init(void)
{
	/*
	for (int i = 0; i < N; i++)
	{
		check[i] = 1;
	}
	*/

	/*
	for (int i = 0; i < N; i++)
	{
		int up = map[0][i];
		int dn = map[1][i];

		select[up]--;

		if (select[up] == 0)
		{
			zeroCnt++;
		}
		else if (select[up] == -1)
		{
			zeroCnt--;
		}

		select[dn]++;

		if (select[dn] == 0)
		{
			zeroCnt++;
		}
		else if (select[dn] == 1)
		{
			zeroCnt--;
		}
	}
	*/

	for (int i = 1; i <= N; i++)
	{
		check[i] = 0;
	}

	return;
}


void run(int level, int start)
{
	int oldZeroCnt;
	int left = N - level;
	
	if (zeroCnt == N)
	{
		maxi = level;

		for (int i = 0; i < N; i++)
		{
			maxiPath[i] = path[i];
		}

		return;
	}

	/*
	if ((zeroCnt == N) && (maxi < level))
	{
		maxi = level;

		for (int i = 0; i < N; i++)
		{
			maxiPath[i] = path[i];
		}
	}
	*/

	if (start >= N)
	{
		return;
	}

	/*
	if ((N - zeroCnt) / 2 > left)
	{
		return;
	}
	*/

	for (int i = start; i < N; i++)
	{
		int up = map[0][i];
		int dn = map[1][i];

		if (check[up] == 1)
		{
			continue;
		}

		check[up] = 1;
		path[level] = up;

		oldZeroCnt = zeroCnt;

		select[up]++;

		if (select[up] == 0)
		{
			zeroCnt++;
		}
		else if (select[up] == 1)
		{
			zeroCnt--;
		}

		select[dn]--;

		if (select[dn] == 0)
		{
			zeroCnt++;
		}
		else if (select[dn] == -1)
		{
			zeroCnt--;
		}

		run(level + 1, i + 1);

		zeroCnt = oldZeroCnt;
		select[up]--;
		select[dn]++;
		path[level] = 0;
		check[up] = 0;
	}

	return;
}

void dfs(int cur, int start)
{
	if (check[cur] > 0)
	{
		if (cur == start)
		{
			maxiPath[maxi] = start;

			maxi++;
		}
	}
	else
	{
		check[cur]++;
		
		dfs(map[1][cur], start);
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	setbuf(stdout, NULL);

	// int i = 0;
	// int j = 0;

	input();

	// init();

	// run(0, 0);

	/*
	printf("%d\n", maxi);

	for (int i = 0; i < maxi; i++)
	{
		printf("%d\n", maxiPath[i]);
	}
	*/

	/*
	printf("%d\n", N - maxi);

	while (i < N)
	{
		if (j == maxi)
		{
			for (int idx = i; idx < N; idx++)
			{
				printf("%d\n", map[0][idx]);
			}

			break;
		}

		if (map[0][i] < maxiPath[j])
		{
			printf("%d\n", map[0][i]);
		}
		else if (map[0][i] > maxiPath[j])
		{

		}
		else
		{
			j++;
		}

		i++;
	}
	*/

	for (int i = 1; i <= N; i++)
	{
		dfs(i, i);

		init();
	}

	printf("%d\n", maxi);

	for (int i = 0; i < maxi; i++)
	{
		printf("%d\n", maxiPath[i]);
	}

	return 0;
}
