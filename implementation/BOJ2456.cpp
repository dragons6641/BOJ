/*
A5 나는 학급회장이다
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 1000
#define MAX_CANDIDATE 3
#define MAX_POINT 3

int comparePoint(int a, int b, int c)
{
	if (a > b)
	{
		return c;
	}
	else if (a < b)
	{
		return -c;
	}
	
	return 0;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);
	// freopen("input3.txt", "r", stdin);
	// freopen("input4.txt", "r", stdin);
	// freopen("input5.txt", "r", stdin);
	// freopen("input6.txt", "r", stdin);

	setbuf(stdout, NULL);

	int N;
	int ret = 0;
	int maxPoint = 0;
	int maxCnt = 0;
	// 1부터 사용
	int topList[MAX_CANDIDATE + 1] = { 0, };
	// 1부터 사용
	int pointList[MAX_CANDIDATE + 1][MAX_POINT + 1] = { 0, };
	// 1부터 사용
	int inputList[MAX_N + 1][MAX_CANDIDATE + 1] = { 0, };

	scanf("%d", &N);

	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= MAX_CANDIDATE; c++)
		{
			scanf("%d", &inputList[r][c]);

			pointList[c][0] += inputList[r][c];
			pointList[c][inputList[r][c]]++;

			// int debug = 1;
		}

		// int debug = 1;
	}

	// 1. 전체 점수로 비교
	ret += comparePoint(pointList[1][0], pointList[2][0], 1);
	ret += comparePoint(pointList[1][0], pointList[3][0], 10);
	ret += comparePoint(pointList[2][0], pointList[3][0], 100);

	// int debug = 1;

	// 1 < 2 < 3
	if (ret == -111)
	{
		// 3이 1등
		printf("3 %d\n", pointList[3][0]);

		return 0;
	}
	// 1 < 3 < 2
	else if (ret == 89)
	{
		// 2가 1등
		printf("2 %d\n", pointList[2][0]);

		return 0;
	}
	// 2 < 1 < 3
	else if (ret == -109)
	{
		// 3이 1등
		printf("3 %d\n", pointList[3][0]);

		return 0;
	}
	// 2 < 3 < 1
	else if (ret == -89)
	{
		// 1이 1등
		printf("1 %d\n", pointList[1][0]);

		return 0;
	}
	// 3 < 1 < 2
	else if (ret == 109)
	{
		// 2가 1등
		printf("2 %d\n", pointList[2][0]);

		return 0;
	}
	// 3 < 2 < 1
	else if (ret == 111)
	{
		// 1이 1등
		printf("1 %d\n", pointList[1][0]);

		return 0;
	}
	// 1 = 2 < 3
	else if (ret == -110)
	{
		// 3이 1등
		printf("3 %d\n", pointList[3][0]);

		return 0;
	}
	// 1 = 3 < 2
	else if (ret == 99)
	{
		// 2가 1등
		printf("2 %d\n", pointList[2][0]);

		return 0;
	}
	// 2 = 3 < 1
	else if (ret == 11)
	{
		// 1이 1등
		printf("1 %d\n", pointList[1][0]);

		return 0;
	}
	// 1 = 2 > 3
	else if (ret == 110)
	{
		// 2. 3점으로 비교
		ret = comparePoint(pointList[1][3], pointList[2][3], 1);

		// 1 > 2 > 3
		if (ret > 0)
		{
			// 1이 1등
			printf("1 %d\n", pointList[1][0]);

			return 0;
		}
		// 2 > 1 > 3
		else if (ret < 0)
		{
			// 2가 1등
			printf("2 %d\n", pointList[2][0]);

			return 0;
		}
		// 1 = 2 > 3
		else
		{
			// 3. 2점으로 비교
			ret = comparePoint(pointList[1][2], pointList[2][2], 1);

			// 1 > 2 > 3
			if (ret > 0)
			{
				// 1이 1등
				printf("1 %d\n", pointList[1][0]);

				return 0;
			}
			// 2 > 1 > 3
			else if (ret < 0)
			{
				// 2가 1등
				printf("2 %d\n", pointList[2][0]);

				return 0;
			}
			// 1 = 2 > 3
			else
			{
				// 판별 불가
				printf("0 %d\n", pointList[1][0]);
			}
		}
	}
	// 1 = 3 > 2
	else if (ret == -99)
	{
		// 2. 3점으로 비교
		ret = comparePoint(pointList[1][3], pointList[3][3], 10);

		// 1 > 3 > 2
		if (ret > 0)
		{
			// 1이 1등
			printf("1 %d\n", pointList[1][0]);

			return 0;
		}
		// 3 > 1 > 2
		else if (ret < 0)
		{
			// 3이 1등
			printf("3 %d\n", pointList[3][0]);

			return 0;
		}
		// 1 = 3 > 2
		else
		{
			// 3. 2점으로 비교
			ret = comparePoint(pointList[1][2], pointList[3][2], 10);

			// 1 > 3 > 2
			if (ret > 0)
			{
				// 1이 1등
				printf("1 %d\n", pointList[1][0]);

				return 0;
			}
			// 3 > 1 > 2
			else if (ret < 0)
			{
				// 3이 1등
				printf("3 %d\n", pointList[3][0]);

				return 0;
			}
			// 1 = 3 > 2
			else
			{
				// 판별 불가
				printf("0 %d\n", pointList[3][0]);
			}
		}
	}
	// 2 = 3 > 1
	else if (ret == -11)
	{
		// 2. 3점으로 비교
		ret = comparePoint(pointList[2][3], pointList[3][3], 100);

		// 2 > 3 > 1
		if (ret > 0)
		{
			// 2가 1등
			printf("2 %d\n", pointList[2][0]);

			return 0;
		}
		// 3 > 2 > 1
		else if (ret < 0)
		{
			// 3이 1등
			printf("3 %d\n", pointList[3][0]);

			return 0;
		}
		// 2 = 3 > 1
		else
		{
			// 3. 2점으로 비교
			ret = comparePoint(pointList[2][2], pointList[3][2], 10);

			// 2 > 3 > 1
			if (ret > 0)
			{
				// 2가 1등
				printf("2 %d\n", pointList[2][0]);

				return 0;
			}
			// 3 > 2 > 1
			else if (ret < 0)
			{
				// 3이 1등
				printf("3 %d\n", pointList[3][0]);

				return 0;
			}
			// 2 = 3 > 1
			else
			{
				// 판별 불가
				printf("0 %d\n", pointList[2][0]);
			}
		}
	}
	// 1 = 2 = 3
	else
	{
		// 2. 3점으로 비교
		ret += comparePoint(pointList[1][3], pointList[2][3], 1);
		ret += comparePoint(pointList[1][3], pointList[3][3], 10);
		ret += comparePoint(pointList[2][3], pointList[3][3], 100);

		// 1 < 2 < 3
		if (ret == -111)
		{
			// 3이 1등
			printf("3 %d\n", pointList[3][0]);

			return 0;
		}
		// 1 < 3 < 2
		else if (ret == 89)
		{
			// 2가 1등
			printf("2 %d\n", pointList[2][0]);

			return 0;
		}
		// 2 < 1 < 3
		else if (ret == -109)
		{
			// 3이 1등
			printf("3 %d\n", pointList[3][0]);

			return 0;
		}
		// 2 < 3 < 1
		else if (ret == -89)
		{
			// 1이 1등
			printf("1 %d\n", pointList[1][0]);

			return 0;
		}
		// 3 < 1 < 2
		else if (ret == 109)
		{
			// 2가 1등
			printf("2 %d\n", pointList[2][0]);

			return 0;
		}
		// 3 < 2 < 1
		else if (ret == 111)
		{
			// 1이 1등
			printf("1 %d\n", pointList[1][0]);

			return 0;
		}
		// 1 = 2 < 3
		else if (ret == -110)
		{
			// 3이 1등
			printf("3 %d\n", pointList[3][0]);

			return 0;
		}
		// 1 = 3 < 2
		else if (ret == 99)
		{
			// 2가 1등
			printf("2 %d\n", pointList[2][0]);

			return 0;
		}
		// 2 = 3 < 1
		else if (ret == 11)
		{
			// 1이 1등
			printf("1 %d\n", pointList[1][0]);

			return 0;
		}
		// 여기로 오면 점수가 모두 같다!
		else
		{
			// 판별 불가
			printf("0 %d\n", pointList[2][0]);
		}
	}

	/*
	int x = 20;
	int y = 20;
	int z = 20;

	ret += comparePoint(x, y, 1);
	ret += comparePoint(x, z, 10);
	ret += comparePoint(y, z, 100);

	printf("%d\n", ret);
	*/

	/*
	// 3명 모두 동점일 경우
	if ((pointList[1][0] == pointList[2][0]) && (pointList[2][0] == pointList[3][0]))
	{
		// 1 > 2
		if (pointList[1][3] > pointList[2][3])
		{
			// 1 > 3
			if (pointList[1][3] > pointList[3][3])
			{
				// 1등 출력
				printf("1 %d\n", pointList[1][0]);
			}
			// 3 > 1
			else if (pointList[1][3] < pointList[3][3])
			{
				// 1등 출력
				printf("3 %d\n", pointList[3][0]);
			}
			// 1 == 3
			else
			{
				// 1 > 3
				if (pointList[1][2] > pointList[3][2])
				{
					// 1등 출력
					printf("1 %d\n", pointList[1][0]);
				}
				// 3 > 1
				else if (pointList[1][2] < pointList[3][2])
				{
					// 1등 출력
					printf("3 %d\n", pointList[3][0]);
				}
				// 1 == 3
				else
				{
					// 불가능
					printf("0 %d\n", pointList[1][0]);
				}
			}
		}
		// 1 < 2
		else if (pointList[1][3] > pointList[2][3])
		{
			// 2 > 3
			if (pointList[2][3] > pointList[3][3])
			{
				// 1등 출력
				printf("2 %d\n", pointList[2][0]);
			}
			// 3 > 2
			else if (pointList[2][3] < pointList[3][3])
			{
				// 1등 출력
				printf("3 %d\n", pointList[3][0]);
			}
			// 2 == 3
			else
			{
				// 2 > 3
				if (pointList[2][2] > pointList[2][2])
				{
					// 1등 출력
					printf("2 %d\n", pointList[2][0]);
				}
				// 3 > 1
				else if (pointList[2][2] < pointList[3][2])
				{
					// 1등 출력
					printf("3 %d\n", pointList[3][0]);
				}
				// 2 == 3
				else
				{
					// 불가능
					printf("0 %d\n", pointList[2][0]);
				}
			}
		}
		// 1 == 2
	}
	// 1, 2만 동점일 경우
	else if (pointList[1][0] == pointList[2][0])
	{
		// 3이 1등이면
		if (pointList[3][0] > pointList[1][0])
		{
			// 1등 출력
			printf("3 %d\n", pointList[3][0]);
		}
		// 3이 꼴등이면
		else
		{
			// 1이 3점 더 많으면
			if (pointList[1][3] > pointList[2][3])
			{
				// 1등 출력
				printf("1 %d\n", pointList[1][0]);
			}
			// 2가 3점 더 많으면
			else if (pointList[1][3] < pointList[2][3])
			{
				// 1등 출력
				printf("2 %d\n", pointList[2][0]);
			}
			// 3점 똑같으면
			else
			{
				// 1이 2점 더 많으면
				if (pointList[1][2] > pointList[2][2])
				{
					// 1등 출력
					printf("1 %d\n", pointList[1][0]);
				}
				// 2가 2점 더 많으면
				else if (pointList[1][2] < pointList[2][2])
				{
					// 1등 출력
					printf("2 %d\n", pointList[2][0]);
				}
				// 2점 똑같으면
				else
				{
					// 불가능
					printf("0 %d\n", pointList[1][0]);
				}
			}
		}
	}
	// 1, 3만 동점일 경우
	else if (pointList[1][0] == pointList[3][0])
	{
		// 2가 1등이면
		if (pointList[2][0] > pointList[3][0])
		{
			// 1등 출력
			printf("2 %d\n", pointList[2][0]);
		}
		// 2가 꼴등이면
		else
		{
			// 1이 3점 더 많으면
			if (pointList[1][3] > pointList[3][3])
			{
				// 1등 출력
				printf("1 %d\n", pointList[1][0]);
			}
			// 3이 3점 더 많으면
			else if (pointList[1][3] < pointList[3][3])
			{
				// 1등 출력
				printf("3 %d\n", pointList[3][0]);
			}
			// 3점 똑같으면
			else
			{
				// 1이 2점 더 많으면
				if (pointList[1][2] > pointList[3][2])
				{
					// 1등 출력
					printf("1 %d\n", pointList[1][0]);
				}
				// 3이 2점 더 많으면
				else if (pointList[1][2] < pointList[3][2])
				{
					// 1등 출력
					printf("3 %d\n", pointList[3][0]);
				}
				// 2점 똑같으면
				else
				{
					// 불가능
					printf("0 %d\n", pointList[3][0]);
				}
			}
		}
	}
	// 2, 3만 동점일 경우
	else if (pointList[2][0] == pointList[3][0])
	{
		// 1이 1등이면
		if (pointList[1][0] > pointList[2][0])
		{
			// 1등 출력
			printf("1 %d\n", pointList[1][0]);
		}
		// 1이 꼴등이면
		else
		{
			// 2가 3점 더 많으면
			if (pointList[2][3] > pointList[3][3])
			{
				// 1등 출력
				printf("2 %d\n", pointList[2][0]);
			}
			// 3이 3점 더 많으면
			else if (pointList[2][3] < pointList[3][3])
			{
				// 1등 출력
				printf("3 %d\n", pointList[3][0]);
			}
			// 3점 똑같으면
			else
			{
				// 2가 2점 더 많으면
				if (pointList[2][2] > pointList[3][2])
				{
					// 1등 출력
					printf("2 %d\n", pointList[2][0]);
				}
				// 3이 2점 더 많으면
				else if (pointList[2][2] < pointList[3][2])
				{
					// 1등 출력
					printf("3 %d\n", pointList[3][0]);
				}
				// 2점 똑같으면
				else
				{
					// 불가능
					printf("0 %d\n", pointList[2][0]);
				}
			}
		}
	}
	// 모두 다르고 1 > 2
	else if (pointList[1][0] > pointList[2][0])
	{
		// 1 > 3
		if (pointList[1][0] > pointList[3][0])
		{
			// 1 > 2?3
			printf("1 %d\n", pointList[1][0]);
		}
		// 3 > 1
		else
		{
			// 3 > 1 > 2
			printf("3 %d\n", pointList[3][0]);
		}
	}
	// 모두 다르고 2 > 1
	else
	{
		// 1 > 3
		if (pointList[1][0] > pointList[3][0])
		{
			// 2 > 1 > 3
			printf("2 %d\n", pointList[2][0]);
		}
		// 3 > 1
		else
		{
			// 2 > 3
			if (pointList[2][0] > pointList[3][0])
			{
				// 2 > 3 > 1
				printf("2 %d\n", pointList[2][0]);
			}
			// 3 > 2
			else
			{
				// 3 > 2 > 1
				printf("3 %d\n", pointList[3][0]);
			}
		}
	}

	// int debug = 1;
	*/

	/*
	int N;
	int A;
	int B;
	int C;
	int maxPoint = 0;
	int maxCnt = 0;
	int max3Point = 0;
	int max3Cnt = 0;
	int max2Point = 0;
	int max2Cnt = 0;
	// 1부터 시작
	int topList[MAX_CANDIDATE + 1] = { 0, };
	int top3List[MAX_CANDIDATE + 1] = { 0, };
	int top2List[MAX_CANDIDATE + 1] = { 0, };
	// 1부터 시작
	int map[MAX_CANDIDATE + 1][MAX_POINT + 1] = { 0, };
	
	scanf("%d", &N);

	// 점수 입력
	for (int i = 0; i < N; i++)
	{
		scanf("%d %d %d", &C, &B, &A);

		map[A][1]++;
		map[B][2]++;
		map[C][3]++;

		map[A][0] += 1;
		map[B][0] += 2;
		map[C][0] += 3;
	}

	// 최고 점수 확인
	for (int i = 1; i <= MAX_CANDIDATE; i++)
	{
		if (maxPoint < map[i][0])
		{
			maxPoint = map[i][0];
			maxCnt = 0;
			topList[++maxCnt] = i;
		}
		else if (maxPoint == map[i][0])
		{
			topList[++maxCnt] = i;
		}
	}

	// 동점자 처리
	// 혼자 1등일 경우
	if (maxCnt == 1)
	{
		printf("%d %d\n", topList[maxCnt], maxPoint);
	}
	// 동점자 있을 경우
	else
	{
		// 3점 비교
		for (int i = 1; i <= maxCnt; i++)
		{
			if (max3Point < map[i][3])
			{
				max3Point = map[i][3];
				max3Cnt = 0;
				top3List[++max3Cnt] = i;
			}
			else if (max3Point == map[i][3])
			{
				top3List[++max3Cnt] = i;
			}
		}

		// 동점자 처리
		// 혼자 1등일 경우
		if (max3Cnt == 1)
		{
			printf("%d %d\n", topList[max3Cnt], maxPoint);
		}
		// 동점자 있을 경우
		else
		{
			// 2점 비교
			for (int i = 1; i <= max3Cnt; i++)
			{
				if (max2Point < map[i][2])
				{
					max2Point = map[i][2];
					max2Cnt = 0;
					top2List[++max2Cnt] = i;
				}
				else if (max2Point == map[i][2])
				{
					top2List[++max2Cnt] = i;
				}
			}

			// 동점자 처리
			// 혼자 1등일 경우
			if (max2Cnt == 1)
			{
				printf("%d %d\n", topList[max2Cnt], maxPoint);
			}
			// 동점자 있을 경우
			else
			{
				// 판별 불가
				printf("0 %d\n", maxPoint);
			}
		}
	}
	*/

	return 0;
}
