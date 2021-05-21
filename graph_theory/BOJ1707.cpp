// KJO1707.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#define _CRT_SECURE_NO_WARNINGS
#define MAX_K 5
#define MAX_V 20000
#define MAX_E 200000

/*
#include "pch.h"
#include <iostream>

#include <stdio.h>
#include <vector>

using namespace std;

// 인접 벡터
// vector < vector < int > > v1;

// 인접 리스트
vector < vector < int > > v2;

// 간선 리스트
vector < pair < int, int > > v3;

// 집합 표시
vector < int > isVisited;

// 이분 그래프인지 판별
int isAns = 0;

void init_v1(int vv)
{
	v1.clear();
	v1.resize(vv + 1);

	for (int r = 0; r < v1.size(); r++)
	{
		v1[r].resize(vv + 1, 0);
	}

	return;
}

void init_v2(int vv)
{
	vector < int > tmp;

	v2.clear();
	v2.resize(vv + 1);

	for (int r = 0; r < v2.size(); r++)
	{
		v2[r].reserve(vv + 1);
		v2[r].push_back(0);
	}

	// 쓰레기값
	// v2.push_back(tmp);

	return;
}

void init_v3(int ee)
{
	v3.clear();
	v3.reserve(ee + 1);

	// 쓰레기값
	v3.push_back(make_pair(0, 0));

	return;
}

void init_isVisited(int vv)
{
	isVisited.clear();
	isVisited.resize(vv + 1, 0);

	return;
}

void print_v1()
{
	printf("v1 : \n");

	for (int r = 1; r < v1.size(); r++)
	{
		for (int c = 1; c < v1[r].size(); c++)
		{
			printf("%d ", v1[r][c]);
		}

		printf("\n");
	}

	return;
}

void print_v2()
{
	printf("v2 : \n");

	for (int r = 1; r < v2.size(); r++)
	{
		for (int c = 1; c < v2[r].size(); c++)
		{
			printf("%d ", v2[r][c]);
		}

		printf("\n");
	}

	return;
}

void print_v3()
{
	printf("v3 : \n");

	for (int i = 1; i < v3.size(); i++)
	{
		printf("%d %d\n", v3[i].first, v3[i].second);
	}

	return;
}

void print_isVisited()
{
	printf("isVisited : ");

	for (int i = 1; i < isVisited.size(); i++)
	{
		printf("%d ", isVisited[i]);
	}

	printf("\n");

	return;
}

void backtrack1(int start)
{
	// 이미 이분그래프 찾았으면
	if (isAns)
	{
		// 더 할 필요 없다
		return;
	}

	// 모든 원소를 집합에 배분했다면
	if (start == isVisited.size() - 1)
	{
		// 정답 찾은 것
		isAns = 1;

		// 더 할 필요 없다
		return;
	}

	// start + 1번째 원소 확인
	int check_1 = 0;
	int check_2 = 0;

	// 이전 집합 확인
	for (int i = 1; i <= start; i++)
	{
		// 해당 원소와 연결되어 있다면
		if (v1[start + 1][i])
		{
			// 집합 1의 원소라면
			if (isVisited[i] == 1)
			{
				// 연결되어 있다고 표시
				check_1 = 1;
			}

			// 집합 2의 원소라면
			if (isVisited[i] == 2)
			{
				// 연결되어 있다고 표시
				check_2 = 2;
			}
		}
	}

	// 집합 1에 포함될 수 있다면
	if (!check_1)
	{
		// 집합 1
		isVisited[start + 1] = 1;
		backtrack1(start + 1);
		isVisited[start + 1] = 0;
	}

	// 집합 2에 포함될 수 있다면
	if (!check_2)
	{
		// 집합 2
		isVisited[start + 1] = 2;
		backtrack1(start + 1);
		isVisited[start + 1] = 0;
	}

	return;
}

void backtrack2(int start)
{
	// printf("start = %d\n", start);
	// print_isVisited();

	// 이미 이분그래프 찾았으면
	if (isAns)
	{
		// 더 할 필요 없다
		return;
	}

	// 모든 원소를 집합에 배분했다면
	if (start == isVisited.size() - 1)
	{
		// 정답 찾은 것
		isAns = 1;

		// 더 할 필요 없다
		return;
	}

	// start + 1번째 원소 확인
	int check_1 = 0;
	int check_2 = 0;

	// 이전 집합 확인
	for (int j = 1; j < v2[start + 1].size(); j++)
	{
		for (int i = 1; i <= start; i++)
		{
			// printf("i = %d, j = %d\n", i, j);

			// 해당 원소와 연결되어 있다면
			if (v2[start + 1][j] == i)
			{
				// 집합 1의 원소라면
				if (isVisited[i] == 1)
				{
					// 연결되어 있다고 표시
					check_1 = 1;
				}

				// 집합 2의 원소라면
				if (isVisited[i] == 2)
				{
					// 연결되어 있다고 표시
					check_2 = 2;
				}
			}
		}
	}

	// printf("check = (%d, %d)\n", check_1, check_2);

	// 집합 1에 포함될 수 있다면
	if (!check_1)
	{
		// 집합 1
		isVisited[start + 1] = 1;
		backtrack2(start + 1);
		isVisited[start + 1] = 0;
	}

	// 집합 2에 포함될 수 있다면
	if (!check_2)
	{
		// 집합 2
		isVisited[start + 1] = 2;
		backtrack2(start + 1);
		isVisited[start + 1] = 0;
	}

	return;
}

void backtrack3(int start)
{
	// 이미 이분그래프 찾았으면
	if (isAns)
	{
		// 더 할 필요 없다
		return;
	}

	// 모든 원소를 집합에 배분했다면
	if (start == v3.size())
	{
		// 정답 찾은 것
		isAns = 1;

		// 더 할 필요 없다
		return;
	}

	printf("start = %d\n", start);
	print_isVisited();

	// 각 간선 확인
	for (int i = start + 1; i < v3.size(); i++)
	{
		// 시작점
		int s = v3[i].first;
		// 도착점
		int e = v3[i].second;

		printf("v3[%d] = (%d, %d), isVisited = (%d, %d)\n", i, s, e, isVisited[s], isVisited[e]);

		// 시작점과 도착점 모두 집합 있는 경우
		if ((isVisited[s]) && (isVisited[e]))
		{
			// 두 집합이 같다면
			if (isVisited[s] == isVisited[e])
			{
				// 불가능
				return;
			}
		}
		// 시작점만 집합 있는 경우
		else if (isVisited[s])
		{
			// 도착점은 다른 집합으로
			isVisited[e] = (isVisited[s] % 2) + 1;
			backtrack3(i);
			isVisited[e] = 0;
		}
		// 도착점만 집합 있는 경우
		else if (isVisited[e])
		{
			// 시작점은 다른 집합으로
			isVisited[s] = (isVisited[e] % 2) + 1;
			backtrack3(i);
			isVisited[s] = 0;
		}
		// 시작점과 도착점 모두 집합 없는 경우
		else
		{
			// 서로 다른 집합으로
			// 여기가 DFS!
			// 경우 1
			isVisited[s] = 1;
			isVisited[e] = 2;
			backtrack3(i);
			isVisited[s] = 0;
			isVisited[e] = 0;

			// 경우 2
			isVisited[s] = 2;
			isVisited[e] = 1;
			backtrack3(i);
			isVisited[s] = 0;
			isVisited[e] = 0;
		}
	}

	return;
}

int check()
{
	// 각 간선을 탐색하면서 확인
	for (int i = 1; i < v3.size(); i++)
	{
		// 같은 간선이라면
		if (isVisited[v3[i].first] == isVisited[v3[i].second])
		{
			// 불가능
			return 0;
		}
	}

	// 나머지는 가능
	return 1;
}

void make_set(int start)
{
	// 이미 이분그래프 찾았으면
	if (isAns)
	{
		// 더 할 필요 없다
		return;
	}

	if (start == isVisited.size() - 1)
	{
		print_isVisited();

		// 다 만들어 졌으면 확인
		int result = check();

		// 이분 그래프 맞다면
		if (result)
		{
			// 정답 찾은 것
			isAns = 1;
		}

		// 더 할 필요 없다
		return;
	}

	// 집합 1
	isVisited[start + 1] = 1;
	make_set(start + 1);
	// isVisited[start + 1] = 0;

	// 집합 2
	isVisited[start + 1] = 2;
	make_set(start + 1);
	// isVisited[start + 1] = 0;

	return;
}

int main()
{
    // std::cout << "Hello World!\n"; 

	int k = 0;
	int vv = 0;
	int ee = 0;
	int s = 0;
	int e = 0;

	scanf("%d", &k);

	for (int t = 1; t <= k; t++)
	{
		scanf("%d %d", &vv, &ee);

		init_v1(vv);
		init_isVisited(vv);

		isAns = 0;

		for (int i = 0; i < ee; i++)
		{
			scanf("%d %d", &s, &e);

			v1[s][e] = 1;
			v1[e][s] = 1;
		}

		// print_v();
		// print_isVisited();

		backtrack(0);

		// 정답 찾았다면
		if (isAns)
		{
			printf("YES\n");
		}
		// 정답 못 찾았다면
		else
		{
			printf("NO\n");
		}
	}

	return 0;
}

void make_v2(int vv)
{
	// 각 정점에는 1부터 vv까지 차례로 번호가 붙어 있다!
	for (int i = 1; i <= vv; i++)
	{
		vector < int > tmp;

		tmp.reserve(vv + 1);

		// 간선 탐색
		for (int j = 1; j < v3.size(); j++)
		{
			// 시작점이 i번째 정점이라면
			if (v3[j].first == i)
			{
				// 벡터에 추가
				tmp.push_back(v3[j].first);
			}

			// 도착점이 i번째 정점이라면
			if (v3[j].second == i)
			{
				// 벡터에 추가
				tmp.push_back(v3[j].second);
			}
		}

		// 한 정점에 대한 인접 리스트 완성
		v2.push_back(tmp);
	}
}

int main()
{
	int k = 0;
	int vv = 0;
	int ee = 0;
	int s = 0;
	int e = 0;

	scanf("%d", &k);

	for (int t = 1; t <= k; t++)
	{
		scanf("%d %d", &vv, &ee);

		// init_v2(vv);
		init_v3(ee);
		init_isVisited(vv);

		// printf("v2.size() = %d\n", v2.size());

		isAns = 0;

		for (int i = 0; i < ee; i++)
		{
			scanf("%d %d", &s, &e);

			// printf("s = %d, e = %d\n", s, e);

			v3.push_back(make_pair(s, e));

			// v2[s].push_back(e);
			// v2[e].push_back(s);

			// print_v2();
		}

		// make_v2(vv);

		// print_v2();
		// print_v3();
		// print_isVisited();

		// backtrack2(0);
		// backtrack3(0);
		make_set(0);

		// 정답 찾았다면
		if (ans)
		{
			printf("YES\n");
		}
		// 정답 못 찾았다면
		else
		{
			printf("NO\n");
		}

		// 정답 찾았다면
		if (isAns)
		{
			printf("YES\n");
		}
		// 정답 못 찾았다면
		else
		{
			printf("NO\n");
		}
	}

	return 0;
}
*/

// 나중에 공부하자...
// 아니 나는 왜 안되냐구요
#include <iostream>
#include <vector>

using namespace std;

vector<int> G[20001];
int color[20001];      //1일때는 빨강, 2일때는 파랑, 0일때는 접근X

void DFS(int node, int c) {
	color[node] = c;
	for (int i = 0; i < G[node].size(); i++) {
		int next = G[node][i];
		if (color[next] == 0) {
			DFS(next, 3 - c); //빨강 다음에는 파랑이여야하고 파랑 다음은 빨강이여야 함.
							//따락서 3-1 = 2, 3-2 = 1
		}
	}
}
int main() {
	int t;
	cin >> t;
	while (t--) {
		int n, m;
		cin >> n >> m;
		for (int i = 1; i <= n; i++) {
			G[i].clear();
			color[i] = 0;
		}
		for (int i = 0; i < m; i++) {
			int u, v;
			cin >> u >> v;
			G[u].push_back(v);
			G[v].push_back(u);
		}
		for (int i = 1; i <= n; i++) {
			if (color[i] == 0) {
				DFS(i, 1);
			}
		}
		bool isBin = true;
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j < G[i].size(); j++) {
				int k = G[i][j];
				if (color[i] == color[k])
					isBin = false;
			}
		}
		if (isBin)
			cout << "YES" << "\n";
		else
			cout << "NO" << "\n";
	}
	return 0;
}
// 출처 : https://jongnan.tistory.com/entry/%EB%B0%B1%EC%A4%80-1707-%EC%9D%B4%EB%B6%84-%EA%B7%B8%EB%9E%98%ED%94%84

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
