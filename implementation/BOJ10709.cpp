/*
A0 기상캐스터
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_R 100
#define MAX_C 100
#define MAX_CLOUD (MAX_R * MAX_C)

struct Node
{
	int r;
	int c;
};

int H;
int W;
int cnt;
int outputMap[MAX_R + 1][MAX_C + 1] = { 0, };
char map[MAX_R + 1][MAX_C + 1] = { 0, };
Node cloudList[MAX_CLOUD] = { {0, 0}, };

void input(void)
{
	scanf("%d %d", &H, &W);

	for (int r = 0; r < H; r++)
	{
		scanf("%s", &map[r]);

		for (int c = 0; c < W; c++)
		{
			if (map[r][c] == 'c')
			{
				cloudList[cnt++] = { r, c };
			}
		}
	}

	return;
}

void init(void)
{
	for (int r = 0; r < H; r++)
	{
		for (int c = 0; c < W; c++)
		{
			outputMap[r][c] = -1;
		}
	}

	for (int i = 0; i < cnt; i++)
	{
		if (outputMap[cloudList[i].r][cloudList[i].c] == -1)
		{
			outputMap[cloudList[i].r][cloudList[i].c] = 0;
		}
	}

	return;
}

// 턴 한번 진행
void simulate(int turn)
{
	/*
	for (int r = 0; r < H; r++)
	{
		for (int c = W - 1; c > 0; c--)
		{
			map[r][c] = map[r][c - 1];
		}
	}
	*/

	for (int i = 0; i < cnt; i++)
	{
		// 한 칸씩 이동
		cloudList[i].c++;

		if (cloudList[i].c < W)
		{
			if (outputMap[cloudList[i].r][cloudList[i].c] == -1)
			{
				outputMap[cloudList[i].r][cloudList[i].c] = turn;
			}
		}
	}

	return;
}

void print(void)
{
	for (int r = 0; r < H; r++)
	{
		for (int c = 0; c < W; c++)
		{
			printf("%d ", outputMap[r][c]);
		}

		printf("\n");
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	// setbuf(stdout, NULL);

	input();

	init();

	for (int c = 1; c <= W; c++)
	{
		simulate(c);
	}

	print();

	return 0;
}
