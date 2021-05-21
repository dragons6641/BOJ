#define _CRT_SECURE_NO_WARNINGS
#define MAX_N 1000
#define MAX_NUM 10000

#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

// 입력 저장 벡터
vector <int> v;

// dp 저장 벡터
vector <vector <int> > dp;

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

void print_dp()
{
	printf("dp : \n");

	for (int i = 0; i < dp.size(); i++)
	{
		for (int j = 0; j < dp[i].size(); j++)
		{
			printf("%d ", dp[i][j]);
		}

		printf("\n");
	}

	return;
}

int solve()
{
	// 근우 점수만 더해줘야 한다!
	int result = 0;

	// 초기값 설정
	// 홀수개면
	if (v.size() % 2)
	{
		// 마지막 한 장은 무조건 근우가 가지고 간다
		for (int i = 0; i < v.size(); i++)
		{
			dp[i][i] = v[i];
		}
	}
	// 짝수개면
	else
	{
		// 마지막 한 장은 무조건 명우가 가지고 간다
		for (int i = 0; i < v.size(); i++)
		{
			dp[i][i] = 0;
		}
	}

	// 점화식 설정
	// i는 거꾸로 돌아야 한다
	// i가 j보다 작은 곳만 확인한다
	for (int i = v.size() - 1; i >= 0; i--)
	{
		for (int j = i + 1; j < v.size(); j++)
		{
			// printf("i = %d, j = %d\n", i, j);

			// 근우 차례일 경우
			if ((i + j + v.size()) % 2)
			{
				// 하나 뽑은 점수가 들어가고
				// 근우는 최선을 다한다
				dp[i][j] = max(dp[i + 1][j] + v[i], dp[i][j - 1] + v[j]);
			}
			// 명우 차례일 경우
			else
			{
				// 뽑은 점수는 들어가지 않는다
				// 명우도 반대쪽에서 최선을 다한다
				dp[i][j] = min(dp[i + 1][j], dp[i][j - 1]);
			}
		}
	}

	result = dp[0][v.size() - 1];

	return result;
}

int main()
{
	int t = 0;
	int n = 0;
	int ans = 0;
	int num = 0;

	vector <int> tmp;

	scanf("%d", &t);

	for (int i = 0; i < t; i++)
	{
		scanf("%d", &n);

		// 초기화
		v.clear();
		dp.clear();

		// 벡터 크기
		v.reserve(n);
		tmp.resize(n);
		dp.reserve(n);

		for (int j = 0; j < n; j++)
		{
			dp.push_back(tmp);
		}

		for (int j = 0; j < n; j++)
		{
			scanf("%d", &num);

			v.push_back(num);
		}

		// print_v();

		ans = solve();

		// print_dp();

		printf("%d\n", ans);
	}

	return 0;
}

// 강사님 코드
/*
#include <stdio.h> 
#include <iostream> 
#include <vector> 
#include <algorithm> 
#include <map> 
#include <string.h> 
#include <utility> 
#include <set> 
#include <queue> 
#include <stack> 
#include <functional> 
#include <math.h> 
#include <limits.h>
#include <stdlib.h>
#include <stack> 
#include <tuple> 

using namespace std;
int testcase; int N;
int card[1001]; int memo[1001][1001]; // solve(i,j)는 i~j까지의 카드만 남았을 때, ""지금 상황에서"" 내가 먹을 수 있는 최대의 점수
int solve(int start, int end)
{
	int & ret = memo[start][end];
	if (ret != 0) return ret;
	if (start >= end) {
		if ((N - (start + end)) % 2) return ret = card[start];
		else return ret = 0;
	}

	if ((N - (start + end)) % 2) {

		ret = max((solve(start + 1, end) + card[start]), (solve(start, end - 1) + card[end]));

	}
	else {

		ret = min((solve(start + 1, end)), (solve(start, end - 1)));
	}

	return ret;
}

int main() {

	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			scanf("%d", &card[i]);
		}

		for (int i = 0; i < N; i++) {
			memset(memo[i], 0, sizeof(int) * N);
		}

		printf("%d\n", solve(0, N - 1));
	}

	return 0;
}
*/
