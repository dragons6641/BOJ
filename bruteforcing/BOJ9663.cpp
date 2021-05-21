/*
C8 N QUEEN
*/

#define _CRT_SECURE_NO_WARNINGS

/*
#include <stdio.h>

#define MAX_N 15
#define START_R 1

int N;
int ans = 0;
// col만 체크하면 된다
// row 번호를 표시
// 1부터 시작
// visit[c] = r
int visit[MAX_N + 1] = { 0, };

bool isPossible(int nowR, int nowC)
{
	for (int i = 1; i <= N; i++)
	{
		// 놓아진 것 없으면 체크 안해도 됨
		if (visit[i] == 0)
		{
			continue;
		}
		// 같은 줄에는 놓으면 안 됨
		else if (visit[i] == nowR)
		{
			return false;
		}

		// 좌측 대각선 체크
		// 같은 대각선에 이미 놓여 있는 경우
		if (nowC - nowR == i - visit[i])
		{
			// 놓을 수 없다
			return false;
		}

		// 우측 대각선 체크
		// 같은 대각선에 이미 놓여 있는 경우
		if (nowC + nowR == i + visit[i])
		{
			// 놓을 수 없다
			return false;
		}
	}

	// 놓을 수 있다
	return true;
}

// row별로 queen을 하나씩 놓는다
void dfs(int nowR)
{
	if (nowR == N + 1)
	{
		ans++;

		return;
	}

	for (int c = 1; c <= N; c++)
	{
		if (visit[c] > 0)
		{
			continue;
		}

		bool ret = isPossible(nowR, c);

		// 조건 체크
		if (ret)
		{
			visit[c] = nowR;

			dfs(nowR + 1);

			visit[c] = 0;
		}
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	scanf("%d", &N);

	dfs(START_R);

	printf("%d\n", ans);

	return 0;
}
*/

#include <stdio.h>
#define MAXN (15)
int N;//체스판 크기, 퀸 개수
int sol;//가능한 횟수
#if 0
int chess[MAXN][MAXN];
int isPossible(int r, int c) {
	//1.세로줄 체크
	for (int h = 0; h < r; h++) if (chess[h][c]) return 0;//놓을수없음
	//2.좌상단대각선
	for (int h = r - 1, w = c - 1; (h >= 0) && (w >= 0); h--, w--) {
		if (chess[h][w]) return 0;//놓을수없음
	}
	//3.우상단대각선
	for (int h = r - 1, w = c + 1; (h >= 0) && (w < N); h--, w++) {
		if (chess[h][w]) return 0;//놓을수없음
	}
	return 1;//놓을수있음
}
void DFS(int n) {//순열
	if (n >= N) {//성공, 종료조건
		sol++;
		return;
	}
	for (int c = 0; c < N; c++) {
		if (!isPossible(n, c)) continue;
		chess[n][c] = 1;//표시
		DFS(n + 1);
		chess[n][c] = 0;//표시제거
	}
}
#else
int check1[MAXN];//세로줄 [c]
int check2[MAXN * 2];//좌상단 [N-1+c-r]
int check3[MAXN * 2];//우상단 [r+c]
void DFS(int r) {
	if (r >= N) {
		sol++; return;
	}
	for (int c = 0; c < N; c++) {
		if (check1[c]) continue;
		if (check2[N - 1 + c - r]) continue;
		if (check3[r + c]) continue;
		check1[c] = check2[N - 1 + c - r] = check3[r + c] = 1;//표시
		DFS(r + 1);
		check1[c] = check2[N - 1 + c - r] = check3[r + c] = 0;//표시제거
	}
}
#endif // 1
int Solve() {
	sol = 0;
	DFS(0);
	return sol;
}
void InputData() {
	scanf("%d", &N);
}
int main() {
	InputData();
	int ans = Solve();
	printf("%d\n", ans);
	return 0;
}
