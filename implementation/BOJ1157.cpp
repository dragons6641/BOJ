/*
1157 단어 공부
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_LENGTH 1000000
#define MAX_ALPHABET ('z' - 'a' + 1)

int main(void)
{
	int length = 0;
	int maxIndex = -1;
	int maxValue = 0;
	int maxCnt = 0;
	int cntList[MAX_ALPHABET] = { 0, };
	char inputStr[MAX_LENGTH + 1] = { 0, };

	scanf("%s", inputStr);

	while (inputStr[length])
	{
		if ((inputStr[length] >= 'A') && (inputStr[length] <= 'Z'))
		{
			inputStr[length] += ('a' - 'A');
		}

		length++;
	}

	for (register int i = 0; i < length; i++)
	{
		int idx = inputStr[i] - 'a';

		cntList[idx]++;

		if (maxValue < cntList[idx])
		{
			maxIndex = idx;
			maxValue = cntList[idx];
			maxCnt = 1;
		}
		else if (maxValue == cntList[idx])
		{
			maxCnt++;
		}
	}

	if (maxCnt == 1)
	{
		printf("%c\n", (maxIndex + 'A'));
	}
	else
	{
		printf("?\n");
	}

	return 0;
}
