/*
1032 명령 프롬프트
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_R 50
#define MAX_C 50

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	int N;
	// bool check[MAX_C + 1] = { false, };
	char map[MAX_R + 1][MAX_C + 1] = { {'\0'}, };

	scanf("%d", &N);

	for (register int r = 1; r <= N; r++)
	{
		scanf("%s", &map[r]);
	}

	register int c = 0;

	while (map[1][c] != '\0')
	{
		map[0][c] = map[1][c];

		for (register int r = 1; r <= N; r++)
		{
			if (map[r][c] != map[1][c])
			{
				// check[c] = true;
				map[0][c] = '?';

				break;
			}
		}

		c++;
	}

	/*
	for (register int i = 0; i <= c; i++)
	{
		if (check[i])
		{
			printf("?");
		}
		else
		{
			printf("%c", map[1][i]);
		}
	}

	printf("\0\n");
	*/

	printf("%s\n", map[0]);

	return 0;
}
