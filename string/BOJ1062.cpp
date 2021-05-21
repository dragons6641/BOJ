#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 50
#define MAX_K 26
#define MAX_M 15
#define START_LEVEL 5
#define START_LEN 4
#define END_LEN 4

// 읽어야 하는 단어의 갯수
int N;
// 가르칠 수 있는 글자의 갯수
int K;
// 최댓값을 가져야 하므로 최솟값으로 초기화
int ans = 0;
// 배운 글자 목록
// int learnList[MAX_K] = { 0, };
// 입력의 길이 목록
int lenList[MAX_N] = { 0, };
// 입력 그대로
char inputMap[MAX_N][MAX_M + 1] = { 0, };
// 백트래킹에 사용
bool visit[MAX_K] = { 0, };
// 전체 입력에 대해 글자가 포함되어 있는지 여부 확인
bool isUsedList[MAX_K] = { 0, };
// 각 입력에 대해 글자가 포함되어 있는지 여부 확인
bool isUsedMap[MAX_N][MAX_K] = { 0, };

int strlen(const char *c)
{
	register int i;

	for (i = 0; c[i]; i++);

	return i;
}

void inputData(void)
{
	scanf("%d %d", &N, &K);

	for (register int r = 0; r < N; r++)
	{
		scanf("%s", &inputMap[r]);

		lenList[r] = strlen(inputMap[r]);

		register int c = 0;

		while (inputMap[r][c])
		{
			isUsedList[inputMap[r][c] - 'a'] = true;
			isUsedMap[r][inputMap[r][c] - 'a'] = true;
			c++;
		}
	}

	return;
}

// 기본적으로 쓰이는 접두어, 접미어 표시
// 이 글자들은 반드시 배우는 글자 목록에 가장 먼저 포함되어야 한다!
void init(void)
{
	/*
	for (register int i = START_LEVEL; i < MAX_K; i++)
	{
		learnList[i] = -1;
	}

	learnList[0] = 'a' - 'a';
	learnList[1] = 'c' - 'a';
	learnList[2] = 'i' - 'a';
	learnList[3] = 'n' - 'a';
	learnList[4] = 't' - 'a';
	*/

	visit['a' - 'a'] = true;
	visit['c' - 'a'] = true;
	visit['i' - 'a'] = true;
	visit['n' - 'a'] = true;
	visit['t' - 'a'] = true;

	return;
}

int checkRead(void)
{
	int cnt = 0;

	for (register int r = 0; r < N; r++)
	{
		// 가지치기
		// 이미 정답이 될 수 없다면 하지 말자!
		if ((cnt + N - r) <= ans)
		{
			break;
		}

		bool isReadable = true;

		/*
		register int c = 0;

		while (inputMap[r][c])
		{
			if (!visit[inputMap[r][c] - 'a'])
			{
				isReadable = false;

				break;
			}

			c++;
		}
		*/

		// 추가로 읽어야 할 글자가 하나라도 있는 경우
		if (lenList[r] > START_LEN + END_LEN)
		{
			for (register int c = START_LEN; c < lenList[r] - END_LEN; c++)
			{
				if (!visit[inputMap[r][c] - 'a'])
				{
					isReadable = false;

					break;
				}
			}
		}

		if (isReadable)
		{
			cnt++;
		}
	}

	return cnt;
}

void dfs(int start, int level)
{
	if (level >= K)
	{
		int ret = checkRead();

		if (ans < ret)
		{
			ans = ret;
		}

		return;
	}

	bool isLearned = false;

	for (register int i = start; i < MAX_K; i++)
	{
		if ((isUsedList[i]) && (!visit[i]))
		{
			visit[i] = true;
			// learnList[level] = i;

			isLearned = true;

			dfs(i + 1, level + 1);

			visit[i] = false;
			// learnList[level] = -1;
		}
	}

	if (!isLearned)
	{
		dfs(start, level + 1);
	}

	return;
}

void solve(void)
{
	if (K == MAX_K)
	{
		ans = N;
	}
	else if (K < START_LEVEL)
	{
		ans = 0;
	}
	else
	{
		dfs(0, START_LEVEL);
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);	// 2
	// freopen("input2.txt", "r", stdin);	// 25
	// freopen("input3.txt", "r", stdin);	// 0
	// freopen("input4.txt", "r", stdin);	// 5
	// freopen("input5.txt", "r", stdin);	// 0
	// freopen("input6.txt", "r", stdin);	// 4
	// freopen("input7.txt", "r", stdin);	// 1
	// freopen("input8.txt", "r", stdin);	// 1
	// freopen("input9.txt", "r", stdin);	// 1
	// freopen("input10.txt", "r", stdin);	// 3
	// freopen("input11.txt", "r", stdin);	// 2
	// freopen("input12.txt", "r", stdin);	// 1
	// freopen("input13.txt", "r", stdin);	// 1
	// freopen("input14.txt", "r", stdin);	// 4
	// freopen("input15.txt", "r", stdin);	// 1
	// freopen("input16.txt", "r", stdin);	// 3
	// freopen("input17.txt", "r", stdin);	// 1
	// freopen("input18.txt", "r", stdin);	// 2
	// freopen("input19.txt", "r", stdin);	// 1
	// freopen("input20.txt", "r", stdin);	// 0

	inputData();

	init();

	solve();

	printf("%d\n", ans);

	return 0;
}
