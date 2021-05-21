/*
A9 자리올림 횟수 찾기
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_LENGTH 10
#define MAX_DIGIT 9

void swap(char* a, char* b)
{
	char temp[MAX_LENGTH + 1] = { 0, };

	*temp = *a;
	*a = *b;
	*b = *temp;

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);
	// freopen("input3.txt", "r", stdin);
	// freopen("input4.txt", "r", stdin);

	setbuf(stdout, NULL);

	while (true)
	{
		int ans = 0;
		int lenA = 0;
		int lenB = 0;
		int maxLen = 0;
		char a[MAX_LENGTH + 1] = { 0, };
		char b[MAX_LENGTH + 1] = { 0, };
		char c[MAX_LENGTH + 1] = { 0, };

		scanf("%s %s", &a, &b);

		if ((a[0] == '0') && (b[0] == '0'))
		{
			break;
		}

		// 문자열 길이 찾기
		for (int i = MAX_LENGTH; i >= 0; i--)
		{
			// a가 끝
			if (a[i] == '\0')
			{
				lenA = i;
			}
			// b가 끝
			if (b[i] == '\0')
			{
				lenB = i;
			}
			// 다 찾았으면
			if ((a[i] > 0) && (b[i] > 0))
			{
				break;
			}
		}

		// 문자열 정리하기
		for (int i = 0; i < lenA; i++)
		{
			a[MAX_LENGTH - i] = a[lenA - i - 1];
		}

		for (int i = 0; i < lenB; i++)
		{
			b[MAX_LENGTH - i] = b[lenB - i - 1];
		}

		/*
		swap(a, b);

		int debug = 1;

		// 앞에 숫자가 더 자릿수 커야함
		if (lenA < lenB)
		{
			swap(a, b);
		}
		*/

		// 계산 횟수
		if (lenA > lenB)
		{
			maxLen = lenA;
		}
		else
		{
			maxLen = lenB;
		}

		for (int i = MAX_LENGTH; i > MAX_LENGTH - maxLen; i--)
		{
			// int debug = 1;

			int aa = 0;
			int bb = 0;
			int cc = 0;

			if (a[i] != 0)
			{
				aa = a[i] - '0';
			}

			if (b[i] != 0)
			{
				bb = b[i] - '0';
			}

			if (c[i] != 0)
			{
				cc = c[i] - '0';
			}

			if (aa + bb + cc > MAX_DIGIT)
			{
				c[i - 1] = '1';
				ans++;
			}

			// int debug = 1;
		}

		/*
		if (ans == 0)
		{
			printf("No carry operation.\n");
		}
		else if (ans == 1)
		{
			printf("1 carry operation.\n");
		}
		else
		{
			printf("%d carry operations.\n", ans);
		}
		*/

		printf("%d\n", ans);
	}

	return 0;
}
