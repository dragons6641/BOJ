/*
1924 2007년
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_MONTH 12
#define MAX_DAY 7
#define MAX_LENGTH 3

int main(void)
{
	int X;
	int Y;
	int dateList[MAX_MONTH + 1] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	char outputList[MAX_DAY][MAX_LENGTH + 1] = { "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT" };

	scanf("%d %d", &X, &Y);

	while (X > 1)
	{
		Y += dateList[X - 1];
		X--;
	}

	printf("%s\n", outputList[(Y % MAX_DAY)]);

	return 0;
}
