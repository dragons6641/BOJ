/*
E3 스위치
*/

#define _CRT_SECURE_NO_WARNINGS

/*
#include <stdio.h>

#define MAX_N 100000
#define MAX_M 100000
#define ROOT 1
#define MODULAR 2
#define TREE_SIZE (1 << 18)

int tree[TREE_SIZE];
int lazy[TREE_SIZE];

void propagate(int node, int s, int e)
{
	if (lazy[node] != 0)
	{
		if (s != e)
		{
			lazy[node * 2] = (lazy[node * 2] + lazy[node]) % MODULAR;
			lazy[node * 2 + 1] = (lazy[node * 2 + 1] + lazy[node]) % MODULAR;
		}

		tree[node] = ((e - s + 1) - tree[node]);
		lazy[node] = 0;
	}

	return;
}

void insertNodeLazy(int node, int s, int e, int idx)
{
	propagate(node, s, e);

	if ((idx < s) || (idx > e))
	{
		return;
	}

	if (s == e)
	{
		tree[node] = 1 - tree[node];

		return;
	}

	int m = (s + e) / 2;

	insertNodeLazy(node * 2, s, m, idx);
	insertNodeLazy(node * 2 + 1, m + 1, e, idx);

	tree[node] = tree[node * 2] + tree[node * 2 + 1];

	return;
}

int searchNodeLazy(int node, int s, int e, int qs, int qe)
{
	propagate(node, s, e);

	if ((qs <= s) && (qe >= e))
	{
		return tree[node];
	}
	else if ((qs > e) || (qe < s))
	{
		return 0;
	}

	int m = (s + e) / 2;
	int l = searchNodeLazy(node * 2, s, m, qs, qe);
	int r = searchNodeLazy(node * 2 + 1, m + 1, e, qs, qe);

	return (l + r);
}

void updateNodeLazy(int node, int s, int e, int us, int ue, int add)
{
	propagate(node, s, e);

	if ((us <= s) && (ue >= e))
	{
		lazy[node] = (lazy[node] + add) % MODULAR;

		propagate(node, s, e);

		return;
	}
	else if ((us > e) || (ue < s))
	{
		return;
	}

	int m = (s + e) / 2;

	updateNodeLazy(node * 2, s, m, us, ue, add);
	updateNodeLazy(node * 2 + 1, m + 1, e, us, ue, add);

	tree[node] = tree[node * 2] + tree[node * 2 + 1];

	return;
}

void inputData(void)
{
	// 스위치의 갯수
	int N;
	// 처리할 일의 갯수
	int M;
	int O;
	int S;
	int T;

	scanf("%d %d", &N, &M);

	for (register int i = 1; i <= M; i++)
	{
		scanf("%d %d %d", &O, &S, &T);

		switch (O)
		{
			// S부터 T까지 스위치 상태를 반전시킨다 
			case 0:
			{
				updateNodeLazy(ROOT, 1, N, S, T, 1);

				break;
			}
			// S부터 T까지 스위치 중 켜져 있는 스위치의 개수를 구한다 
			case 1:
			{
				// query
				int ret = searchNodeLazy(ROOT, 1, N, S, T);

				printf("%d\n", ret);

				break;
			}
			default:
			{
				break;
			}
		}

		int debug = 1;
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);

	inputData();

	return 0;
}
*/

#include <stdio.h>
#define MAXN ((int)1e5)
#define MAXM ((int)1e5)
#define MAXT (1<<18)
int N, M;//스위치개수, 명령개수
//segment tree
int tree[MAXT];//구간합
int lazy[MAXT];//lazy propagation용
void InitTree(int n, int s, int e) {
	lazy[n] = tree[n] = 0;
	if (s == e) return;
	int L = n * 2, R = L + 1, m = (s + e) / 2;
	InitTree(L, s, m);
	InitTree(R, m + 1, e);
}
void LazyPropagation(int n, int s, int e) {
	if (lazy[n] % 2) {//반전이므로 홀수일때만 반전
		tree[n] = e - s + 1 - tree[n];
		if (s != e) {
			int L = n * 2, R = L + 1;
			lazy[L] += lazy[n];
			lazy[R] += lazy[n];
		}
	}
	lazy[n] = 0;
}
int query(int n, int s, int e, int qs, int qe) {
	LazyPropagation(n, s, e);
	if ((qe < s) || (e < qs)) return 0;
	if ((qs <= s) && (e <= qe)) return tree[n];
	int L = n * 2, R = L + 1, m = (s + e) / 2;
	return query(L, s, m, qs, qe) + query(R, m + 1, e, qs, qe);//구간합
}
void update(int n, int s, int e, int qs, int qe) {
	int L = n * 2, R = L + 1, m = (s + e) / 2;
	LazyPropagation(n, s, e);
	if ((qe < s) || (e < qs)) return;
	if ((qs <= s) && (e <= qe)) {
		tree[n] = e - s + 1 - tree[n];
		if (s != e) {
			lazy[L]++;
			lazy[R]++;
		}
		return;
	}
	update(L, s, m, qs, qe);
	update(R, m + 1, e, qs, qe);
	tree[n] = tree[L] + tree[R];//구간합
}
void InputData() {
	scanf("%d %d", &N, &M);
}
void Solve() {
	int cmd, s, t;
	InitTree(1, 1, N);
	for (int i = 1; i <= M; i++) {
		scanf("%d %d %d", &cmd, &s, &t);
		if (cmd == 0) {//update
			update(1, 1, N, s, t);
		}
		else {
			printf("%d\n", query(1, 1, N, s, t));
		}
	}
}
int main() {
	InputData();
	Solve();
	return 0;
}
