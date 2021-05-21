#define _CRT_SECURE_NO_WARNINGS
#define ll long long
#define MAX_N 100000
#define MAX_M 100000
#define ROOT 1

#include <stdio.h>

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

int main()
{
	ll n = 0;
	ll m = 0;
	ll a = 0;
	ll b = 0;
	ll ans = 0;

	scanf("%lld %lld", &n, &m);

	for (int i = 1; i <= n; i++)
	{
		scanf("%lld", &arr[i]);
	}

	// 세그먼트 트리 만들자
	init(ROOT, ROOT, MAX_N);

	// print_tree();

	for (int i = 0; i < m; i++)
	{
		scanf("%lld %lld", &a, &b);

		ans = sum(ROOT, ROOT, MAX_N, a, b);

		printf("%lld\n", ans);
	}

	return 0;
}

// 강사님 코드
/*
#include<stdio.h>

int A[100001], B[100001];

int main()
{
	int i, n, m, x, y;
	scanf("%d%d", &n, &m);

	for (i = 1; i <= n; i++)
	{
		scanf("%d", &A[i]);
		B[i] = B[i - 1] + A[i];
	}

	for (i = 1; i <= m; i++)
	{
		scanf("%d%d", &x, &y);
		printf("%d\n", B[y] - B[x - 1]);
	}
	return 0;
}
*/
