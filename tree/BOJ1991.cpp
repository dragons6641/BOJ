#define _CRT_SECURE_NO_WARNINGS
#define MAX_N 26

#include <stdio.h>

using namespace std;

typedef struct node
{
	char v;
	char lc;
	char rc;
}
NODE;

NODE tree[MAX_N];

void preorder(char c)
{
	int num = (int)(c - 'A');

	printf("%c", c);

	if (tree[num].lc != '.')
	{
		preorder(tree[num].lc);
	}
	
	if (tree[num].rc != '.')
	{
		preorder(tree[num].rc);
	}

	return;
}

void inorder(char c)
{
	int num = (int)(c - 'A');

	if (tree[num].lc != '.')
	{
		inorder(tree[num].lc);
	}

	printf("%c", c);

	if (tree[num].rc != '.')
	{
		inorder(tree[num].rc);
	}

	return;
}

void postorder(char c)
{
	int num = (int)(c - 'A');

	if (tree[num].lc != '.')
	{
		postorder(tree[num].lc);
	}

	if (tree[num].rc != '.')
	{
		postorder(tree[num].rc);
	}

	printf("%c", c);

	return;
}

int main()
{
	int n = 0;
	int idx = -1;
	char value[2];
	char left_child[2];
	char right_child[2];

	scanf("%d", &n);

	for (int i = 0; i < n; i++)
	{
		scanf("%s %s %s", &value, &left_child, &right_child);

		// printf("%c %c %c\n", value, left_child, right_child);
		
		// 알파벳이 아닌 경우
		if (value[0] == '.')
		{
			idx = -1;
		}
		// 알파벳인 경우
		else
		{
			idx = (int)(value[0] - 'A');

			tree[idx].v = value[0];
			tree[idx].lc = left_child[0];
			tree[idx].rc = right_child[0];
		}
	}

	preorder(tree[0].v);
	printf("\n");

	inorder(tree[0].v);
	printf("\n");

	postorder(tree[0].v);
	printf("\n");

	return 0;
}
