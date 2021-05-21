#define _CRT_SECURE_NO_WARNINGS
#define MAX_INPUT 30

#include <stdio.h>

using namespace std;

char input[MAX_INPUT + 1];

char stack[MAX_INPUT];
int ptr = -1;

void print_stack()
{
	printf("stack : ");

	for (int i = 0; i <= ptr; i++)
	{
		printf("%c ", stack[i]);
	}

	printf("\n");

	return;
}

void push(char c)
{
	ptr += 1;
	stack[ptr] = c;

	return;
}

char pop()
{
	char result = 0;

	// 비어있을 경우
	if (ptr == -1)
	{
		result = '\0';
	}
	// 일반적인 경우
	else
	{
		result = stack[ptr];
		ptr -= 1;
	}

	return result;
}

int size()
{
	return (ptr + 1);
}

int empty()
{
	int result = 0;

	// 비어있을 경우
	if (ptr == -1)
	{
		result = 1;
	}
	// 일반적인 경우
	else
	{
		result = 0;
	}

	return result;
}

char top()
{
	char result = 0;

	// 비어있을 경우
	if (ptr == -1)
	{
		result = '\0';
	}
	// 일반적인 경우
	else
	{
		result = stack[ptr];
	}

	return result;
}


int main()
{
	char cur = '\0';
	char tmp = '\0';
	int score = 1;
	int ans = 0;
	int isOK = 1;

	scanf("%s", &input);

	for (int i = 0; i <= MAX_INPUT; i++)
	{
		cur = input[i];

		// printf("cur = %c, i = %d, ans = %d, score = %d\n", cur, i, ans, score);

		if (cur == '\0')
		{
			break;
		}
		else
		{
			// 1. 여는 괄호
			if (cur == '(')
			{
				// 여는 괄호 넣고
				push(cur);

				// 점수 임시 표시
				score *= 2;
			}
			else if (cur == '[')
			{
				// 여는 괄호 넣고
				push(cur);

				// 점수 임시 표시
				score *= 3;
			}

			// 2. 닫는 괄호
			else if (cur == ')')
			{
				tmp = top();

				// printf("cur = %c, tmp = %c, ans = %d, score = %d\n", cur, tmp, ans, score);

				// 비어있다면
				if (tmp == '\0')
				{
					// 올바르지 않음
					ans = 0;

					break;
				}
				// 짝이 맞다면
				else if (tmp == '(')
				{
					// 여는 괄호 꺼내고
					pop();

					// 바로 이전 괄호와 짝이 맞다면
					if (input[i - 1] == '(')
					{
						// 점수 더해준다
						ans += score;
					}

					// 임시 점수 원래대로
					score /= 2;
				}
				// 짝이 맞지 않다면
				else if (tmp == '[')
				{
					// 올바르지 않음
					ans = 0;

					break;
				}
				// 기타 입력
				else
				{

				}
			}
			else if (cur == ']')
			{
				tmp = top();

				// printf("cur = %c, tmp = %c, ans = %d, score = %d\n", cur, tmp, ans, score);

				// 비어있다면
				if (tmp == '\0')
				{
					// 올바르지 않음
					ans = 0;

					break;
				}
				// 짝이 맞다면
				else if (tmp == '[')
				{
					// 여는 괄호 꺼내고
					pop();

					// 바로 이전 괄호와 짝이 맞다면
					if (input[i - 1] == '[')
					{
						// 점수 더해준다
						ans += score;
					}

					// 임시 점수 원래대로
					score /= 3;
				}
				// 짝이 맞지 않다면
				else if (tmp == '(')
				{
					// 올바르지 않음
					ans = 0;

					break;
				}
				// 기타 입력
				else
				{

				}
			}

			// 3. 기타 입력
			else
			{

			}
		}
	}

	// 스택에 괄호가 남아있다면
	if (!(empty()))
	{
		// 올바르지 않음
		ans = 0;
	}

	printf("%d\n", ans);

	return 0;
}
