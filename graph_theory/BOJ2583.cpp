/*
Pro입문 4주차 Problem F 영역 구하기
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

// R == M
#define MAX_R 100
// C == N
#define MAX_C 100
// 사각형 갯수
#define MAX_K 100
// 방향 갯수
#define MAX_DIR 4

int M;
int N;
int K;
// 영역 수
int ans = 0;
// 각 영역 넓이, 초기화 필수
int cnt = 0;
// 입력
int map[MAX_R][MAX_C] = { 0, };
// 방문 표시
// int visit[MAX_R][MAX_C] = { 0, };
// 방향배열
int directR[MAX_DIR] = { -1, 1, 0, 0 };
int directC[MAX_DIR] = { 0, 0, -1, 1};
// 정답 출력용
int dat[MAX_R * MAX_C] = { 0, };

void input(void)
{
	scanf("%d %d %d", &M, &N, &K);

	int r1;
	int r2;
	int c1;
	int c2;

	for (int i = 0; i < K; i++)
	{
		scanf("%d %d %d %d", &c1, &r1, &c2, &r2);

		for (int r = r1; r < r2; r++)
		{
			for (int c = c1; c < c2; c++)
			{
				map[r][c] = -1;
			}
		}
	}

	return;
}

void print(void)
{
	printf("%d\n", ans);

	for (int i = 1; i < (MAX_R * MAX_C); i++)
	{
		if (dat[i] > 0)
		{
			for (int j = 0; j < dat[i]; j++)
			{
				printf("%d ", i);
			}
		}
	}

	printf("\n");

	return;
}

void dfs(int nowR, int nowC)
{
	for (int d = 0; d < MAX_DIR; d++)
	{
		int dr = nowR + directR[d];
		int dc = nowC + directC[d];

		// 불가능한 조건 가지치기
		if ((dr < 0) || (dc < 0) || (dr >= M) || (dc >= N))
		{
			continue;
		}
		else if ((map[dr][dc] != 0))
		{
			continue;
		}

		// 가능한 경우 추가 탐색
		cnt++;
		map[dr][dc] = ans;

		dfs(dr, dc);
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	setbuf(stdout, NULL);

	input();

	for (int r = 0; r < M; r++)
	{
		for (int c = 0; c < N; c++)
		{
			/*
			if ((r == 4) && (c == 0))
			{
				int debug = 1;
			}
			*/

			if ((map[r][c] == 0))
			{
				ans++;
				cnt = 1;
				map[r][c] = ans;

				dfs(r, c);

				dat[cnt]++;
				
				// int debug = 1;
			}
		}
	}

	// int debug = 1;

	print();

	return 0;
}
