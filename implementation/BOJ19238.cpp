/*
19238 스타트 택시
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 20
#define MAX_M (MAX_N * MAX_N)
#define MAX_QUEUE (MAX_N * MAX_N)
#define MAX_K 500000
#define MAX_DIR 4

struct Node
{
	// 위치
	int r;
	int c;
	// 남아있는 연료
	int fuel;
};

struct Info
{
	// 출발지
	int sr;
	int sc;
	// 도착지
	int er;
	int ec;
};

// 격자 크기
int N;
// 승객 수
int M;
// 우선순위는 행 번호 작음 -> 열 번호 작음 순
// 상 좌 우 하
int directR[MAX_DIR] = { -1, 0, 0, 1 };
int directC[MAX_DIR] = { 0, -1, 1, 0 };
// Barrier!
// 1부터 N까지 사용
// 초기화 필요
int map[MAX_N + 2][MAX_N + 2] = { 0, };
// Barrier!
// 1부터 N까지 사용
// 초기화 필요
bool visit[MAX_N + 2][MAX_N + 2] = { 0, };
// 택시 정보
Node taxi = { 0, 0, 0 };
// bfs용
// 초기화 필요
Node queue[MAX_QUEUE] = { {0, 0, 0}, };
// 승객 정보
// 1부터 사용
Info passengerList[MAX_M + 1] = { {0, 0, 0, 0}, };

// 음수일 경우 앞 승객, 양수일 경우 뒷 승객 선택
int comp(Node *x, Node *y)
{
	if (x->r == y->r)
	{
		// 열 번호가 가장 작은 승객
		return (x->c - y->c);
	}

	// 행 번호가 가장 작은 승객
	return (x->r - y->r);
}

void initMap(void)
{
	for (register int r = 0; r <= N + 1; r++)
	{
		map[r][0] = -1;
		map[r][N + 1] = -1;
	}

	for (register int c = 0; c <= N + 1; c++)
	{
		map[0][c] = -1;
		map[N + 1][c] = -1;
	}

	return;
}

void initVisit(void)
{
	for (register int r = 1; r <= N; r++)
	{
		for (register int c = 1; c <= N; c++)
		{
			visit[r][c] = false;
		}
	}

	return;
}

void inputData(void)
{
	scanf("%d %d %d", &N, &M, &taxi.fuel);

	initMap();

	for (register int r = 1; r <= N; r++)
	{
		for (register int c = 1; c <= N; c++)
		{
			scanf("%d", &map[r][c]);

			// 벽은 -1로 바꿔주자
			if (map[r][c] == 1)
			{
				map[r][c] = -1;
			}
		}
	}

	scanf("%d %d", &taxi.r, &taxi.c);

	for (register int i = 1; i <= M; i++)
	{
		scanf("%d %d %d %d", &passengerList[i].sr, &passengerList[i].sc, &passengerList[i].er, &passengerList[i].ec);

		// 승객 탑승 위치를 지도에 표시
		map[passengerList[i].sr][passengerList[i].sc] = i;
	}

	return;
}

// 1. 태울 승객을 찾는다. 
int bfs1(void)
{
	// 큐 초기화
	register int head = 0;
	register int tail = 0;
	// 승객 후보
	// r, c, fuel
	// 거리가 제일 짧다 -> 남은 연료가 제일 많다
	// 즉 fuel값은 최솟값으로 초기화
	Node candidate = { -1, -1, -1 };

	// 현재 택시의 위치를 큐에 추가
	visit[taxi.r][taxi.c] = true;
	queue[tail++] = { taxi };

	while (head != tail)
	{
		Node now = queue[head++];

		if (head == MAX_QUEUE)
		{
			head = 0;
		}

		// 더 이상 후보가 없다면
		// 연료를 더 소모했다는 것은 더 이동했다는 것
		// 즉 최단거리가 될 수 없다
		if (candidate.fuel > now.fuel)
		{
			// 더 이상 진행하지 않는다
			break;
		}

		int num = map[now.r][now.c];

		// 승객을 태울 수 있다면
		// 단, 이미 태웠던 승객은 안됨
		if (num > 0)
		{
			// 첫 후보 승객일 경우
			if (candidate.fuel == -1)
			{
				// 후보로 등록
				candidate = now;
			}
			// 다른 후보와 경쟁하는 경우
			else if (candidate.fuel == now.fuel)
			{
				// 둘을 비교한다
				int ret = comp(&candidate, &now);

				// 현재 승객을 먼저 태워야 할 경우
				if (ret > 0)
				{
					// 후보로 등록
					candidate = now;
				}
			}
		}

		// 현재 연료가 0인데 승객을 태우지 못한 경우
		if (now.fuel == 0)
		{
			// 해당 위치에서는 추가 탐색 불가
			continue;
		}

		// 4방향 탐색
		// 우선순위는 이미 반영되어 있음
		for (register int d = 0; d < MAX_DIR; d++)
		{
			int dr = now.r + directR[d];
			int dc = now.c + directC[d];

			// 벽이라면 이동 불가
			if (map[dr][dc] == -1)
			{
				continue;
			}

			// 이미 방문한 곳이라면 이동 불가
			if (visit[dr][dc])
			{
				continue;
			}

			// 탐색할 위치를 큐에 추가
			visit[dr][dc] = true;
			queue[tail++] = { dr, dc, now.fuel - 1 };

			if (tail == MAX_QUEUE)
			{
				tail = 0;
			}
		}
	}

	if (candidate.fuel == -1)
	{
		// 불가능할 경우 -1 리턴
		return -1;
	}

	// 연료 양 반영
	taxi.fuel = candidate.fuel;

	// 승객의 번호 리턴
	return map[candidate.r][candidate.c];
}

// 2. 승객을 목적지까지 이동한다. 
int bfs2(int num)
{
	// 큐 초기화
	register int head = 0;
	register int tail = 0;

	Node start = { passengerList[num].sr, passengerList[num].sc, taxi.fuel };
	Node end = { passengerList[num].er, passengerList[num].ec, taxi.fuel };

	// 현재 출발지의 위치를 큐에 추가
	visit[start.r][start.c] = true;
	queue[tail++] = { start };

	while (head != tail)
	{
		Node now = queue[head++];

		if (head == MAX_QUEUE)
		{
			head = 0;
		}

		// 목적지에 도착했을 경우
		if ((now.r == end.r) && (now.c == end.c))
		{
			// 택시 위치 반영
			taxi.r = end.r;
			taxi.c = end.c;

			// 남은 연료 량 리턴
			return now.fuel;
		}

		// 현재 연료가 0인데 승객을 태우지 못한 경우
		if (now.fuel == 0)
		{
			// 해당 위치에서는 추가 탐색 불가
			continue;
		}

		// 4방향 탐색
		// 우선순위는 이미 반영되어 있음
		for (register int d = 0; d < MAX_DIR; d++)
		{
			int dr = now.r + directR[d];
			int dc = now.c + directC[d];

			// 벽이라면 이동 불가
			if (map[dr][dc] == -1)
			{
				continue;
			}

			// 이미 방문한 곳이라면 이동 불가
			if (visit[dr][dc])
			{
				continue;
			}

			// 탐색할 위치를 큐에 추가
			visit[dr][dc] = true;
			queue[tail++] = { dr, dc, now.fuel - 1 };

			if (tail == MAX_QUEUE)
			{
				tail = 0;
			}
		}
	}

	// 불가능할 경우 -1 리턴
	return -1;
}

int solve(void)
{
	int result = -1;

	// 총 M명의 승객을 태워야 함
	for (register int i = 1; i <= M; i++)
	{
		// 초기화 필요
		initVisit();

		// 1. 태울 승객을 찾는다. 
		int ret1 = bfs1();

		// 승객을 태울 수 없으면 영업 끝
		// 승객의 번호 리턴
		if (ret1 == -1)
		{
			return ret1;
		}
		else
		{
			// 승객을 태웠다고 표시
			map[passengerList[ret1].sr][passengerList[ret1].sc] = 0;
		}

		// 초기화 필요
		initVisit();

		// 2. 승객을 목적지까지 이동한다. 
		int ret2 = bfs2(ret1);

		// 승객을 태울 수 없으면 영업 끝
		// 남은 연료량 리턴
		if (ret2 == -1)
		{
			return ret2;
		}
		else
		{
			// 연료량 반영
			taxi.fuel += (taxi.fuel - ret2);
			result = taxi.fuel;
		}

		int debug = 1;
	}

	return result;
}

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

	inputData();

	int ans = solve();

	printf("%d\n", ans);

	return 0;
}
