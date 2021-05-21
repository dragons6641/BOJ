#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <set>

using namespace std;

int main()
{
	int u = 0;
	int v = 0;
	int isFinished = 0;
	int edges = 0;
	int t = 0;

	set<int> s;

	while (1)
	{
		// 테스트 케이스 번호
		t += 1;

		// 테스트 케이스마다 간선 갯수 초기화
		edges = 0;

		// 테스트 케이스마다 셋도 초기화
		s.clear();

		while (1)
		{
			scanf("%d %d", &u, &v);

			// 테스트 케이스 하나 끝나면
			if (u + v == 0)
			{
				break;
			}
			// 테스트 케이스 전체 끝나면
			else if (u + v < 0)
			{
				isFinished = 1;

				break;
			}

			s.insert(u);
			s.insert(v);

			// 간선 갯수 증가
			edges += 1;
		}
		
		// 테스트 케이스 전체 끝나면
		if (isFinished)
		{
			break;
		}

		// 마이너스는 위험하다, 플러스 사용 습관!
		// 간선이 없는 것도 트리다
		// vertexes = edges + 1
		if ((edges == 0) || (s.size() == edges + 1))
		{
			printf("Case %d is a tree.\n", t);
		}
		// 트리의 조건 만족하지 않으면
		else
		{
			printf("Case %d is not a tree.\n", t);
		}
	}

	return 0;
}
