#define _CRT_SECURE_NO_WARNINGS
#define MAX_N 100
#define MAX_M 100000
#define INF 1000000000

#include <stdio.h>
#include <vector>

using namespace std;

// 인접 행렬 벡터로 구현
// [시작][도착] = 비용
vector <vector <int> > graph;

void print_graph()
{
	// printf("graph : \n");

	for (int i = 1; i < graph.size(); i++)
	{
		for (int j = 1; j < graph[i].size(); j++)
		{
			printf("%d ", graph[i][j]);
		}

		printf("\n");
	}

	return;
}

void floyd_warshall()
{
	// k는 경유지
	for (int k = 1; k < graph.size(); k++)
	{
		// i는 출발지
		for (int i = 1; i < graph.size(); i++)
		{
			// j는 도착지
			for (int j = 1; j < graph.size(); j++)
			{
				// 경유해서 가는 게 더 비용이 적게 든다면
				if (graph[i][k] + graph[k][j] < graph[i][j])
				{
					// 무한대일때는 연산 X
					if ((graph[i][k] != INF) && (graph[k][j] != INF))
					{
						graph[i][j] = graph[i][k] + graph[k][j];
					}
				}
			}
		}
	}

	return;
}

int main()
{
	int n = 0;	// 도시의 갯수
	int m = 0;	// 버스의 갯수
	int a = 0;	// 시작 도시
	int b = 0;	// 도착 도시
	int c = 0;	// 비용

	vector <int> tmp;

	scanf("%d", &n);
	scanf("%d", &m);

	// 2차원 벡터 resize
	// 크기는 반드시 n + 1!
	for (int i = 0; i <= n; i++)
	{
		tmp.resize(n + 1);
		graph.push_back(tmp);
	}
	
	// 벡터 초기화
	for (int i = 1; i < graph.size(); i++)
	{
		for (int j = 1; j < graph[i].size(); j++)
		{
			if (i == j)
			{
				graph[i][j] = 0;
			}
			else
			{
				graph[i][j] = INF;
			}
		}
	}

	for (int i = 0; i < m; i++)
	{
		scanf("%d %d %d", &a, &b, &c);

		if (c < graph[a][b])
		{
			graph[a][b] = c;
		}
	}

	// 플로이드-워셜 알고리즘
	floyd_warshall();

	for (int i = 1; i < graph.size(); i++)
	{
		for (int j = 1; j < graph[i].size(); j++)
		{
			// 음수 사이클 확인
			if (i == j)
			{
				if (graph[i][j] < 0)
				{
					
				}
			}
			// 갈 수 없으면 0으로
			else
			{
				if (graph[i][j] == INF)
				{
					graph[i][j] = 0;
				}
			}
		}
	}

	print_graph();

	return 0;
}

// 강사님 코드
/*
#include <stdio.h>
#define INF 100000*100+1
int n, m;
int mat[101][101];
int min(int a, int b) { return a<b ? a : b; }

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) mat[i][j] = (i == j ? 0 : INF);
	for (int i = 0, a, b, c; i<m; i++)
	{
		scanf("%d%d%d", &a, &b, &c);
		mat[a][b] = min(mat[a][b], c);
	}
	for (int k = 1; k <= n; k++)
		for (int s = 1; s <= n; s++)
			for (int e = 1; e <= n; e++)
				mat[s][e] = min(mat[s][e], mat[s][k] + mat[k][e]);
	for (int s = 1; s <= n; s++)
	{
		for (int e = 1; e <= n; e++) printf("%d ", mat[s][e] == INF ? 0 : mat[s][e]);
		printf("\n");
	}
	return 0;
}
*/
