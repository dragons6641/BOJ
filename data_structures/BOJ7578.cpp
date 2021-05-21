#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 500000
#define MAX_M 1000000
#define MAX_SEGMENT (1 << 20)

typedef long long LL;

// 기계 수
int N;
// A열 Mapping 정보
// 1부터 사용
int A[MAX_M + 1] = { 0, };
// B열 구간합 정보
LL segmentTree[MAX_SEGMENT] = { 0, };

void updateNewData(int node, int s, int e, int idx, LL data)
{
	if (s == e)
	{
		segmentTree[node] = data;

		return;
	}

	int m = (s + e) / 2;
	int lch = node * 2;
	int rch = lch + 1;

	if (m >= idx)
	{
		updateNewData(lch, s, m, idx, data);
	}
	else
	{
		updateNewData(rch, m + 1, e, idx, data);
	}

	segmentTree[node] = segmentTree[lch] + segmentTree[rch];

	return;
}

LL query(int node, int s, int e, int qs, int qe)
{
	if ((s >= qs) && (e <= qe))
	{
		return segmentTree[node];
	}

	if ((s > qe) || (e < qs))
	{
		return 0;
	}

	int m = (s + e) / 2;
	int lch = node * 2;
	int rch = lch + 1;

	LL lq = query(lch, s, m, qs, qe);
	LL rq = query(rch, m + 1, e, qs, qe);

	return (lq + rq);
}

LL solve(void)
{
	int M;
	LL result = 0;

	scanf("%d", &N);

	// A열
	for (register int i = 1; i <= N; i++)
	{
		scanf("%d", &M);

		A[M] = i;
	}

	// B열
	for (register int i = 1; i <= N; i++)
	{
		scanf("%d", &M);

		updateNewData(1, 1, N, A[M], 1);

		LL ret = query(1, 1, N, A[M] + 1, N);

		result += ret;
	}

	return result;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	LL ans = solve();

	printf("%lld\n", ans);

	return 0;
}
