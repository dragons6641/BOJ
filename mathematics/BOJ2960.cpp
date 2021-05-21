#define _CRT_SECURE_NO_WARNINGS
#define MAX_N 1000

#include <stdio.h>
#include <vector>

using namespace std;

// 상태 표시 벡터
vector <int> check;

int sieve(int n, int k)
{
	int result = 0;
	int cnt = 0;

	// i는 시작점의 위치
	for (int i = 2; i < check.size(); i++)
	{
		// j는 간격
		for (int j = i; j < check.size(); j += i)
		{
			// 배수이면
			if (check[j] == 0)
			{
				cnt += 1;

				// 지워준다
				check[j] = 1;

				// 수를 찾았으면
				if (cnt == k)
				{
					result = j;

					return result;
				}
			}
		}
	}

	return result;
}

int main()
{
	int n = 0;
	int k = 0;
	int ans = 0;

	scanf("%d %d", &n, &k);

	// 벡터 크기
	check.resize(n + 1);

	// 에라토스테네스의 체
	ans = sieve(n, k);

	// print_erase();

	printf("%d\n", ans);

	return 0;
}


// 강사님 코드
/*
#include <cstdio>
int N,K;
bool isPrime[1001];

int main() 
{
    scanf("%d%d",&N,&K);
    isPrime[0] = isPrime[1] = false;
    for(int i=2;i<=N;i++) isPrime[i] = true;

    int ans = -1;
    for (int i = 2; i <= N; i++) {
        if(!isPrime[i]) continue;

        for (int j = i; j <= N; j+=i) {
            if(!isPrime[j]) continue;
            isPrime[j] = false;
            if(--K == 0) ans = j;
        }
        if(K==0) break;
    }
    printf("%d",ans);
}
*/
