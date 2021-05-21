// KJO15662.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#define _CRT_SECURE_NO_WARNINGS
#define MAX_T 1000
#define MAX_S 8
#define MAX_K 1000
#define UU 0
#define DD 4
#define RR 2
#define LL 6

/*
#include "pch.h"
#include <iostream>
*/

#include <stdio.h>
#include <vector>

using namespace std;

typedef struct NODE
{
	// 톱니바퀴의 번호
	int n = 0;
	// 회전 방향
	int d = 0;
}
node;

// 톱니 저장 벡터
vector < vector < char > > v;

// 방문 여부 표시
vector < int > isVisited;

// 명령 저장 벡터
vector < node > cmd;

void init_v(int t)
{
	v.resize(t + 1);

	for (int r = 0; r < v.size(); r++)
	{
		v[r].resize(MAX_S);
	}

	return;
}

void init_isVisited(int t)
{
	isVisited.resize(t + 1);

	return;
}

void init_cmd(int k)
{
	cmd.resize(k + 1);

	return;
}

void print_v()
{
	printf("v : \n");

	for (int r = 1; r < v.size(); r++)
	{
		for (int c = 0; c < v[r].size(); c++)
		{
			printf("%c", v[r][c]);
		}

		printf("\n");
	}

	return;
}

void print_isVisited()
{
	printf("isVisited : ");

	for (int r = 1; r < isVisited.size(); r++)
	{
		printf("%d ", isVisited[r]);
	}

	printf("\n");

	return;
}

void print_cmd()
{
	printf("cmd : \n");

	for (int r = 1; r < cmd.size(); r++)
	{
		printf("%d %d\n", cmd[r].n, cmd[r].d);
	}

	return;
}

void clock(int n, int d)
{
	// 마지막 값을 보관
	char tmp = v[n][MAX_S - 1];

	// 한 칸씩 뒤로
	// 뒤에서부터!
	// 7 6 5 4 3 2 1
	for (int i = MAX_S - 1; i > 0; i--)
	{
		v[n][i] = v[n][i - 1];
	}

	// 첫 값에 복사
	v[n][0] = tmp;

	return;
}

void counterclock(int n, int d)
{
	// 첫 값을 보관
	char tmp = v[n][0];

	// 한 칸씩 앞으로
	// 앞에서부터!
	// 1 2 3 4 5 6 7
	for (int i = 1; i < MAX_S; i++)
	{
		v[n][i - 1] = v[n][i];
	}

	// 마지막 값에 복사
	v[n][MAX_S - 1] = tmp;

	return;
}

int check_l(int n)
{
	// 자신이 가장 왼쪽 톱니바퀴라면
	if (n == 0)
	{
		// 불가능
		return 0;
	}
	// 이미 방문한 톱니바퀴라면
	else if (isVisited[n - 1])
	{
		// 불가능
		return 0;
	}
	// 서로 같은 극이 마주보고 있다면
	else if (v[n][LL] == v[n - 1][RR])
	{
		// 불가능
		return 0;
	}
	
	// 나머지는 같이 돈다
	return 1;
}

int check_r(int n)
{
	// 자신이 가장 오른쪽 톱니바퀴라면
	if (n == v.size() - 1)
	{
		// 불가능
		return 0;
	}
	// 이미 방문한 톱니바퀴라면
	else if (isVisited[n + 1])
	{
		// 불가능
		return 0;
	}
	// 서로 같은 극이 마주보고 있다면
	else if (v[n][RR] == v[n + 1][LL])
	{
		// 불가능
		return 0;
	}

	// 나머지는 같이 돈다
	return 1;
}

// 톱니바퀴 번호, 회전 방향
void simulate(int n, int d)
{
	// 해당 톱니바퀴 방문 표시
	isVisited[n] = 1;

	// 왼쪽도 함께 도는지 확인
	int next_l = check_l(n);
	// 오른쪽도 함께 도는지 확인
	int next_r = check_r(n);

	// 시계 방향
	if (d == 1)
	{
		clock(n, d);

		// 왼쪽 함께 돈다면
		if (next_l)
		{
			// 반시계로 돌린다
			simulate(n - 1, -1);
		}
		// 오른쪽 함께 돈다면
		if (next_r)
		{
			// 반시계로 돌린다
			simulate(n + 1, -1);
		}
	}
	// 반시계 방향
	else if (d == -1)
	{
		counterclock(n, d);

		// 왼쪽 함께 돈다면
		if (next_l)
		{
			// 시계로 돌린다
			simulate(n - 1, 1);
		}
		// 오른쪽 함께 돈다면
		if (next_r)
		{
			// 시계로 돌린다
			simulate(n + 1, 1);
		}
	}

	return;
}

void print_ans()
{
	int ans = 0;

	for (int r = 1; r < v.size(); r++)
	{
		// 12시 방향 체크
		// S극 1이면
		if (v[r][UU] == '1')
		{
			ans += 1;
		}
	}

	printf("%d\n", ans);

	return;
}

int main()
{
    // std::cout << "Hello World!\n"; 

	// 톱니바퀴 개수
	int t = 0;
	// 회전 횟수
	int k = 0;

	scanf("%d", &t);

	init_v(t);

	for (int r = 1; r < v.size(); r++)
	{
		getchar();

		for (int c = 0; c < v[r].size(); c++)
		{
			scanf("%c", &v[r][c]);
		}

		// getchar();
	}

	scanf("%d", &k);

	init_cmd(k);

	for (int r = 1; r < cmd.size(); r++)
	{
		scanf("%d %d", &cmd[r].n, &cmd[r].d);
	}

	// print_v();
	// print_isVisited();
	// print_cmd();

	for (int r = 1; r < cmd.size(); r++)
	{
		init_isVisited(t);

		simulate(cmd[r].n, cmd[r].d);

		// print_v();

		// 초기화
		isVisited.clear();
	}

	print_ans();

	return 0;
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
