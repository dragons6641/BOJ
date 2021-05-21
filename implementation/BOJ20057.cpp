#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 500
#define MAX_A 1000
#define MAX_DIR 4

int N;
int dr[MAX_DIR] = { 0, 1, 0, -1 };
int dc[MAX_DIR] = { -1, 0, 1, 0 };
int A[MAX_N + 1][MAX_N + 1] = { 0, };

void inputData(void)
{
	scanf("%d", &N);

	for (register int r = 1; r <= N; r++)
	{
		for (register int c = 1; c <= N; c++)
		{
			scanf("%d", &A[r][c]);
		}
	}

	return;
}

bool checkPossible(int nowR, int nowC)
{
	if ((nowR <= 0) || (nowC <= 0) || (nowR > N) || (nowC > N))
	{
		return false;
	}

	return true;
}

int moveSand(int xr, int xc, int yr, int yc, int dist, int sideDist, int dir, int leftDir, int rightDir, int sand)
{
	// 토네이도가 x에서 y로 이동하면, y의 모든 모래가 비율과 α가 적혀있는 칸으로 이동한다. 
	// 비율이 적혀있는 칸으로 이동하는 모래의 양은 y에 있는 모래의 해당 비율만큼이고, 계산에서 소수점 아래는 버린다.
	// 모래가 이미 있는 칸으로 모래가 이동하면, 모래의 양은 더해진다.

	if (sand == 0)
	{
		return 0;
	}

	int result = 0;
	int nextR;
	int nextC;

	nextR = xr + (dr[dir] * dist) + (dr[leftDir] * sideDist);
	nextC = xc + (dc[dir] * dist) + (dc[leftDir] * sideDist);

	A[yr][yc] -= sand;

	if (checkPossible(nextR, nextC))
	{
		A[nextR][nextC] += sand;
	}
	else
	{
		result += sand;
	}

	if (sideDist == 0)
	{
		return result;
	}

	nextR = xr + (dr[dir] * dist) + (dr[rightDir] * sideDist);
	nextC = xc + (dc[dir] * dist) + (dc[rightDir] * sideDist);

	A[yr][yc] -= sand;

	if (checkPossible(nextR, nextC))
	{
		A[nextR][nextC] += sand;
	}
	else
	{
		result += sand;
	}

	return result;
}

int moveTornado(int xr, int xc, int dir)
{
	int result = 0;
	int yr = xr + dr[dir];
	int yc = xc + dc[dir];
	int leftDir = (dir + 1) % MAX_DIR;
	int rightDir = (dir + MAX_DIR - 1) % MAX_DIR;
	int sand = A[yr][yc];

	// int moveSand(int xr, int xc, int yr, int yc, int dist, int sideDist, int dir, int leftDir, int rightDir, int sand)

	// 10%
	result += moveSand(xr, xc, yr, yc, 2, 1, dir, leftDir, rightDir, sand / 10);

	// 7%
	result += moveSand(xr, xc, yr, yc, 1, 1, dir, leftDir, rightDir, sand * 7 / 100);

	// 5%
	result += moveSand(xr, xc, yr, yc, 3, 0, dir, leftDir, rightDir, sand / 20);

	// 2%
	result += moveSand(xr, xc, yr, yc, 1, 2, dir, leftDir, rightDir, sand / 50);

	// 1%
	result += moveSand(xr, xc, yr, yc, 0, 1, dir, leftDir, rightDir, sand / 100);

	// α로 이동하는 모래의 양은 비율이 적혀있는 칸으로 이동하지 않은 남은 모래의 양과 같다. 
	result += moveSand(xr, xc, yr, yc, 2, 0, dir, leftDir, rightDir, A[yr][yc]);

	return result;
}

int solve(void)
{
	int nowR = (N + 1) / 2;
	int nowC = (N + 1) / 2;
	int dir = 0;
	int dist = 1;
	int result = 0;

	while (true)
	{
		for (register int i = 1; i <= dist; i++)
		{
			result += moveTornado(nowR, nowC, dir);

			nowR = nowR + dr[dir];
			nowC = nowC + dc[dir];

			if ((nowR == 1) && (nowC == 1))
			{
				return result;
			}
		}

		dir = (dir + 1) % MAX_DIR;

		if (dir % 2 == 0)
		{
			dist++;
		}
	}

	return 0;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);	// 10
	// freopen("input2.txt", "r", stdin);	// 85
	// freopen("input3.txt", "r", stdin);	// 139
	// freopen("input4.txt", "r", stdin);	// 7501
	// freopen("input5.txt", "r", stdin);	// 283
	// freopen("input6.txt", "r", stdin);	// 22961

	inputData();

	int ans = solve();

	printf("%d\n", ans);

	return 0;
}
