#define _CRT_SECURE_NO_WARNINGS
#define MAX_N 300
#define MAX_S 10000

#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct node
{
	int v1 = 0;
	int v2 = 0;
}
NODE;

// 입력을 저장할 벡터
vector <int> v;

/*
// dp 저장 벡터
vector <int> dp;

// 한 계단 밟은 횟수 저장 벡터
vector <int> chk;
*/

vector <NODE> dp;

void print_v()
{
	printf("v : ");

	for (int i = 0; i < v.size(); i++)
	{
		printf("%d ", v[i]);
	}

	printf("\n");

	return;
}

/*
void print_dp()
{
	printf("dp : ");

	for (int i = 0; i < dp.size(); i++)
	{
		printf("%d ", dp[i]);
	}

	printf("\n");

	return;
}

void print_chk()
{
	printf("chk : ");

	for (int i = 0; i < chk.size(); i++)
	{
		printf("%d ", chk[i]);
	}

	printf("\n");

	return;
}
*/

/*
// dp와 chk 배열!
// k는 계단의 갯수
int solve(int k)
{
	int result = 0;

	// 초기값 설정
	dp[0] = v[0];
	chk[0] = 0;

	// [1]로 오는 방법은 두 가지
	// 첫 번째는 [0]을 밟고 오는 것
	dp[1] = dp[0] + v[1];
	chk[1] = chk[0] + 1;

	// 점화식 설정
	for (int i = 2; i < v.size(); i++)
	{
		// print_dp();
		// print_chk();

		// 이미 한 칸씩 한 번 움직였을 때
		if (chk[i - 1] == 1)
		{
			// 무조건 두 칸 움직여야 함
			dp[i] = dp[i - 2] + v[i];

			// 움직인 횟수 초기화
			chk[i] = 0;
		}
		// 아직 한 칸 움직일 수 있을 때
		else
		{
			// [i - 1]이 더 클 경우
			if (dp[i - 1] > dp[i - 2])
			{
				// 한 칸 움직이고
				dp[i] = dp[i - 1] + v[i];

				// 움직인 횟수 증가
				chk[i] = chk[i - 1] + 1;
			}
			// [i - 2]가 더 클 경우
			else
			{
				// 무조건 두 칸 움직여야 함
				dp[i] = dp[i - 2] + v[i];

				// 움직인 횟수 초기화
				chk[i] = 0;
			}
		}

		// 마지막 계단을 밟을 수 있는 지 확인
		// 그러려면 마지막에서 두 번째를 확인
		if (i == v.size() - 2)
		{
			// 마지막 계단 도달 못 할 경우
			if (chk[i] == 1)
			{
				// 무조건 두 칸 움직여야 함
				dp[i] = dp[i - 2] + v[i];

				// 움직인 횟수 초기화
				chk[i] = 0;
			}
		}
	}

	print_dp();
	print_chk();

	// 마지막 계단에 기록된 점수가 정답
	if (dp[k - 1] > result)
	{
		result = dp[k - 1];
	}

	if (k >= 3)
	{
		dp.resize(k, 0);
		chk.resize(k, 0);

		// 초기값 설정
		dp[0] = v[0];
		chk[0] = 0;

		// [1]로 오는 방법은 두 가지
		// 두 번째는 시작점에서 바로 오는 것
		dp[1] = v[1];
		chk[1] = 0;

		// [2]로 오는 방법은 [1]에서 오는 것만 고려한다
		dp[2] = dp[1] + v[2];
		chk[2] = chk[1] + 1;

		// [2]

		// 점화식 설정
		for (int i = 3; i < v.size(); i++)
		{
			// print_dp();
			// print_chk();

			// 이미 한 칸씩 한 번 움직였을 때
			if (chk[i - 1] == 1)
			{
				// 무조건 두 칸 움직여야 함
				dp[i] = dp[i - 2] + v[i];

				// 움직인 횟수 초기화
				chk[i] = 0;
			}
			// 아직 한 칸 움직일 수 있을 때
			else
			{
				// [i - 1]이 더 클 경우
				if (dp[i - 1] > dp[i - 2])
				{
					// 한 칸 움직이고
					dp[i] = dp[i - 1] + v[i];

					// 움직인 횟수 증가
					chk[i] = chk[i - 1] + 1;
				}
				// [i - 2]가 더 클 경우
				else
				{
					// 무조건 두 칸 움직여야 함
					dp[i] = dp[i - 2] + v[i];

					// 움직인 횟수 초기화
					chk[i] = 0;
				}
			}

			// 마지막 계단을 밟을 수 있는 지 확인
			// 그러려면 마지막에서 두 번째를 확인
			if (i == v.size() - 2)
			{
				// 마지막 계단 도달 못 할 경우
				if (chk[i] == 1)
				{
					// 무조건 두 칸 움직여야 함
					dp[i] = dp[i - 2] + v[i];

					// 움직인 횟수 초기화
					chk[i] = 0;
				}
			}
		}

		print_dp();
		print_chk();

		// 마지막 계단에 기록된 점수가 정답
		if (dp[k - 1] > result)
		{
			result = dp[k - 1];
		}
	}

	return result;
}

int new_solve(int k)
{
	int result = 0;
	int tmp = 0;

	// 초기값 설정
	dp[0] = v[0];
	chk[0] = 1;

	dp[1] = v[1];
	chk[1] = 0;

	for (int i = 0; i < v.size(); i++)
	{
		print_dp();
		print_chk();

		// 아직 두 번 안 왔다면
		if (chk[i] < 1)
		{
			// [i + 1] 것
			if ((i + 1) < v.size())
			{
				tmp = dp[i] + v[i + 1];

				if (tmp > dp[i + 1])
				{
					dp[i + 1] = tmp;

					chk[i + 1] = chk[i] + 1;
				}
			}
		}

		// [i + 2] 것
		if ((i + 2) < v.size())
		{
			tmp = dp[i] + v[i + 2];

			if (tmp > dp[i + 2])
			{
				dp[i + 2] = tmp;

				chk[i + 2] = 0;
			}
		}
	}

	print_dp();
	print_chk();

	result = dp[k - 1];

	return result;
}
*/

int upgrade_solve(int k)
{
	int result = 0;

	// 초기값 설정
	// 한 계단 올라왔을 때
	dp[1].v1 = v[1];
	// 두 계단 올라왔을 때
	dp[1].v2 = 0;

	// 점화식 설정
	for (int i = 2; i < dp.size(); i++)
	{
		// 한 계단 올라오는 경우
		dp[i].v1 = max(dp[i - 2].v1, dp[i - 2].v2) + v[i];
		// 두 계단 올라오는 경우
		dp[i].v2 = dp[i - 1].v1 + v[i];
		
	}

	result = max(dp[k].v1, dp[k].v2);

	return result;
}

int main()
{
	int n = 0;
	int input = 0;
	int ans = 0;

	scanf("%d", &n);

	v.reserve(n + 1);
	dp.resize(n + 1);
	// chk.resize(n + 1, 0);

	// 쓰레기값
	v.push_back(0);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &input);

		v.push_back(input);
	}

	// print_v();

	// 예외 처리
	if (n == 1)
	{
		ans = input;
	}
	else
	{
		// ans = solve(n);
		// ans = new_solve(n);
		ans = upgrade_solve(n);
	}

	// print_dp();
	// print_chk();

	printf("%d\n", ans);

	return 0;
}

// 강사님 코드
/*
#include<stdio.h>
#include<algorithm>

using namespace std;

int A[301];
int D[301][2];

int main()
{
	int i, n;
	scanf("%d", &n);
	for (i = 1; i <= n; i++)
	{
		scanf("%d", &A[i]);
	}

	D[1][0] = A[1];
	for (i = 1; i <= n; i++)
	{
		D[i][0] = max(D[i - 2][0], D[i - 2][1]) + A[i];
		D[i][1] = D[i - 1][0] + A[i];
	}

	printf("%d\n", max(D[n][0], D[n][1]));
	return 0;
}
*/
