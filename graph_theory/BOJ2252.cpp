#define _CRT_SECURE_NO_WARNINGS
#define MAX_N 32000

#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

typedef struct node
{
	int e = -1;
	int v = -1;
}
NODE;

struct Compare
{
	bool operator() (const NODE x, const NODE y)
	{
		return x.e > y.e;
	}
}
;

priority_queue< NODE, vector<NODE>, Compare > pq;

int arr[MAX_N + 1];

// >> 연산자와 구분하기 위해 사이에 공백 넣기
vector< vector<int> > v(MAX_N + 1);
vector<int> cycle;

void arr_init()
{
	for (int i = 1; i <= MAX_N; i++)
	{
		// -1로 초기화해야 오류가 없다!
		arr[i] = -1;
	}

	return;
}

void print_arr()
{
	printf("arr : \n");

	for (int i = 1; i <= MAX_N; i++)
	{
		if (arr[i] >= 0)
		{
			printf("%d %d\n", i, arr[i]);
		}
	}

	printf("\n");

	return;
}

void print_vector()
{
	printf("vector : \n");

	for (int i = 1; i <= MAX_N; i++)
	{
		if (v[i].size() > 0)
		{
			printf("%d -> ", i);

			for (int j = 0; j < v[i].size(); j++)
			{
				printf("%d ", v[i][j]);
			}

			printf("\n");
		}
	}

	return;
}

void prev_topo_sort()
{
	int flag = 0;
	int min_index = -1;
	int min_value = MAX_N;

	// 모두 -1일때까지
	while (1)
	{
		flag = 1;
		min_index = -1;
		min_value = MAX_N;

		cycle.clear();

		// print_arr();

		// 배열을 순회
		for (int i = 1; i <= MAX_N; i++)
		{
			// print_arr();

			if ((arr[i] <= min_value) && (arr[i] > 0))
			{
				if (arr[i] == min_value)
				{
					cycle.push_back(i);
				}
				else
				{
					cycle.clear();
					cycle.push_back(i);
				}

				min_index = i;
				min_value = arr[i];

				// printf("min %d ", min_index);
			}

			// 자기 자신을 가리키는 간선이 없는 정점이라면
			if (arr[i] == 0)
			{
				// 줄 세운다
				printf("%d ", i);

				// 정점을 없앤다
				arr[i] = -1;

				// 간선을 없앤다
				for (int j = 0; j < v[i].size(); j++)
				{
					arr[v[i][j]] -= 1;
				}

				flag = 0;

				break;
			}
		}

		// printf("\n");

		// 모두 -1일 경우
		if (flag == 1)
		{
			// 사이클
			if (min_index != -1)
			{
				// printf("CYCLE ");

				/*
				for (int i = 0; i < cycle.size(); i++)
				{
					printf("%d ", cycle[i]);
				}
				*/

				for (int i = 0; i < cycle.size(); i++)
				{
					// 줄 세운다
					printf("%d ", cycle[i]);

					// 정점을 없앤다
					arr[cycle[i]] = -1;

					// 간선을 없앤다
					for (int j = 0; j < v[cycle[i]].size(); j++)
					{
						arr[v[cycle[i]][j]] -= 1;
					}
				}
			}

			break;
		}
	}

	return;
}

void topo_sort()
{
	NODE cur;

	// 초기 세팅
	for (int i = 1; i <= MAX_N; i++)
	{
		if (arr[i] >= 0)
		{
			cur.e = arr[i];
			cur.v = i;

			pq.push(cur);
		}
	}

	// printf("%d \n", pq.size());

	while (!pq.empty())
	{
		// 하나 꺼냄
		cur = pq.top();
		pq.pop();

		// 줄 세운다
		if (arr[cur.v] >= 0)
		{
			printf("%d ", cur.v);

			// print_arr();

			// 정점을 없앤다
			arr[cur.v] = -1;

			// 간선을 없앤다
			for (int j = 0; j < v[cur.v].size(); j++)
			{
				arr[v[cur.v][j]] -= 1;
			}
		}

		/*
		// 초기 세팅
		for (int i = 1; i <= MAX_N; i++)
		{
			if (arr[i] == 0)
			{
				cur.e = arr[i];
				cur.v = i;

				pq.push(cur);
			}
		}
		*/
	}

	return;
}

int my_main()
{
	int n = 0;
	int m = 0;
	int a = 0;
	int b = 0;

	arr_init();

	scanf("%d %d", &n, &m);

	for (int i = 0; i < m; i++)
	{
		scanf("%d %d", &a, &b);

		// printf("%d %d\n", a, b);

		// 배열에 반영
		if (arr[a] == -1)
		{
			arr[a] = 0;
		}
		if (arr[b] == -1)
		{
			arr[b] = 0;
		}

		arr[b] += 1;

		// print_arr();

		// 벡터에 반영
		v[a].push_back(b);

		// print_vector();
	}

	/*
	print_arr();
	print_vector();
	*/

	topo_sort();

	printf("\n");

	return 0;
}

// 강사님 코드
int n, m;
vector<int> mp[32001];
int indegree[32001];
queue<int> q;

int main()
{
	int x, y;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= m; i++)
	{
		scanf("%d %d", &x, &y);
		mp[x].push_back(y);
		indegree[y]++;
	}

	for (int i = 1; i <= n; i++)
	{
		if (indegree[i] == 0)q.push(i);
	}

	for (int i = 1; i <= n; i++)
	{
		x = q.front(); q.pop();
		printf("%d ", x);

		for (int p : mp[x])
		{
			indegree[p]--;
			if (indegree[p] == 0)
				q.push(p);
		}
	}
	return 0;
}
