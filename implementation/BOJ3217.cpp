/*
D5 메모리 관리 함수
*/

#define _CRT_SECURE_NO_WARNINGS

/*
#include <stdio.h>

#define MAX_LENGTH 20

int N;

void inputData(void)
{
	char cmd[MAX_LENGTH + 1] = { 0, };

	scanf("%d", &N);

	for (int i = 0; i < N; i++)
	{
		scanf("%s", &cmd);
	}

	return;
}

int main(void)
{
	freopen("input1.txt", "r", stdin);

	inputData();

	return 0;
}
*/

#include <stdio.h>
#define MAXN ((int)1e5)
#define MAXT ((int)1e3)
int N;//명령어 개수
struct NODE {
	int s, size;//시작구역번호, 크기
	NODE *next;
};
NODE freearea;//dummy node
int totalsize;//할당 가능한 크기
NODE * var[MAXT + 10];//변수테이블
//배열기반
NODE tmpnode[MAXN + 10];
int tmpnodeidx;
NODE *myalloc(int s, int size, NODE *next) {
	NODE *np = &tmpnode[tmpnodeidx++];
	np->s = s; np->size = size; np->next = next;
	return np;
}
//Hash Table 변수문자열 =>숫자(1~1000)
void strcopy(char *dst, const char *src) {
	while (*dst++ = *src++);
}
int strcompare(const char *a, const char *b) {
	int i;
	for (i = 0; a[i] && (a[i] == b[i]); i++);
	return a[i] - b[i];
}
int HashFunc(char *s) {
	int code = 5381;
	for (int i = 0; s[i]; i++) {
		code = (code * 33 + s[i]) % MAXT;
	}
	return code;
}
int NewId;
struct HT {
	int id;
	char org[8];//변수명
	HT *next;
};
HT htbl[MAXT + 10];//dummy node
//배열기반
HT tmpht[MAXT + 10];
int tmphtidx;
HT *myhtalloc(int id, char *org, HT *next) {
	HT *np = &tmpht[tmphtidx++];
	np->id = id; strcopy(np->org, org); np->next = next;
	return np;
}
int InsertKey(char *org) {
	int key = HashFunc(org);
	HT *p = &htbl[key];
	while (p->next) {
		int r = strcompare(p->next->org, org);
		if (r == 0) return p->next->id;//이미 등록된 변수임(같은 아이디)
		if (r > 0) break;
		p = p->next;
	}
	//새로운 아이디 부여
	p->next = myhtalloc(++NewId, org, p->next);
	return NewId;
}
void Init() {
	tmpnodeidx = 0;
	NewId = 0;
	tmphtidx = 0;
	freearea.next = myalloc(1, MAXN, NULL);
	totalsize = MAXN;
	for (int i = 1; i <= MAXT; i++) {
		var[i] = NULL;
	}
	for (int i = 0; i < MAXT; i++) {
		htbl[i].next = NULL;
	}
}
void InputData() {
	scanf("%d", &N);
}
NODE *memalloc(int size) {
	if (totalsize < size) return NULL;//할당 불가능
	NODE *p = &freearea;
	int rem = totalsize;
	while (p->next && (rem >= size)) {
		if (p->next->size == size) {//할당 가능
			NODE *rp = p->next;
			p->next = rp->next;
			rp->next = NULL;
			totalsize -= size;
			return rp;
		}
		if (p->next->size > size) {//할당 가능
			NODE *rp = myalloc(p->next->s, size, NULL);
			p->next->s += size;
			p->next->size -= size;
			totalsize -= size;
			return rp;
		}
		rem -= p->next->size;
		p = p->next;
	}
	return NULL;//할당 불가능
}
void memfree(NODE *fm) {
	if (fm == NULL) return;//해제 불필요
	NODE *p = &freearea;
	totalsize += fm->size;
	if (p->next == NULL) {
		p->next = fm;
		return;
	}
	while (p->next) {
		if (p->next->s > fm->s + fm->size) {
			fm->next = p->next;
			p->next = fm;
			return;
		}
		p = p->next;
		if (p->s == fm->s + fm->size) {
			p->s = fm->s;
			p->size += fm->size;
			return;
		}
		if (p->s + p->size == fm->s) {
			p->size += fm->size;
			if (p->next && (p->next->s == p->s + p->size)) {
				p->size += p->next->size;
				p->next = p->next->next;
			}
			return;
		}
	}
	p->next = fm;
}
void Solve() {
	char cmd[100];
	char name[10] = { 0 };
	int size, vid;
	for (int i = 1; i <= N; i++) {
		scanf("%s", cmd);
		if (cmd[4] == '=') {//malloc 함수 baka=malloc(214);
			for (int k = 0; k < 4; k++) {
				name[k] = cmd[k];
			}//변수명 복사
			vid = InsertKey(name);
			sscanf(&cmd[12], "%d", &size);
			var[vid] = memalloc(size);
		}
		else if (cmd[0] == 'f') {//free 함수 free(baka);
			for (int k = 0; k < 4; k++) {
				name[k] = cmd[5 + k];
			}//변수명 복사
			vid = InsertKey(name);
			memfree(var[vid]);
			var[vid] = NULL;
		}
		else {//print 함수 print(deda);
			for (int k = 0; k < 4; k++) {
				name[k] = cmd[6 + k];
			}//변수명 복사
			vid = InsertKey(name);
			if (var[vid] == NULL) printf("0\n");
			else printf("%d\n", var[vid]->s);
		}
	}
}
int main() {
	Init();
	InputData();
	Solve();
	return 0;
}
