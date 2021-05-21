/*
Pro입문 3일차 Problem I 세로 읽기
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_R 5
#define MAX_C 15

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);

	char map[MAX_R][MAX_C + 5] = { '\0', };

	for (int r = 0; r < MAX_R; r++)
	{
		scanf("%s", map[r]);
	}

	for (int c = 0; c < MAX_C; c++)
	{
		for (int r = 0; r < MAX_R; r++)
		{
			if (map[r][c] != 0)
			{
				printf("%c", map[r][c]);
			}
		}
	}

	printf("\n");

	return 0;
}
