# define _CRT_SECURE_NO_WARNINGS
# include <stdio.h>

# define MAX 1001

int v = 0;
int e = 0;

int a = 0;
int b = 0;

int isVisited[MAX] = { 0 };
int isConnected[MAX][MAX] = { 0 };

int ans = 0;

void dfs_recursive(int now)
{
	//아직 탐색하지 않은 정점 중에서 현재 정점과 연결된 정점을 탐색
	for (int i = 1; i <= v; i++)
	{
		if ((isVisited[i] == 0) && (isConnected[now][i] != 0))
		{
			// 방문한 정점을 체크
			isVisited[i] = 1;

			dfs_recursive(i);
		}
	}
}

int main()
{
	// G(V, E)
	scanf("%d", &v);
	scanf("%d", &e);

	// printf("%d %d", v, e);

	// 입력 받기
	for (int i = 0; i < e; i++)
	{
		scanf("%d %d", &a, &b);

		isConnected[a][b] += 1;
		isConnected[b][a] += 1;
	}

	/*
	for (int i = 1; i <= v; i++)
	{
	printf("%d \n", isVisited[i]);
	}
	*/

	/*
	for (int i = 1; i <= v; i++)
	{
	printf("%d %d %d %d %d %d \n", isConnected[i][1], isConnected[i][2], isConnected[i][3], isConnected[i][4], isConnected[i][5], isConnected[i][6]);
	}
	*/

	// dfs 실행
	for (int i = 1; i <= v; i++)
	{
		if (isVisited[i] == 0)
		{
			//printf("%d \n", i);

			ans += 1;

			// 방문한 정점을 체크
			isVisited[i] = 1;

			dfs_recursive(i);

			/*
			for (int i = 1; i <= v; i++)
			{
			printf("%d", isVisited[i]);
			}
			*/
		}
	}

	printf("%d", ans);
}
