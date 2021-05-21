#define _CRT_SECURE_NO_WARNINGS
#define ROOT 1
#define INF 1000000000

#include <stdio.h>
#include <vector>

using namespace std;

// 연결 리스트로 구현!
vector <vector <int> > graph;

// 방문 순서 표시
vector <int> order;

// 자신 이후로 방문하는 정점들 중
// 자신을 거치지 않고 방문할 수 있는
// order 중 가장 작은 값 표시
vector <int> low;

// 단절점을 기록해 둘 벡터
vector <int> ans;

// 임시 벡터
vector <int> vv;

// 방문 순서 기록할 전역 변수
int cnt = 0;

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
				printf("%d ", graph[i][j]);
			}

			printf("\n");
		}
	}

	return;
}

void print_order()
{
	printf("order : ");

	for (int i = 1; i < graph.size(); i++)
	{
		printf("%d ", order[i]);
	}

	printf("\n");

	return;
}

void print_low()
{
	printf("low : \t");

	for (int i = 1; i < graph.size(); i++)
	{
		printf("%d ", low[i]);
	}

	printf("\n");

	return;
}

void print_ans()
{
	int result = 0;

	for (int i = 1; i < ans.size(); i++)
	{
		if (ans[i] > 0)
		{
			result += 1;
		}
	}

	printf("%d\n", result);

	for (int i = 1; i < ans.size(); i++)
	{
		if (ans[i] > 0)
		{
			printf("%d ", i);
		}
	}

	printf("\n");

	return;
}

void print_v()
{
	for (int i = 1; i < ans.size(); i++)
	{
		if (ans[i] > 0)
		{
			vv.push_back(i);
		}
	}

	printf("%d\n", vv.size());

	for (int i = 0; i < vv.size(); i++)
	{
		printf("%d ", vv.at(i));
	}

	printf("\n");

	return;
}

int my_dfs(int cur, int depth)
{
	// 노드의 번호
	int idx = 0;

	// 리턴받은 값
	int result = INF;

	// 호출 횟수
	int check = 0;

	// 아직 방문하지 않았다면
	if (order[cur] == 0)
	{
		// 방문 순서 표시
		cnt += 1;
		order[cur] = cnt;

		// printf("cur = %d\n", cur);

		// 현재 정점과 연결된 정점마다 dfs 수행
		for (int j = 0; j < graph[cur].size(); j++)
		{
			idx = graph[cur][j];

			if (order[idx] == 0)
			{
				check += 1;

				result = my_dfs(idx, depth + 1);

				// printf("result = %d, cur = %d, order = %d, check = %d, depth = %d\n", result, cur, order[cur], check, depth);

				// printf("cur = %d, idx = %d\n", cur, idx);

				// 단절점 여부 확인
				// 리턴받은 값이 나의 순서라면 단절점
				if (result == order[cur])
				{
					ans[cur] = 1;
				}
			}
		}
	}

	for (int j = 0; j < graph[cur].size(); j++)
	{
		idx = graph[cur][j];

		// low 값 찾기
		// 처음 기록이라면
		if (low[cur] == 0)
		{
			// 일단 기록
			low[cur] = order[idx];
		}

		// 해당 노드의 방문 순서가 기존 값보다 더 작으면
		if (order[idx] < low[cur])
		{
			// 일단 기록
			low[cur] = order[idx];
		}
	}

	// printf("result = %d, low = %d\n", result, low[cur]);

	if (low[cur] < result)
	{
		result = low[cur];
	}

	// 시작 노드일 경우 따로 처리!
	if (depth == 1)
	{
		/*
		// 연결된 간선이 없거나 하나면 단절점 아님
		if (graph[cur].size() <= 1)
		{
			ans[cur] = 0;
		}
		// 사이클이 있는 경우를 어떻게??
		else
		{
			ans[cur] = 1;
		}
		*/

		if (check <= 1)
		{
			ans[cur] = 0;
		}
		else
		{
			ans[cur] = 1;
		}
	}
	
	return result;
}

int my_main()
{
	int v = 0;
	int e = 0;
	int a = 0;
	int b = 0;

	scanf("%d %d", &v, &e);

	// 벡터 사이즈 지정
	graph.resize(v + 1);
	order.resize(v + 1);
	low.resize(v + 1);
	ans.resize(v + 1);

	for (int i = 0; i < e; i++)
	{
		scanf("%d %d", &a, &b);

		// 무향 그래프이므로 양쪽 모두에 표시
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	// print_graph();

	// 모든 정점에 대해 dfs 수행
	// 무조건 크기보다는 작게 돌아야 한다!
	for (int i = 1; i < graph.size(); i++)
	{
		if (order[i] == 0)
		{
			my_dfs(i, ROOT);
		}
	}

	/*
	print_order();
	print_low();
	*/

	// print_ans();

	print_v();

	return 0;
}

// 강사님 코드
///*
#include<iostream>
#include<vector>
using namespace std;
vector<vector<int>> v(10001);
int check[10001];
int checknum[10001];
int answer;
int num = 0;
int dfs(int a, int b)
{
	check[a] = 1;
	num++;
	checknum[a] = num;
	if (b == 0)
	{
		num = 1;
		checknum[a] = 1;
		int check1 = 0;
		for (int i = 0; i<v[a].size(); i++)
		{
			if (check[v[a][i]] == 0)
			{
				check1++;
				dfs(v[a][i], num);
			}
		}
		if (check1>1)
		{
			answer++;
			check[a] = 2;
		}
	}
	else
	{
		int low = 2e9, temp;
		for (int i = 0; i<v[a].size(); i++)
		{
			if (checknum[v[a][i]] == 0)
			{

				temp = dfs(v[a][i], 1);
				if (temp<low)	low = temp;
				if (checknum[a] == temp&&check[a] == 1)
				{
					answer++;
					check[a] = 2;
				}
			}
			else {
				if (checknum[v[a][i]]<low)	low = checknum[v[a][i]];
			}
		}


		return low;
	}
}
int main()
{
	int n, m;
	cin >> n >> m;
	for (int i = 0; i<m; i++)
	{
		int a, b;
		cin >> a >> b;
		v[a].push_back(b);
		v[b].push_back(a);
	}
	for (int i = 1; i <= n; i++)
	{
		if (check[i] == 0)
		{
			dfs(i, 0);
		}
	}
	cout << answer << "\n";
	for (int i = 1; i <= n; i++)
	{
		if (check[i] == 2)
		{
			cout << i << " ";
		}
	}
}
//*/
