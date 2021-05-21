/*
Problem F 세친구
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

const int LM = (int)2e6 + 10;
int N;
int L;
int ans;
char str[LM];
char* ret;

int strcmp(const char* s, const char* t)
{
	while ((*s) && (*s == *t))
	{
		++s;
		++t;
	}

	return (*s - *t);
}

void check(char* s, char* t)
{
	if ((N % 2) == 0)
	{
		return;
	}

	register int i = 0;
	register int j = 0;
	int diff = 0;

	while (i < L)
	{
		if (s[i] != t[j])
		{
			if (diff > 0)
			{
				return;
			}

			diff++;
			j++;
		}
		else
		{
			i++;
			j++;
		}
	}

	ret = s;
	ans++;

	return;
}

void solve(void)
{
	L = N / 2;

	check(str, str + L);
	check(str + L + 1, str);

	str[L] = 0;

	return;
}

void outputAns(void)
{
	if (ans == 0)
	{
		puts("NOT POSSIBLE");
	}
	else if (ans == 1)
	{
		puts(ret);
	}
	else
	{
		if (strcmp(str, str + L + 1))
		{
			puts("NOT UNIQUE");
		}
		else
		{
			puts(ret);
		}
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);
	// freopen("input3.txt", "r", stdin);

	scanf("%d %s", &N, str);

	solve();

	outputAns();

	return 0;
}
