/*
D4 개구리 공주
*/

#define _CRT_SECURE_NO_WARNINGS

/*
#include <stdio.h>

#define MAX_N ((int)1e5)
#define MAX_K ((int)1e5)
#define MAX_DIR 4
#define MAX_R ((int)1e9)
#define MAX_C ((int)1e9)

// 식물의 수
int N;
// 점프의 수
int K;
char jumpList[MAX_K] = { 0, };

void inputData(void)
{
	scanf("%d %d", &N, &K);
	scanf("%s", &jumpList);

	for (int i = 0; i < N; i++)
	{
		
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	inputData();

	return 0;
}
*/

#include <stdio.h>
#define MAXNK ((int)1e5)
int N, K;//식물수, 명령수
char cmd[MAXNK + 10];//선택한 방향(명령)
int idx[MAXNK + 10];
int tmp[MAXNK + 10];
struct NODE {
	int X, Y;//식물 좌표
	NODE *A, *B, *C, *D;
};
NODE leaf[MAXNK + 10];
NODE *frog;//개구리
void DelNode(NODE *p) {
	if (p->A) p->A->D = p->D;
	if (p->D) p->D->A = p->A;
	if (p->B) p->B->C = p->C;
	if (p->C) p->C->B = p->B;
}
int compdiff(int a, int b) {//a,b는 leaf배열의 인덱스(요소번호)
	int diffa = leaf[a].X - leaf[a].Y;
	int diffb = leaf[b].X - leaf[b].Y;
	int suma = leaf[a].X + leaf[a].Y;
	int sumb = leaf[b].X + leaf[b].Y;
	if (diffa == diffb) return suma < sumb;
	return diffa < diffb;
}
int compsum(int a, int b) {//a,b는 leaf배열의 인덱스(요소번호)
	int diffa = leaf[a].X - leaf[a].Y;
	int diffb = leaf[b].X - leaf[b].Y;
	int suma = leaf[a].X + leaf[a].Y;
	int sumb = leaf[b].X + leaf[b].Y;
	if (suma == sumb) return diffa < diffb;
	return suma < sumb;
}
void mergesort(int s, int e, int(*comp)(int, int)) {
	if (s >= e) return;
	int i = s, k = s, m = (s + e) / 2, j = m + 1;
	mergesort(s, m, comp);
	mergesort(m + 1, e, comp);
	while ((i <= m) && (j <= e)) {
		if (comp(idx[i], idx[j])) tmp[k++] = idx[i++];
		else tmp[k++] = idx[j++];
	}
	while (i <= m) tmp[k++] = idx[i++];
	while (j <= e) tmp[k++] = idx[j++];
	for (i = s; i <= e; i++) idx[i] = tmp[i];
}
void Solve() {
	for (int i = 1; i <= N; i++) {
		idx[i] = i;
	}
	//1.AD 링크 연결하기(차, 합) 정렬
	mergesort(1, N, compdiff);
	for (int i = 1; i < N; i++) {
		NODE *n = &leaf[idx[i]];
		NODE *m = &leaf[idx[i + 1]];
		if ((n->X - n->Y) == (m->X - m->Y)) {
			n->A = m;
			m->D = n;
		}
	}
	//2.BC 링크 연결하기(합, 차) 정렬
	mergesort(1, N, compsum);
	for (int i = 1; i < N; i++) {
		NODE *n = &leaf[idx[i]];
		NODE *m = &leaf[idx[i + 1]];
		if ((n->X + n->Y) == (m->X + m->Y)) {
			n->B = m;
			m->C = n;
		}
	}
	//3.명령처리
	frog = &leaf[1];
	for (int i = 0; i < K; i++) {
		switch (cmd[i]) {
		case 'A':
			if (frog->A) {
				DelNode(frog);
				frog = frog->A;
			}
			break;
		case 'B':
			if (frog->B) {
				DelNode(frog);
				frog = frog->B;
			}
			break;
		case 'C':
			if (frog->C) {
				DelNode(frog);
				frog = frog->C;
			}
			break;
		case 'D':
			if (frog->D) {
				DelNode(frog);
				frog = frog->D;
			}
			break;
		}
	}
}
void InputData() {
	scanf("%d %d", &N, &K);
	scanf("%s", cmd);
	for (int i = 1; i <= N; i++) {
		scanf("%d %d", &leaf[i].X, &leaf[i].Y);
		leaf[i].A = leaf[i].B = leaf[i].C = leaf[i].D = NULL;
	}
}
void OutputData() {
	printf("%d %d\n", frog->X, frog->Y);
}
int main() {
	InputData();
	Solve();
	OutputData();
	return 0;
}
