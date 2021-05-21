/*
1212 8진수 2진수
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define SRC_DIGIT 8
#define SRC_LENGTH 3
#define INPUT_LENGTH 333334

int main(void)
{
	char src[INPUT_LENGTH + 1] = { '\0' };
	char firstList[SRC_DIGIT][SRC_LENGTH + 1] = { "", "1", "10", "11", "100", "101", "110", "111" };
	char otherList[SRC_DIGIT][SRC_LENGTH + 1] = { "000", "001", "010", "011", "100", "101", "110", "111" };

	scanf("%s", &src);

	if (src[0] == '0')
	{
		printf("0\n");
	}
	else
	{
		printf("%s", firstList[(src[0] - '0')]);

		for (int i = 1; src[i]; i++)
		{
			printf("%s", otherList[(src[i] - '0')]);
		}

		printf("\n");
	}

	return 0;
}
