// KJO15685.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#define _CRT_SECURE_NO_WARNINGS
#define MAX_N 20
#define MAX_X 100
#define MAX_Y 100
#define MAX_D 3
#define MAX_G 10

/*
#include "pch.h"
#include <iostream>
*/

#include <stdio.h>

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct dc {
	int x = -1;
	int y = -1;
	int d = -1;
	int g = -1;
} DC;

///*
typedef struct dir {
	int val = -1;
	int from = -1;
	int to = -1;
}DIR;
//*/

int n = 0;
int ans = 0;

DIR matrix[MAX_Y + 1][MAX_X + 1];
// int matrix[MAX_Y][MAX_X] = { 0 };
DC info_list[MAX_N];
DC save_list[MAX_G + 1];

void init()
{
	for (int row = 0; row < MAX_Y + 1; row++)
	{
		for (int col = 0; col < MAX_X + 1; col++)
		{
			// matrix[row][col] = -1;

			matrix[row][col].val = -1;
			matrix[row][col].from = -1;
			matrix[row][col].to = -1;
		}
	}

	for (int i = 0; i < MAX_N; i++)
	{
		info_list[i].x = -1;
		info_list[i].y = -1;
		info_list[i].d = -1;
		info_list[i].g = -1;
	}

	for (int i = 0; i <= MAX_G; i++)
	{
		save_list[i].x = -1;
		save_list[i].y = -1;
		save_list[i].d = -1;
		save_list[i].g = -1;
	}

	return;
}

void print_info()
{
	printf("info_list : \n");

	for (int i = 0; i < n; i++)
	{
		printf("%d %d %d %d\n", info_list[i].x, info_list[i].y, info_list[i].d, info_list[i].g);
	}

	printf("\n");

	return;
}

void print_matrix()
{
	printf("matrix : \n");

	for (int row = 0; row < 20; row++)
	// for (int row = 0; row < MAX_Y; row++)
	{
		for (int col = 0; col < 20; col++)
		// for (int col = 0; col < MAX_X; col++)
		{
			printf("%d ", matrix[row][col].val);
			// printf("%d ", matrix[row][col].from);
		}

		printf("\n");
	}

	printf("\n");

	return;
}

int get_dir(int cur_d)
{
	// 오른쪽이면
	if (cur_d == 0)
	{
		// 아래쪽으로
		return 3;
		
	}
	// 위쪽이면
	else if (cur_d == 1)
	{
		// 오른쪽으로
		return 0;
	}
	// 왼쪽이면
	else if (cur_d == 2)
	{
		// 위쪽으로
		return 1;
	}
	// 아래쪽이면
	else if (cur_d == 3)
	{
		// 왼쪽으로
		return 2;
	}

	return -1;
}

int reverse_dir(int cur_d)
{
	// 오른쪽이면
	if (cur_d == 0)
	{
		// 왼쪽으로
		return 2;
	}
	// 위쪽이면
	else if (cur_d == 1)
	{
		// 아래쪽으로
		return 3;
	}
	// 왼쪽이면
	else if (cur_d == 2)
	{
		// 오른쪽으로
		return 0;
	}
	// 아래쪽이면
	else if (cur_d == 3)
	{
		// 위쪽으로
		return 1;
	}

	return -1;
}

int get_row(int cur_r, int cur_d)
{
	// 오른쪽이면
	if (cur_d == 0)
	{
		// 변동 없음
		return cur_r;
	}
	// 위쪽이면
	else if (cur_d == 1)
	{
		// 감소
		return cur_r - 1;
	}
	// 왼쪽이면
	else if (cur_d == 2)
	{
		// 변동 없음
		return cur_r;
	}
	// 아래쪽이면
	else if (cur_d == 3)
	{
		// 증가
		return cur_r + 1;
	}

	return -1;
}

int get_col(int cur_c, int cur_d)
{
	// 오른쪽이면
	if (cur_d == 0)
	{
		// 증가
		return cur_c + 1;
	}
	// 위쪽이면
	else if (cur_d == 1)
	{
		// 변동 없음
		return cur_c;
	}
	// 왼쪽이면
	else if (cur_d == 2)
	{
		// 감소
		return cur_c - 1;
	}
	// 아래쪽이면
	else if (cur_d == 3)
	{
		// 변동 없음
		return cur_c;
	}

	return -1;
}

void make_curve(int start_r, int start_c, int start_d, int end_g)
{
	int factor = 1;

	// 0세대
	int rear_r = start_r;
	int rear_c = start_c;
	int rear_d = start_d;

	int front_r = get_row(rear_r, rear_d);
	int front_c = get_col(rear_c, rear_d);
	int front_d = -1;

	// 위치 표시
	matrix[rear_r][rear_c].val = 0;
	matrix[front_r][front_c].val = 0;
	matrix[front_r][front_c].from = reverse_dir(rear_d);

	// 1세대부터 끝까지
	for (int gen = 1; gen <= end_g; gen++)
	{
		// 위치 불러오기
		rear_r = front_r;
		rear_c = front_c;

		for (int len = 1; len <= factor; len++)
		{
			// 다음 방향 정하기
			rear_d = matrix[rear_r][rear_c].from;
			front_d = get_dir(rear_d);

			// printf("rear : (%d, %d) %d, front : (%d, %d) %d, gen = %d, len = %d\n", rear_r, rear_c, rear_d, front_r, front_c, front_d, gen, len);

			// 뒤로 먼저 가고
			rear_r = get_row(rear_r, rear_d);
			rear_c = get_col(rear_c, rear_d);

			// 앞으로 그대로 그린다
			front_r = get_row(front_r, front_d);
			front_c = get_col(front_c, front_d);

			// 위치 표시
			// matrix[rear_r][rear_c].from = rear_d;
			matrix[front_r][front_c].from = reverse_dir(front_d);
			matrix[front_r][front_c].val = gen;

			// print_matrix();
		}

		// 2배씩 길이 증가
		factor *= 2;
	}

	return;
}

void check_curve()
{
	for (int row = 0; row < MAX_Y - 1; row++)
	{
		for (int col = 0; col < MAX_X - 1; col++)
		{
			if ((matrix[row][col].val != -1) && (matrix[row + 1][col].val != -1) && (matrix[row][col + 1].val != -1) && (matrix[row + 1][col + 1].val != -1))
			{
				ans += 1;
			}
		}
	}

	return;
}

void solve()
{
	for (int i = 0; i < n; i++)
	{
		init();

		// printf("%d %d %d %d\n", info_list[i].y, info_list[i].x, info_list[i].d, info_list[i].g);

		make_curve(info_list[i].y, info_list[i].x, info_list[i].d, info_list[i].g);

		// print_matrix();
	}

	// print_matrix();

	check_curve();

	return;
}

/*
int main()
{
    // std::cout << "Hello World!\n"; 

	// init();

	scanf("%d", &n);

	for (int i = 0; i < n; i++)
	{
		scanf("%d %d %d %d", &info_list[i].x, &info_list[i].y, &info_list[i].d, &info_list[i].g);
	}

	// print_info();

	solve();

	// print_matrix();

	printf("%d", ans);

	return 0;
}
*/

// 일단 제출은 하되 공부하자!

//시간 복잡도: O(n*2^g + xy)
//공간 복잡도: O(xy)
//사용한 알고리즘: 반복문
//사용한 자료구조: 스택(1차원 벡터), 2차원 배열, 1차원 배열

bool map[102][102];

//끝점의 정보
int end_x = 0;
int end_y = 0;


//왼쪽, 위쪽, 오른쪽, 아래쪽
int dx[] = { 0, -1, 0, 1 };
int dy[] = { 1, 0, -1, 0 };


//이전 세대의 방향정보를 저장하는 스택
//stl 스택쓰면 귀찮으니까 인덱스로 접근 할 수 있는 벡터를 사용한다.
vector<int> dragon;

//스택을 조사하면서 드래곤 커브를 만드는 함수
void make_generation(vector<int> &dragon) {

	//현재 스택의 크기를 먼저 계산해 놓는다.
	int size = (int)dragon.size();

	//스택의 뒤에서 부터 꺼내면서
	//다음세대의 방향정보를 dir = (dragon[i] + 1)%4; 규칙에 따라 생성한다.
	for (int i = size - 1; i >= 0; i--) {
		int dir = (dragon[i] + 1) % 4;

		//다음 세대의 방향정보를 바탕으로 다음 x,y를 찾고 이를 갱신한다.
		end_x = end_x + dx[dir];
		end_y = end_y + dy[dir];

		//만들어진 드래곤 커브를 지도에 놓아준다.
		map[end_x][end_y] = true;

		//다음세대를 위하 스택에 방향정보를 넣어준다.
		dragon.push_back(dir);
	}
}

int main() {

	int n;
	cin >> n;

	for (int i = 0; i < n; i++) {
		//x, y의 순서를 바꿔서 입력받는다.
		int y, x, d, g;
		cin >> y >> x >> d >> g;

		//기존 드래곤 커브의 스택을 비워준다.
		dragon.clear();

		//끝점을 갱신한다.
		end_x = x;
		end_y = y;

		//현재 위치에 드래곤 커브가 놓여있으므로 지도에 표시해준다.
		map[end_x][end_y] = true;

		//0세대는 미리 만들어 놓는다.
		end_x = x + dx[d];
		end_y = y + dy[d];

		//0세대를 만든 이후에도 지도에 표시해준다.
		map[end_x][end_y] = true;

		//0세대의 방향정보를 스택에 넣어준다.
		dragon.push_back(d);

		//반복문을 통해 0부터 차례차례 드래곤 커브를 만들면서 g세대까지 만든다.
		for (int i = 0; i < g; i++) {

			//드래곤 커브를 만들자
			make_generation(dragon);
		}

	}

	//100*100 2차원 행렬을 2중 for문 사용한 단순한 탐색
	//인접한 4칸이 모두 true이면, 4칸이 모두 드래곤 커브의 일부인것
	//갯수를 1증가시킨다.
	int result = 0;
	for (int i = 0; i <= 100; i++) {
		for (int j = 0; j <= 100; j++) {

			//인접한 4칸의 정사각형이 모두 드래곤의 일부이면
			if (map[i][j] == true && map[i][j + 1] == true && map[i + 1][j] == true && map[i + 1][j + 1] == true) {

				//갯수를 1 증가시킨다.
				result++;
			}
		}
	}

	//갯수 출력
	cout << result << endl;

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
