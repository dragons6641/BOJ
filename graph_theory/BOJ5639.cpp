#define _CRT_SECURE_NO_WARNINGS
#define MAX_N 10000
#define ROOT 1

#include <stdio.h>

using namespace std;

typedef struct node
{
	int v = -1;
	int p = -1;
	int lc = -1;
	int rc = -1;
}
NODE;

int n = 0;

NODE tree[MAX_N + 1];

void print_tree()
{
	printf("tree : \n");

	for (int i = 1; i <= 9; i++)
	{
		if (tree[i].v > 0)
		{
			printf("%d %d %d %d\n", tree[i].v, tree[i].p, tree[i].lc, tree[i].rc);
		}
	}

	printf("\n");

	return;
}

void postorder(int num)
{
	if (tree[num].lc != -1)
	{
		postorder(tree[num].lc);
	}

	if (tree[num].rc != -1)
	{
		postorder(tree[num].rc);
	}

	printf("%d\n", tree[num].v);

	return;
}

int my_main()
{
	int tmp = 0;
	int max_idx = 0;
	int next_idx = 0;

	/*
	while (scanf("%d", &tmp) != EOF)
	{
		n += 1;

		tree[n].v = tmp;
		tree[n].p = -1;
		tree[n].lc = -1;
		tree[n].rc = -1;
	}
	*/

	n = 9;

	for (int i = 1; i <= 9; i++)
	{
		scanf("%d", &tmp);

		tree[i].v = tmp;
		tree[i].p = -1;
		tree[i].lc = -1;
		tree[i].rc = -1;

		// print_tree();
	}

	// i는 자식, j는 부모
	for (int i = 2; i <= n; i++)
	{
		// 거꾸로
		for (int j = i - 1; j >= 0; j--)
		{
			printf("child = %d, parent = %d\n", tree[i].v, tree[j].v);

			// 저장된 값 없으면
			if (max_idx == 0)
			{
				max_idx = j;
			}
			// 이미 저장된 값과 비교
			else if (tree[j].v > tree[max_idx].v)
			{
				max_idx = j;
			}

			// 내가 제일 크면
			if (j == 0)
			{
				// 그나마 가장 컸던 노드의 오른쪽 자식으로 들어간다
				tree[i].p = max_idx;
				tree[max_idx].rc = i;

				break;
			}

			// 더 큰 원소가 앞에 있으면
			if (tree[i].v < tree[j].v)
			{
				next_idx = j + 1;

				printf("next_idx : %d\n", next_idx);

				// 그곳 아래가 바로 부모의 위치
				tree[i].p = next_idx;

				// 만약 부모의 왼쪽 자식이 없다면
				if (tree[next_idx].lc == -1)
				{
					// 왼쪽 자식으로 들어간다
					tree[next_idx].lc = i;

					break;
				}
				// 만약 부모의 오른쪽 자식이 없다면
				else if (tree[next_idx].rc == -1)
				{
					// 오른쪽 자식으로 들어간다
					tree[next_idx].rc = i;

					break;
				}
				// error
				else
				{

				}
			}
			// 아님 말고
			else
			{

			}
		}

		// print_tree();
	}

	// print_tree();

	// 후위 순회
	postorder(tree[ROOT].v);

	return 0;
}

// cur와 value는 인덱스!
int main()
{
	int value = 0;
	int cur = 0;
	int n = 1;

	scanf("%d", &value);

	tree[ROOT].v = value;
	value = ROOT;

	while (scanf("%d", &value) != EOF)
	{
		n += 1;

		tree[n].v = value;
		value = n;

		cur = ROOT;

		while (1)
		{
			// printf("n : %d, cur = %d\n", tree[n].v, tree[cur].v);

			// 숫자가 작으면
			if (tree[n].v < tree[cur].v)
			{
				// 왼쪽 자식 있으면
				if (tree[cur].lc != -1)
				{
					// 왼쪽 트리로 가서 계속 탐색
					cur = tree[cur].lc;
				}
				// 왼쪽 자식 없으면
				else
				{
					// 왼쪽 자식으로 들어간다
					tree[cur].lc = n;
					tree[n].p = cur;

					break;
				}
			}
			// 숫자가 크면
			else if (tree[n].v > tree[cur].v)
			{
				// 오른쪽 자식 있으면
				if (tree[cur].rc != -1)
				{
					// 오른쪽 트리로 가서 계속 탐색
					cur = tree[cur].rc;
				}
				// 오른쪽 자식 없으면
				else
				{
					// 오른쪽 자식으로 들어간다
					tree[cur].rc = n;
					tree[n].p = cur;

					break;
				}
			}
			// 같은 경우는 없다
			else
			{

			}
		}

		// printf("%d %d %d %d\n", tree[cur].v, tree[cur].p, tree[cur].lc, tree[cur].rc);
		// printf("%d %d %d %d\n", tree[value].v, tree[value].p, tree[value].lc, tree[value].rc);

		// print_tree();
	}

	// 후위 순회
	postorder(ROOT);

	return 0;
}
