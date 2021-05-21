#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_T 100
#define MAX_R 100
#define MAX_C 100
#define MAX_QUEUE ((MAX_R + 2) * (MAX_C + 2))
#define MAX_DIR 4
#define START_R 0
#define START_C 0
#define ALPHABETS 26

struct Node
{
	int r;
	int c;
};

// 테스트 케이스의 갯수
int T;
// rows
int H;
// cols
int W;
// 상근이가 훔칠 수 있는 문서의 최대 개수
int ans;
int directR[MAX_DIR] = { -1, 1, 0, 0 };
int directC[MAX_DIR] = { 0, 0, -1, 1 };
int headList[ALPHABETS] = { 0, };
int tailList[ALPHABETS] = { 0, };
// 가지고 있는 열쇠의 종류 표시
bool isPossible[ALPHABETS] = { 0, };
char keyList[ALPHABETS] = { 0, };
// Barrier!
// 0부터 N + 1까지 사용
char map[MAX_R + 2][MAX_C + 2] = { 0, };
// Barrier!
// 0부터 N + 1까지 사용
bool visit[MAX_R + 2][MAX_C + 2] = { 0, };
Node queue[MAX_QUEUE] = { { 0, 0 }, };
// 아직은 열쇠가 없지만, 열쇠를 찾으면 열 수 있는 문들의 위치 저장
Node doorQueue[ALPHABETS][MAX_QUEUE] = { {0, 0}, };

void init(void)
{
	// 최댓값을 가져야 하므로 최솟값으로 초기화
	ans = 0;

	// map, visit 초기화
	for (register int r = 0; r <= H + 1; r++)
	{
		map[r][0] = '.';
		map[r][W + 1] = '.';

		for (register int c = 0; c <= W + 1; c++)
		{
			if ((r == 0) || (r == H + 1))
			{
				map[r][c] = '.';
			}

			visit[r][c] = false;
		}
	}

	for (register int i = 0; i < ALPHABETS; i++)
	{
		isPossible[i] = false;
		headList[i] = 0;
		tailList[i] = 0;
	}

	for (register int i = 0; keyList[i]; i++)
	{
		if (keyList[i] == '0')
		{
			break;
		}

		isPossible[keyList[i] - 'a'] = true;
	}

	return;
}

int bfs(void)
{
	int cnt = 0;
	register int head = 0;
	register int tail = 0;

	visit[START_R][START_C] = true;
	queue[tail++] = { START_R, START_C };

	while (head != tail)
	{
		Node now = queue[head++];

		if (head == MAX_QUEUE)
		{
			head = 0;
		}

		// 4방향 탐색
		for (register int d = 0; d < MAX_DIR; d++)
		{
			int dr = now.r + directR[d];
			int dc = now.c + directC[d];
			int idx;

			if ((dr < 0) || (dc < 0) || (dr > H + 1) || (dc > W + 1))
			{
				continue;
			}

			// 벽일 경우
			if (map[dr][dc] == '*')
			{
				continue;
			}

			// 이미 방문했을 경우
			if (visit[dr][dc])
			{
				continue;
			}

			visit[dr][dc] = true;

			// 문서를 발견했을 경우
			if (map[dr][dc] == '$')
			{
				// 발견한 문서 갯수 추가
				cnt++;

				// 중복 발견 방지
				map[dr][dc] = '.';
			}
			// 문을 발견했을 경우
			else if ((map[dr][dc] >= 'A') && (map[dr][dc] <= 'Z'))
			{
				idx = map[dr][dc] - 'A';

				// 열 수 없는 문일 경우
				if (!isPossible[idx])
				{
					// 열 수 없는 문으로 일단 추가
					doorQueue[idx][tailList[idx]++] = { dr, dc };

					if (tailList[idx] == MAX_QUEUE)
					{
						tailList[idx] = 0;
					}

					// 아직은 큐에 넣으면 안된다
					continue;
				}
			}
			// 열쇠롤 발견했을 경우
			else if ((map[dr][dc] >= 'a') && (map[dr][dc] <= 'z'))
			{
				idx = map[dr][dc] - 'a';

				// 열쇠 목록에 추가
				isPossible[idx] = true;

				// 중복 발견 방지
				map[dr][dc] = '.';

				// 열 수 있는 문들 추가
				while (headList[idx] != tailList[idx])
				{
					queue[tail] = doorQueue[idx][headList[idx]];

					tail++;
					headList[idx]++;

					if (tail == MAX_QUEUE)
					{
						tail = 0;
					}

					if (headList[idx] == MAX_QUEUE)
					{
						headList[idx] = 0;
					}
				}
			}
			
			// 빈 공간일 경우, 열 수 있는 문일 경우 기본 처리
			queue[tail++] = { dr, dc };

			if (tail == MAX_QUEUE)
			{
				tail = 0;
			}
		}
	}

	return cnt;
}

void solve(void)
{
	scanf("%d", &T);

	for (register int testCase = 1; testCase <= T; testCase++)
	{
		scanf("%d %d", &H, &W);

		for (register int r = 1; r <= H; r++)
		{
			for (register int c = 1; c <= W; c++)
			{
				scanf(" %c", &map[r][c]);
			}
		}

		scanf("%s", &keyList);

		init();

		int ans = bfs();

		printf("%d\n", ans);
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	solve();

	return 0;
}
