/*
17822 원판 돌리기
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_R 50
#define MAX_C 50
#define MAX_T 50
#define MAX_X MAX_R
#define MAX_K MAX_C
#define MAX_DIR 4

struct Node
{
	int x;
	int d;
	int k;
};

int N;
int M;
int T;
int flag = 0;
int directR[MAX_DIR] = { -1, 1, 0, 0 };
int directC[MAX_DIR] = { 0, 0, -1, 1 };
// 1부터 사용
int map[MAX_R + 1][MAX_C + 1] = { 0, };
// 1부터 사용
int checkMap[MAX_R + 1][MAX_C + 1] = { 0, };
// 평균은 소수점!
// double totalAvg = 0.0;
int totalSum = 0;
int totalCnt = 0;
// 1부터 사용
Node cmdList[MAX_T + 1] = { {0, 0, 0}, };

void input(void)
{
	scanf("%d %d %d", &N, &M, &T);

	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= M; c++)
		{
			scanf("%d", &map[r][c]);

			totalSum += map[r][c];
			totalCnt += 1;
		}
	}

	/*
	// 디버그 시 소수로 제대로 나오는지 확인
	if (totalCnt == 0.0)
	{
		totalAvg = 0.0;
	}
	else
	{
		totalAvg = totalSum / totalCnt;	
	}
	*/

	for (int i = 1; i <= T; i++)
	{
		scanf("%d %d %d", &cmdList[i].x, &cmdList[i].d, &cmdList[i].k);
	}

	return;
}

// now번째 원판을 시계방향으로 회전
void clockwise(int now)
{
	int temp = map[now][M];

	for (int c = M; c > 1; c--)
	{
		map[now][c] = map[now][c - 1];
	}

	map[now][1] = temp;

	return;
}

// now번째 원판을 반시계방향으로 회전
void counterclockwise(int now)
{
	int temp = map[now][1];

	for (int c = 1; c < M; c++)
	{
		map[now][c] = map[now][c + 1];
	}

	map[now][M] = temp;

	return;
}

// (r, c) 칸의 수 기준 인접 여부 확인
void checkAdj(int nowR, int nowC)
{
	// for (int d = 0; d < MAX_DIR; d++)
	for (int d = 1; d < MAX_DIR; d += 2)
	{
		int dr = nowR + directR[d];
		int dc = nowC + directC[d];

		// row check
		if ((dr < 1) || (dr > N))
		{
			continue;
		}
		// col check
		else if (dc == 0)
		{
			dc = M;
		}
		// col check
		else if (dc == M + 1)
		{
			dc = 1;
		}

		// 0은 체크할 필요 없다!
		if (map[dr][dc] == 0)
		{
			continue;
		}

		// 인접한 수가 같으면 표시
		if (map[nowR][nowC] == map[dr][dc])
		{
			checkMap[nowR][nowC] = 1;
			checkMap[dr][dc] = 1;
			flag = 1;
		}
	}

	return;
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
	// freopen("input11.txt", "r", stdin);
	// freopen("input12.txt", "r", stdin);

	setbuf(stdout, NULL);

	input();

	// 1. 회전
	for (int i = 1; i <= T; i++)
	{
		if (totalCnt == 0)
		{
			totalSum = 0;

			break;
		}

		flag = 0;

		// a번째 원판을
		for (int a = cmdList[i].x; a <= N; a += cmdList[i].x)
		{
			// 시계방향으로
			if (cmdList[i].d == 0)
			{
				// b만큼 회전
				for (int b = 1; b <= cmdList[i].k; b++)
				{
					clockwise(a);
				}
			}
			// 반시계방향으로
			else if (cmdList[i].d == 1)
			{
				// b만큼 회전
				for (int b = 1; b <= cmdList[i].k; b++)
				{
					counterclockwise(a);
				}
			}
		}

		// 2. 인접 체크
		for (int r = 1; r <= N; r++)
		{
			for (int c = 1; c <= M; c++)
			{
				// 이미 지운 수는 체크할 필요 없다!
				if (map[r][c] > 0)
				{
					checkAdj(r, c);
				}
			}
		}

		// 2-1. 삭제
		if (flag == 1)
		{
			for (int r = 1; r <= N; r++)
			{
				for (int c = 1; c <= M; c++)
				{
					// 인접한 것 확인 되었다면
					if (checkMap[r][c] == 1)
					{
						// 평균부터 먼저 계산
						totalSum -= map[r][c];
						totalCnt -= 1;

						// 삭제해주고 초기화
						map[r][c] = 0;
						checkMap[r][c] = 0;
					}
				}
			}
		}
		// 2-2. 평균
		else
		{
			/*
			// 디버그 시 소수로 제대로 나오는지 확인
			if (totalCnt == 0.0)
			{
				totalAvg = 0.0;
			}
			else
			{
				totalAvg = totalSum / totalCnt;
			}
			*/

			int tempSum = totalSum;

			for (int r = 1; r <= N; r++)
			{
				for (int c = 1; c <= M; c++)
				{
					// 0이 아닌 경우에 한해서
					if (map[r][c] > 0)
					{
						// 평균보다 클 경우
						// if (map[r][c] > totalAvg)
						if (map[r][c] * totalCnt > tempSum)
						{
							// 1을 빼준다
							map[r][c]--;
							totalSum -= 1;
						}
						// 평균보다 작을 경우
						// else if (map[r][c] < totalAvg)
						else if (map[r][c] * totalCnt < tempSum)
						{
							// 1을 더한다
							map[r][c]++;
							totalSum += 1;
						}
					}
				}
			}
		}

		// int debug = 1;
	}

	// printf("%d\n", (int)(totalSum));
	printf("%d\n", totalSum);

	return 0;
}
