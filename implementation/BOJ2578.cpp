/*
Pro입문 3주차 Problem A 빙고
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_R 5
#define MAX_C 5
#define MAX_SIZE (MAX_R * MAX_C)
#define MAX_BINGO 3

struct Node
{
	int r;
	int c;
}whereNum[MAX_SIZE + 1];

int lineCntR; // 대각선, 왼쪽 위부터 아래로
int lineCntL; // 대각선, 오른쪽 위부터 아래로
int lineCntGaro[MAX_C];
int lineCntSero[MAX_R];
int map[MAX_R][MAX_C];
int checkMap[MAX_R][MAX_C];

void input(void)
{
	for (int r = 0; r < MAX_R; r++)
	{
		for (int c = 0; c < MAX_R; c++)
		{
			scanf("%d", &map[r][c]);

			whereNum[map[r][c]] = { r, c };
		}
	}

	return;
}

int setNumber(int num)
{
	// 빙고 = return 0;
	int ret = 0;
	int r = whereNum[num].r;
	int c = whereNum[num].c;

	checkMap[r][c] = 1;

	lineCntGaro[c]++;
	lineCntSero[r]++;

	if (r == c)
	{
		lineCntR++;
	}

	if (r + c == MAX_R - 1)
	{
		lineCntL++;
	}

	if (lineCntGaro[c] == MAX_C)
	{
		lineCntGaro[c]++;
		ret++;
	}
	if (lineCntSero[r] == MAX_R)
	{
		lineCntSero[r]++;
		ret++;
	}
	if (lineCntR == MAX_R)
	{
		lineCntR++;
		ret++;
	}
	if (lineCntL == MAX_R)
	{
		lineCntL++;
		ret++;
	}

	if (ret == 0)
	{
		return 0;
	}
	else
	{
		return ret;
	}
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	setbuf(stdout, NULL);

	input();

	int num;
	int callCnt = 0;
	int bingoCnt = 0;

	for (int r = 0; r < MAX_R; r++)
	{
		for (int c = 0; c < MAX_C; c++)
		{
			scanf("%d", &num);

			bingoCnt += setNumber(num);

			callCnt++;

			/*
			if (ret == 0)
			{
				bingoCnt++;

				if (bingoCnt >= MAX_BINGO)
				{
					printf("%d\n", callCnt);

					return 0;
				}
			}
			*/

			if (bingoCnt >= MAX_BINGO)
			{
				printf("%d\n", callCnt);

				return 0;
			}
		}
	}

	return 0;
}
