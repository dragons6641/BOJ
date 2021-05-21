/*
1152 단어의 개수
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_LENGTH 1000000

int main(void)
{
	int ans = 0;
	char inputStr[MAX_LENGTH + 1] = { 0, };

	while (scanf("%s", &inputStr) != EOF)
	{
		ans++;
	}

	printf("%d\n", ans);

	return 0;
}
