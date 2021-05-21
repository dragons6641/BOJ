/*
5676 음주 코딩
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define NUM_DATA    (100000)
// #define NUM_DATA (4)
#define MAX_DATA    (NUM_DATA)
#define MAX_TREE        ((1 << 18) + 1)
// #define MAX_TREE     (40)
#define LAST_NODE   (MAX_TREE - 1)

int N;//개수

int K;//명령개수

int A[100000 + 10];//입력데이터1번요소부터N번까지저장

char sol[100000 + 10];//답은0번요소부터순서대로저장

// 0, +, -중 하나의 값을 가짐
char tree[1 << 18];;

// int exam[NUM_DATA + 1] = { 0,1,2,3,4,5 }; // 0번 index 공간 무시

#define PRINT_TREE {int j;printf("( "); for(j=1;j<=LAST_NODE;j++){printf("%3d ",tree[j]);}printf(")\n");}

char calcData(int data)
{
	if (data > 0)
	{
		return '+';
	}
	else if (data < 0)
	{
		return '-';
	}

	return '0';
}

char calcNode(char leftData, char rightData)
{
	if ((leftData == '+') && (rightData == '+'))
	{
		return '+';
	}
	else if ((leftData == '+') && (rightData == '-'))
	{
		return '-';
	}
	else if ((leftData == '-') && (rightData == '+'))
	{
		return '-';
	}
	else if ((leftData == '-') && (rightData == '-'))
	{
		return '+';
	}

	return '0';
}

void Update_New_Data(int node, int s, int e, int idx, int data)
{
	int m = (s + e) / 2;

	if (s == e)
	{
		tree[node] = calcData(data);

		return;
	}

	if (idx <= m)
	{
		Update_New_Data(node * 2, s, m, idx, data);
	}
	else
	{
		Update_New_Data(node * 2 + 1, m + 1, e, idx, data);
	}

	tree[node] = calcNode(tree[node * 2], tree[node * 2 + 1]);

	return;
}

char Query(int node, int s, int e, int qs, int qe)
{
	if ((qs <= s) && (qe >= e))
	{
		return tree[node];
	}
	else if ((qs > e) || (qe < s))
	{
		return '+';
	}

	int m = (s + e) / 2;

	char l = Query(node * 2, s, m, qs, qe);
	char r = Query(node * 2 + 1, m + 1, e, qs, qe);

	return calcNode(l, r);
}

void Update_C(int node, int s, int e, int us, int ue, char c)
{
	if ((us > e) || (ue < s))
	{
		return;
	}

	if (s == e)
	{
		tree[node] = c;

		return;
	}

	int m = (s + e) / 2;        // s ~ m, (m + 1) ~ e

	Update_C(node * 2, s, m, us, ue, c);
	Update_C(node * 2 + 1, m + 1, e, us, ue, c);

	tree[node] = calcNode(tree[node * 2], tree[node * 2 + 1]);

	return;
}

void init(void)
{
	for (register int i = 0; i < (1 << 18); i++)
	{
		tree[i] = '\0';
	}

	return;
}

void solve(void)
{
	char result;
	char cmd;
	int a;
	int b;

	for (int i = 1; i <= K; i++)
	{
		scanf(" %c %d %d", &cmd, &a, &b);

		if (cmd == 'C')
		{
			// void Update_C(int node, int s, int e, int us, int ue, char c)
			Update_C(1, 1, NUM_DATA, a, a, calcData(b));
		}
		else if (cmd == 'P')
		{
			// int Query(int node, int s, int e, int qs, int qe)
			result = Query(1, 1, NUM_DATA, a, b);

			printf("%c", result);
		}

		// int debug = 1;
	}

	printf("\n");

	return;
}

void input_data(void)
{
	register int i;

	while (scanf("%d %d", &N, &K) != EOF)
	{
		init();

		for (i = 1; i <= N; i++) {

			scanf("%d", &A[i]);

			// void Update_New_Data(int node, int s, int e, int idx, int data)
			Update_New_Data(1, 1, NUM_DATA, i, A[i]);

			// int debug = 1;
		}

		solve();

		// printf("%s\n", sol);
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	input_data();

	/*
	solve();

	printf("%s\n", sol);
	*/

	return 0;
}
