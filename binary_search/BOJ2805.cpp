/*
A8 나무 자르기
*/

#define _CRT_SECURE_NO_WARNINGS
#define ll long long

#include <stdio.h>

/*
#define MAX_N 1000000
#define MAX_M 2000000000

// 나무의 수
int N;
// 집으로 가져가야 하는 나무의 총 길이
int M;
// 최소 높이
// int minHeight = MAX_M + 1;
// 최대 높이
// int maxHeight = 0;
int inputList[MAX_N] = { 0, };
int tmpList[MAX_N] = { 0, };

void inputData(void)
{
	scanf("%d %d", &N, &M);

	for (int i = 0; i < N; i++)
	{
		scanf("%d", &inputList[i]);
	}

	return;
}

void mergeSort(int s, int e) 
{
	if (s >= e)
	{
		return;
	}
		
	int i = s;
	int k = s;
	int m = (s + e) / 2;
	int j = m + 1;

	mergeSort(s, m); 
	mergeSort(m + 1, e);

	while ((i <= m) && (j <= e)) 
	{
		if (inputList[i] >= inputList[j])
		{
			tmpList[k++] = inputList[i++];
		}
		else
		{
			tmpList[k++] = inputList[j++];
		}
	}

	while (i <= m)
	{
		tmpList[k++] = inputList[i++];
	}
		
	while (j <= e)
	{
		tmpList[k++] = inputList[j++];
	}
		
	for (i = s; i <= e; i++)
	{
		inputList[i] = tmpList[i];
	}
	
	return;
}

ll getDiff(int h)
{
	ll sumHeight = 0;

	for (int i = 0; i < N; i++)
	{
		if (inputList[i] <= h)
		{
			break;
		}
		else
		{
			sumHeight += (ll)(inputList[i] - h);
		}
	}

	return sumHeight;
}
*/

/*
int binarySearchLower(int s, int e, int d) // d보다 크거나 같은 값 중에 제일 작은 인덱스
{
	int sol = -1;

	while (s <= e) 
	{
		int m = (s + e) / 2;

		if (inputList[m] >= d) 
		{
			sol = m; 
			e = m - 1;
		}
		else
		{
			s = m + 1;
		}
	}

	return sol;
}

int binarySearchUpper(int s, int e, int d) // d보다 작거나 같은 값 중에 제일 큰 인덱스
{
	int sol = -1;

	while (s <= e) 
	{
		int m = (s + e) / 2;

		if (inputList[m] <= d) 
		{
			sol = m; 
			s = m + 1;
		}
		else
		{
			e = m - 1;
		}
	}

	return sol;
}
*/

/*
int binarySearchLower(int s, int e, int d) // d보다 크거나 같은 값 중에 제일 작은 값
{
	int sol = 0;

	while (s >= e)
	{
		int m = (s + e) / 2;
		ll ret = getDiff(m);

		if (ret >= (ll)d)
		{
			sol = m;
			e = m + 1;
		}
		else
		{
			s = m - 1;
		}
	}

	return sol;
}

int solve(void)
{
	// 1. 정렬
	// void mergeSort(int s, int e) 
	mergeSort(0, N - 1);

	// 2. 이분탐색
	// int binarySearchLower(int s, int e, int d)
	int ret = binarySearchLower(inputList[0], inputList[N - 1], M);

	return ret;
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

#pragma warning (disable : 4996)
#include <stdio.h>
#define MAXN ((int)1e6 + 10)
int N, M;//나무 수, 나무 총길이
int H[MAXN];//나무 높이
void InputData() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		scanf("%d", &H[i]);
	}
}
int isPossible(int m) {
	int sum = M;
	for (int i = 0; i < N; i++) {
		if (H[i] <= m) continue;
		sum -= H[i] - m;
		if (sum <= 0) return 1;//가능
	}
	return 0;//불가능
}
int solve() {
	int s = 0, e = 0, m, sol = 0;
	for (int i = 0; i < N; i++) {
		if (e < H[i]) e = H[i];//제일 높은 나무가 e임
	}
	while (s <= e) {//upper bound찾기 (제한 높이가 낮을수록 더 많은 나무를 얻을수 있음)
		m = (s + e) / 2;
		if (isPossible(m)) {
			sol = m; s = m + 1;
		}
		else e = m - 1;
	}
	return sol;
}
int main() {
	InputData();
	int ans = solve();
	printf("%d\n", ans);
	return 0;
}
