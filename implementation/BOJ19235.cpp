/*
19235 모노미노도미노
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 10e4
#define MAX_DIR 4
#define MIN_R 4
#define MIN_C 4
#define MID_R 6
#define MID_C 6
#define MAX_R 10
#define MAX_C 10

int N;
// 총 점수
int score = 0;
// 아랫쪽에 놓인 블록의 갯수
int cntGreen = 0;
// 오른쪽에 놓인 블록의 갯수
int cntBlue = 0;
// 행마다 놓인 갯수 체크
// 쓰는 칸은 6, 7, 8, 9
int cntRowList[MAX_R + 1] = { 0, };
// 열마다 놓인 갯수 체크
// 쓰는 칸은 6, 7, 8, 9
int cntColList[MAX_C + 1] = { 0, };
// 방향 저장
// 상, 하, 좌, 우
int directR[MAX_DIR] = { -1, 1, 0, 0 };
int directC[MAX_DIR] = { 0, 0, -1, 1 };
// 오른쪽과 아래쪽을 Barrier로 채운다!
int map[MAX_R + 1][MAX_C + 1] = { 0, };

void simulate(int turn, int type, int nowR, int nowC)
{
	int dr = 0;
	int dc = 0;

	// 1. 블록 놓기
	// t = 1: 크기가 1×1인 블록을 (x, y)에 놓은 경우
	if (type == 1)
	{
		// 디버깅용
		map[nowR][nowC] = turn;

		// 아래 방향으로 놓기
		for (register int r = MIN_R; r < MAX_R; r++)
		{
			// 다음 칸이 채워져 있는 경우
			if (map[r + 1][nowC] != 0)
			{
				// 블록을 놓는다
				map[r][nowC] = turn;

				// 아래쪽 영역 갯수 증가
				cntGreen += 1;

				// 행, 열마다 갯수 개산
				cntRowList[r] += 1;
				cntColList[nowC] += 1;

				// 이미 놨는데 더 놓으면 안된다
				break;
			}
		}

		// 오른쪽 방향으로 놓기
		for (register int c = MIN_C; c < MAX_C; c++)
		{
			// 다음 칸이 채워져 있는 경우
			if (map[nowR][c + 1] != 0)
			{
				// 블록을 놓는다
				map[nowR][c] = turn;

				// 오른쪽 영역 갯수 증가
				cntBlue += 1;

				// 행, 열마다 갯수 개산
				cntRowList[nowR] += 1;
				cntColList[c] += 1;

				// 이미 놨는데 더 놓으면 안된다
				break;
			}
		}
	}
	// t = 2: 크기가 1×2인 블록을(x, y), (x, y + 1)에 놓은 경우
	else if (type == 2)
	{
		// 디버깅용
		map[nowR][nowC] = turn;
		map[nowR][nowC + 1] = turn;

		// 아래 방향으로 놓기
		for (register int r = MIN_R; r < MAX_R; r++)
		{
			// 다음 두 칸 중 하나라도 차 있을 경우
			if ((map[r + 1][nowC] != 0) || (map[r + 1][nowC + 1] != 0))
			{
				// 블록을 놓는다
				map[r][nowC] = turn;
				map[r][nowC + 1] = turn;

				// 아래쪽 영역 갯수 증가
				cntGreen += 2;

				// 행, 열마다 갯수 개산
				cntRowList[r] += 2;
				cntColList[nowC] += 1;
				cntColList[nowC + 1] += 1;

				// 이미 놨는데 더 놓으면 안된다
				break;
			}
		}

		// 오른쪽 방향으로 놓기
		for (register int c = MIN_C; c < MAX_C - 1; c++)
		{
			// 다음 칸이 채워져 있는 경우
			if (map[nowR][c + 2] != 0)
			{
				// 블록을 놓는다
				map[nowR][c] = turn;
				map[nowR][c + 1] = turn;

				// 오른쪽 영역 갯수 증가
				cntBlue += 2;

				// 행, 열마다 갯수 개산
				cntRowList[nowR] += 2;
				cntColList[c] += 1;
				cntColList[c + 1] += 1;

				// 이미 놨는데 더 놓으면 안된다
				break;
			}
		}
	}
	// t = 3: 크기가 2×1인 블록을(x, y), (x + 1, y)에 놓은 경우
	else if (type == 3)
	{
		// 디버깅용
		map[nowR][nowC] = turn;
		map[nowR + 1][nowC] = turn;

		// 아래 방향으로 놓기
		for (register int r = MIN_R; r < MAX_R - 1; r++)
		{
			// 다음 칸이 채워져 있는 경우
			if (map[r + 2][nowC] != 0)
			{
				// 블록을 놓는다
				map[r][nowC] = turn;
				map[r + 1][nowC] = turn;

				// 아래쪽 영역 갯수 증가
				cntGreen += 2;

				// 행, 열마다 갯수 개산
				cntRowList[r] += 1;
				cntRowList[r + 1] += 1;
				cntColList[nowC] += 2;

				// 이미 놨는데 더 놓으면 안된다
				break;
			}
		}

		// 오른쪽 방향으로 놓기
		for (register int c = MIN_C; c < MAX_C; c++)
		{
			// 다음 두 칸 중 하나라도 차 있을 경우
			if ((map[nowR][c + 1] != 0) || (map[nowR + 1][c + 1] != 0))
			{
				// 블록을 놓는다
				map[nowR][c] = turn;
				map[nowR + 1][c] = turn;

				// 오른쪽 영역 갯수 증가
				cntBlue += 2;

				// 행, 열마다 갯수 개산
				cntRowList[nowR] += 1;
				cntRowList[nowR + 1] += 1;
				cntColList[c] += 2;

				// 이미 놨는데 더 놓으면 안된다
				break;
			}
		}
	}

	int debug = 1;

	while (true)
	{
		int flag1 = 0;

		// 2. 타일 지우기
		// 초록색 영역(row) 확인
		for (register int r = MID_R; r < MAX_R; r++)
		{
			// row 하나가 꽉 찼다면
			if (cntRowList[r] == MIN_C)
			{
				flag1 = 1;

				// 일단 지운다
				for (register int c = 0; c < MIN_C; c++)
				{
					map[r][c] = 0;
					cntColList[c]--;
				}

				cntRowList[r] = 0;
				// 초록색 영역 갯수 갱신
				cntGreen -= MIN_C;
				// 점수 추가
				score++;
			}
		}

		// 더 안해도 되면
		if (flag1 == 0)
		{
			// 그만하자!
			break;
		}

		// 3. 중력
		// 내려와서 계속 점수 얻는 경우 있다!
		// 초록색 영역(row) 확인
		// 중력 적용
		// 아래쪽부터 row 탐색
		for (register int r = MAX_R - 2; r >= MIN_R; r--)
		{
			// 왼쪽부터 col 탐색
			for (register int c = 0; c < MIN_C; c++)
			{
				// 현재 칸은 차있는데 아랫쪽 칸이 비어있는 경우
				if ((map[r][c] > 0) && (map[r + 1][c] == 0))
				{
					int flag2 = 0;
					int targetR = 0;

					// 4방향 탐색
					for (register int d = 0; d < MAX_DIR; d++)
					{
						int dr = r + directR[d];
						int dc = c + directC[d];

						// 범위를 벗어나면
						if ((dr < MIN_R) || (dc < 0) || (dr >= MAX_R) || (dc >= MIN_C))
						{
							// 해당사항 없음
							continue;
						}

						// 인접 칸에 같은 블록이 있다면
						if (map[dr][dc] == map[r][c])
						{
							// 중력 이미 적용했다고 표시
							flag2 = 1;

							// 같이 움직여 준다
							// 0 : 위에 있을 경우
							if (d == 0)
							{
								// 이동할 곳 탐색
								for (int tmpR = r; tmpR < MAX_R; tmpR++)
								{
									// 아랫 칸이 차있을 경우
									if (map[tmpR + 1][c] != 0)
									{
										// 그곳으로 내려줘야 한다
										targetR = tmpR;

										break;
									}
								}

								// 움직이지 않는 경우
								if (targetR == r)
								{
									// 이동할 필요 없음
									continue;
								}
								// 한 칸만 내려오는 경우
								else if (targetR - 1 == r)
								{
									// 하나만 이동
									map[targetR][c] = map[r - 1][c];
									map[r - 1][c] = 0;

									// 정보 갱신
									cntRowList[targetR] += 1;
									cntRowList[r - 1] -= 1;
								}
								// 일반적인 경우
								else
								{
									// 두 개 모두 이동
									map[targetR][c] = map[r][c];
									map[targetR - 1][c] = map[r - 1][c];
									map[r][c] = 0;
									map[r - 1][c] = 0;

									// 정보 갱신
									cntRowList[targetR] += 1;
									cntRowList[targetR - 1] += 1;
									cntRowList[r] -= 1;
									cntRowList[r - 1] -= 1;
								}
							}
							// 2 : 왼쪽에 있을 경우
							// 3 : 오른쪽에 있을 경우
							else if (d != 1)
							{
								// 같이 내려와야 한다
								// 이동할 곳 탐색
								for (int tmpR = r; tmpR < MAX_R; tmpR++)
								{
									// 아랫 칸이 차있을 경우
									// 둘 중 하나라도 해당하면
									if ((map[tmpR + 1][c] != 0) || (map[tmpR + 1][dc] != 0))
									{
										// 그곳으로 내려줘야 한다
										targetR = tmpR;

										break;
									}
								}

								// 움직이지 않는 경우
								if (targetR == r)
								{
									// 이동할 필요 없음
									continue;
								}

								// 하나만 이동
								map[targetR][c] = map[r][c];
								map[r][c] = 0;
								map[targetR][dc] = map[r][dc];
								map[r][dc] = 0;

								// 정보 갱신
								cntRowList[targetR] += 2;
								cntRowList[r] -= 2;
							}

							break;
						}
					}

					// 1 * 1짜리 처리
					if (flag2 == 0)
					{
						// 이동할 곳 탐색
						for (int tmpR = r; tmpR < MAX_R; tmpR++)
						{
							// 아랫 칸이 차있을 경우
							if (map[tmpR + 1][c] != 0)
							{
								// 그곳으로 내려줘야 한다
								targetR = tmpR;

								break;
							}
						}

						// 움직이지 않는 경우
						if (targetR == r)
						{
							// 이동할 필요 없음
							continue;
						}

						// 하나만 이동
						map[targetR][c] = map[r][c];
						map[r][c] = 0;

						// 정보 갱신
						cntRowList[targetR] += 1;
						cntRowList[r] -= 1;
					}
				}
			}
		}
	}

	while (true)
	{
		int flag1 = 0;

		// 2. 타일 지우기
		// 파란색 영역(col) 확인
		for (register int c = MID_C; c < MAX_C; c++)
		{
			// col 하나가 꽉 찼다면
			if (cntColList[c] == MIN_R)
			{
				flag1 = 1;

				// 일단 지운다
				for (register int r = 0; r < MIN_R; r++)
				{
					map[r][c] = 0;
					cntRowList[r]--;
				}

				cntColList[c] = 0;
				// 파란색 영역 갯수 갱신
				cntBlue -= MIN_R;
				// 점수 추가
				score++;
			}
		}

		// 더 안해도 되면
		if (flag1 == 0)
		{
			// 그만하자!
			break;
		}

		// 3. 중력
		// 내려와서 계속 점수 얻는 경우 있다!
		// 파란색 영역(col) 확인
		// 중력 적용
		// 오른쪽부터 col 탐색
		for (register int c = MAX_C - 2; c >= MIN_C; c--)
		{
			// 위쪽부터 row 탐색
			for (register int r = 0; r < MIN_R; r++)
			{
				// 현재 칸은 차있는데 오른쪽 칸이 비어있는 경우
				if ((map[r][c] > 0) && (map[r][c + 1] == 0))
				{
					int flag2 = 0;
					int targetC = 0;

					// 4방향 탐색
					for (register int d = 0; d < MAX_DIR; d++)
					{
						int dr = r + directR[d];
						int dc = c + directC[d];

						// 범위를 벗어나면
						if ((dr < 0) || (dc < MIN_C) || (dr >= MIN_R) || (dc >= MAX_C))
						{
							// 해당사항 없음
							continue;
						}

						// 인접 칸에 같은 블록이 있다면
						if (map[dr][dc] == map[r][c])
						{
							// 중력 이미 적용했다고 표시
							flag2 = 1;

							// 같이 움직여 준다
							// 2 : 왼쪽에 있을 경우
							if (d == 2)
							{
								// 이동할 곳 탐색
								for (int tmpC = c; tmpC < MAX_C; tmpC++)
								{
									// 오른쪽 칸이 차있을 경우
									if (map[r][tmpC + 1] != 0)
									{
										// 그곳으로 내려줘야 한다
										targetC = tmpC;

										break;
									}
								}

								// 움직이지 않는 경우
								if (targetC == c)
								{
									// 이동할 필요 없음
									continue;
								}
								// 한 칸만 오른쪽으로 오는 경우
								else if (targetC - 1 == c)
								{
									// 하나만 이동
									map[r][targetC] = map[r][c - 1];
									map[r][c - 1] = 0;

									// 정보 갱신
									cntColList[targetC] += 1;
									cntColList[c - 1] -= 1;
								}
								// 일반적인 경우
								else
								{
									// 두 개 모두 이동
									map[r][targetC] = map[r][c];
									map[r][targetC - 1] = map[r][c - 1];
									map[r][c] = 0;
									map[r][c - 1] = 0;

									// 정보 갱신
									cntColList[targetC] += 1;
									cntColList[targetC - 1] += 1;
									cntColList[c] -= 1;
									cntColList[c - 1] -= 1;
								}
							}
							// 0 : 위쪽에 있을 경우
							// 1 : 아래쪽에 있을 경우
							else if (d != 3)
							{
								// 같이 내려와야 한다
								// 이동할 곳 탐색
								for (int tmpC = c; tmpC < MAX_C; tmpC++)
								{
									// 오른쪽 칸이 차있을 경우
									// 둘 중 하나라도 해당하면
									if ((map[r][tmpC + 1] != 0) || (map[dr][tmpC + 1] != 0))
									{
										// 그곳으로 내려줘야 한다
										targetC = tmpC;

										break;
									}
								}

								// 움직이지 않는 경우
								if (targetC == c)
								{
									// 이동할 필요 없음
									continue;
								}

								// 하나만 이동
								map[r][targetC] = map[r][c];
								map[r][c] = 0;
								map[dr][targetC] = map[dr][c];
								map[dr][c] = 0;

								// 정보 갱신
								cntColList[targetC] += 2;
								cntColList[c] -= 2;
							}

							break;
						}
					}

					// 1 * 1짜리 처리
					if (flag2 == 0)
					{
						// 이동할 곳 탐색
						for (int tmpC = c; tmpC < MAX_C; tmpC++)
						{
							// 현재 칸은 없고 오른쪽 이 차있을 경우
							if (map[r][tmpC + 1] != 0)
							{
								// 그곳으로 내려줘야 한다
								targetC = tmpC;

								break;
							}
						}

						// 움직이지 않는 경우
						if (targetC == c)
						{
							// 이동할 필요 없음
							continue;
						}

						// 하나만 이동
						map[r][targetC] = map[r][c];
						map[r][c] = 0;

						// 정보 갱신
						cntColList[targetC] += 1;
						cntColList[c] -= 1;
					}
				}
			}
		}
	}

	// 4. 스페셜 블록
	// 초록색 영역(row) 확인
	for (register int r = MIN_R; r < MID_R; r++)
	{
		// 블럭이 들어왔다면
		if (cntRowList[r] > 0)
		{
			// 일단 이동량만 계산
			dr = MID_R - r;

			// 이미 이동했으니 더 이동하면 안된다
			break;
		}
	}

	// 초록색 영역 이동
	if (dr > 0)
	{
		// 전처리
		for (register int r = MAX_R - dr; r < MAX_R; r++)
		{
			cntGreen -= cntRowList[r];

			for (register int c = 0; c < MIN_C; c++)
			{
				if (map[r][c] > 0)
				{
					cntColList[c]--;
				}
			}
		}

		// 이동
		for (register int r = MAX_R - 1; r >= MIN_R + dr; r--)
		{
			for (register int c = 0; c < MIN_C; c++)
			{
				map[r][c] = map[r - dr][c];
			}

			cntRowList[r] = cntRowList[r - dr];
		}

		// 후처리
		for (register int r = MID_R - dr; r < MID_R; r++)
		{
			for (register int c = 0; c < MIN_C; c++)
			{
				map[r][c] = 0;
			}

			cntRowList[r] = 0;
		}
	}

	// 파란색 영역(col) 확인
	for (register int c = MIN_C; c < MID_C; c++)
	{
		// 블럭이 들어왔다면
		if (cntColList[c] > 0)
		{
			// 일단 이동량만 계산
			dc = MID_C - c;

			// 이미 이동했으니 더 이동하면 안된다
			break;
		}
	}

	// 파란색 영역 이동
	if (dc > 0)
	{
		// 전처리
		for (register int c = MAX_C - dc; c < MAX_C; c++)
		{
			cntBlue -= cntColList[c];

			for (register int r = 0; r < MIN_R; r++)
			{
				if (map[r][c] > 0)
				{
					cntRowList[r]--;
				}
			}
		}

		// 이동
		for (register int c = MAX_C - 1; c >= MIN_C + dc; c--)
		{
			for (register int r = 0; r < MIN_R; r++)
			{
				map[r][c] = map[r][c - dc];
			}

			cntColList[c] = cntColList[c - dc];
		}

		// 후처리
		for (register int c = MID_C - dc; c < MID_C; c++)
		{
			for (register int r = 0; r < MIN_R; r++)
			{
				map[r][c] = 0;
			}

			cntColList[c] = 0;
		}
	}

	return;
}

void init(void)
{
	for (register int r = 0; r < MAX_R; r++)
	{
		map[r][MAX_C] = -1;
	}

	for (register int c = 0; c < MAX_C; c++)
	{
		map[MAX_R][c] = -1;
	}

	map[MAX_R][MAX_C] = -1;

	return;
}

void input(void)
{
	int T;
	int R;
	int C;

	scanf("%d", &N);

	for (register int i = 1; i <= N; i++)
	{
		scanf("%d %d %d", &T, &R, &C);

		simulate(i, T, R, C);

		int debug = 1;
	}

	return;
}

void print(void)
{
	printf("%d\n", score);
	printf("%d\n", (cntGreen + cntBlue));

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);	// 0 2
	// freopen("input2.txt", "r", stdin);	// 0 6
	// freopen("input3.txt", "r", stdin);	// 1 10
	// freopen("input4.txt", "r", stdin);	// 1 12
	// freopen("input5.txt", "r", stdin);	// 1 16
	// freopen("input6.txt", "r", stdin);	// 1 18
	// freopen("input7.txt", "r", stdin);	// 3 11
	// freopen("input8.txt", "r", stdin);	// 6 10
	// freopen("input9.txt", "r", stdin);	// 2 11
	// freopen("input10.txt", "r", stdin);	// 1 12
	// freopen("input11.txt", "r", stdin);	// 4 12
	// freopen("input12.txt", "r", stdin);	// 1 16
	// freopen("input13.txt", "r", stdin);	// 1 13

	init();

	input();

	print();

	return 0;
}
