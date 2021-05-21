/*
Pro입문 3주차 Problem C 카드게임
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_DIGIT 10
#define MAX_N 5

int isSameColor = 1;
int isContiNum = 0;
int maxNum;
int minNumTwo = MAX_DIGIT;
int dat[MAX_DIGIT];
int sameCnt[MAX_N + 1];
int sameCntMaxNum[MAX_N + 1];
int nums[MAX_N];
char chs[MAX_N];

void init(void)
{
	char ch = '\0';

	for (int i = 0; i < MAX_N; i++)
	{
		// white space 없애기 위해 %c 앞에 공백 한 글자 넣어준다
		scanf(" %c %d", &chs[i], &nums[i]);

		if (ch == '\0')
		{
			ch = chs[i];
		}
		else if (ch != chs[i])
		{
			isSameColor = 0;
		}

		if (maxNum < nums[i])
		{
			maxNum = nums[i];
		}

		dat[nums[i]]++;
	}

	for (int i = 1; i < MAX_DIGIT; i++)
	{
		if (dat[i] > 0)
		{
			sameCnt[dat[i]]++;

			if (sameCntMaxNum[dat[i]] < i)
			{
				sameCntMaxNum[dat[i]] = i;
			}
		}
	}

	if (sameCnt[2] == 2)
	{
		for (int i = 1; i < MAX_DIGIT; i++)
		{
			if ((dat[i] == 2) && (minNumTwo > i))
			{
				minNumTwo = i;
			}
		}
	}

	if (sameCnt[1] == MAX_N)
	{
		isContiNum = 1;

		for (int i = maxNum; i > maxNum - MAX_N; i--)
		{
			if (dat[i] == 0)
			{
				isContiNum = 0;

				break;
			}
		}
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	setbuf(stdout, NULL);

	init();

	int result;

	if ((isSameColor == 1) && (isContiNum == 1))
	{
		result = maxNum + 900;
	}
	else if (sameCnt[4] == 1)
	{
		result = sameCntMaxNum[4] + 800;
	}
	else if ((sameCnt[3] == 1) && (sameCnt[2] == 1))
	{
		result = (sameCntMaxNum[3] * 10) + sameCntMaxNum[2] + 700;
	}
	else if (isSameColor == 1)
	{
		result = maxNum + 600;
	}
	else if (isContiNum == 1)
	{
		result = maxNum + 500;
	}
	else if (sameCnt[3] == 1)
	{
		result = sameCntMaxNum[3] + 400;
	}
	else if (sameCnt[2] == 2)
	{
		result = (sameCntMaxNum[2] * 10) + minNumTwo + 300;
	}
	else if (sameCnt[2] == 1)
	{
		result = sameCntMaxNum[2] + 200;
	}
	else
	{
		result = maxNum + 100;
	}

	printf("%d\n", result);

	return 0;
}
