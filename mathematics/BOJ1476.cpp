/*
1476 날짜 계산
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_E 15
#define MAX_S 28
#define MAX_M 19

int yearList[MAX_E + 1][MAX_S + 1][MAX_M + 1];

void init(void)
{
	int a = 2;
	int b = 2;
	int c = 2;
	int d = 2;

	yearList[1][1][1] = 1;

	while (true)
	{
		if ((a == 1) && (b == 1) && (c == 1))
		{
			break;
		}

		yearList[a][b][c] = d;

		a++;
		b++;
		c++;
		d++;

		if (a > MAX_E)
		{
			a = 1;
		}

		if (b > MAX_S)
		{
			b = 1;
		}

		if (c > MAX_M)
		{
			c = 1;
		}
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);
	// freopen("input3.txt", "r", stdin);
	// freopen("input4.txt", "r", stdin);

	setbuf(stdout, NULL);

	init();

	int E;
	int S;
	int M;

	scanf("%d %d %d", &E, &S, &M);

	printf("%d\n", yearList[E][S][M]);

	return 0;
}
