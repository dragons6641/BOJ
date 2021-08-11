#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <set>

#define MAX_K 1000000

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);
	// freopen("input3.txt", "r", stdin);
	// freopen("input4.txt", "r", stdin);
	// freopen("input5.txt", "r", stdin);
	// freopen("input6.txt", "r", stdin);
	// freopen("input7.txt", "r", stdin);

	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	int T;
	std::cin >> T;
	// std::cout << T << '\n';

	for (register int testCase = 0; testCase < T; testCase++)
	{
		int K;
		std::multiset<int> ms;

		std::cin >> K;
		// std::cout << K << '\n';

		for (register int operationIdx = 0; operationIdx < K; operationIdx++)
		{
			char cmd;
			int num;

			std::cin >> cmd >> num;
			// std::cout << cmd << ' ' << num << '\n';

			if (cmd == 'I')
			{
				ms.insert(num);

				// std::cout << ms.size() << '\n';
			}
			else if(cmd == 'D')
			{
				if (ms.empty())
				{
					continue;
				}

				if (num == 1)
				{
					ms.erase(--ms.end());
				}
				else if (num == -1)
				{
					ms.erase(ms.begin());
				}

				// std::cout << ms.size() << '\n';
			}
		}

		// std::cout << ms.size() << '\n';

		if (ms.empty())
		{
			std::cout << "EMPTY\n";
		}
		else
		{
			std::cout << *(ms.rbegin()) << ' ' << *(ms.begin()) << '\n';
		}
	}

	return 0;
}
