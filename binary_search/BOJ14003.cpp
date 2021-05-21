#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

// 입력값
vector <int> a;

// dp값(1~i까지 최장 증가 길이)
vector <int> dp;

// 이전값
vector <int> p;

// 출력을 위한 스택
stack <int> s;

void print_a()
{
	printf("a : ");

	for (int i = 0; i < a.size(); i++)
	{
		printf("%d ", a[i]);
	}

	printf("\n");

	return;
}

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

void print_p()
{
	printf("p : ");

	for (int i = 0; i < p.size(); i++)
	{
		printf("%d ", p[i]);
	}

	printf("\n");

	return;
}

int solve()
{
	int result = 0;
	int i = 1;
	int cur = a[i];
	int pos = 0;

	// 초기값 설정
	p.push_back(0);
	dp.push_back(a[0]);

	// 점화식 설정
	while (i < a.size())
	{
		cur = a[i];

		// 현재 배열 값이 dp배열의 최댓값보다 크다면
		if (cur > dp.back())
		{
			// 부분 수열에 추가
			p.push_back(dp.back());
			dp.push_back(cur);
		}
		// 크지 않다면
		else
		{
			// lower bound
			pos = (lower_bound(dp.begin(), dp.end(), cur) - dp.begin());

			// 값 대입
			dp[pos - 1] = cur;
		}

		i += 1;

		print_dp();
		print_p();
	}

	return result;
}

int new_solve()
{
	int result = 0;
	int i = 1;
	int cur = 0;
	int pos = 0;
	int t = 0;
	
	// 입력값 : a (arr), (ans -> second)
	// 문제 정답 : dp (lis)
	// 위치 정보 : p (ans -> first)

	// 초기값 설정
	dp.push_back(a[0]);
	p.push_back(0);

	while (i < a.size())
	{
		cur = a[i];

		// printf("i = %d, cur = %d, back = %d\n", i, cur, dp.back());

		// print_dp();

		// 수열이 될 수 있는 후보라면
		if (cur > dp.back())
		{
			// 문제 정답에 넣어준다
			dp.push_back(cur);

			// printf("size : %d\n", dp.size());

			// 위치정보 기록
			p.push_back(dp.size() - 1);
		}
		// 수열이 될 수 있는 후보가 아니라면
		else
		{
			// lower bound 이용
			pos = lower_bound(dp.begin(), dp.end(), cur) - dp.begin();

			// printf("pos = %d\n", pos);

			dp[pos] = a[i];

			// 위치정보 기록
			p.push_back(pos);
		}

		i += 1;
	}

	// 길이 출력
	printf("%d\n", dp.size());

	// print_dp();
	// print_p();

	// 스택에 담아 역출력
	result = dp.size();

	t = dp.size() - 1;

	// 뒤에서부터 루프!
	for (i = a.size() - 1; i >= 0; i--)
	{
		if (p[i] == t)
		{
			s.push(a[i]);

			t -= 1;
		}
	}

	while (!s.empty())
	{
		printf("%d ", s.top());

		s.pop();
	}

	printf("\n");

	return result;
}

int main()
{
	int n = 0;
	int num = 0;
	int ans = 0;

	scanf("%d", &n);

	// 벡터 크기
	a.reserve(n);
	dp.reserve(n);
	p.reserve(n);

	for (int i = 0; i < n; i++)
	{
		scanf("%d", &num);

		a.push_back(num);
	}

	// print_a();

	// ans = solve();

	ans = new_solve();

	// printf("%d\n", ans);

	return 0;
}

/*
// 강사님 코드
#include <cstdio>
#include <cstdlib>
#define NMAX 1000005
int N, A[NMAX][2], maxtree[NMAX * 3], Nidx;
int D[NMAX], prev[NMAX], ans[NMAX];
int maxidx[NMAX * 3 + 10];
int ret_idx;
int max(int a, int b)
{
	return (a > b) ? a : b;
}

int min(int a, int b)
{
	return (a < b) ? a : b;
}

int comp(const void * arg1, const void * arg2)
{
	int * a = (int*)arg1;
	int * b = (int*)arg2;
	if (a[0] != b[0]) return a[0] - b[0];
	else return b[1] - a[1]; // 값이 같은 경우 인덱스가 큰 값부터 처리 
}

void update(int idx, int num)
{
	int cur = idx;
	while (cur > 0)
	{
		if (maxtree[cur] < num)
		{
			maxtree[cur] = num; // max tree 값 갱신 
			maxidx[cur] = idx; // max 인덱스 정보 갱신 
			cur /= 2;
		}
		else break;
	}
}

int query(int s, int e)
{
	int ret = 0; // 구간의 max값 저장 
	ret_idx = -1; // 구간의 max값을 가지는 인덱스 저장 
	while (s <= e)
	{
		if (s % 2 == 1)
		{
			if (ret < maxtree[s])
			{
				ret = maxtree[s];
				ret_idx = maxidx[s];
			}
		}
		if (e % 2 == 0)
		{
			if (ret < maxtree[e])
			{
				ret = maxtree[e];
				ret_idx = maxidx[e];
			}
		}
		s = (s + 1) / 2;
		e = (e - 1) / 2;
	}
	return ret;
}
int main()
{
	scanf("%d", &N);
	// 인덱스 트리 초기화 
	for (int i = 0; i < N * 3; i++) maxtree[i] = 0;
	Nidx = 1;
	while (Nidx < N) Nidx *= 2;

	for (int i = 0; i < N; i++)
	{
		scanf("%d", &D[i]);
		A[i][0] = D[i]; // 값 
		A[i][1] = i; // 인덱스 
	}

	// 값 기준으로 정렬 
	qsort(A, N, sizeof(int) * 2, comp);

	// 값이 작은 인덱스부터 처리 
	for (int i = 0; i < N; i++)
	{
		// 현재 인덱스보다 앞에 있는 값 중 가장 LIS 값이 큰 값과 인덱스를 구해온다. 
		int maxCnt = query(0 + Nidx, A[i][1] + Nidx - 1);
		// 현재 인덱스 앞에 연결된 LIS 인덱스 갱신 
		prev[A[i][1]] = ret_idx - Nidx;
		// 현재 인덱스까지 사용해서 만들 수 있는 LIS값 갱신 : maxCnt+1
		update(A[i][1] + Nidx, maxCnt + 1);
	}

	printf("%d\n", maxtree[1]); // 가장 긴 LIS 길이 값 출력 

	int cur = maxidx[1] - Nidx; // 가장 긴 LIS 길이 값을 만드는 마지막 인덱스 
	for (int i = maxtree[1] - 1; i >= 0; i--)
	{
		ans[i] = D[cur];
		cur = prev[cur];
	}
	for (int i = 0; i < maxtree[1]; i++)printf("%d ", ans[i]); printf("\n");
}
*/
