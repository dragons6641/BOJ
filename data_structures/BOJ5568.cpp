#define _CRT_SECURE_NO_WARNINGS
#define MAX_DIGIT 2

#include <stdio.h>
#include <set>
#include <string>
#include <vector>
// #include <iostream>

using namespace std;

// 여기에 집어넣자
// set < vector <char> > s;
set <string> s;

vector <string> v;
vector <bool> isSelected;

// vector <char> tmp(MAX_DIGIT + 1, '\0');

// char input[MAX_DIGIT + 1] = "\0";

// 인풋을 저장할 문자열
string input;

// 결과를 만들 문자열
string ans;

int n = 0;
int k = 0;
// int ans = 0;
int tmp_int = 0;

void print_s()
{
	printf("size : %d\n", s.size());

	printf("s : ");

	for (auto iter = s.begin(); iter != s.end(); iter++)
	{
		printf("%s ", iter);
	}

	printf("\n");

	return;
}

/*
void print_tmp()
{
	printf("tmp : ");

	for (int i = 0; i < tmp.size(); i++)
	{
		printf("%c", tmp[i]);
	}

	printf("\n");

	return;
}
*/

/*
void print_input()
{
	printf("input : ");

	for (int i = 0; i < strlen(input); i++)
	{
		printf("%c", input[i]);
	}

	printf("\n");

	return;
}
*/

void print_string(string tmp)
{
	printf("string : ");

	for (int i = 0; i < tmp.size(); i++)
	{
		printf("%c", tmp[i]);
	}

	printf("\n");

	return;
}

void solve(vector <string> :: iterator cur, string tmp, int depth)
{
	// tmp += *cur;

	// 문자열 갯수 모두 사용했으면
	if (depth == k)
	{
		// 집합에 넣어준다
		s.insert(tmp);

		// print_string(tmp);
		// printf("depth : %d\n\n", depth);

		return;
	}

	// printf("tmp : %s, depth : %d\n", tmp, depth);
	// print_string(tmp);
	// printf("depth : %d\n\n", depth);

	for (auto iter = v.begin()++; iter != v.end(); iter++)
	{
		// 자기 자신은 제외
		if (iter != cur)
		{
			// print_string(tmp);
			// print_string(*iter);
			// printf("\n");

			// 문자열을 골랐을 경우
			solve(iter, (tmp + *iter), (depth + 1));
		}

		// cur++;

		// 문자열을 고르지 않았을 경우
		// solve(cur, tmp, (depth + 1));
	}

	return;
}

void new_solve(int cur, string tmp, int depth)
{
	if (depth == k)
	{
		s.insert(tmp);

		// print_string(tmp);

		return;
	}

	for (int i = 0; i < v.size(); i++)
	{
		// 자기 자신은 사용하면 안됨
		if (i != cur)
		{
			// 아직 사용하지 않았다면
			if (!isSelected[i])
			{
				// printf("cur = %d, i = %d\n", cur, i);

				// 썼다고 표시
				isSelected[i] = true;

				// 사용한다
				new_solve(i, tmp + v[i], depth + 1);

				// 쓴거 다시 초기화
				isSelected[i] = false;
			}
		}
	}

	return;
}

int main()
{
	/*
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	*/

	scanf("%d", &n);
	scanf("%d", &k);

	for (int i = 0; i < n; i++)
	{
		/*
		// scanf("%s", tmp);
		// scanf("%s", input);
		// getline(cin, input);

		// print_input();
		printf("input = %s\n", input);

		s.insert(input);

		printf("size : %d\n", s.size());
		*/

		scanf("%d", &tmp_int);

		// s.insert(to_string(tmp_int));
		v.push_back(to_string(tmp_int));

		// printf("size : %d\n", s.size());
	}

	isSelected.resize(v.size(), false);

	// print_s();

	new_solve(-1, ans, 0);

	/*
	// 처음을 골랐을 경우
	solve(v.begin(), ans, 0);
	// 처음을 고르지 않았을 경우
	solve(v.begin(), (ans + *v.begin()), 1);
	*/

	printf("%d\n", s.size());

	return 0;
}

// 강사님 코드
/*
#include <stdio.h>
#include <algorithm>
using namespace std;
int N, K;
int A[10], V[10];
int P[10 * 9 * 8 * 7], pcnt;

void back(int cnt, int num)
{
	if (cnt == K) P[pcnt++] = num;
	else
	{
		for (int i = 0; i<N; i++)
		{
			if (V[i] == 0)
			{
				V[i] = 1;
				int n_num = num * 10;
				if (A[i]>9) n_num *= 10;
				back(cnt + 1, n_num + A[i]);
				V[i] = 0;
			}
		}
	}

}

int main()
{
	scanf("%d%d", &N, &K);
	for (int i = 0; i<N; i++)
	{
		scanf("%d", A + i);
		V[i] = 0;
	}
	pcnt = 0;
	back(0, 0);
	sort(P, P + pcnt);
	int ans = 0, ex_num = -1;
	for (int i = 0; i<pcnt; i++)
	{
		if (ex_num<P[i])
		{
			ans++;
			ex_num = P[i];
		}
	}
	printf("%d", ans);
}
*/
