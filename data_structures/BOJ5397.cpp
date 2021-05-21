#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_T 5
#define MAX_L 1000000

struct LinkNode
{
	char data;
	LinkNode* prev;
	LinkNode* next;
};

// 테스트 케이스 수
int T;
// 패스워드의 길이
int len;
// 사용한 버퍼의 갯수
int bcnt;
// 패스워드 로그
char log[MAX_L + 1];
// 첫 번째 패스워드를 가리킴
LinkNode head;
// 마지막 패스워드를 가리킴
LinkNode tail;
// 패스워드 버퍼
LinkNode buf[MAX_L];
// 현재 커서의 위치
LinkNode* cur;

// 1. empty() : 리스트가 비었다면 참을 반환
bool empty(void)
{
	return (len == 0);
}

// 2. size() : 리스트에 담긴 원소의 개수를 반환
int size(void)
{
	return len;
}

// 3. begin() : 리스트의 첫 원소의 주소값 반환
LinkNode* begin(void)
{
	return &head;
}

// 4. end() : 리스트의 마지막 원소 이후의 주소를 반환
LinkNode* end(void)
{
	return &tail;
}

// 5. insert(data) : 리스트의 cur와 cur->prev 사이에 새로운 노드(data를 갖는)를 삽입한다.
void insert(char data)
{
	buf[bcnt] = { data, cur->prev, cur };

	cur->prev->next = &buf[bcnt];
	cur->prev = &buf[bcnt];

	len++;
	bcnt++;

	return;
}

// 6. erase() : 리스트의 cur가 참조하는 노드를 삭제하고 cur는 cur->next로 이동.
void erase(void)
{
	cur->prev->next = cur->next;
	cur->next->prev = cur->prev;

	cur = cur->next;

	len--;

	return;
}

void init(void)
{
	len = 0;
	bcnt = 0;

	head = { '\0', (LinkNode*)NULL, &tail };
	tail = { '\0', &head, (LinkNode*)NULL };

	cur = &tail;

	return;
}

void outputData(void)
{
	for (LinkNode* p = head.next; p != &tail; p = p->next)
	{
		printf("%c", p->data);
	}

	printf("\n");

	return;
}

void solve(void)
{
	scanf("%d", &T);

	for (register int testCase = 1; testCase <= T; testCase++)
	{
		init();

		scanf("%s", &log);

		for (register int i = 0; log[i]; i++)
		{
			switch (log[i])
			{
				// ‘-’는 백스페이스를 이용하여 삭제가 가능하다면 커서의 바로 앞 1문자를 삭제한 로그이다. 
				case '-':
				{
					if (cur->prev != &head)
					{
						cur = cur->prev;

						erase();
					}

					break;
				}
				// ‘<’는 왼쪽 방향키를 이용하여 이동이 가능하다면 커서 바로 왼쪽 1문자 앞으로 이동한 로그이다.
				case '<':
				{
					if (cur->prev != &head)
					{
						cur = cur->prev;
					}

					break;
				}
				// ‘>’는 오른쪽 방향키를 이용하여 이동이 가능하다면 커서 바로 오른쪽 1문자 뒤로 이동한 로그이다.
				case '>':
				{
					if (cur != &tail)
					{
						cur = cur->next;
					}

					break;
				}
				default:
				{
					insert(log[i]);

					break;
				}
			}
		}

		outputData();
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	solve();

	return 0;
}
