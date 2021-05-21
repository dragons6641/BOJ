#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 10
#define MAX_M 8
#define ALPHABETS 26
#define START_LEVEL 0

int N;
// 최댓값을 가져야 하므로 최솟값으로 초기화
int ans = 0;
// 사용된 알파벳 수
int cnt = 0;
// 알파벳 -> 숫자로 변환 방법 저장
int convertList[ALPHABETS] = { 0, };
// 사용한 알파벳 표시
bool isUsed[ALPHABETS] = { 0, };
// 백트래킹에 사용
bool visit[ALPHABETS] = { 0, };
char inputMap[MAX_N][MAX_M + 2] = { 0, };

void inputData(void)
{
	scanf("%d", &N);

	for (register int r = 0; r < N; r++)
	{
		scanf("%s", inputMap[r]);

		register int c = 0;

		while (inputMap[r][c])
		{
			if (isUsed[inputMap[r][c] - 'A'] == false)
			{
				isUsed[inputMap[r][c] - 'A'] = true;
				cnt++;
			}
			
			c++;
		}
	}

	return;
}

void init(void)
{
	for (register int i = 0; i < ALPHABETS; i++)
	{
		convertList[i] = -1;
	}

	return;
}

int convertToNum(int r)
{
	int result = 0;
	register int c = 0;

	while (inputMap[r][c])
	{
		result = (result * MAX_N) + convertList[inputMap[r][c] - 'A'];

		c++;
	}

	return result;
}

int calcAns(void)
{
	int result = convertToNum(0);

	for (register int i = 1; i < N; i++)
	{
		int ret = convertToNum(i);

		result += ret;
	}

	return result;
}

void dfs(int level)
{
	if (level == cnt)
	{
		// int debug = 1;

		int ret = calcAns();

		if (ans < ret)
		{
			ans = ret;
		}

		return;
	}

	for (register int i = 0; i < ALPHABETS; i++)
	{
		if ((isUsed[i]) && (!visit[i]))
		{
			visit[i] = true;
			convertList[i] = MAX_N - level - 1;

			dfs(level + 1);

			visit[i] = false;
			convertList[i] = -1;
		}
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);	// 1998
	// freopen("input2.txt", "r", stdin);	// 99437
	// freopen("input3.txt", "r", stdin);	// 45
	// freopen("input4.txt", "r", stdin);	// 187
	// freopen("input5.txt", "r", stdin);	// 98765432
	// freopen("input6.txt", "r", stdin);	// 495
	// freopen("input7.txt", "r", stdin);	// 9
	// freopen("input8.txt", "r", stdin);	// 999999990
	// freopen("input9.txt", "r", stdin);	// 1857

	inputData();

	init();

	dfs(START_LEVEL);

	printf("%d\n", ans);

	return 0;
}
