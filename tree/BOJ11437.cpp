/*
#define _CRT_SECURE_NO_WARNINGS
#define MAX_N 100000
#define ROOT 1

// 2^16 = 65536
#define MAX_POW 20

#include <stdio.h>
#include <vector>

using namespace std;

// 이진 트리가 아니다!
// 인접 리스트로 트리 구현해야 함
// 이중 벡터
vector< vector <int> > tree;

// 노드의 부모 표시
// 2차원 DP!
// [K][V]
// K : 2의 K승(MAX_POW + 1개)
// V : 그 때의 부모(node개)
vector< vector <int> > parent;

// 노드의 깊이 표시
vector <int> depth;

// 함수 바꿔라
void print_parent()
{
printf("parent : \n");

for (int i = 0; i < parent.size(); i++)
{
for (int j = 1; j < parent[i].size(); j++)
{
printf("%d ", parent[i][j]);
}

printf("\n");
}

return;
}

void print_depth()
{
printf("depth : ");

for (int i = 1; i < depth.size(); i++)
{
printf("%d ", depth[i]);
}

printf("\n");

return;
}

void print_tree()
{
printf("tree : \n");

// size가 (n + 1)이기 때문에 사이즈보다 작게 돈다!
for (int i = 1; i < tree.size(); i++)
{
if (tree[i].size() > 0)
{
printf("%d -> ", i);

for (int j = 0; j < tree[i].size(); j++)
{
printf("%d ", tree[i][j]);
}

printf("\n");
}
}

return;
}

// 최소 공통 조상 찾기
// 2의 거듭제곱을 곱하거나 나누면 shift 연산으로!
// 2의 거듭제곱 구한 값을 미리 배열에 넣어둬도 좋다!
int LCA(int x, int y)
{
int x_depth = depth[x];
int y_depth = depth[y];
int x_tmp = x_depth;
int y_tmp = y_depth;
int diff = x_tmp - y_tmp;
int result = 0;

// printf("x_depth : %d, y_depth : %d\n", x_depth, y_depth);
// printf("x : %d, y : %d\n", x, y);

// 깊이 같게 맞추기
while (1)
{
x_tmp = x_depth;
y_tmp = y_depth;
diff = x_tmp - y_tmp;

// x가 더 아래
if (diff > 0)
{
for (int i = 0; i < parent.size(); i++)
{
x_tmp -= (1 << i);

// 깊이를 2의 거듭제곱만큼 줄임
// 그 값으로 인해 더 높아지면
if ((x_tmp < y_tmp) || (x_tmp <= 1))
{
// printf("x_tmp : %d, y_tmp : %d\n", x_tmp, y_tmp);

x_depth -= (1 << (i - 1));
x = parent[i - 1][x];

// printf("x_depth : %d, y_depth : %d\n", x_depth, y_depth);
// printf("x : %d, y: %d\n", x, y);

break;
}
}
}
// y가 더 아래
else if (diff < 0)
{
for (int i = 0; i < parent.size(); i++)
{
y_tmp -= (1 << i);

// 깊이를 2의 거듭제곱만큼 줄임
// 그 값으로 인해 더 높아지면
if ((y_tmp < x_tmp) || (y_tmp <= 1))
{
// printf("x_tmp : %d, y_tmp : %d\n", x_tmp, y_tmp);

y_depth -= (1 << (i - 1));
y = parent[i - 1][y];

// printf("x_depth : %d, y_depth : %d\n", x_depth, y_depth);
// printf("x : %d, y : %d\n", x, y);

break;
}
}
}
// 같으면
else
{
// printf("x_depth : %d, y_depth : %d\n", x_depth, y_depth);
// printf("x : %d, y : %d\n", x, y);

// 다음 단계 수행
break;
}
}

// 이미 같으면
if (x == y)
{
result = x;

return result;
}
// 바로 위에 있으면
else if (parent[0][x] == parent[0][y])
{
// 정답 찾았다
result = parent[0][x];

return result;
}
// 같지 않으면
else
{
// 공통 부모 찾기
while (1)
{
// 거꾸로 루프 돈다!
// 처음으로 달라지는 것 찾기
for (int i = parent.size() - 1; i >= 0; i--)
{
// printf("i = %d, parent[i][x] = %d, parent[i][y] = %d\n", i, parent[i][x], parent[i][y]);

// 다르면
if (parent[i][x] != parent[i][y])
{
// 값 수정
x = parent[i][x];
y = parent[i][y];

// 부모가 같으면
if (parent[0][x] == parent[0][y])
{
// 정답 찾았다
result = parent[0][x];

return result;
}
}
}
}
}

return result;
}

int my_main()
{
int n = 0;
int m = 0;
int a = 0;
int b = 0;
int ans = 0;
int cur = 0;

vector <int> tmp;

scanf("%d", &n);

// 값을 받으면 트리 사이즈 재조정!
// 항상 (n + 1)만큼 해줘야 오류가 없다!
tree.resize(n + 1);
depth.resize(n + 1);

// 2차원 벡터 resize
// 크기는 반드시 n + 1!
for (int i = 0; i <= MAX_POW; i++)
{
tmp.resize(n + 1);
parent.push_back(tmp);
}

// printf("%d %d\n", parent.size(), parent[0].size());

// 트리의 간선 갯수는 n - 1개
for (int i = 0; i < n - 1; i++)
{
// 연결된 정점 정보
scanf("%d %d", &a, &b);

// 무향 그래프이므로 양쪽 모두에 표시
tree[a].push_back(b);
tree[b].push_back(a);
}

// 루트의 부모는 없음
parent[0][ROOT] = 0;

// 루트의 깊이는 1
depth[ROOT] = 1;

// parent 배열과 depth 배열 만들기
for (int i = 2; i < tree.size(); i++)
{
for (int j = 0; j < tree[i].size(); j++)
{
cur = tree[i][j];

// 아직 깊이가 정해지지 않았다면
if (depth[cur] == 0)
{
// 응 안해~
}
// 이미 깊이가 정해졌다면
else
{
// 그분이 부모입니다...
parent[0][i] = cur;

// 내 깊이는 부모 + 1
depth[i] = depth[cur] + 1;

// 부모는 한 명 뿐
break;
}
}
}

// printf("%d %d\n", parent.size(), parent[0].size());

// parent 벡터 완성하자
// i는 거듭제곱
for (int i = 1; i < parent.size(); i++)
{
// j는 노드
for (int j = 1; j < parent[i].size(); j++)
{
// parent[i][j] : j번 노드의 2^i번째 조상
parent[i][j] = parent[i - 1][parent[i - 1][j]];
}
}

// 트리 잘 만들었다~
// print_tree();
// print_parent();
// print_depth();

scanf("%d", &m);

for (int i = 0; i < m; i++)
{
// LCA 구하고 싶은 정점 정보
scanf("%d %d", &a, &b);

ans = LCA(a, b);

printf("%d\n", ans);
}

return 0;
}
*/

// 강사님 코드
///*
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
#define KMAX 17 // 2^17 = 131072
int N, M;
vector <int> adj[100001];
queue <int> que;
int depth[100001];
int par[KMAX + 1][100001];
int main()
{
	scanf("%d", &N);
	for (int i = 0; i <= N; i++)
	{
		depth[i] = -1;
		adj[i].clear();
		for (int k = 0; k < KMAX + 1; k++) par[k][i] = 0;
	}
	for (int i = 1; i < N; i++)
	{
		int from, to;
		scanf("%d %d", &from, &to);
		adj[from].push_back(to);
		adj[to].push_back(from);
	}
	// 트리 만들기
	depth[1] = 0;
	par[0][1] = 1;
	que.push(1);
	while (!que.empty())
	{
		int node = que.front(); que.pop();
		int len = adj[node].size();
		for (int i = 0; i < len; i++)
		{
			int nnode = adj[node][i];
			if (depth[nnode] == -1)
			{
				par[0][nnode] = node; //nnode의 부모는 node
				depth[nnode] = depth[node] + 1; // depth 갱신
				que.push(nnode);
			}
		}
	}

	// make sparse table
	for (int k = 1; k < KMAX + 1; k++)
	{
		for (int n = 1; n <= N; n++)
		{
			// n의 2^k번째 조상은 n의 2^(k-1)번째 조상의 2^(k-1)번째 조상.
			// 2^k = 2^(k-1) + 2^(k-1)
			par[k][n] = par[k - 1][par[k - 1][n]];
		}
	}

	scanf("%d", &M);
	for (int i = 0, a, b; i < M; i++)
	{
		scanf("%d %d", &a, &b);

		//a의 높이를 b와 맞춘다.
		if (depth[a] < depth[b])
		{
			for (int k = KMAX; k >= 0; k--)
			{
				while (a != b && depth[par[k][b]] >= depth[a]) b = par[k][b];
			}
		}
		else if (depth[a] > depth[b])
		{
			for (int k = KMAX; k >= 0; k--)
			{
				while (a != b && depth[par[k][a]] >= depth[b]) a = par[k][a];
			}
		}

		int ans;

		//유사 binary search
		for (int k = KMAX; k >= 0; k--)
		{
			while (a != b && par[k][a] != par[k][b])
			{
				a = par[k][a];
				b = par[k][b];
			}
		}

		// 두 노드가 같다면 -> a는 b의 조상. -> LCA = a
		if (a == b) ans = a;
		else ans = par[0][a];
		printf("%d\n", ans);
	}
}
