/*
10757 큰 수 A+B
*/

#define _CRT_SECURE_NO_WARNINGS
#define ll long long

#include <stdio.h>

#define MAX_LENGTH 10000
#define DIGIT 10

int main(void)
{
	int lenA = 0;
	int lenB = 0;
	register int i = 0;

	char A[MAX_LENGTH + 10] = { 0, };
	char B[MAX_LENGTH + 10] = { 0, };
	char carry[MAX_LENGTH + 10] = { 0, };
	char ans[MAX_LENGTH + 10] = { 0, };

	for (i = 0; i <= MAX_LENGTH + 8; i++)
	{
		carry[i] = '0';
	}

	scanf("%s %s", &A, &B);

	i = 0;

	while (A[i] || B[i])
	{
		if (A[i])
		{
			lenA++;
		}

		if (B[i])
		{
			lenB++;
		}

		i++;
	}

	for (i = 0; i < (lenA / 2); i++)
	{
		char tmp = A[i];
		A[i] = A[lenA - i - 1];
		A[lenA - i - 1] = tmp;
	}

	for (i = 0; i < (lenB / 2); i++)
	{
		char tmp = B[i];
		B[i] = B[lenB - i - 1];
		B[lenB - i - 1] = tmp;
	}

	i = 0;

	while (A[i] || B[i])
	{
		int tmp;
		char next;

		if (A[i] && B[i])
		{
			tmp = A[i] + B[i] + carry[i] - ('0' * 3);

			if (tmp >= DIGIT)
			{
				ans[i] = (tmp - DIGIT) + '0';
				carry[i + 1] = '1';
			}
			else
			{
				ans[i] = tmp + '0';
			}
		}
		else if (A[i])
		{
			next = A[i] + carry[i] - '0';

			if (next >= DIGIT + '0')
			{
				ans[i] = next - DIGIT;
				carry[i + 1] = '1';
			}
			else
			{
				ans[i] = next;
			}
		}
		else if (B[i])
		{
			next = B[i] + carry[i] - '0';

			if (next >= DIGIT + '0')
			{
				ans[i] = next - DIGIT;
				carry[i + 1] = '1';
			}
			else
			{
				ans[i] = next;
			}
		}

		i++;
	}

	if (carry[i] == '0')
	{
		i--;
	}
	else
	{
		ans[i] = carry[i];
	}

	for (register int j = i; j >= 0; j--)
	{
		printf("%c", ans[j]);
	}

	printf("\n");

	return 0;
}
