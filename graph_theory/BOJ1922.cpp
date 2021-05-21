#define _CRT_SECURE_NO_WARNINGS
#define MAX_N 1000

#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct edge
{
	int c = -1; // 비용
	int s = -1; // 시작
	int f = -1; // 끝
}
EDGE;

vector<int> parent;
vector<EDGE> edge_v;

bool Compare(EDGE x, EDGE y)
{
	if (x.c == y.c)
	{
		return x.s < y.s;
	}
	else
	{
		return x.c < y.c;
	}
}

void Print_Parent()
{
	printf("parent : ");

	for (int i = 1; i < parent.size(); i++)
	{
		printf("%d ", parent[i]);
	}

	printf("\n");

	return;
}

void Print_Edge()
{
	printf("Edge : \n");

	for (int i = 0; i < edge_v.size(); i++)
	{
		printf("%d %d %d\n", edge_v[i].s, edge_v[i].f, edge_v[i].c);
	}

	printf("\n");

	return;
}

void Init()
{
	for (int i = 1; i < parent.size(); i++)
	{
		parent[i] = i;
	}

	return;
}

int Find(int z)
{
	if (parent[z] == z)
	{
		return z;
	}
	else
	{
		parent[z] = Find(parent[z]);

		return parent[z];
	}

	return -1;
}

void Union(int x, int y)
{
	int xRoot = -1;
	int yRoot = -1;

	xRoot = Find(x);
	yRoot = Find(y);

	parent[xRoot] = yRoot;

	return;
}

int Kruskal()
{
	int cur_c = -1;
	int cur_s = -1;
	int cur_f = -1;
	int sRoot = -1;
	int fRoot = -1;
	int result = 0;

	for (int i = 0; i < edge_v.size(); i++)
	{
		cur_c = edge_v[i].c;
		cur_s = edge_v[i].s;
		cur_f = edge_v[i].f;

		// 연결되어 있는지 확인
		sRoot = Find(cur_s);
		fRoot = Find(cur_f);

		// printf("s : %d, sRoot : %d, f : %d, fRoot : %d\n", cur_s, sRoot, cur_f, fRoot);

		// 연결되어 있으면
		if (sRoot == fRoot)
		{

		}
		// 연결되어 있지 않다면
		else
		{
			Union(cur_s, cur_f);

			result += cur_c;
		}

		// Print_Parent();
	}

	return result;
}

int main()
{
	int n = 0;
	int m = 0;
	int a = 0;
	int b = 0;
	int c = 0;
	int ans = 0;

	EDGE tmp;

	scanf("%d", &n);
	scanf("%d", &m);

	parent.resize(n + 1);

	for (int i = 0; i < m; i++)
	{
		scanf("%d %d %d", &a, &b, &c);

		tmp.c = c;
		tmp.s = a;
		tmp.f = b;

		edge_v.push_back(tmp);
	}

	Init();

	sort(edge_v.begin(), edge_v.end(), Compare);

	// Print_Edge();

	ans = Kruskal();

	printf("%d\n", ans);

	return 0;
}

// 강사님 코드
/*
#include<cstdio>
#include<algorithm>

using namespace std;

struct Edge {
	int dist;
	int x, y;
	bool operator < (const Edge a)const {
		return dist < a.dist;
	}
}data[100001];

int n, m;
int uni[100001];

int getParent(int x)
{
	if (x == uni[x])return x;
	return uni[x] = getParent(uni[x]);
}

void join(int x, int y)
{
	x = getParent(x);
	y = getParent(y);
	uni[x] = uni[y];
}

int main()
{
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; i++)
	{
		scanf("%d %d %d", &data[i].x, &data[i].y, &data[i].dist);
	}
	for (int i = 1; i <= n; i++)uni[i] = i;
	sort(data + 1, data + m + 1);
	int ans = 0;
	for (int i = 1; i <= m; i++)
	{
		if (getParent(data[i].x) != getParent(data[i].y))
		{
			join(data[i].x, data[i].y);
			ans += data[i].dist;
		}
	}

	printf("%d", ans);
	return 0;
}
*/
