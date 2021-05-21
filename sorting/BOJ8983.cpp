/*
A0 사냥꾼
*/

#define _CRT_SECURE_NO_WARNINGS

/*
#include <stdio.h>

#define MAX_M ((int)1e5)
#define MAX_N ((int)1e5)
#define MAX_L ((int)1e9)

// 사대의 수
int M;
// 동물의 수
int N;
// 사정거리
int L;

struct Node
{
	int idx;
	int r;
	int c;
};

// 사대 좌표 목록
// 1부터 사용
int mList[MAX_M + 1] = { 0, };
// 동물 좌표 목록
// 1부터 사용
Node sumList[MAX_N + 1] = { {0, 0} };
Node diffList[MAX_N + 1] = { {0, 0} };
// mergeSort용
Node tmpList[MAX_N + 1] = { {0, 0} };

int compSum(Node *x, Node *y)
{
	return ((x->r + x->c) - (y->r + y->c));
}

int compDiff(Node *x, Node *y)
{
	return ((x->r - x->c) - (y->r - y->c));
}

int Sort_Merge(Node *d, Node *tmp, int order, int s, int e, int(*comp)(Node *x, Node *y))
{
	int m, idx1, idx2, idxtmp;
	if (s >= e) return -1;

	m = (s + e) / 2;

	Sort_Merge(d, tmp, order, s, m, comp);
	Sort_Merge(d, tmp, order, m + 1, e, comp);

	idx1 = s; idx2 = m + 1; idxtmp = s;
	while (idx1 <= m && idx2 <= e)
	{
		if ((order * comp(&d[idx1], &d[idx2])) < 0) tmp[idxtmp++] = d[idx1++];
		else tmp[idxtmp++] = d[idx2++];
	}

	if (idx1 <= m) while (idx1 <= m) tmp[idxtmp++] = d[idx1++];
	else while (idx2 <= e) tmp[idxtmp++] = d[idx2++];

	for (idxtmp = s; idxtmp <= e; idxtmp++) d[idxtmp] = tmp[idxtmp];
	return e - s + 1;
}

int Binary_Search(Node *src, int s, int e, Node *d, int(*comp)(Node *x, Node *y))
{
	int m, ret;

	while (s <= e)
	{
		m = (s + e) / 2;
		ret = comp(d, &src[m]);
		if (ret == 0) return m;
		else if (ret > 0) s = m + 1;
		else e = m - 1;
	}

	return -1;
}

int Binary_Search_Lower(Node *src, int s, int e, Node *d, int(*comp)(Node *x, Node *y))
{
	int m, ret, sol = -1;

	while (s <= e)
	{
		m = (s + e) / 2;
		ret = comp(d, &src[m]);
		if (ret <= 0)
		{
			sol = m;
			e = m - 1;
		}
		else s = m + 1;
	}

	return sol;
}

int Binary_Search_Upper(Node *src, int s, int e, Node *d, int(*comp)(Node *x, Node *y))
{
	int m, ret, sol = -1;

	while (s <= e)
	{
		m = (s + e) / 2;
		ret = comp(d, &src[m]);
		if (ret >= 0)
		{
			sol = m;
			s = m + 1;
		}
		else e = m - 1;
	}

	return sol;
}

void inputData(void)
{
	int r;
	int c;

	scanf("%d %d %d", &M, &N, &L);

	for (register int i = 1; i <= M; i++)
	{
		scanf("%d", &mList[i]);
	}

	for (register int i = 1; i <= N; i++)
	{
		scanf("%d %d", &c, &r);

		sumList[i] = { i, r, c };
		diffList[i] = { i, r, c };
	}

	return;
}

int solve(void)
{
	// 합 : 11시~5시 대각선
	Sort_Merge(sumList, tmpList, 1, 1, N, compSum);
	
	// 차 : 1시 ~ 7시 대각선
	Sort_Merge(diffList, tmpList, 1, 1, N, compDiff);

	// 각 사대에 대하여
	for (register int i = 1; i <= M; i++)
	{
		
	}

	return 6;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	inputData();

	int ans = solve();

	printf("%d\n", ans);

	return 0;
}
*/

/*
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_M (100000)
#define MAX_N (100000)

typedef struct
{
	int x;
	int y;
}ANIMAL;

int M, N, L;
int shoot[MAX_M];
int tmp_shoot[MAX_M];

ANIMAL animal[MAX_N];

void Input_Data(void)
{
	int i;
	scanf("%d %d %d", &M, &N, &L);
	for (i = 0; i < M; i++)
	{
		scanf("%d", &shoot[i]);
	}
	for (i = 0; i < N; i++)
	{
		scanf("%d %d", &animal[i].x, &animal[i].y);
	}
}


int Binary_Search_Upper(int s, int e, int d)
{
	int m, sol = -1;

	while (s <= e)
	{
		m = (s + e) / 2;
		if (shoot[m] <= d)
		{
			sol = m;
			s = m + 1;
		}
		else e = m - 1;
	}
	return sol;
}

int Binary_Search_Lower(int s, int e, int d)
{
	int m, sol = -1;

	while (s <= e)
	{
		m = (s + e) / 2;
		if (shoot[m] >= d)
		{
			sol = m;
			e = m - 1;
		}
		else s = m + 1;
	}
	return sol;
}
#define ABS(X) ((X)<0 ? -(X) : (X))
int Get_Distance(int idx_animal, int idx_shoot)
{
	return animal[idx_animal].y + ABS(animal[idx_animal].x - shoot[idx_shoot]);
}

void Merge_Sort_Shoot(int s, int e)
{
	int m, idx1, idx2, idxtmp;
	if (s >= e) return;
	m = (s + e) / 2;
	Merge_Sort_Shoot(s, m);
	Merge_Sort_Shoot(m + 1, e);

	idx1 = s; idx2 = m + 1; idxtmp = s;
	while (idx1 <= m && idx2 <= e)
	{
		if (shoot[idx1] < shoot[idx2]) tmp_shoot[idxtmp++] = shoot[idx1++];
		else tmp_shoot[idxtmp++] = shoot[idx2++];
	}

	while (idx1 <= m) tmp_shoot[idxtmp++] = shoot[idx1++];
	while (idx2 <= e) tmp_shoot[idxtmp++] = shoot[idx2++];

	for (idxtmp = s; idxtmp <= e; idxtmp++) shoot[idxtmp] = tmp_shoot[idxtmp];
}

int Get_Solution(void)
{
	int i, ret, cnt = 0;
	Merge_Sort_Shoot(0, M - 1);
	for (i = 0; i < N; i++)
	{
		ret = Binary_Search_Upper(0, M - 1, animal[i].x);
		if (ret != -1 && Get_Distance(i, ret) <= L)
		{
			cnt++;
			continue;
		}

		ret = Binary_Search_Lower(0, M - 1, animal[i].x);
		if (ret != -1 && Get_Distance(i, ret) <= L)
		{
			cnt++;
			continue;
		}
	}
	return cnt;
}
int main(void)
{
	Input_Data();

	printf("%d\n", Get_Solution());

	return 0;
}
*/

#include <stdio.h>

#define MAX_M (100000)
#define MAX_N (100000)

int M, N, L;

int shoot[MAX_M];
int tmp_shoot[MAX_M];

typedef struct
{
	int x;
	int y;
}ANIMAL;

ANIMAL animal[MAX_N];
ANIMAL tmp_animal[MAX_N];

void Input_Data(void)
{
	int i;
	scanf("%d %d %d", &M, &N, &L);
	for (i = 0; i < M; i++)
	{
		scanf("%d", &shoot[i]);
	}
	for (i = 0; i < N; i++)
	{
		scanf("%d %d", &animal[i].x, &animal[i].y);
	}
}

void Merge_Sort_Shoot(int s, int e)
{
	int m, idx1, idx2, idxtmp;
	if (s >= e) return;
	m = (s + e) / 2;
	Merge_Sort_Shoot(s, m);
	Merge_Sort_Shoot(m + 1, e);

	idx1 = s; idx2 = m + 1; idxtmp = s;
	while (idx1 <= m && idx2 <= e)
	{
		if (shoot[idx1] < shoot[idx2]) tmp_shoot[idxtmp++] = shoot[idx1++];
		else tmp_shoot[idxtmp++] = shoot[idx2++];
	}

	while (idx1 <= m) tmp_shoot[idxtmp++] = shoot[idx1++];
	while (idx2 <= e) tmp_shoot[idxtmp++] = shoot[idx2++];

	for (idxtmp = s; idxtmp <= e; idxtmp++) shoot[idxtmp] = tmp_shoot[idxtmp];
}

void Merge_Sort_Animal(int s, int e)
{
	int m, idx1, idx2, idxtmp;
	if (s >= e) return;
	m = (s + e) / 2;
	Merge_Sort_Animal(s, m);
	Merge_Sort_Animal(m + 1, e);

	idx1 = s; idx2 = m + 1; idxtmp = s;
	while (idx1 <= m && idx2 <= e)
	{
		if (animal[idx1].x < animal[idx2].x) tmp_animal[idxtmp++] = animal[idx1++];
		else tmp_animal[idxtmp++] = animal[idx2++];
	}

	while (idx1 <= m) tmp_animal[idxtmp++] = animal[idx1++];
	while (idx2 <= e) tmp_animal[idxtmp++] = animal[idx2++];

	for (idxtmp = s; idxtmp <= e; idxtmp++) animal[idxtmp] = tmp_animal[idxtmp];
}

int Get_Solution(void)
{
	int i;
	int cnt = 0;
	int l = -1;

	for (i = 0; i < N; i++)
	{
		while ((l + 1 < M) && (shoot[l + 1] <= animal[i].x)) l++;

		if (l >= 0 && (animal[i].x - shoot[l] + animal[i].y <= L)) cnt++;
		else if (l + 1 < M && (shoot[l + 1] - animal[i].x + animal[i].y <= L)) cnt++;
	}
	return cnt;
}

int main(void)
{
	Input_Data();

	Merge_Sort_Shoot(0, M - 1);
	Merge_Sort_Animal(0, N - 1);

	printf("%d\n", Get_Solution());

	return 0;
}
