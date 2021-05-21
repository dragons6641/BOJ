/*
A2 터보
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>

#define MAX_N 100000
#define TREE_SIZE (1 << 18)
// #define TREE_SIZE (16)

// 숫자의 갯수
int N;
// 숫자들의 초기 위치
// 1부터 사용
int posList[MAX_N + 1] = { 0, };
int tree[TREE_SIZE] = { 0, };
int lazy[TREE_SIZE] = { 0, };

/*
struct linkNode
{
	int id;
	linkNode *prev;
	linkNode *next;
};

int N;
int leftCnt = 0;
int rightCnt = 0;
linkNode *Head;
linkNode *Tail;
linkNode *Left;
linkNode *Right;

linkNode *Search_Id_Node_Left(linkNode *head, int id)
{
	leftCnt = 0;

	for (;; leftCnt++)
	{
		if (head->next == (linkNode *)0) return (linkNode *)0;
		if (head->next->id == id) return head->next;
		head = head->next;
	}
}

linkNode *Search_Id_Node_Right(linkNode *tail, int id)
{
	rightCnt = 0;

	for (;; rightCnt++)
	{
		if (tail->prev == (linkNode *)0) return (linkNode *)0;
		if (tail->prev->id == id) return tail->prev;
		tail = tail->prev;
	}
}

void Delete_Node(linkNode *d)
{
	d->prev->next = d->next;
	d->next->prev = d->prev;

	return;
}

void Swap_Left(linkNode *head, linkNode *d)
{
	linkNode *now = head;

	// 해당 노드를 삭제하듯이 동작, 단 free는 하지 않음
	Delete_Node(d);

	// 새로운 링크 반영
	d->prev = now;
	d->next = now->next;
	now->next->prev = d;
	now->next = d;

	return;
}

void Swap_Right(linkNode *tail, linkNode *d)
{
	linkNode *now = tail;

	// 해당 노드를 삭제하듯이 동작, 단 free는 하지 않음
	Delete_Node(d);

	// 새로운 링크 반영
	d->next = now;
	d->prev = now->prev;
	now->prev->next = d;
	now->prev = d;

	return;
}

int Insert_Node(linkNode *head, linkNode *tail, linkNode *d)
{
	linkNode *prev = head;
	linkNode *newnode;
	while (prev->next)
	{
		// if (prev->next->id > d->id) break;
		// if (prev->next->id == d->id) return -2;
		prev = prev->next;
	}

	newnode = (linkNode *)calloc(1, sizeof(linkNode));
	if (newnode == (linkNode *)0) return -1;
	*newnode = *d;

	// newnode->prev = prev;
	newnode->prev = tail->prev;
	// newnode->next = prev->next;
	newnode->next = tail;
	newnode->prev->next = newnode;
	// if (newnode->next) 
	newnode->next->prev = newnode;

	return 1;
}

void init(void)
{
	Head = (linkNode *)calloc(1, sizeof(linkNode));
	Tail = (linkNode *)calloc(1, sizeof(linkNode));

	Head->next = Tail;
	Tail->prev = Head;

	return;
}

void inputData(void)
{
	linkNode tmp;

	scanf("%d", &N);

	for (register int i = 1; i <= N; i++)
	{
		scanf("%d", &tmp.id);

		Insert_Node(Head, Tail, &tmp);

		int debug = 1;
	}

	return;
}

void solve(void)
{
	int leftID = 1;
	int rightID = N;
	linkNode *tmp;

	// i번 출력해야 함
	for (register int i = 1; i <= N; i++)
	{
		// 홀수번째인 경우
		if (i % 2 == 1)
		{
			// 앞에서부터 작은 것 찾아나간다
			tmp = Search_Id_Node_Left(Head, leftID);

			printf("%d\n", leftCnt - leftID + 1);

			leftID++;

			// 자리 이동
			Swap_Left(Left, tmp);

			Left = Left->next;
		}
		// 짝수번째인 경우
		else
		{
			// 뒤에서부터 큰 것 찾아나간다
			tmp = Search_Id_Node_Right(Tail, rightID);

			printf("%d\n", rightCnt - leftID + 2);

			rightID--;

			// 자리 이동
			Swap_Right(Right, tmp);

			Right = Right->prev;
		}

		if (leftID == rightID)
		{
			printf("0\n");

			break;
		}
	}

	return;
}
*/

/*
void InitTree(int n, int s, int e) {//n번 노드는 s~e구간 정보를 갖고 있음
	if (s == e) {//leaf node
		if (s <= M) tree[n] = 0;
		else {
			tree[n] = 1;
			rpos[s - M] = s;
		}
		return;
	}
	int L = n * 2, R = L + 1, m = (s + e) / 2;
	InitTree(L, s, m);
	InitTree(R, m + 1, e);
	tree[n] = tree[L] + tree[R];
}
*/

void Propagate(int node, int s, int e)
{
	if (lazy[node])
	{
		if (s != e)
		{
			lazy[node * 2] += lazy[node];
			lazy[node * 2 + 1] += lazy[node];
		}
		tree[node] += (e - s + 1) * lazy[node];
		lazy[node] = 0;
	}
}

void Update_New_Data_Lazy(int node, int s, int e, int idx, int data)
{
	int m;
	Propagate(node, s, e);
	if ((idx < s) || (e < idx)) return;
	if (s == e)
	{
		tree[node] = data;
		return;
	}

	m = (s + e) / 2;
	Update_New_Data_Lazy(node * 2, s, m, idx, data);
	Update_New_Data_Lazy(node * 2 + 1, m + 1, e, idx, data);

	tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

int Query_Lazy(int node, int s, int e, int qs, int qe)
{
	int m, l, r;
	Propagate(node, s, e);
	if (qs <= s && e <= qe) return tree[node];
	if (qe < s || e < qs) return 0;

	m = (s + e) / 2;
	l = Query_Lazy(node * 2, s, m, qs, qe);
	r = Query_Lazy(node * 2 + 1, m + 1, e, qs, qe);

	return l + r;
}

void Update_Add_Lazy(int node, int s, int e, int us, int ue, int add)
{
	int m;
	Propagate(node, s, e);
	if (us <= s && e <= ue)
	{
		lazy[node] += add;
		Propagate(node, s, e);
		return;
	}
	else if (ue < s || e < us) return;
	m = (s + e) / 2;
	Update_Add_Lazy(node * 2, s, m, us, ue, add);
	Update_Add_Lazy(node * 2 + 1, m + 1, e, us, ue, add);

	tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

void inputData(void)
{
	int M;

	scanf("%d", &N);

	for (register int i = 1; i <= N; i++)
	{
		scanf("%d", &M);

		posList[M] = i;
	}

	return;
}

void solve(void)
{
	// 초기화 : 모든 노드에 1씩 추가
	// 즉, 모든 원소가 아직 정렬되지 않은 상태
	// void Update_Add_Lazy(int node, int s, int e, int us, int ue, int add)
	Update_Add_Lazy(1, 1, N, 1, N, 1);

	register int lp = 1;
	register int rp = N;
	
	for (register int i = 1; i <= N; i++)
	{
		int ret;

		// 홀수번째 단계이면, 아직까지 고르지 않은 숫자 중 제일 작은 수를 고른 다음에, 
		// 그것을 인접한 숫자와 위치를 바꾸면서 올바른 위치로 이동시키고
		if (i % 2 == 1)
		{
			// int Query_Lazy(int node, int s, int e, int qs, int qe)
			ret = Query_Lazy(1, 1, N, 1, posList[lp] - 1);

			// void Update_Add_Lazy(int node, int s, int e, int us, int ue, int add)
			Update_Add_Lazy(1, 1, N, posList[lp], posList[lp], -1);

			lp++;
		}
		// 짝수번째 단계일때는, 제일 큰 수를 고른 다음에 위치를 이동시키는 것이다.
		else
		{
			// int Query_Lazy(int node, int s, int e, int qs, int qe)
			ret = Query_Lazy(1, 1, N, posList[rp] + 1, N);

			// void Update_Add_Lazy(int node, int s, int e, int us, int ue, int add)
			Update_Add_Lazy(1, 1, N, posList[rp], posList[rp], -1);

			rp--;
		}

		printf("%d\n", ret);
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);
	// freopen("input3.txt", "r", stdin);

	// init();

	inputData();

	solve();

	return 0;
}
