#define _CRT_SECURE_NO_WARNINGS
#define MAX_N 1000000

#include <stdio.h>
#include <vector>

using namespace std;

vector<int> parent;

void Print_Parent()
{
	printf("parent : ");

	for (int i = 0; i < parent.size(); i++)
	{
		printf("%d ", parent[i]);
	}

	printf("\n");

	return;
}

void Init()
{
	for (int i = 0; i < parent.size(); i++)
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

int main()
{
	int n = 0;
	int m = 0;
	int c = 0;
	int a = 0;
	int b = 0;
	int aRoot = -1;
	int bRoot = -1;

	scanf("%d %d", &n, &m);

	parent.resize(n + 1);

	// printf("size : %d\n", parent.size());

	// 초기화
	Init();

	// Print_Parent();

	for (int i = 0; i < m; i++)
	{
		scanf("%d %d %d", &c, &a, &b);

		// Union
		if (c == 0)
		{
			Union(a, b);
		}
		// Find
		else if (c == 1)
		{
			aRoot = Find(a);
			bRoot = Find(b);

			if (aRoot == bRoot)
			{
				printf("YES\n");
			}
			else
			{
				printf("NO\n");
			}
		}
		// Error
		else
		{

		}
	}

	return 0;
}

// 강사님 코드
/*
#include<cstdio>

int n, m;
int uni[1000001];

int getParent(int x)
{
	if (x == uni[x])return x;
	//path compressing
	return uni[x] = getParent(uni[x]);
}
int join(int x, int y)
{
	x = getParent(x);
	y = getParent(y);
	uni[x] = uni[y];
}

int main()
{
	scanf("%d %d", &n, &m);

	int query, a, b;

	//union 배열 초기화
	for (int i = 0; i <= n; i++)
		uni[i] = i;

	for (int i = 1; i <= m; i++)
	{
		scanf("%d %d %d", &query, &a, &b);

		if (query == 0)
		{
			join(a, b);
		}
		else
		{
			//uni[a]==uni[b]가 아니다. -- why?
			if (getParent(a) == getParent(b))
				printf("YES\n");
			else
				printf("NO\n");
		}
	}
}
*/
