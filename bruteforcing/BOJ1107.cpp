#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 500000
#define MAX_M 10
#define MAX_LEVEL 6
#define INF (MAX_N * 2)
#define START_N 100
#define START_CHANNEL 0
#define START_LEVEL 0

// 이동하려고 하는 채널
int N;
// 고장난 버튼의 갯수
int M;
// 최소 횟수이므로 최댓값으로 초기화
// 초기화는 입력 받고 해준다!
int ans;
// 정상인지 표시
bool isAvailable[MAX_M] = { 0, };

void initIsAvailable(void)
{
	for (register int i = 0; i < MAX_M; i++)
	{
		isAvailable[i] = true;
	}

	return;
}

void initAns(void)
{
	if (N > START_N)
	{
		ans = N - START_N;
	}
	else
	{
		ans = START_N - N;
	}

	return;
}

void inputData(void)
{
	int K;

	scanf("%d", &N);
	scanf("%d", &M);

	for (register int i = 0; i < M; i++)
	{
		scanf("%d", &K);

		isAvailable[K] = false;
	}

	return;
}

// 중복순열
void dfs(int channel, int level)
{
	// 가지치기
	// 100번 채널에서 번호 사용하지 않고 이동한 경우보다 더 이동할 수 없다!
	if (level >= ans)
	{
		return;
	}

	if (level > 0)
	{
		int result = level;

		if (channel > N)
		{
			result += (channel - N);
		}
		else
		{
			result += (N - channel);
		}

		if (ans > result)
		{
			ans = result;
		}
	}

	if (level == MAX_LEVEL)
	{
		return;
	}

	for (register int i = 0; i < MAX_M; i++)
	{
		if (isAvailable[i])
		{
			dfs((channel * MAX_M) + i, level + 1);
		}
	}

	return;
}

void solve(void)
{
	if (M != MAX_M)
	{
		dfs(START_CHANNEL, START_LEVEL);
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);	// 6
	// freopen("input2.txt", "r", stdin);	// 0
	// freopen("input3.txt", "r", stdin);	// 11117
	// freopen("input4.txt", "r", stdin);	// 670
	// freopen("input5.txt", "r", stdin);	// 1
	// freopen("input6.txt", "r", stdin);	// 62
	// freopen("input7.txt", "r", stdin);	// 11
	// freopen("input8.txt", "r", stdin);	// 99
	// freopen("input9.txt", "r", stdin);	// 2
	// freopen("input10.txt", "r", stdin);	// 1
	// freopen("input11.txt", "r", stdin);	// 1
	// freopen("input12.txt", "r", stdin);	// 6
	// freopen("input13.txt", "r", stdin);	// 99
	// freopen("input14.txt", "r", stdin);	// 1011
	// freopen("input15.txt", "r", stdin);	// 5
	// freopen("input16.txt", "r", stdin);	// 2
	// freopen("input17.txt", "r", stdin);	// 100
	// freopen("input18.txt", "r", stdin);	// 4
	// freopen("input19.txt", "r", stdin);	// 4

	initIsAvailable();

	inputData();

	initAns();

	solve();

	printf("%d\n", ans);

	return 0;
}
