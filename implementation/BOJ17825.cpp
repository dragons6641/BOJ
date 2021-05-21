/*
17825 주사위 윷놀이
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define HORSES 4
#define TURNS 10
#define EYES 5
#define START_LEVEL 0
#define START_POINT 0
#define ROWS 12
#define COLS 5

struct Node
{
	int r;
	int c;
};

// 최대값을 가져야 함
int ans = 0;
// 주사위에서 나올 수 10개
int eyeList[TURNS] = { 0, };
// 각 주사위로 어느 말이 움직였는지 표시
int selectList[TURNS] = { 0, };
// 빨간 화살표일 경우 다음 ROW는 어디?
int nextRedList[ROWS] = 
{
	1, 2, 3, 4, 10, 8, 8, 8, 9, 10, 11, -1
};
// 파란 화살표일 경우 다음 ROW는 어디?
int nextBlueList[ROWS] = 
{
	-1, 5, 6, 7, -1, -1, -1, -1, -1, -1, -1, -1
};
// 각 ROW의 마지막 COL 기록
int lastColList[ROWS] = 
{
	0, 4, 4, 4, 3, 2, 1, 2, 0, 1, 0, 0
};
// 윷놀이판
// 빈 칸은 -1
// 구역 설정의 대 원칙 : 빠짐 없이, 중복 없이
int map[ROWS][COLS] = 
{
	{0, -1, -1, -1, -1}, // 0, 시작점
	{2, 4, 6, 8, 10}, // 1
	{12, 14, 16, 18, 20}, // 2
	{22, 24, 26, 28, 30}, // 3
	{32, 34, 36, 38, -1}, // 4
	{13, 16, 19, -1, -1}, // 5
	{22, 24, -1, -1, -1}, // 6
	{28, 27, 26, -1, -1}, // 7
	{25, -1, -1, -1, -1}, // 8
	{30, 35, -1, -1, -1}, // 9
	{40, -1, -1}, // 10
	{0, -1, -1, -1, -1} // 11, 도착점
};
// 말 개수 체크
int visit[ROWS][COLS] = { HORSES, };
// 각 말들의 위치(map)
Node horseList[HORSES] = { {0, 0}, };

void input(void)
{
	for (int i = 0; i < TURNS; i++)
	{
		scanf("%d", &eyeList[i]);
	}

	return;
}

// now번째 말을 turn번째 주사위 눈만큼 이동
// 이동 가능하면 점수 추가, 불가능하면 -1
int moveHorse(int now, int turn)
{
	// 시작 좌표 백업
	Node temp = horseList[now];

	// 한 칸씩 이동
	for (int i = 0; i < eyeList[turn]; i++)
	{
		// 도착했다면
		if ((horseList[now].r == ROWS - 1) && (horseList[now].c == 0))
		{
			// 더 이동할 필요 없음
			break;
		}

		// 시작할 때 체크
		if (i == 0)
		{
			// ROW의 끝에서 이동할 경우
			if (lastColList[horseList[now].r] == horseList[now].c)
			{
				// 파란 화살표가 있다면
				if (nextBlueList[horseList[now].r] != -1)
				{
					// 파란 화살표로 이동
					horseList[now].r = nextBlueList[horseList[now].r];
					horseList[now].c = 0;
				}
				// 빨간 화살표라면
				else
				{
					// 다음 줄로 이동
					horseList[now].r = nextRedList[horseList[now].r];
					horseList[now].c = 0;
				}
			}
			// 일반적인 경우
			else
			{
				// 다음 칸으로 이동
				horseList[now].c++;
			}
		}
		// 시작점이 아닐 경우
		else
		{
			// ROW의 끝에서 이동할 경우
			if (lastColList[horseList[now].r] == horseList[now].c)
			{
				// 다음 줄로 이동
				horseList[now].r = nextRedList[horseList[now].r];
				horseList[now].c = 0;
			}
			// 일반적인 경우
			else
			{
				// 다음 칸으로 이동
				horseList[now].c++;
			}
		}
	}

	// 아직 도착하지 않았는데
	if ((horseList[now].r != ROWS - 1) || (horseList[now].c != 0))
	{
		// 도착한 곳에 이미 다른 말이 있다면
		if (visit[horseList[now].r][horseList[now].c] == 1)
		{
			// 원상복구
			horseList[now] = temp;

			// 거기엔 놓을 수 없다
			return -1;
		}
	}

	// 현재 칸의 점수 리턴
	return map[horseList[now].r][horseList[now].c];
}

void run(int point, int level)
{
	int ret = 0;
	Node temp = { 0, 0 };

	// 10번 모두 끝났으면
	if (level == TURNS)
	{
		if ((selectList[2] == 1) && (selectList[4] == 2) && (selectList[5] == 2) && (selectList[6] == 2))
		{
			int debug = 1;
		}

		// 정답 확인
		if (ans < point)
		{
			ans = point;
		}

		return;
	}

	// 0번 말부터 3번 말까지
	for (int i = 0; i < HORSES; i++)
	{
		// 해당 말이 아직 도착하지 않았다면
		if ((horseList[i].r != ROWS - 1) || (horseList[i].c != 0))
		{
			// 좌표 백업
			temp = horseList[i];

			// i번 말 이동
			ret = moveHorse(i, level);

			// 이동할 수 있는 경우라면
			if (ret != -1)
			{
				// 기존 방문 해제
				visit[temp.r][temp.c] = 0;
				// 신규 방문 표시
				visit[horseList[i].r][horseList[i].c] = 1;
				// 선택 표시
				selectList[level] = i;

				// 완전탐색
				run(point + ret, level + 1);

				/*
				// 돌아갈 수 없는 경우에는 끝!
				if (visit[temp.r][temp.c] == 1)
				{
					return;
				}
				*/

				// 선택 해제
				selectList[level] = -1;
				// 기존 방문 해제
				visit[horseList[i].r][horseList[i].c] = 0;
				// 신규 방문 표시
				visit[temp.r][temp.c] = 1;

				/*
				if (visit[temp.r][temp.c] > 1)
				{
					if ((temp.r != 0) || (temp.c != 0))
					{
						int debug = 1;
					}	
				}
				*/

				// 좌표 복원
				horseList[i] = temp;
			}
		}
	}

	return;
}

void init(void)
{
	for (int i = 0; i < TURNS; i++)
	{
		selectList[i] = -1;
	}
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);
	// freopen("input3.txt", "r", stdin);
	// freopen("input4.txt", "r", stdin);

	setbuf(stdout, NULL);

	input();

	init();

	run(START_POINT, START_LEVEL);

	printf("%d\n", ans);

	return 0;
}
