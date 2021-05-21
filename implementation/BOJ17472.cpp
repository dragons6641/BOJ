/*
17472 다리 만들기
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_R 10
#define MAX_C 10
#define MAX_QUEUE (MAX_R * MAX_C)
#define MAX_ISLAND 6
#define MAX_INT 21e8
#define MAX_DIR 4
#define MAX_COMBINATION ((MAX_ISLAND / 2) * (MAX_ISLAND - 1))
#define MIN_LENGTH 2
#define START_LEVEL 1
#define START_ISLAND 1
#define MAX_LEVEL 2
#define START_LENGTH 0

struct Node
{
	int r;
	int c;
	// 각 섬간의 거리
	int dist;
};

int N;
int M;
// 전체 섬의 개수
int islandCnt = 0;
// 연결된 섬의 개수
int connectCnt = 0;
// 만들 수 있는 다리 개수
int combinationCnt = 0;
int ans = MAX_INT;
// 각 섬의 연결 상태 표시
// 1부터 시작
// int connect[MAX_ISLAND + 1] = { 0, };
int connect[MAX_ISLAND + 1][MAX_ISLAND + 1] = { 0, };
// 입력
int map[MAX_R][MAX_C] = { 0, };
// 섬 번호 표시, 방문 표시
int visit[MAX_R][MAX_C] = { 0, };
// 방향배열
int directR[MAX_DIR] = { -1, 1, 0, 0 };
int directC[MAX_DIR] = { 0, 0, -1, 1 };
// 조합들
Node combination[MAX_COMBINATION] = { {0, 0, 0}, };

void input(void)
{
	scanf("%d %d", &N, &M);

	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < M; c++)
		{
			scanf("%d", &map[r][c]);
		}
	}

	return;
}

void bfs(int nowR, int nowC)
{
	int head = 0;
	int tail = 1;
	// bfs
	Node queue[MAX_QUEUE] = { {nowR, nowC, 0} };

	visit[nowR][nowC] = islandCnt;

	while (head != tail)
	{
		Node now = queue[head++];

		for (int d = 0; d < MAX_DIR; d++)
		{
			int dr = now.r + directR[d];
			int dc = now.c + directC[d];

			// 밖으로 가면 안돼!
			if ((dr < 0) || (dc < 0) || (dr >= N) || (dc >= M))
			{
				continue;
			}

			// 바다이거나 아직 방문한 곳도 안돼!
			if ((map[dr][dc] == 0) || (visit[dr][dc] != 0))
			{
				continue;
			}

			visit[dr][dc] = islandCnt;

			queue[tail++] = { dr, dc, 0 };
		}
	}

	return;
}

int check_ans()
{
	int head = 0;
	int tail = 1;
	int checkList[MAX_ISLAND + 1] = { 0, };

	// bfs
	int queue[MAX_QUEUE] = { 1, };

	checkList[1] = 1;

	while (head != tail)
	{
		int now = queue[head++];

		for (int d = 1; d <= islandCnt; d++)
		{
			// 연결 안 되어 있으면 안돼!
			if (connect[now][d] == 0)
			{
				continue;
			}

			// 이미 방문한 곳은 안돼!
			if (checkList[d] > 0)
			{
				continue;
			}

			checkList[d] = now;

			queue[tail++] = d;
		}
	}

	for (int i = 1; i <= islandCnt; i++)
	{
		if (checkList[i] == 0)
		{
			return -1;
		}
	}

	return 0;
}

void run(int nowR, int nowC, int level, int length)
{
	// 다리 다 놓았으면
	if (level == islandCnt)
	{
		/*
		if (length == 8)
		{
			int debug = 1;
		}
		*/

		/*
		if (visit[1][4] == 0)
		{
			int debug = 1;
		}
		*/

		/*
		for (int i = 1; i <= islandCnt; i++)
		{
			if (connect[i] == 0)
			{
				return;
			}
		}
		*/

		int ret = check_ans();

		if (ret == -1)
		{
			return;
		}

		// 정답 갱신
		if (ans > length)
		{
			ans = length;
		}

		return;
	}

	if ((nowR == -1) && (nowC == -1))
	{
		return;
	}

	int nextR = -1;
	int nextC = -1;
	int flag = 0;
	int cnt = 0;

	/*
	nowR = 3;
	nowC = 1;
	*/

	// 다음 타겟 찾기
	for (int r = nowR; r < N; r++)
	{
		if (r == nowR)
		{
			for (int c = nowC + 1; c < M; c++)
			{
				if (visit[r][c] > 0)
				{
					nextR = r;
					nextC = c;
					flag = 1;

					break;
				}
			}
		}
		else
		{
			for (int c = 0; c < M; c++)
			{
				if (visit[r][c] > 0)
				{
					nextR = r;
					nextC = c;
					flag = 1;

					break;
				}
			}
		}

		if (flag == 1)
		{
			break;
		}
	}

	flag = 1;

	// 현재 기준으로 4방향 탐색
	// 1. 위쪽
	for (int r = nowR - 1; r >= 0; r--)
	{
		if (visit[r][nowC] == 0)
		{
			flag = 0;
		}
		// 다른 섬을 찾으면
		else if (visit[r][nowC] > 0)
		{
			// 자신의 섬이면 중단
			if (visit[r][nowC] == visit[nowR][nowC])
			{
				break;
			}

			// 이미 연결되어 있다면 중단
			if (connect[visit[nowR][nowC]][visit[r][nowC]] == 1)
			{
				break;
			}

			// 이미 놓았던 곳이면 중단
			if (flag == 1)
			{
				break;
			}

			// 다리 길이는 최소 2 이상
			if (nowR - r <= MIN_LENGTH)
			{
				break;
			}

			// 다리 놓기
			for (int k = nowR - 1; k > r; k--)
			{
				visit[k][nowC]--;
				cnt++;
			}

			connect[visit[nowR][nowC]][visit[r][nowC]] = 1;
			connect[visit[r][nowC]][visit[nowR][nowC]] = 1;
			connectCnt++;

			// 완전탐색
			run(nextR, nextC, level + 1, length + cnt);

			// 원상복구
			for (int k = nowR - 1; k > r; k--)
			{
				visit[k][nowC]++;
				cnt--;
			}

			connect[visit[nowR][nowC]][visit[r][nowC]] = 0;
			connect[visit[r][nowC]][visit[nowR][nowC]] = 0;
			connectCnt--;

			break;
		}
	}

	flag = 1;

	// 2. 아래쪽
	for (int r = nowR + 1; r < N; r++)
	{
		if (visit[r][nowC] == 0)
		{
			flag = 0;
		}
		// 다른 섬을 찾으면
		else if (visit[r][nowC] > 0)
		{
			// 자신의 섬이면 중단
			if (visit[r][nowC] == visit[nowR][nowC])
			{
				break;
			}

			// 이미 연결되어 있다면 중단
			if (connect[visit[nowR][nowC]][visit[r][nowC]] == 1)
			{
				break;
			}

			// 이미 놓았던 곳이면 중단
			if (flag == 1)
			{
				break;
			}

			// 다리 길이는 최소 2 이상
			if (r - nowR <= MIN_LENGTH)
			{
				break;
			}

			// 다리 놓기
			for (int k = nowR + 1; k < r; k++)
			{
				visit[k][nowC]--;
				cnt++;
			}

			connect[visit[nowR][nowC]][visit[r][nowC]] = 1;
			connect[visit[r][nowC]][visit[nowR][nowC]] = 1;
			connectCnt++;

			// 완전탐색
			run(nextR, nextC, level + 1, length + cnt);

			// 원상복구
			for (int k = nowR + 1; k < r; k++)
			{
				visit[k][nowC]++;
				cnt--;
			}

			connect[visit[nowR][nowC]][visit[r][nowC]] = 0;
			connect[visit[r][nowC]][visit[nowR][nowC]] = 0;
			connectCnt--;

			break;
		}
	}

	flag = 1;

	// 3. 왼쪽
	for (int c = nowC - 1; c >= 0; c--)
	{
		if (visit[nowR][c] == 0)
		{
			flag = 0;
		}
		// 다른 섬을 찾으면
		else if ((visit[nowR][c] > 0))
		{
			// 자신의 섬이면 중단
			if (visit[nowR][c] == visit[nowR][nowC])
			{
				break;
			}

			// 이미 연결되어 있다면 중단
			if (connect[visit[nowR][nowC]][visit[nowR][c]] == 1)
			{
				break;
			}

			// 이미 놓았던 곳이면 중단
			if (flag == 1)
			{
				break;
			}

			// 다리 길이는 최소 2 이상
			if (nowC - c <= MIN_LENGTH)
			{
				break;
			}

			// 다리 놓기
			for (int k = nowC - 1; k > c; k--)
			{
				visit[nowR][k]--;
				cnt++;
			}

			connect[visit[nowR][nowC]][visit[nowR][c]] = 1;
			connect[visit[nowR][c]][visit[nowR][nowC]] = 1;
			connectCnt++;

			// 완전탐색
			run(nextR, nextC, level + 1, length + cnt);

			// 원상복구
			for (int k = nowC - 1; k > c; k--)
			{
				visit[nowR][k]++;
				cnt--;
			}

			connect[visit[nowR][nowC]][visit[nowR][c]] = 0;
			connect[visit[nowR][c]][visit[nowR][nowC]] = 0;
			connectCnt--;

			break;
		}
	}

	flag = 1;

	// 4. 오른쪽
	for (int c = nowC + 1; c < M; c++)
	{
		if (visit[nowR][c] == 0)
		{
			flag = 0;
		}
		// 다른 섬을 찾으면
		else if ((visit[nowR][c] > 0))
		{
			// 자신의 섬이면 중단
			if (visit[nowR][c] == visit[nowR][nowC])
			{
				break;
			}

			// 이미 연결되어 있다면 중단
			if (connect[visit[nowR][nowC]][visit[nowR][c]] == 1)
			{
				break;
			}

			// 이미 놓았던 곳이면 중단
			if (flag == 1)
			{
				break;
			}

			// 다리 길이는 최소 2 이상
			if (c - nowC <= MIN_LENGTH)
			{
				break;
			}

			// 다리 놓기
			for (int k = nowC + 1; k < c; k++)
			{
				visit[nowR][k]--;
				cnt++;
			}

			connect[visit[nowR][nowC]][visit[nowR][c]] = 1;
			connect[visit[nowR][c]][visit[nowR][nowC]] = 1;
			connectCnt++;

			// 완전탐색
			run(nextR, nextC, level + 1, length + cnt);

			// 원상복구
			for (int k = nowC + 1; k < c; k++)
			{
				visit[nowR][k]++;
				cnt--;
			}

			connect[visit[nowR][nowC]][visit[nowR][c]] = 0;
			connect[visit[nowR][c]][visit[nowR][nowC]] = 0;
			connectCnt--;

			break;
		}
	}

	// 5. 놓지 않아도 계속 탐색은 해야 한다!
	run(nextR, nextC, level, length);

	return;
}

/*
// 여기서 거리까지 한번에!
void make_combination(int level, int now)
{


	return;
}
*/

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);
	// freopen("input3.txt", "r", stdin);
	// freopen("input4.txt", "r", stdin);
	// freopen("input5.txt", "r", stdin);
	// freopen("input6.txt", "r", stdin);
	// freopen("input7.txt", "r", stdin);
	// freopen("input8.txt", "r", stdin);
	// freopen("input9.txt", "r", stdin);
	// freopen("input10.txt", "r", stdin);
	// freopen("input11.txt", "r", stdin);
	// freopen("input12.txt", "r", stdin);
	// freopen("input13.txt", "r", stdin);
	// freopen("input14.txt", "r", stdin);
	// freopen("input15.txt", "r", stdin);
	// freopen("input16.txt", "r", stdin);
	// freopen("input17.txt", "r", stdin);
	// freopen("input18.txt", "r", stdin);
	// freopen("input19.txt", "r", stdin);
	// freopen("input20.txt", "r", stdin);
	// freopen("input21.txt", "r", stdin);
	// freopen("input22.txt", "r", stdin);
	// freopen("input23.txt", "r", stdin);
	// freopen("input24.txt", "r", stdin);
	// freopen("input25.txt", "r", stdin);
	// freopen("input26.txt", "r", stdin);
	// freopen("input27.txt", "r", stdin);
	// freopen("input28.txt", "r", stdin);

	setbuf(stdout, NULL);

	int startR = 0;
	int startC = 0;

	input();

	// 1. 영역 나누기
	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < M; c++)
		{
			// 육지이고 아직 방문하지 않았다면
			if ((map[r][c] == 1) && (visit[r][c] == 0))
			{
				if (islandCnt == 0)
				{
					startR = r;
					startC = c;
					// connect[START_LEVEL] = 1;
				}

				islandCnt++;

				// 탐색 시작
				bfs(r, c);
			}
		}
	}

	int debug = 1;

	// 2. 다리 놓기
	run(startR, startC, START_LEVEL, START_LENGTH);

	/*
	// 2. 조합 생성
	make_combination(START_LEVEL, START_ISLAND);
	*/

	if (ans == MAX_INT)
	{
		ans = -1;
	}

	printf("%d\n", ans);

	return 0;
}
