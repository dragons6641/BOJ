// KJO2151.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#define _CRT_SECURE_NO_WARNINGS
#define MAX_N 50
#define MAX_M (MAX_N * MAX_N)
#define MAX_DIR 4

/*
#include "pch.h"
#include <iostream>

#include <stdio.h>
#include <vector>

using namespace std;

// 4방향
// 상, 하, 좌, 우
int dr[MAX_DIR] = { -1, 1, 0, 0 };
int dc[MAX_DIR] = { 0, 0, -1, 1 };

// 집 벡터
vector < vector < char > > v;

// 거울 위치
vector < pair < int, int > > w;

// 방문 벡터
vector < vector < int > > isVisited;

// 최솟값을 가져야한다
// 초기화는 최대로
int ans = MAX_M;

int n = 0;

// 가능한지 체크
int isAns = 0;

// 빛 방향 : 상, 하, 좌, 우
// 시작점
int sd = -1;
int sr = -1;
int sc = -1;

// 도착점
int ed = -1;
int er = -1;
int ec = -1;

void init_v()
{
	v.clear();
	v.resize(n);

	for (int r = 0; r < v.size(); r++)
	{
		v[r].resize(n);
	}

	return;
}

void init_isVisited()
{
	isVisited.clear();
	isVisited.resize(n);

	for (int r = 0; r < isVisited.size(); r++)
	{
		isVisited[r].resize(n);
	}

	return;
}

void print_v()
{
	printf("v : \n");

	for (int r = 0; r < v.size(); r++)
	{
		for (int c = 0; c < v[r].size(); c++)
		{
			printf("%c", v[r][c]);
		}

		printf("\n");
	}

	return;
}

void print_w()
{
	printf("w : \n");

	for (int i = 0; i < w.size(); i++)
	{
		printf("(%d, %d)\n", w[i].first, w[i].second);
	}

	return;
}

// 빛의 방향 찾기
int find_dir(int r, int c)
{
	// 상
	if (r == v.size() - 1)
	{
		return 0;
	}
	// 하
	else if (r == 0)
	{
		return 1;
	}
	// 좌
	else if (c == v[r].size() - 1)
	{
		return 2;
	}
	// 우
	else if (c == 0)
	{
		return 3;
	}

	// error
	return -1;
}

int check(int d, int r, int c)
{
	int next_r = r + dr[d];
	int next_c = c + dc[d];

	// 상, 하 체크
	if ((next_r < 0) || (next_r >= v.size()))
	{
		// 불가능
		return 0;
	}
	// 좌, 우 체크
	else if ((next_c < 0) || (next_c >= v[r].size()))
	{
		// 불가능
		return 0;
	}
	// 벽이라면
	// 거울이면 진행은 가능하긴 함!
	else if (v[next_r][next_c] == '*')
	{
		// 불가능
		return 0;
	}
	// 이미 방문한 거울이라면
	else if ((v[next_r][next_c] == 's') || (v[next_r][next_c] == 'r'))
	{
		// 방문 여부는 거울이 설치되어 있을때만 체크!
		if (isVisited[next_r][next_c])
		{
			// 불가능
			return 0;
		}
	}

	// 나머지는 가능
	return 1;
}

int change_dir(char m, int d)
{
	// 11시-5시 거울
	if (m == 's')
	{
		// 상일 경우
		if (d == 0)
		{
			// 좌로
			return 2;
		}
		// 하일 경우
		else if (d == 1)
		{
			// 우로
			return 3;
		}
		// 좌일 경우
		else if (d == 2)
		{
			// 상으로
			return 0;
		}
		// 우일 경우
		else if (d == 3)
		{
			// 하로
			return 1;
		}
	}
	// 1시-7시 거울
	else if (m == 'r')
	{
		// 상일 경우
		if (d == 0)
		{
			// 우로
			return 3;
		}
		// 하일 경우
		else if (d == 1)
		{
			// 좌로
			return 2;
		}
		// 좌일 경우
		else if (d == 2)
		{
			// 하로
			return 1;
		}
		// 우일 경우
		else if (d == 3)
		{
			// 상으로
			return 0;
		}
	}

	// error
	return -1;
}

// 재귀로 한 칸씩 가자
void simulate(int d, int r, int c)
{
	// printf("d = %d, (%d, %d)\n", d, r, c);

	// 도착했다면
	if ((r == er) && (c == ec))
	{
		// 정답 찾았다고 표시
		isAns = 1;

		// 더 할 필요 없다
		return;
	}

	// 정답 찾았다면
	if (isAns)
	{
		// 더 할 필요 없다
		return;
	}

	// 거울일 경우 방문 표시!
	if ((v[r][c] == 's') || (v[r][c] == 'r'))
	{
		// 아직 방문하지 않은 거울이라면
		if (!isVisited[r][c])
		{
			isVisited[r][c] = 1;
		}
	}

	// 다음 방향 계산
	int next_d = d;

	// printf("d = %d, v[r][c] = %c\n", d, v[r][c]);

	// 현재 위치 기준
	// 11시-5시 거울이 있다면
	if (v[r][c] == 's')
	{
		next_d = change_dir('s', next_d);
	}
	// 1시-7시 거울이 있다면
	else if (v[r][c] == 'r')
	{
		next_d = change_dir('r', next_d);
	}

	// 빛이 진행 가능한지 체크
	int isPossible = check(next_d, r, c);

	printf("isPossible = %d, next_d = %d, (%d, %d)\n", isPossible, next_d, r, c);

	// 진행 가능하다면
	if (isPossible)
	{
		// 다음 위치 구하고
		int next_r = r + dr[next_d];
		int next_c = c + dc[next_d];

		// 해당 위치로 가서 재귀
		simulate(next_d, next_r, next_c);
	}

	return;
}

// cur : 현재 거울 번호
// depth : 설치한 거울 갯수
void backtrack(int idx, int depth)
{
	int r = -1;
	int c = -1;

	 // 최소값 불가능하면
	if (depth > ans)
	{
		// 더 할 게 없다
		return;
	}
	// 모든 거울 다 정했으면 
	else if (idx == w.size())
	{
		print_v();
		// printf("ans : %d\n", ans);

		// 방문 벡터 초기화
		init_isVisited();

		// printf("depth = %d\n\n", depth);

		// 모든 경우의 수 체크
		simulate(sd, sr, sc);

		// printf("isAns = %d\n", isAns);

		// 조건 만족한다면
		if (isAns)
		{
			// 일단 원래대로 돌려놓고
			isAns = 0;

			// 최솟값일 경우
			if (depth < ans)
			{
				// 정답 갱신
				ans = depth;
			}
		}

		// 더 할 게 없다
		return;
	}

	// printf("(%d, %d), idx = %d, depth = %d\n", w[idx].first, w[idx].second, idx, depth);

	// 값 불러오기
	r = w[idx].first;
	c = w[idx].second;

	// 거울 경우의 수 3가지
	// ! : 없음
	backtrack(idx + 1, depth);

	// ㄴ(s) : 11시-5시 거울
	v[r][c] = 's';
	backtrack(idx + 1, depth + 1);
	v[r][c] = '!';

	// ㄱ(r) : 1시-7시 거울
	v[r][c] = 'r';
	backtrack(idx + 1, depth + 1);
	v[r][c] = '!';

	return;
}

int main()
{
    // std::cout << "Hello World!\n"; 

	scanf("%d", &n);

	init_v();

	w.reserve(MAX_M);

	for (int r = 0; r < v.size(); r++)
	{
		getchar();

		for (int c = 0; c < v[r].size(); c++)
		{
			scanf("%c", &v[r][c]);

			// 거울 설치 가능한 위치 기록
			if (v[r][c] == '!')
			{
				w.push_back(make_pair(r, c));
			}
			// 문 위치 기록
			else if (v[r][c] == '#')
			{
				// 시작점 기록
				if (sd == -1)
				{
					sr = r;
					sc = c;
					sd = find_dir(sr, sc);
				}
				// 도착점 기록
				else
				{
					er = r;
					ec = c;
					ed = find_dir(er, ec);
				}
			}
		}
	}

	// print_v();
	// print_w();

	// printf("s : %d, (%d, %d), e : %d, (%d, %d)\n", sd, sr, sc, ed, er, ec);

	backtrack(0, 0);

	printf("%d\n", ans);

	return 0;
}
*/

// 넘나 어렵다 ㅠㅠ
// 일단 제출하고 나중에 공부하자!
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

struct mirror {
	int x, y, z;
};

int n, ex, ey;
char a[50][50];
int dist[50][50][4];
queue<mirror> q;
const int dx[] = { -1, 1, 0, 0 }, dy[] = { 0, 0, -1, 1 };

bool move(int x, int y, int z) {
	if (x < 0 || x >= n || y < 0 || y >= n) return false;
	if (dist[x][y][z] == '*') return false;
	return true;
}

void bfs() {
	while (!q.empty()) {
		int x = q.front().x, y = q.front().y, z = q.front().z; q.pop();
		if (x == ex && y == ey) {
			printf("%d\n", dist[x][y][z]);
			return;
		}
		int nx = x + dx[z], ny = y + dy[z];
		while (move(nx, ny, z) && a[nx][ny] == '.') {
			nx += dx[z], ny += dy[z];
		}
		if (move(nx, ny, z) && a[nx][ny] == '!') {
			dist[nx][ny][z] = dist[x][y][z];
			q.push({ nx, ny, z });
			int k = z < 2 ? 2 : 0;
			for (int i = k; i < k + 2; i++) {
				if (dist[nx][ny][i] == -1) {
					dist[nx][ny][i] = dist[x][y][z] + 1;
					q.push({ nx, ny, i });
				}
			}
		}
	}
}

int main() {
	scanf("%d", &n);
	memset(dist, -1, sizeof(dist));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf(" %1c", &a[i][j]);
			if (a[i][j] == '#') {
				if (q.empty()) {
					for (int k = 0; k < 4; k++) {
						q.push({ i, j, k });
						dist[i][j][k] = 0;
					}
				}
				else {
					ex = i, ey = j;
				}
				a[i][j] = '!';
			}
		}
	}
	bfs();
	return 0;
}
// 출처: https://rebas.kr/781 [PROJECT REBAS]

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
