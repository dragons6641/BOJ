/*
B4 색종이(초)
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_R 100
#define MAX_C 100
#define MAX_LENGTH 10

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	setbuf(stdout, NULL);

	int ans = 0;
	int N;
	int R;
	int C;
	int map[MAX_R][MAX_C] = { 0, };

	scanf("%d", &N);

	for (int i = 0; i < N; i++)
	{
		scanf("%d %d", &R, &C);

		for (int a = R; a < R + MAX_LENGTH; a++)
		{
			for (int b = C; b < C + MAX_LENGTH; b++)
			{
				if (map[a][b] == 0)
				{
					map[a][b] = 1;
					ans++;
				}
			}
		}
	}

	printf("%d\n", ans);

	return 0;
}
