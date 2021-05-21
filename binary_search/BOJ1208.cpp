/*
1208 부분수열의 합 2
*/

#define _CRT_SECURE_NO_WARNINGS
#define ll long long

#include <stdio.h>
#include <algorithm>

using namespace std;

#define MAX_N 40
#define MAX_DIVIDE 2
#define MAX_CNT 1500000
#define START_LEVEL 0

int N;
int S;
ll ans = 0;
int cnt = 0;
// 1부터 시작
int inputList[MAX_N + 1] = { 0, };
// 1부터 시작
int visit[MAX_N + 1] = { 0, };
// 1부터 시작
int tempList[MAX_DIVIDE + 1][MAX_CNT + 1] = { 0, };
// 1부터 시작
// dp[start][end] : start번째 ~ end번째 수로 이루어진 부분수열의 합
// int dp[MAX_N + 1][MAX_N + 1] = { 0, };
// 각 집합의 합 목록
// 1부터 시작
// 0번째에는 cnt
int sumList[MAX_DIVIDE + 1][MAX_CNT + 1] = { 0, };

void mergeSort(int idx, int *data, int *tmp, int start, int end)
{
	if (start >= end)
	{
		return;
	}

	int mid = (start + end) / 2;
	int idxTmp = start;
	int idx1 = start;
	int idx2 = mid + 1;

	mergeSort(idx, data, tmp, start, mid);
	mergeSort(idx, data, tmp, mid + 1, end);

	while ((idx1 <= mid) && (idx2 <= end))
	{
		if (data[idx1] < data[idx2])
		{
			tmp[idxTmp++] = data[idx1++];
		}
		else
		{
			tmp[idxTmp++] = data[idx2++];
		}
	}

	while (idx1 <= mid)
	{
		tmp[idxTmp++] = data[idx1++];
	}

	while (idx2 <= end)
	{
		tmp[idxTmp++] = data[idx2++];
	}

	for (int i = start; i <= end; i++)
	{
		data[i] = tmp[i];
	}

	return;
}

void quickSort(int idx, int *data, int start, int end)
{
	if (start >= end)
	{
		return;
	}

	int threshold = start;
	int ptr = end;
	int temp;

	for (int left = start; left < ptr; left++)
	{
		if (data[left] < data[ptr])
		{
			if (left != threshold)
			{
				temp = data[left];
				data[left] = data[threshold];
				data[threshold] = temp;
			}

			threshold++;
		}
	}

	if (ptr != threshold)
	{
		temp = data[ptr];
		data[ptr] = data[threshold];
		data[threshold] = temp;
	}

	quickSort(idx, data, start, threshold - 1);
	quickSort(idx, data, threshold + 1, end);

	return;
}

void run(int idx, int start, int end, int level)
{
	if (level == (end - start + 1))
	{
		int sum = 0;

		for (int i = start; i <= end; i++)
		{
			if (visit[i] == 2)
			{
				sum += inputList[i];
			}
		}

		/*
		if ((sum == S) && (cnt > 0))
		{
			ans++;
		}
		*/

		/*
		if (cnt > 0)
		{
			sumList[idx][++sumList[idx][0]] = sum;
		}
		*/

		sumList[idx][++sumList[idx][0]] = sum;

		return;
	}

	// 1. 선택하지 않음
	visit[start + level] = 1;

	run(idx, start, end, level + 1);

	visit[start + level] = 0;

	// 2. 선택
	visit[start + level] = 2;
	cnt++;

	run(idx, start, end, level + 1);

	visit[start + level] = 0;
	cnt--;

	return;
}

void solve(void)
{
	int lp = 1;
	int rp = sumList[2][0];

	/*
	while (true)
	{
		int sum = sumList[1][lp] + sumList[2][rp];

		// 왼쪽 절반만 더했을때 합이 나온다면
		if (sumList[1][lp] == S)
		{
			// 정답에 추가
			ans++;
		}

		// 오른쪽 절반만 더했을때 합이 나온다면
		if (sumList[2][rp] == S)
		{
			// 정답에 추가
			ans++;
		}

		// 합이 목표값보다 작으면
		if (sum < S)
		{
			// 예외처리
			if (lp == sumList[1][0])
			{
				for (int i = rp; i >= 1; i--)
				{
					// 오른쪽 절반만 더했을때 합이 나온다면
					if (sumList[2][rp] == S)
					{
						// 정답에 추가
						ans++;
					}
				}

				break;
			}
			else
			{
				// 합이 커져야 한다
				lp++;
			}
		}
		// 합이 목표값보다 크면
		else if (sum > S)
		{
			// 예외처리
			if (rp == 1)
			{
				for (int i = lp; i <= sumList[1][0]; i++)
				{
					// 왼쪽 절반만 더했을때 합이 나온다면
					if (sumList[1][lp] == S)
					{
						// 정답에 추가
						ans++;
					}
				}

				break;
			}
			else
			{
				// 합이 커져야 한다
				rp--;
			}
		}
		// 합을 찾았으면
		else
		{
			// 정답에 추가
			ans++;

			// 둘 중 하나는 움직여야 한다
			// 둘 다 움직일 수 없으면
			if ((lp == sumList[1][0]) && (rp == 1))
			{
				// 끝
				break;
			}
			// rp만 이동할 수 없으면
			else if (rp == 1)
			{
				for (int i = lp; i <= sumList[1][0]; i++)
				{
					// 왼쪽 절반만 더했을때 합이 나온다면
					if (sumList[1][lp] == S)
					{
						// 정답에 추가
						ans++;
					}
				}

				break;
			}
			// lp만 이동할 수 없으면
			else if (lp == sumList[1][0])
			{
				for (int i = rp; i >= 1; i--)
				{
					// 오른쪽 절반만 더했을때 합이 나온다면
					if (sumList[2][rp] == S)
					{
						// 정답에 추가
						ans++;
					}
				}

				break;
			}
			// 둘 다 움직일 수 있을 경우
			// rp를 움직였을 때 변화량이 더 큰 경우
			else if (sumList[1][lp + 1] - sumList[1][lp] < sumList[2][rp] - sumList[2][rp - 1])
			{
				// lp를 이동
				lp++;
			}
			// lp를 움직였을 때 변화량이 더 큰 경우
			// 변화량이 같은 경우
			else
			{
				// rp를 이동
				rp--;
			}
		}
	}
	*/

	while ((lp <= sumList[1][0]) && (rp >= 1))
	{
		int sum = sumList[1][lp] + sumList[2][rp];

		/*
		// 왼쪽 절반만 더했을때 합이 나온다면
		if (sumList[1][lp] == S)
		{
			// 정답에 추가
			ans++;
		}

		// 오른쪽 절반만 더했을때 합이 나온다면
		if (sumList[2][rp] == S)
		{
			// 정답에 추가
			ans++;
		}
		*/

		if (sum < S)
		{
			lp++;
		}
		else if (sum > S)
		{
			rp--;
		}
		else
		{
			int lv = sumList[1][lp];
			int rv = sumList[2][rp];
			ll lc = 0;
			ll rc = 0;

			while ((lp <= sumList[1][0]) && (sumList[1][lp] == lv))
			{
				/*
				// 왼쪽 절반만 더했을때 합이 나온다면
				if ((sumList[1][lp] == S) && (lc > 0))
				{
					// 정답에 추가
					ans++;
				}
				*/

				lc++;
				lp++;
			}

			while ((rp >= 1) && (sumList[2][rp] == rv))
			{
				/*
				// 오른쪽 절반만 더했을때 합이 나온다면
				if ((sumList[2][rp] == S) && (rc > 0))
				{
					// 정답에 추가
					ans++;
				}
				*/

				rc++;
				rp--;
			}

			ans += (lc * rc);
		}
	}

	/*
	while (lp <= sumList[1][0])
	{
		int sum = sumList[1][lp] + sumList[2][rp];

		// 왼쪽 절반만 더했을때 합이 나온다면
		if (sumList[1][lp] == S)
		{
			// 정답에 추가
			ans++;
		}

		if (sum == S)
		{
			ans++;
		}
		else if (sum > S)
		{
			break;
		}

		lp++;
	}

	while (rp >= 1)
	{
		int sum = sumList[1][lp] + sumList[2][rp];

		// 오른쪽 절반만 더했을때 합이 나온다면
		if (sumList[2][rp] == S)
		{
			// 정답에 추가
			ans++;
		}

		if (sum == S)
		{
			ans++;
		}
		else if (sum < S)
		{
			break;
		}

		rp--;
	}
	*/

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);
	// freopen("input3.txt", "r", stdin);
	// freopen("input4.txt", "r", stdin);
	// freopen("input5.txt", "r", stdin);
	// freopen("input6.txt", "r", stdin);
	// freopen("input7.txt", "r", stdin);

	setbuf(stdout, NULL);

	scanf("%d %d", &N, &S);

	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &inputList[i]);
	}

	/*
	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &dp[i][i]);

		if (dp[i][i] == S)
		{
			ans++;
		}
	}

	for (int c = 1; c <= N; c++)
	{
		for (int r = 1; r < c; r++)
		{
			dp[r][c] = dp[r][c - 1] + dp[c][c];

			if (dp[r][c] == S)
			{
				ans++;
			}
		}
	}
	*/

	if (N == 1)
	{
		if (inputList[1] == S)
		{
			ans = 1;
		}
		else
		{
			ans = 0;
		}
	}
	else
	{
		run(1, 1, N / 2, START_LEVEL);
		run(2, (N / 2) + 1, N, START_LEVEL);

		mergeSort(1, sumList[1], tempList[1], 1, sumList[1][0]);
		mergeSort(2, sumList[2], tempList[2], 1, sumList[2][0]);

		// quickSort(1, sumList[1], 1, sumList[1][0]);
		// quickSort(2, sumList[2], 1, sumList[2][0]);

		// sort(sumList[1] + 1, sumList[1] + sumList[1][0] + 1);
		// sort(sumList[2] + 1, sumList[2] + sumList[2][0] + 1);

		solve();

		if (S == 0)
		{
			ans--;
		}
	}

	printf("%lld\n", ans);

	return 0;
}
