/*
17471 게리맨더링
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 10
#define MAX_M 100
#define MAX_QUEUE (MAX_N * MAX_N)
#define START_LEVEL 0
#define MAX_DIVIDE 2
#define MAX_INT 21e8

int N;
// 최솟값을 가져야 함, 초기화는 최대값으로
int ans = MAX_INT;
// 1부터 사용
// 각 선거구별 도시 갯수
int cntList[MAX_DIVIDE + 1] = { 0, };
// 1부터 사용
// 두 선거구로 나눈 결과
int divide[MAX_N + 1] = { 0, };
// 1부터 사용
// 선거구끼리 연결되어 있는지 확인
int visit[MAX_N + 1] = { 0, };
// 1부터 사용
// 각 도시의 인구수
int populationList[MAX_N + 1] = { 0, };
// 1부터 사용
// 입력을 인접 리스트로
int adjList[MAX_N + 1][MAX_N + 1] = { 0, };

void input(void)
{
	scanf("%d", &N);

	cntList[0] = N;

	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &populationList[i]);
	}

	for (int r = 1; r <= N; r++)
	{
		scanf("%d", &adjList[r][0]);

		for (int c = 1; c <= adjList[r][0]; c++)
		{
			scanf("%d", &adjList[r][c]);
		}
	}

	return;
}

int calc(void)
{
	int diff = 0;

	for (int i = 1; i <= N; i++)
	{
		if (divide[i] == 1)
		{
			diff += populationList[i];
		}
		else if (divide[i] == 2)
		{
			diff -= populationList[i];
		}
	}

	if (diff < 0)
	{
		diff = (-diff);
	}
	
	return diff;
}

// k번 선거구에 대한 bfs
// k = 1, 2 
int bfs(int k)
{
	int start = 0;
	int cnt = 1;
	int result = -1;
	int head = 0;
	int tail = 1;

	// 시작점 찾기
	for (int i = 1; i <= N; i++)
	{
		if (divide[i] == k)
		{
			start = i;

			break;
		}
	}

	int queue[MAX_QUEUE] = {start, };

	visit[start] = k;

	// 시작점부터 탐색
	while (head != tail)
	{
		int now = queue[head++];

		for (int c = 1; c <= adjList[now][0]; c++)
		{
			int next = adjList[now][c];

			if ((visit[next] == 0) && (divide[next] == k))
			{
				visit[next] = k;
				cnt++;
				queue[tail++] = next;
			}
		}
	}

	// 가능한 경우
	if (cnt == cntList[k])
	{
		// 해당 선거구 도시 수를 리턴
		result = cnt;
	}

	return result;
}

void init(void)
{
	for (int i = 1; i <= N; i++)
	{
		visit[i] = 0;
	}

	return;
}

void run(int level)
{
	int ret;

	if (level == N)
	{
		int debug = 1;

		for (int i = 1; i <= MAX_DIVIDE; i++)
		{
			if (cntList[i] == 0)
			{
				return;
			}
		}

		for (int i = 1; i <= MAX_DIVIDE; i++)
		{
			ret = bfs(i);

			init();

			// 불가능한 경우
			if (ret == -1)
			{
				return;
			}
		}

		// 선거구 차이 계산
		ret = calc();

		// 정답 갱신
		if (ans > ret)
		{
			ans = ret;
		}

		return;
	}

	for (int i = 1; i <= MAX_DIVIDE; i++)
	{
		divide[level + 1] = i;
		cntList[i]++;

		run(level + 1);

		cntList[i]--;
	}

	// 초기화
	// divide[i] = 0;

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);
	// freopen("input3.txt", "r", stdin);
	// freopen("input4.txt", "r", stdin);

	setbuf(stdout, NULL);

	input();

	run(START_LEVEL);

	if (ans == MAX_INT)
	{
		ans = -1;
	}

	printf("%d\n", ans);

	return 0;
}
