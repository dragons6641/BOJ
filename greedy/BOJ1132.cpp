#define _CRT_SECURE_NO_WARNINGS
#define ll long long

#include <stdio.h>

#define MAX_N 50
#define MAX_M 12
#define ALPHABETS 10
#define START_LEVEL 0

int N;
// 최댓값을 가져야 하므로 최솟값으로 초기화
ll ans = 0;
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

ll convertToNum(int r)
{
	ll result = 0;
	register int c = 0;

	while (inputMap[r][c])
	{
		int k = convertList[inputMap[r][c] - 'A'];

		if ((c == 0) && (k == 0))
		{
			result = -1;

			break;
		}

		result = (ll)((result * ALPHABETS) + k);

		c++;
	}

	return result;
}

ll calcAns(void)
{
	ll result = convertToNum(0);

	if (result != -1)
	{
		for (register int i = 1; i < N; i++)
		{
			ll ret = convertToNum(i);

			if (ret == -1)
			{
				result = -1;

				break;
			}

			result += ret;
		}
	}

	return result;
}

void dfs(int level)
{
	if (level == cnt)
	{
		// int debug = 1;

		ll ret = calcAns();

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
			convertList[i] = ALPHABETS - level - 1;

			dfs(level + 1);

			visit[i] = false;
			convertList[i] = -1;
		}
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);	// 1875
	// freopen("input2.txt", "r", stdin);	// 9876540327
	// freopen("input3.txt", "r", stdin);	// 1840761650839
	// freopen("input4.txt", "r", stdin);	// 9876543210
	// freopen("input5.txt", "r", stdin);	// 2922
	// freopen("input6.txt", "r", stdin);	// 1044
	// freopen("input7.txt", "r", stdin);	// 2684

	inputData();

	init();

	dfs(START_LEVEL);

	printf("%lld\n", ans);

	return 0;
}
