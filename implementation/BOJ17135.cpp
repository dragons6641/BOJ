// KJO17135.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#define _CRT_SECURE_NO_WARNINGS
#define MAX_N 15
#define MAX_M 15
#define MAX_D 10
#define ARCHERS 3
#define MAX_E MAX_N * MAX_M
#define INF 1000000000

/*
#include "pch.h"
#include <iostream>
*/

#include <stdio.h>
#include <cmath>

using namespace std;

typedef struct pos {
	int isAlive = -1;
	int r = -1;
	int c = -1;
} POS;

typedef struct victim {
	int index = -1;
	int dist = INF;
	int r = -1;
	int c = -1;
} VICTIM;

// 행
int n = 0;
// 열
int m = 0;
// 사정거리
int d = 0;
// 정답
int ans = 0;
// 정답 후보
int result = 0;
// 적의 수
int cnt = 0;

// 맵 상태
int matrix[MAX_N][MAX_M] = { -1 };
// 궁수의 col list
int archer_list[ARCHERS] = { -1 };
// 궁수가 죽일 적의 index 저장
VICTIM target_list[ARCHERS];
// 적의 pos list
POS enemy_list[MAX_E];

void init()
{
	ans = 0;
	result = 0;
	cnt = 0;

	for (int row = 0; row < MAX_N; row++)
	{
		for (int col = 0; col < MAX_M; col++)
		{
			matrix[row][col] = -1;
		}
	}

	for (int i = 0; i < ARCHERS; i++)
	{
		archer_list[i] = -1;

		target_list[i].index = -1;
		target_list[i].dist = INF;
		target_list[i].r = -1;
		target_list[i].c = -1;
	}

	for (int i = 0; i < MAX_E; i++)
	{
		enemy_list[i].isAlive = -1;
		enemy_list[i].r = -1;
		enemy_list[i].c = -1;
	}
}

void print_matrix()
{
	printf("matrix : \n");

	for (int row = 0; row < n; row++)
	{
		for (int col = 0; col < m; col++)
		{
			printf("%d ", matrix[row][col]);
		}

		printf("\n");
	}

	printf("\n");

	return;
}

void print_archer()
{
	printf("archer_list : \n");

	for (int i = 0; i < ARCHERS; i++)
	{
		printf("%d ", archer_list[i]);
	}

	printf("\n");

	return;
}

void print_target()
{
	printf("target_list : \n");

	for (int i = 0; i < ARCHERS; i++)
	{
		printf("%d %d, (%d, %d)\n", target_list[i].index, target_list[i].dist, target_list[i].r, target_list[i].c);
	}

	printf("\n");

	return;
}

void print_enemy()
{
	printf("enemy_list : \n");

	for (int i = 0; i < cnt; i++)
	{
		printf("%d, (%d, %d)\n", enemy_list[i].isAlive, enemy_list[i].r, enemy_list[i].c);
	}

	printf("\n");

	return;
}

int calc_dist(int a1, int b1, int a2, int b2)
{
	return abs(a1 - a2) + abs(b1 - b2);
}

void aim(int turn)
{
	int archer_row = -1;
	int archer_col = -1;
	int enemy_row = -1;
	int enemy_col = -1;
	int cur_dist = 0;

	// 궁수마다 타겟 설정
	for (int i = 0; i < ARCHERS; i++)
	{
		// 궁수 위치 설정
		archer_row = n - turn;
		archer_col = archer_list[i];

		// 적 한명씩 확인
		for (int j = 0; j < cnt; j++)
		{
			// 적이 살아있을 경우에만 의미있음!
			// 또한 궁수보다 위에 있어야 함
			if ((enemy_list[j].isAlive == 1) && (archer_row > enemy_row))
			{
				// 적 위치 설정
				enemy_row = enemy_list[j].r;
				enemy_col = enemy_list[j].c;

				// 거리 계산
				cur_dist = calc_dist(archer_row, archer_col, enemy_row, enemy_col);

				// printf("dist = %d\n", cur_dist);

				// 거리가 사정거리와 같거나 가까울 경우
				if (cur_dist <= d)
				{
					// 아직 타겟이 없다면
					if (target_list[i].index == -1)
					{
						// 타겟 설정
						target_list[i].index = j;
						target_list[i].dist = cur_dist;
						target_list[i].r = enemy_row;
						target_list[i].c = enemy_col;
					}
					// 이미 타겟이 있다면
					else
					{
						// 거리가 더 가까울 경우
						if (cur_dist < target_list[i].dist)
						{
							// 타겟 설정
							target_list[i].index = j;
							target_list[i].dist = cur_dist;
							target_list[i].r = enemy_row;
							target_list[i].c = enemy_col;
						}
						// 거리가 같을 경우에는
						else if (cur_dist == target_list[i].dist)
						{
							// 더 왼쪽일 경우
							if (enemy_col < target_list[i].c)
							{
								// 타겟 설정
								target_list[i].index = j;
								target_list[i].dist = cur_dist;
								target_list[i].r = enemy_row;
								target_list[i].c = enemy_col;
							}
						}
					}
				}
			}
		}
	}

	return;
}

void kill()
{
	// 궁수마다 한 명씩 쏜다, 동시에
	for (int i = 0; i < ARCHERS; i++)
	{
		// 타겟으로 한 사람이 아직 살아있다면
		if (enemy_list[target_list[i].index].isAlive == 1)
		{
			// 죽이고
			enemy_list[target_list[i].index].isAlive = 0;

			// 킬 수 적립
			result += 1;
		}
	}

	return;
}

int forward(int turn)
{
	int remain = 0;

	// 궁수 위치를 앞으로 옮긴다는 생각!
	// 궁수 위치는 이미 aim에 반영
	// 성곽에 도착한 적만 체크!
	for (int j = 0; j < cnt; j++)
	{
		// 살아있을 경우
		if (enemy_list[j].isAlive == 1)
		{
			// row값을 체크해서 넘었으면
			if (enemy_list[j].r + turn == n - 1)
			{
				// 없애준다
				enemy_list[j].isAlive = -1;
			}
		}

		// 그래도 살아있으면
		if (enemy_list[j].isAlive == 1)
		{
			remain += 1;
		}
	}

	return remain;
}

void check_result()
{
	result = 0;

	for (int j = 0; j < cnt; j++)
	{
		// 맞아 죽었으면
		if (enemy_list[j].isAlive == 0)
		{
			result += 1;
		}
	}

	return;
}

void simulate()
{
	// 값 초기화
	result = 0;

	int remain = 0;

	// 다시 살리고 시작
	for (int i = 0; i < cnt; i++)
	{
		enemy_list[i].isAlive = 1;
	}

	// 최대 n회의 턴동안(0턴부터 시작)
	for (int i = 0; i < n; i++)
	{
		// 타겟은 매 턴 초기화
		for (int i = 0; i < ARCHERS; i++)
		{
			target_list[i].index = -1;
			target_list[i].dist = INF;
			target_list[i].r = -1;
			target_list[i].c = -1;
		}

		// 1. 타겟 설정
		aim(i);

		// print_target();

		// 2. 죽인다
		kill();

		// print_enemy();

		// 3. 전진
		// 탈출 조건 체크
		remain = forward(i);

		// 모두 죽었다면
		if (remain == 0)
		{
			// 시뮬레이션 종료
			break;
		}
	}

	// 왜 답이 안맞지?
	check_result();

	// 정답 갱신
	if (result > ans)
	{
		// printf("result = %d\n", result);

		ans = result;
	}

	return;
}

void backtrack(int start, int depth)
{
	// printf("start : %d, depth : %d\n", start, depth);

	// 모든 궁수 배치했으면
	if (depth == ARCHERS)
	{
		// print_archer();

		// 시뮬레이션 시작
		simulate();

		return;
	}

	for (int i = start; i < m; i++)
	{
		// 위치 표시해주고
		archer_list[depth] = i;

		// 완전탐색
		backtrack(i + 1, depth + 1);

		// 위치 초기화
		archer_list[depth] = -1;
	}

	return;
}

int main()
{
    // std::cout << "Hello World!\n"; 

	init();

	int tmp = 0;

	scanf("%d %d %d", &n, &m, &d);

	for (int row = 0; row < n; row++)
	{
		for (int col = 0; col < m; col++)
		{
			scanf("%d", &tmp);

			matrix[row][col] = tmp;

			// 적이라면
			if (tmp == 1)
			{
				// 표시
				enemy_list[cnt].isAlive = 1;
				enemy_list[cnt].r = row;
				enemy_list[cnt].c = col;

				// 적의 수 증가
				cnt += 1;
			}
		}
	}

	/*
	print_matrix();
	print_enemy();
	*/

	backtrack(0, 0);

	printf("%d", ans);

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
