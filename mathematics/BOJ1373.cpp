/*
1373 2진수 8진수
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define INPUT_LENGTH 1000000
#define OUTPUT_LENGTH ((INPUT_LENGTH / DEST_LENGTH) + 1)
#define DEST_LENGTH 3

char src[INPUT_LENGTH + 1] = { '\0' };

int main(void)
{
	char tmp[DEST_LENGTH + 1] = { '\0' };
	char outputList[OUTPUT_LENGTH + 1] = { '\0' };

	scanf("%s", &src);

	if (src[0] == '0')
	{
		printf("0\n");
	}
	else
	{
		register int inputCnt = 0;
		register int outputCnt = 0;
		bool flag = false;

		while (src[inputCnt])
		{
			inputCnt++;
		}

		register int digit = DEST_LENGTH - 1;

		while (inputCnt > 0)
		{
			inputCnt--;
			tmp[digit] = src[inputCnt];
			digit--;

			if (digit == -1)
			{
				if (tmp[0] == '0')
				{
					if (tmp[1] == '0')
					{
						if (tmp[2] == '0')
						{
							outputList[outputCnt] = '0';
						}
						else
						{
							outputList[outputCnt] = '1';
						}
					}
					else
					{
						if (tmp[2] == '0')
						{
							outputList[outputCnt] = '2';
						}
						else
						{
							outputList[outputCnt] = '3';
						}
					}
				}
				else
				{
					if (tmp[1] == '0')
					{
						if (tmp[2] == '0')
						{
							outputList[outputCnt] = '4';
						}
						else
						{
							outputList[outputCnt] = '5';
						}
					}
					else
					{
						if (tmp[2] == '0')
						{
							outputList[outputCnt] = '6';
						}
						else
						{
							outputList[outputCnt] = '7';
						}
					}
				}

				outputCnt++;
				digit = DEST_LENGTH - 1;
			}
		}

		while ((digit >= 0) && (digit < DEST_LENGTH - 1))
		{
			flag = true;

			tmp[digit] = '0';
			digit--;
		}

		if (flag)
		{
			if (tmp[0] == '0')
			{
				if (tmp[1] == '0')
				{
					if (tmp[2] == '0')
					{
						outputList[outputCnt] = '0';
					}
					else
					{
						outputList[outputCnt] = '1';
					}
				}
				else
				{
					if (tmp[2] == '0')
					{
						outputList[outputCnt] = '2';
					}
					else
					{
						outputList[outputCnt] = '3';
					}
				}
			}
			else
			{
				if (tmp[1] == '0')
				{
					if (tmp[2] == '0')
					{
						outputList[outputCnt] = '4';
					}
					else
					{
						outputList[outputCnt] = '5';
					}
				}
				else
				{
					if (tmp[2] == '0')
					{
						outputList[outputCnt] = '6';
					}
					else
					{
						outputList[outputCnt] = '7';
					}
				}
			}

			outputCnt++;
		}

		for (int i = outputCnt - 1; i >= 0; i--)
		{
			printf("%c", outputList[i]);
		}

		printf("\n");
	}

	return 0;
}
