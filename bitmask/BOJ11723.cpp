/*
11723 집합
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_LENGTH 10
#define MAX_N 20
#define MAX_M 3000000

int bitMask = 0;
int outputCnt = 0;
bool outputList[MAX_M] = { 0, };
// 1부터 시작
bool S[MAX_N + 1] = {0,};

int strcmp(const char* a, const char* b)
{
	int index = 0;

	while (true)
	{
		if (a[index] < b[index])
		{
			return -1;
		}
		else if (a[index] > b[index])
		{
			return 1;
		}
		
		if ((a[index] == '\0') && (b[index] == '\0'))
		{
			break;
		}

		index++;
	}

	return 0;
}

void addS(int x)
{
	// S[x] = true;

	bitMask |= (1 << (x - 1));

	return;
}

void removeS(int x)
{
	// S[x] = false;

	bitMask &= (~(1 << (x - 1)));

	return;
}

int checkS(int x)
{
	/*
	if (S[x])
	{
		return 1;
	}
	else
	{
		return 0;
	}
	*/

	/*
	if (bitMask & (1 << (x - 1)))
	{
		return 1;
	}
	else
	{
		return 0;
	}
	*/

	return (((bitMask & (1 << (x - 1))) == 0) ? 0 : 1);
}

void toggleS(int x)
{
	/*
	if (S[x])
	{
		S[x] = false;
	}
	else
	{
		S[x] = true;
	}
	*/

	// S[x] = (!S[x]);

	/*
	if (checkS(x))
	{
		removeS(x);
	}
	else
	{
		addS(x);
	}
	*/

	bitMask ^= (1 << (x - 1));

	return;
}

void allS(void)
{
	/*
	for (int i = 1; i <= MAX_N; i++)
	{
		S[i] = true;
	}
	*/

	// bitMask = (~(0 << (MAX_N - 1)));

	bitMask = (1 << MAX_N) - 1;

	return;
}

void emptyS(void)
{
	/*
	for (int i = 1; i <= MAX_N; i++)
	{
		S[i] = false;
	}
	*/

	// bitMask = (0 << (MAX_N - 1));

	bitMask = 0;

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);
	// freopen("input3.txt", "r", stdin);
	// freopen("input4.txt", "r", stdin);
	// freopen("input5.txt", "r", stdin);

	// setbuf(stdout, NULL);

	int M;
	int N;
	int ans;
	char cmd[MAX_LENGTH + 1] = { 0, };

	scanf("%d", &M);

	for (int i = 0; i < M; i++)
	{
		scanf("%s", &cmd);

		// add N
		if (!strcmp(cmd, "add"))
		{
			scanf("%d", &N);

			addS(N);
		}
		// remove N
		else if (!strcmp(cmd, "remove"))
		{
			scanf("%d", &N);

			removeS(N);
		}
		// check N
		else if (!strcmp(cmd, "check"))
		{
			scanf("%d", &N);

			ans = checkS(N);

			// printf("%d\n", ans);

			outputList[outputCnt] = ans;
			outputCnt++;
		}
		// toggle N
		else if (!strcmp(cmd, "toggle"))
		{
			scanf("%d", &N);

			toggleS(N);
		}
		// all
		else if (!strcmp(cmd, "all"))
		{
			allS();
		}
		// empty
		else if (!strcmp(cmd, "empty"))
		{
			emptyS();
		}

		int debug = 1;
	}

	for (int i = 0; i < outputCnt; i++)
	{
		// printf("%d\n", outputList[i]);

		if (outputList[i])
		{
			printf("1\n");
		}
		else
		{
			printf("0\n");
		}
	}

	return 0;
}
