#define _CRT_SECURE_NO_WARNINGS
#define INF 1000000000

#include <stdio.h>
#include <vector>
#include <queue>

using namespace std;

typedef struct node
{
	int next = 0;
	int cost = 0;
}
NODE;

bool operator<(NODE a, NODE b) 
{
	return a.cost > b.cost;
}

// 연결 리스트로 구현!
vector <vector <NODE> > graph;

// 개선된 알고리즘
vector <int> d;

priority_queue <NODE> pq;

void print_graph()
{
	printf("graph : \n");

	// size가 (n + 1)이기 때문에 사이즈보다 작게 돈다!
	for (int i = 1; i < graph.size(); i++)
	{
		if (graph[i].size() > 0)
		{
			printf("%d -> ", i);

			for (int j = 0; j < graph[i].size(); j++)
			{
				printf("(%d, %d) ", graph[i][j].next, graph[i][j].cost);
			}

			printf("\n");
		}
	}

	return;
}

void print_d()
{
	printf("d : ");

	for (int i = 1; i < graph.size(); i++)
	{
		printf("%d ", d[i]);
	}

	printf("\n");

	return;
}

void dijkstra(int s)
{
	int n = 0;
	int c = 0;
	int x = 0;
	int y = 0;

	NODE cur;

	// 우선순위 큐에 시작점 넣기
	cur.next = s;
	cur.cost = 0;

	pq.push(cur);

	// 큐가 비면 종료
	while (!pq.empty())
	{
		// 꺼내자
		cur = pq.top();
		pq.pop();

		n = cur.next;
		c = cur.cost;

		// printf("n = %d, c = %d\n", n, c);

		// 현재 정점에서 인접한 모든 정점 탐색
		for (int j = 0; j < graph[n].size(); j++)
		{
			x = c + graph[n][j].cost;
			y = d[graph[n][j].next];

			// printf("j = %d, x = %d, y = %d\n", j, x, y);

			// 현재까지 저장된 최단거리보다 이 방법이 더 가까울 경우
			if (x < y)
			{
				// 거리 갱신
				d[graph[n][j].next] = x;

				// 큐에 넣는다
				cur.next = graph[n][j].next;
				cur.cost = x;

				pq.push(cur);
			}
		}

		// print_d();
	}

	return;
}

int main()
{
	int v = 0;
	int e = 0;
	int k = 0; // 시작 정점의 번호
	int start = 0; // 간선 시작
	int end = 0; // 간선 끝
	int w = 0; // 간선 가중치

	NODE tmp;

	scanf("%d %d", &v, &e);

	// 벡터 크기 조정
	graph.resize(v + 1);
	d.resize(v + 1);

	// 무한대로 초기화
	for (int i = 1; i < d.size(); i++)
	{
		d[i] = INF;
	}

	// print_d();
	
	scanf("%d", &k);

	// 출발점은 0으로 초기화
	d[k] = 0;

	for (int i = 0; i < e; i++)
	{
		// 다중 간선이 존재할 수도 있다!
		// 하지만 pq 쓰면 ㄱㅊ
		scanf("%d %d %d", &start, &end, &w);

		tmp.next = end;
		tmp.cost = w;

		// 방향 그래프다! 한쪽만
		graph[start].push_back(tmp);
	}

	// print_graph();

	// 다익스트라 알고리즘
	dijkstra(k);

	for (int i = 1; i < d.size(); i++)
	{
		if (d[i] == INF)
		{
			printf("INF\n");
		}
		else
		{
			printf("%d\n", d[i]);
		}
	}

	return 0;
}

// 강사님 코드
/*
#include<cstdio>
#include<vector>
#include<queue>
using namespace std;

typedef struct _edge {
	int b;
	int c;


}edge;

bool operator<(edge a, edge b) {
	return a.c > b.c;
}


vector<edge> adj[20001];
int arr[20001];
priority_queue<edge> pq;


int main(void) {
	int v, e;
	scanf("%d %d", &v, &e);

	int s;
	scanf("%d", &s);

	int a, b, c;
	int Inf = 300000;

	for (int i = 0; i < e; i++) {
		scanf("%d %d %d", &a, &b, &c);
		adj[a].push_back({ b,c });
	}


	for (int i = 1; i <= v; i++) arr[i] = Inf;

	arr[s] = 0;

	pq.push({ s,0 });


	while (!pq.empty()) {
		edge t = pq.top();
		pq.pop();

		int cur = t.b;
		int cst = t.c;

		for (int i = 0; i < adj[cur].size(); i++) {
			int idx = adj[cur][i].b;

			if ((cst + adj[cur][i].c) < arr[idx]) {
				arr[idx] = cst + adj[cur][i].c;
				pq.push({ idx,arr[idx] });
			}
		}
	}

	for (int i = 1; i <= v; i++) {
		if (arr[i] == Inf) printf("INF\n");
		else printf("%d\n", arr[i]);
	}


	return 0;
}
*/
