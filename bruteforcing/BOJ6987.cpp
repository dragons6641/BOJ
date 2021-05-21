/*
A3 월드컵
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

// 테스트 케이스 갯수
#define MAX_N 4
// 팀 갯수
#define MAX_M 6
#define MAX_VERSUS 2
#define MAX_LEVEL (MAX_M / 2) * (MAX_M - 1)
#define START_NOW 0
#define START_LEVEL 0

struct Node
{
	// 승
	int w;
	// 무
	int d;
	// 패
	int l;
};

struct Football
{
	// 홈팀
	int home;
	// 원정팀
	int away;
	// 승무패 결과
	int result;
};

int cnt = 0;
// 정답인지 아닌지 체크
// 1부터 사용
int ansList[MAX_N + 1] = { 0, };
// 팀 사용 체크
// 1부터 사용
int visit[MAX_M + 1] = { 0, };
// 승무패 결과 표시
// 1 : 홈팀 승
// 0 : 무승부
// -1 : 홈팀 패
// 완전탐색 한 번마다 만드는 결과
// 1부터 사용
Node outputList[MAX_M + 1] = { {0, 0, 0}, };
// 입력으로 주어지는 결과
// 1부터 사용
Node inputList[MAX_N + 1][MAX_M + 1] = { {0, 0, 0,}, };
// 경기 목록 생성
// 1부터 사용
Football matchList[MAX_LEVEL + 1] = { {0, 0, 0}, };

void input(void)
{
	for (int r = 1; r <= MAX_N; r++)
	{
		for (int c = 1; c <= MAX_M; c++)
		{
			scanf("%d %d %d", &inputList[r][c].w, &inputList[r][c].d, &inputList[r][c].l);
		}
	}

	return;
}

// 6개 중 2개 고르기
void makeMatch(int now, int level)
{
	if (level == MAX_VERSUS)
	{
		// 경기 배정 확정
		cnt++;

		return;
	}

	for (int i = now + 1; i <= MAX_M; i++)
	{
		if (visit[i] == 0)
		{
			visit[i] = 1;
			
			// 홈팀은 있고 원정팀이 비어있는 경우
			if (level == 1)
			{
				// 홈팀 먼저 배정
				matchList[cnt + 1].home = now;
				// 원정팀에 배정
				matchList[cnt + 1].away = i;
			}

			// 다음 레벨 탐색
			makeMatch(i, level + 1);

			visit[i] = 0;
		}
	}

	return;
}

void checkAns(void)
{
	for (int r = 1; r <= MAX_N; r++)
	{
		if (ansList[r] == 0)
		{
			// 테스트 케이스 하나마다 체크
			int flag = 0;

			for (int c = 1; c <= MAX_M; c++)
			{
				// 하나라도 다르면
				if ((inputList[r][c].w != outputList[c].w) || (inputList[r][c].d != outputList[c].d) || (inputList[r][c].l != outputList[c].l))
				{
					// 다르다고 표시
					flag = 1;

					break;
				}
			}

			// 모두 같으면
			if (flag == 0)
			{
				// 찾았다고 표시
				ansList[r] = 1;
			}
		}
	}

	return;
}

void run(int level)
{
	if (level == MAX_LEVEL)
	{
		// 일치 확인
		checkAns();

		return;
	}

	// 15경기를 직접 한다
	// 홈팀 승
	matchList[level + 1].result = 1;
	outputList[matchList[level + 1].home].w++;
	outputList[matchList[level + 1].away].l++;

	run(level + 1);

	outputList[matchList[level + 1].home].w--;
	outputList[matchList[level + 1].away].l--;

	// 무승부
	matchList[level + 1].result = 0;
	outputList[matchList[level + 1].home].d++;
	outputList[matchList[level + 1].away].d++;

	run(level + 1);

	outputList[matchList[level + 1].home].d--;
	outputList[matchList[level + 1].away].d--;

	// 홈팀 패
	matchList[level + 1].result = -1;
	outputList[matchList[level + 1].home].l++;
	outputList[matchList[level + 1].away].w++;

	run(level + 1);

	outputList[matchList[level + 1].home].l--;
	outputList[matchList[level + 1].away].w--;

	// 원상 복구
	matchList[level + 1].result = 0;

	return;
}

void print(void)
{
	for (int i = 1; i <= MAX_N; i++)
	{
		printf("%d ", ansList[i]);
	}

	printf("\n");

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	// setbuf(stdout, NULL);

	input();

	// 6C2
	// N과 M
	makeMatch(START_NOW, START_LEVEL);

	run(START_LEVEL);

	print();

	return 0;
}
