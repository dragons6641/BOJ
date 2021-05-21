#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 100000
#define MAX_M 100000
#define MAXINF 1000000001
#define MAX_SEGMENT (1 << 18)

// 정수의 갯수
int N;
// 쿼리의 갯수
int M;
// 연속한 구간의 최솟값
int segmentTree[MAX_SEGMENT] = { 0, };

inline int Min(const int a, const int b)
{
	return ((a < b) ? a : b);
}

void updateNewData(int node, int s, int e, int idx, int data)
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

	segmentTree[node] = Min(segmentTree[lch], segmentTree[rch]);

	return;
}

int query(int node, int s, int e, int qs, int qe)
{
	if ((s >= qs) && (e <= qe))
	{
		return segmentTree[node];
	}

	if ((s > qe) || (e < qs))
	{
		return MAXINF;
	}

	int m = (s + e) / 2;
	int lch = node * 2;
	int rch = lch + 1;

	int lq = query(lch, s, m, qs, qe);
	int rq = query(rch, m + 1, e, qs, qe);

	return Min(lq, rq);
}

void solve(void)
{
	int K;
	int A;
	int B;

	scanf("%d %d", &N, &M);

	for (register int i = 1; i <= N; i++)
	{
		scanf("%d", &K);

		updateNewData(1, 1, N, i, K);
	}

	for (register int i = 1; i <= M; i++)
	{
		scanf("%d %d", &A, &B);

		int ret = query(1, 1, N, A, B);

		printf("%d\n", ret);
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	solve();

	return 0;
}
