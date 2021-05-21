#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 100000
#define MAX_SEGMENT (1 << 18)

// 전체 사람의 수
int N;
// 사람들의 키 집합
// 1부터 사용
int inputList[MAX_N + 1] = { 0, };
// 정답 저장
// 1부터 사용
int outputList[MAX_N + 1] = { 0, };
// 키 수열
// 1부터 사용
int S[MAX_N + 1] = { 0, };
// mergeSort에 사용
int listTmp[MAX_N + 1] = { 0, };
// 줄 서 있는 사람들의 상태
int segmentTree[MAX_SEGMENT] = { 0, };

void mergeSort(int s, int e)
{
	if (s >= e)
	{
		return;
	}

	int m = (s + e) / 2;

	mergeSort(s, m);
	mergeSort(m + 1, e);

	register int idx1 = s;
	register int idx2 = m + 1;
	register int idxTmp = s;

	while ((idx1 <= m) && (idx2 <= e))
	{
		if (inputList[idx1] < inputList[idx2])
		{
			listTmp[idxTmp] = inputList[idx1++];
		}
		else
		{
			listTmp[idxTmp] = inputList[idx2++];
		}

		idxTmp++;
	}

	while (idx1 <= m)
	{
		listTmp[idxTmp] = inputList[idx1++];

		idxTmp++;
	}

	while (idx2 <= e)
	{
		listTmp[idxTmp] = inputList[idx2++];

		idxTmp++;
	}

	for (idxTmp = s; idxTmp <= e; idxTmp++)
	{
		inputList[idxTmp] = listTmp[idxTmp];
	}

	return;
}

void updateNewData(int node, int s, int e, int idx, int data)
{
	if (s == e)
	{
		segmentTree[node] = data;

		return;
	}

	int m = (s + e) / 2;
	int lch = node * 2;
	int rch = lch + 1;

	if (m >= idx)
	{
		updateNewData(lch, s, m, idx, data);
	}
	else
	{
		updateNewData(rch, m + 1, e, idx, data);
	}

	segmentTree[node] = segmentTree[lch] + segmentTree[rch];

	return;
}

void updateAdd(int node, int s, int e, int rank, int idx)
{
	segmentTree[node]--;

	if (s == e)
	{
		outputList[idx] = inputList[s];

		return;
	}

	int m = (s + e) / 2;
	int lch = node * 2;
	int rch = lch + 1;

	if (segmentTree[lch] >= rank)
	{
		updateAdd(lch, s, m, rank, idx);
	}
	else
	{
		updateAdd(rch, m + 1, e, rank - segmentTree[lch], idx);
	}

	return;
}

void inputData(void)
{
	scanf("%d", &N);

	for (register int i = 1; i <= N; i++)
	{
		scanf("%d", &inputList[i]);
	}

	for (register int i = 1; i <= N; i++)
	{
		scanf("%d", &S[i]);
	}

	return;
}

void solve(void)
{
	mergeSort(1, N);

	for (register int i = 1; i <= N; i++)
	{
		updateNewData(1, 1, N, i, 1);
	}

	for (register int i = N; i >= 1; i--)
	{
		updateAdd(1, 1, N, S[i] + 1, i);
	}

	return;
}

void outputData(void)
{
	for (register int i = 1; i <= N; i++)
	{
		printf("%d\n", outputList[i]);
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	inputData();

	solve();

	outputData();

	return 0;
}
