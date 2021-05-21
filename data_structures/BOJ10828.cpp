#define _CRT_SECURE_NO_WARNINGS
#define MAX_N 10000

#include <stdio.h>

using namespace std;

int stack[MAX_N];
int ptr = -1;

void print_stack()
{
	printf("stack : ");

	for (int i = 0; i <= ptr; i++)
	{
		printf("%d ", stack[i]);
	}

	printf("\n");

	return;
}

void push(int num)
{
	ptr += 1;
	stack[ptr] = num;

	return;
}

int pop()
{
	int result = 0;

	// 비어있을 경우
	if (ptr == -1)
	{
		result = -1;
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

int top()
{
	int result = 0;

	// 비어있을 경우
	if (ptr == -1)
	{
		result = -1;
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
	int n = 0;
	int tmp = 0;
	int x = 0;
	char cmd[20];

	scanf("%d", &n);

	for (int i = 0; i < n; i++)
	{
		scanf("%s", &cmd);

		// printf("cmd = %s\n", cmd);

		// push
		if ((cmd[0] == 'p') && (cmd[1] == 'u') && (cmd[2] == 's') && (cmd[3] == 'h'))
		{
			scanf("%d", &x);

			push(x);
		}
		// pop
		else if ((cmd[0] == 'p') && (cmd[1] == 'o') && (cmd[2] == 'p'))
		{
			tmp = pop();

			printf("%d\n", tmp);
		}
		// size
		else if ((cmd[0] == 's') && (cmd[1] == 'i') && (cmd[2] == 'z') && (cmd[3] == 'e'))
		{
			tmp = size();

			printf("%d\n", tmp);
		}
		// empty
		else if ((cmd[0] == 'e') && (cmd[1] == 'm') && (cmd[2] == 'p') && (cmd[3] == 't') && (cmd[4] == 'y'))
		{
			tmp = empty();

			printf("%d\n", tmp);
		}
		// top
		else if ((cmd[0] == 't') && (cmd[1] == 'o') && (cmd[2] == 'p'))
		{
			tmp = top();

			printf("%d\n", tmp);
		}
		// error
		else
		{

		}

		// print_stack();
	}

	return 0;
}
