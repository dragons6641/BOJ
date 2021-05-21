#define _CRT_SECURE_NO_WARNINGS
#define INF 9000000000000000000
#define START 1
#define ll long long

#include <stdio.h>
#include <vector>

using namespace std;

typedef struct node
{
	int s = 0;
	int d = 0;
	int c = 0;
}
NODE;

// 간선 리스트로 구현!
// 크기는 간선의 갯수 + 1
vector <NODE> graph;

// 최단 거리 정보
// 크기는 정점의 갯수 + 1
vector <ll> d;

// 경로 저장
// 크기는 정점의 갯수 + 1
vector <ll> p;

void print_graph()
{
	printf("graph : \n");

	for (int i = 1; i < graph.size(); i++)
	{
		printf("(%d -> %d), %d\n", graph[i].s, graph[i].d, graph[i].c);
	}

	printf("\n");

	return;
}

void print_d()
{
	printf("d : ");

	for (int i = 1; i < d.size(); i++)
	{
		printf("%d ", d[i]);
	}

	printf("\n");

	return;
}

void print_p()
{
	printf("p : ");

	for (int i = 1; i < p.size(); i++)
	{
		printf("%d ", p[i]);
	}

	printf("\n");

	return;
}

int bellman_ford(int s)
{
	int cur_s = 0;
	int cur_d = 0;
	int cur_c = 0;
	ll result = 0;

	// 모든 정점에 대해서
	for (int i = 1; i < d.size(); i++)
	{
		// 모든 간선에 대해서
		for (int j = 1; j < graph.size(); j++)
		{
			cur_s = graph[j].s;
			cur_d = graph[j].d;
			cur_c = graph[j].c;

			// 도착점의 최단 거리가 현재 거리보다 더 작다면
			if ((d[cur_s] + cur_c < d[cur_d]))
			{
				//printf("s = %d, d = %d, c = %d\n", cur_s, cur_d, cur_c);

				// 시작점이 무한대이면 연산 X!
				if (d[cur_s] != INF)
				{
					// 거리 정보 반영
					d[cur_d] = d[cur_s] + cur_c;

					// 어디로부터 왔는지 표시
					p[cur_d] = cur_s;
				}

				/*
				print_d();
				print_p();
				*/
			}
		}
	}

	// 음의 사이클 확인
	// 모든 간선에 대해서
	for (int j = 1; j < graph.size(); j++)
	{
		cur_s = graph[j].s;
		cur_d = graph[j].d;
		cur_c = graph[j].c;

		// 도착점의 최단 거리가 현재 거리보다 더 작다면
		if (d[cur_s] + cur_c < d[cur_d])
		{
			// 음의 사이클이 있다!
			result = -1;

			break;
		}
	}

	// printf("%d\n", d[cur_s]);

	// 음의 사이클이 있을 경우
	if (result == -1)
	{
		// 음의 사이클에 도달할 수 없다면
		if (d[cur_s] == INF)
		{
			// 시간이 무한정 되돌려지진 않는다!
			result = 0;
		}
	}

	// printf("result = %d\n", result);

	return result;
}

int main()
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);
	// freopen("input3.txt", "r", stdin);

	setbuf(stdout, NULL);

	int n = 0;
	int m = 0;
	int a = 0; // 시작 도시
	int b = 0; // 도착 도시
	int c = 0; // 이동 시간
	ll ans = 0; // 최단 거리

	NODE tmp;

	scanf("%d %d", &n, &m);

	// 벡터 크기 조정
	d.resize(n + 1);
	p.resize(n + 1);

	// 무한대로 초기화
	for (int i = 1; i < d.size(); i++)
	{
		d[i] = INF;
	}

	// 출발점은 0으로
	d[START] = 0;

	// 쓰레기값
	graph.push_back(tmp);

	for (int i = 0; i < m; i++)
	{
		scanf("%d %d %d", &a, &b, &c);

		tmp.s = a;
		tmp.d = b;
		tmp.c = c;

		// 방향 그래프다! 한쪽만
		graph.push_back(tmp);
	}

	// print_graph();

	/*
	print_d();
	print_p();
	*/

	// 벨만-포드 알고리즘
	ans = bellman_ford(START);

	/*
	print_d();
	print_p();
	*/

	// 사이클이 있는 경우
	if (ans == -1)
	{
		printf("%d\n", ans);
	}
	// 경로 전체 출력
	else
	{
		for (int i = 2; i < d.size(); i++)
		{
			// 불가능한 경우
			if (d[i] == INF)
			{
				ans = -1;

				printf("%d\n", ans);
			}
			// 일반적인 경우
			else
			{
				printf("%d\n", d[i]);
			}
		}
	}

	return 0;
}

// 강사님 코드
/*
#include <cstdio>
#define MAX_VALUE 500*10000+1
int path[6001][3];
int dist[501];

int main()
{
	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++) {
		// 시작점에서 각 정점으로 가는 최단 거리 저장 배열 초기화
		dist[i] = MAX_VALUE;
	}

	for (int i = 1; i <= m; i++) {
		scanf("%d %d %d", &path[i][0], &path[i][1], &path[i][2]);
	}
	// 1번 정점이 시작점, 시작점까지의 최단거리는 0
	dist[1] = 0;
	for (int i = 1; i<n; i++) // 정점의 수 - 1 번 수행
	{
		for (int j = 1; j <= m; j++) // 모든 간선을 사용하여 최단거리가 줄어들면 정보 갱신
		{
			if (dist[path[j][0]] != MAX_VALUE &&  dist[path[j][1]] > dist[path[j][0]] + path[j][2])
			{
				dist[path[j][1]] = dist[path[j][0]] + path[j][2];
			}
		}
	}

	// 음수 cycle 확인
	// 만약 음수 cycle이 없다면 시작점에서 모든 점으로 가는 최단거리는 갱신되어 있어야 한다.
	for (int j = 1; j <= m; j++)
	{
		// 만약 갱신되는 간선이 있다면 음수 cycle 존재
		if (dist[path[j][0]] != MAX_VALUE && dist[path[j][1]] > dist[path[j][0]] + path[j][2])
		{
			printf("-1");
			return 0;
		}
	}

	for (int i = 2; i <= n; i++) {
		if (dist[i] != MAX_VALUE) {
			printf("%d\n", dist[i]);
		}
		else {
			printf("-1\n");
		}
	}
}
*/
