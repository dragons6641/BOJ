#define _CRT_SECURE_NO_WARNINGS
#define ll long long
// #define MAX_N 4000000
#define MAX_N 2000
#define MAX_M 100000
#define ROOT 1

#include <stdio.h>
#include <vector>

using namespace std;

// DP 저장할 벡터
vector <vector <int> >dp;

using namespace std;

ll arr[MAX_N + 1];
ll tree[MAX_N * 4 + 1];
ll ans = 0;

void print_arr()
{
	printf("arr : \n");

	for (int i = ROOT; i <= MAX_N; i++)
	{
		if (arr[i] > 0)
		{
			printf("%d %lld\n", i, arr[i]);
		}
	}

	printf("\n");

	return;
}

void print_tree()
{
	///*
	printf("tree : \n");

	for (int i = ROOT; i <= 4 * MAX_N; i++)
	{
		if (tree[i] > 0)
		{
			printf("%d %lld\n", i, tree[i]);
		}
	}

	printf("\n");
	//*/

	/*
	printf("tree : ");

	for (int i = 1; i <= 4 * MAX_N; i++)
	{
	printf("%lld ", tree[i]);
	}

	printf("\n");
	*/

	return;
}

// 1. 트리 구성
ll init(ll cur, ll start, ll end)
{
	// 리프 노드일 경우
	if (start == end)
	{
		// 노드의 값을 트리에 입력
		tree[cur] = arr[start];

		return tree[cur];
	}

	// 이분 탐색 응용
	ll mid = (start + end) / 2;

	// 왼쪽 트리와 오른쪽 트리로 분할
	tree[cur] = init(cur * 2, start, mid) + init(cur * 2 + 1, mid + 1, end);

	return tree[cur];
}

// 2. 구간의 합
// start ~ end : 현재 노드를 루트로 하는 트리의 전체 범위
// left ~ right : 전체 트리 중 부분 합을 구할 구간의 범위
ll sum(ll cur, ll start, ll end, ll left, ll right)
{
	// 1. 구하고자 하는 합의 범위와 전혀 관계가 없음
	if ((right < start) || (left > end))
	{
		// 더 이상 볼 필요가 없다
		return 0;
	}

	// 2. 구하고자 하는 합의 범위에 모두 들어가 있음
	if ((left <= start) && (right >= end))
	{
		// 루트 값을 되돌려준다
		return tree[cur];
	}

	// 3. 구하고자 하는 합의 범위가 트리에 모두 포함되어 있음
	// 4. 구하고자 하는 합의 범위가 일부분만 포함되어 있음
	// 이 경우들은 하위 트리 재탐색 필요!
	// 이분 탐색 응용
	ll mid = (start + end) / 2;

	return (sum(cur * 2, start, mid, left, right) + sum(cur * 2 + 1, mid + 1, end, left, right));
}

// 3. 데이터 갱신
void update(ll cur, ll start, ll end, ll idx, ll diff)
{
	// 인덱스 범위 확인
	if ((start > idx) || (end < idx))
	{
		return;
	}

	// 바뀐 정보 반영
	tree[cur] += diff;

	// 리프 노드가 아닐 경우
	if (start < end)
	{
		// 이분 탐색 응용
		ll mid = (start + end) / 2;

		// 왼쪽 자식 트리 업데이트
		update(cur * 2, start, mid, idx, diff);

		// 오른쪽 자식 트리 업데이트
		update(cur * 2 + 1, mid + 1, end, idx, diff);
	}

	return;
}

void print_dp()
{
	printf("dp : \n");

	for (int r = 1; r < dp.size(); r++)
	{
		for (int c = 1; c < dp[r].size(); c++)
		{
			printf("%d ", dp[r][c]);
		}

		printf("\n");
	}

	return;
}

// 세그먼트 트리
/*
int main()
{
	ll n = 0;
	ll m = 0;
	ll x1 = 0;
	ll y1 = 0;
	ll x2 = 0;
	ll y2 = 0;
	ll ans = 0;
	ll a = 0;
	ll b = 0;

	scanf("%lld %lld", &n, &m);

	for (int i = 1; i <= (n * n); i++)
	{
		scanf("%lld", &arr[i]);
	}

	// 세그먼트 트리 만들자
	init(ROOT, ROOT, MAX_N);

	// print_tree();

	for (int i = 0; i < m; i++)
	{
		ans = 0;

		scanf("%lld %lld %lld %lld", &x1, &y1, &x2, &y2);

		a = ((x1 - 1) * n + y1);
		b = ((x2 - 1) * n + y2);

		// printf("a = %lld, b = %lld\n", a, b);
		for (int j = 0; j <= x2 - x1; j++)
		{
			ans += sum(ROOT, ROOT, MAX_N, a + (j * n), a + (j * n) + (y2 - y1));
		}

		// ans = sum(ROOT, ROOT, MAX_N, a, b);

		printf("%lld\n", ans);
	}

	return 0;
}
*/

// DP
int main()
{
	int n = 0;
	int m = 0;
	int input = 0;
	int x1 = 0;
	int y1 = 0;
	int x2 = 0;
	int y2 = 0;
	int ans = 0;

	vector <int> tmp;

	scanf("%d %d", &n, &m);

	// 벡터 사이즈
	tmp.resize(n + 1);

	for (int i = 0; i <= n; i++)
	{
		dp.push_back(tmp);
	}

	// 초기값과 점화식을 한번에
	for (int r = 1; r < dp.size(); r++)
	{
		for (int c = 1; c < dp[r].size(); c++)
		{
			scanf("%d", &input);

			// 초기값일 경우
			if ((r == 1) && (c == 1))
			{
				// 그냥 넣는다
				dp[r][c] = input;
			}
			// row 벽일 경우
			else if (r == 1)
			{
				// 이전 거에 현재 값 더하기
				dp[r][c] = dp[r][c - 1] + input;
			}
			// col 벽일 경우
			else if (c == 1)
			{
				// 이전 거에 현재 값 더하기
				dp[r][c] = dp[r - 1][c] + input;
			}
			// 일반적인 경우
			else
			{
				// 겹치는 부분은 빼주고 현재 값 더하기
				dp[r][c] = dp[r][c - 1] + dp[r - 1][c] - dp[r - 1][c - 1] + input;
			}
		}
	}

	// print_dp();

	// 구할 수 입력받기
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		
		ans = dp[x2][y2] - dp[x2][y1 - 1] - dp[x1 - 1][y2] + dp[x1 - 1][y1 - 1];

		// printf("ans = %d - %d - %d + %d\n", dp[x2][y2], dp[x2][y1 - 1], dp[x1 - 1][y2], dp[x1 - 1][y1 - 1]);

		printf("%d\n", ans);
	}

	return 0;
}

// 강사님 코드
/*
#include<stdio.h>

int A[1025][1025];
int B[1025][1025];

int main()
{
	int i, j, x1, y1, x2, y2, n, m;
	scanf("%d%d", &n, &m);
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
		{
			scanf("%d", &A[i][j]);
			B[i][j] = A[i][j] + B[i][j - 1] + B[i - 1][j] - B[i - 1][j - 1];
		}
	}

	for (i = 1; i <= m; i++)
	{
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		printf("%d\n", B[x2][y2] - B[x2][y1 - 1] - B[x1 - 1][y2] + B[x1 - 1][y1 - 1]);
	}
	return 0;
}
*/
