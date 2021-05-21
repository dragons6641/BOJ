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
int segmentTreeMin[MAX_SEGMENT] = { 0, };
// 연속한 구간의 최댓값
int segmentTreeMax[MAX_SEGMENT] = { 0, };

inline int Min(const int a, const int b)
{
	return ((a < b) ? a : b);
}

inline int Max(const int a, const int b)
{
	return ((a > b) ? a : b);
}

void updateNewDataMin(int node, int s, int e, int idx, int data)
{
	if (s == e)
	{
		segmentTreeMin[node] = data;

		return;
	}

	int m = (s + e) / 2;
	int lch = node * 2;
	int rch = lch + 1;

	if (m >= idx)
	{
		updateNewDataMin(lch, s, m, idx, data);
	}
	else
	{
		updateNewDataMin(rch, m + 1, e, idx, data);
	}

	segmentTreeMin[node] = Min(segmentTreeMin[lch], segmentTreeMin[rch]);

	return;
}

void updateNewDataMax(int node, int s, int e, int idx, int data)
{
	if (s == e)
	{
		segmentTreeMax[node] = data;

		return;
	}

	int m = (s + e) / 2;
	int lch = node * 2;
	int rch = lch + 1;

	if (m >= idx)
	{
		updateNewDataMax(lch, s, m, idx, data);
	}
	else
	{
		updateNewDataMax(rch, m + 1, e, idx, data);
	}

	segmentTreeMax[node] = Max(segmentTreeMax[lch], segmentTreeMax[rch]);

	return;
}

int queryMin(int node, int s, int e, int qs, int qe)
{
	if ((s >= qs) && (e <= qe))
	{
		return segmentTreeMin[node];
	}

	if ((s > qe) || (e < qs))
	{
		return MAXINF;
	}

	int m = (s + e) / 2;
	int lch = node * 2;
	int rch = lch + 1;

	int lq = queryMin(lch, s, m, qs, qe);
	int rq = queryMin(rch, m + 1, e, qs, qe);

	return Min(lq, rq);
}

int queryMax(int node, int s, int e, int qs, int qe)
{
	if ((s >= qs) && (e <= qe))
	{
		return segmentTreeMax[node];
	}

	if ((s > qe) || (e < qs))
	{
		return 0;
	}

	int m = (s + e) / 2;
	int lch = node * 2;
	int rch = lch + 1;

	int lq = queryMax(lch, s, m, qs, qe);
	int rq = queryMax(rch, m + 1, e, qs, qe);

	return Max(lq, rq);
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

		updateNewDataMin(1, 1, N, i, K);
		updateNewDataMax(1, 1, N, i, K);
	}

	for (register int i = 1; i <= M; i++)
	{
		scanf("%d %d", &A, &B);

		int retMin = queryMin(1, 1, N, A, B);
		int retMax = queryMax(1, 1, N, A, B);

		printf("%d %d\n", retMin, retMax);
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	solve();

	return 0;
}
