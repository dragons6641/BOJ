#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>

#define MAX_N 20
#define MAX_DIR 4
#define MAX_STUDENT 4

struct seatNode
{
	// 자리의 실제 위치
	int r;
	int c;
	// 좋아하는 학생이 인접한 칸의 갯수
	int adjacencyCnt;
	// 비어있는 인접한 칸의 갯수
	int emptyCnt;

	bool operator < (const seatNode &cmpNode)
	{
		if (this->adjacencyCnt == cmpNode.adjacencyCnt)
		{
			// 2. 1을 만족하는 칸이 여러 개이면, 
			// 인접한 칸 중에서 비어있는 칸이 가장 많은 칸으로 자리를 정한다.
			if (this->emptyCnt == cmpNode.emptyCnt)
			{
				// 3. 2를 만족하는 칸도 여러 개인 경우에는 행의 번호가 가장 작은 칸으로, 
				// 그러한 칸도 여러 개이면 열의 번호가 가장 작은 칸으로 자리를 정한다.
				return (((this->r * MAX_N) + this->c) < ((cmpNode.r * MAX_N) + cmpNode.c));
			}

			return (this->emptyCnt > cmpNode.emptyCnt);
		}

		// 1. 비어있는 칸 중에서 좋아하는 학생이 인접한 칸에 가장 많은 칸으로 자리를 정한다.
		return (this->adjacencyCnt > cmpNode.adjacencyCnt);
	}
};

struct studentNode
{
	// 학생이 앉은 자리 위치
	int r;
	int c;
	// 학생 번호
	int idx;
	// 좋아하는 학생 목록
	int preferStudentArr[MAX_STUDENT];
};

// 격자의 크기
int N;
// 전체 학생 수
int studentCnt;
// 최종 만족도
int answer;
// 인접한 위치 찾기
int dr[MAX_DIR] = { -1, 1, 0, 0 };
int dc[MAX_DIR] = { 0, 0, -1, 1 };
// 좋아하는 학생 수에 따른 만족도 목록
int satisfactionArr[MAX_STUDENT + 1] = { 0, 1, 10, 100, 1000 };
// 실제 자리 배치
int seatArr[MAX_N + 2][MAX_N + 2];
// 각 칸마다 인접한 비어있는 칸 갯수 세기
int emptyCntArr[MAX_N + 2][MAX_N + 2];
// 좋아하는 학생 정보
studentNode studentNodeArr[MAX_N * MAX_N];

void inputData(void)
{
	std::cin >> N;

	studentCnt = N * N;

	for (register int i = 0; i < studentCnt; i++)
	{
		std::cin >> studentNodeArr[i].idx;

		for (register int j = 0; j < MAX_STUDENT; j++)
		{
			std::cin >> studentNodeArr[i].preferStudentArr[j];
		}
	}

	return;
}

void init(void)
{
	int rowCnt = 0;
	int colCnt = 0;

	for (register int r = 0; r <= N + 1; r++)
	{
		seatArr[r][0] = -1;
		seatArr[r][N + 1] = -1;
	}

	for (register int c = 0; c <= N + 1; c++)
	{
		seatArr[0][c] = -1;
		seatArr[N + 1][c] = -1;
	}

	for (register int r = 1; r <= N; r++)
	{
		for (register int c = 1; c <= N; c++)
		{
			if ((r == 1) || (r == N))
			{
				rowCnt = 1;
			}
			else
			{
				rowCnt = 2;
			}

			if ((c == 1) || (c == N))
			{
				colCnt = 1;
			}
			else
			{
				colCnt = 2;
			}

			emptyCntArr[r][c] = rowCnt + colCnt;
		}
	}

	return;
}

int getAdjacencyCnt(int i, int curR, int curC)
{
	int result = 0;

	// 인접 4방향 확인
	for (register int dir = 0; dir < MAX_DIR; dir++)
	{
		int nextR = curR + dr[dir];
		int nextC = curC + dc[dir];

		// 좋아하는 학생 4명 확인
		for (register int j = 0; j < MAX_STUDENT; j++)
		{
			// 좋아하는 학생이 인접해 있을 경우 갯수 증가
			if (seatArr[nextR][nextC] == studentNodeArr[i].preferStudentArr[j])
			{
				result++;
			}
		}
	}

	return result;
}

void placeStudent(int i, int curR, int curC)
{
	// 해당 칸에 학생을 앉힌다. 
	seatArr[curR][curC] = studentNodeArr[i].idx;
	studentNodeArr[i].r = curR;
	studentNodeArr[i].c = curC;

	// 인접한 자리에 빈 자리 갯수를 갱신해 준다. 
	for (register int dir = 0; dir < MAX_DIR; dir++)
	{
		int nextR = curR + dr[dir];
		int nextC = curC + dc[dir];

		emptyCntArr[nextR][nextC]--;
	}

	return;
}

void getAnswer(void)
{
	// 학생별 만족도 계산
	for (register int i = 0; i < studentCnt; i++)
	{
		// 학생이 앉은 위치
		int curR = studentNodeArr[i].r;
		int curC = studentNodeArr[i].c;
		int satisfactionCnt = 0;

		// 인접 4방향 확인
		for (register int dir = 0; dir < MAX_DIR; dir++)
		{
			int nextR = curR + dr[dir];
			int nextC = curC + dc[dir];

			// 좋아하는 학생 4명 확인
			for (register int j = 0; j < MAX_STUDENT; j++)
			{
				// 좋아하는 학생이 인접해 있을 경우 갯수 증가
				if (seatArr[nextR][nextC] == studentNodeArr[i].preferStudentArr[j])
				{
					satisfactionCnt++;
				}
			}
		}

		// 해당 학생의 만족도를 정답에 더한다. 
		answer += satisfactionArr[satisfactionCnt];
	}

	return;
}

void solve(void)
{
	// 각 학생별로 같은 작업 반복
	for (register int i = 0; i < studentCnt; i++)
	{
		// 만족하는 칸의 갯수
		int seatNodeCnt = 0;
		// 최고 인접 갯수 기록
		int maxAdjacencyCnt = -1;
		// 좋아하는 학생이 인접한 칸에 가장 많은 칸들의 목록
		seatNode seatNodeArr[MAX_N * MAX_N];

		for (register int r = 1; r <= N; r++)
		{
			for (register int c = 1; c <= N; c++)
			{
				// 자리가 차있으면 확인할 필요 없음
				if (seatArr[r][c] != 0)
				{
					continue;
				}

				// 좋아하는 학생이 몇 명 인접했는지 확인
				int adjacencyCnt = getAdjacencyCnt(i, r, c);

				// 최고 기록인 경우 리셋
				if (maxAdjacencyCnt < adjacencyCnt)
				{
					maxAdjacencyCnt = adjacencyCnt;
					seatNodeCnt = 0;
				}
				
				// 같은 기록인 경우 추가
				if (maxAdjacencyCnt == adjacencyCnt)
				{
					seatNodeArr[seatNodeCnt++] = { r, c, adjacencyCnt, emptyCntArr[r][c] };
				}
			}
		}

		// 문제의 우선순위대로 정렬
		std::sort(seatNodeArr, seatNodeArr + seatNodeCnt);

		// 학생 자리 배치
		placeStudent(i, seatNodeArr[0].r, seatNodeArr[0].c);
	}

	// 만족도 구하기
	getAnswer();

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);	// 54
	// freopen("input2.txt", "r", stdin);	// 1053

	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	inputData();

	init();

	solve();

	std::cout << answer;

	return 0;
}
