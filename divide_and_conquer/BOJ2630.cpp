#include <stdio.h>

#define MAX_N (128)

int N;
int paper[MAX_N][MAX_N];

int cnt[2];

void Input_Data(void)
{
	int r, c;
	scanf("%d", &N);
	for (r = 0; r < N; r++)
	{
		for (c = 0; c < N; c++)
		{
			scanf("%d", &paper[r][c]);
		}
	}
}

int Check_Paper(int sr, int sc, int len)
{
	int r, c;

	for (r = sr; r < sr + len; r++)
	{
		for (c = sc; c < sc + len; c++)
		{
			if (paper[sr][sc] != paper[r][c])
				return 0;
		}
	}
	return 1;
}

void Count_Paper(int sr, int sc, int len)
{
	if (Check_Paper(sr, sc, len))
	{
		cnt[paper[sr][sc]]++;
	}
	else
	{
		Count_Paper(sr, sc, len / 2);
		Count_Paper(sr, sc + len / 2, len / 2);
		Count_Paper(sr + len / 2, sc, len / 2);
		Count_Paper(sr + len / 2, sc + len / 2, len / 2);
	}
}

int main(void)
{
	Input_Data();

	Count_Paper(0, 0, N);

	printf("%d\n", cnt[0]);
	printf("%d\n", cnt[1]);
	return 0;
}
