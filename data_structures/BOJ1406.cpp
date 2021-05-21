/*
D1 에디터
*/

#define _CRT_SECURE_NO_WARNINGS

/*
#include <stdio.h>
#include <malloc.h>

#define MAX_LENGTH 100000
#define MAX_N 500000

struct linkNode
{
	char value;
	linkNode* prev;
	linkNode* next;
};

// 입력할 명령어의 갯수
int N;
// 초기에 편집기에 입력되어 있는 문자열
char inputStr[MAX_LENGTH + 1] = { 0, };
linkNode head;
linkNode tail;
linkNode cursor;
*/

/*
linkNode* searchNode(linkNode* head, int id)
{
	while (true)
	{
		if (head->next == (linkNode*)0x0)
		{
			return (linkNode*)0x0;
		}
			
		if (head->next->id == id)
		{
			return head->next;
		}
			
		head = head->next;
	}
}

int insertNode(linkNode* head, linkNode* d)
{
	linkNode* node = head;

	while (node->next)
	{
		if (d->id < node->next->id)
		{
			break;
		}
		else if (d->id == node->next->id)
		{
			return -2;
		}

		node = node->next;
	}

	linkNode* newNode = (linkNode*)calloc(1, sizeof(linkNode));

	if (newNode == (linkNode*)0)
	{
		return -1;
	}

	*newNode = *d;

	newNode->prev = node;
	newNode->next = node->next;
	newNode->prev->next = newNode;

	if (newNode->next)
	{
		newNode->next->prev = newNode;
	}

	return 1;
}

int deleteNode(linkNode* head, int id)
{
	linkNode* delNode = searchNode(head, id);

	if (delNode == (linkNode*)0)
	{
		return -1;
	}

	delNode->prev->next = delNode->next;

	if (delNode->next)
	{
		delNode->next->prev = delNode->prev;
	}

	free(delNode);

	return 1;
}
*/

/*
void insertNode(linkNode* d)
{
	linkNode* newNode = (linkNode*)calloc(1, sizeof(linkNode));

	*newNode = *d;

	newNode->prev = tail.prev;
	newNode->next = &tail;
	tail.prev->next = newNode;
	tail.prev = newNode;

	return;
}

void swapNode(linkNode* left, linkNode* right)
{
	left->next = right->next;
	right->prev = left->prev;
	left->prev = right;
	right->next = left;

	return;
}

void deleteLeft(void)
{
	linkNode* delNode = cursor.prev;

	delNode->prev->next = &cursor;
	cursor.prev = delNode->prev;

	free(delNode);

	return;
}

void insertLeft(linkNode* d)
{
	linkNode* newNode = (linkNode*)calloc(1, sizeof(linkNode));

	*newNode = *d;

	newNode->prev = cursor.prev;
	newNode->next = &cursor;
	cursor.prev->next = newNode;
	cursor.prev = newNode;

	return;
}

void printNode(void)
{
	linkNode* node = head.next;

	while (node->next)
	{
		if (node->value != 'C')
		{
			printf("%c", node->value);
		}

		node = node->next;
	}

	printf("\n");

	return;
}

void init(void)
{
	register int i;
	linkNode tmp;

	head.prev = (linkNode*)0;
	head.next = &tail;
	tail.prev = &head;
	tail.next = (linkNode*)0;

	for (i = 0; inputStr[i]; i++)
	{
		tmp.value = inputStr[i];

		insertNode(&tmp);
	}

	cursor.value = 'C';
	cursor.prev = tail.prev;
	cursor.next = &tail;
	tail.prev = &cursor;

	// insertNode(&cursor);

	return;
}

void inputData(void)
{
	char cmd;
	linkNode tmp;

	scanf("%s", &inputStr);

	init();

	scanf("%d", &N);

	for (register int i = 0; i < N; i++)
	{
		scanf(" %c", &cmd);

		switch (cmd)
		{
			case 'L':
			{
				if (cursor.prev != &head)
				{
					swapNode(cursor.prev, &cursor);
				}

				break;
			}
			case 'D':
			{
				if (cursor.next != &tail)
				{
					swapNode(&cursor, cursor.next);
				}

				break;
			}
			case 'B':
			{
				if (cursor.prev != &head)
				{
					deleteLeft();
				}

				break;
			}
			case 'P':
			{
				scanf(" %c", &tmp.value);

				insertLeft(&tmp);

				break;
			}
			default:
			{
				break;
			}
		}
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	inputData();

	printNode();

	return 0;
}
*/

#include <stdio.h>
#define MAXS ((int)1e5)
#define MAXN ((int)5e5)
char str[MAXS + MAXN + 10];//초기 문자열
int N;//명령어 개수
//double linked list
struct NODE {
	char ch;
	NODE *prev;
	NODE *next;
};
NODE *head, *tail, *cur;
//배열 기반 linked list
NODE tmpnode[MAXS + MAXN + 10];
int tmpnodeidx;
NODE * myalloc(char ch, NODE *p) {
	NODE *np = &tmpnode[tmpnodeidx++];
	if (p == NULL) {//dummy node
		np->ch = 0;
		np->next = np->prev = NULL;
	}
	else {
		np->ch = ch; np->next = p; np->prev = p->prev;
		p->prev->next = np;
	}
	return np;
}
void InitNode() {
	tmpnodeidx = 0;
	head = NULL; tail = NULL; cur = NULL;
	head = myalloc(0, NULL);
	tail = myalloc(0, NULL);
	head->next = tail; tail->prev = head; cur = tail;
}
void InsertNode(char ch) {
	cur->prev = myalloc(ch, cur);
}
void Left() {
	if (cur->prev == head) return;
	cur = cur->prev;
}
void Right() {
	if (cur == tail) return;
	cur = cur->next;
}
void Del() {
	if (cur->prev == head) return;
	cur->prev = cur->prev->prev;
	cur->prev->next = cur;
}
void Solve() {
	//1.초기 문자열 linked list 추가
	for (int i = 0; str[i]; i++) {
		InsertNode(str[i]);
	}
	//2.명령어 따른 처리
	char cmd, ch;
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf(" %c", &cmd);
		switch (cmd) {
		case 'L'://커서 왼쪽으로 이동
			Left();
			break;
		case 'D'://커서 오른쪽으로 이동
			Right();
			break;
		case 'B'://커서 앞 문제 삭제
			Del();
			break;
		default:
			scanf(" %c", &ch);
			InsertNode(ch);
		}
	}
	//3.head와 tail사이 문자들을 저장
	int i = 0;
	for (NODE *p = head->next; p != tail; p = p->next) {
		str[i++] = p->ch;
	}
	str[i] = NULL;
}
void InputData() {
	scanf("%s", str);
}
void OutputData() {
	printf("%s\n", str);
}
int main() {
	InitNode();
	InputData();
	Solve();
	OutputData();
	return 0;
}
