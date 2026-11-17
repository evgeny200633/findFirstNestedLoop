#include "findFirstNestedLoop/findFirstNestedLoop.h"

#include <stdio.h>
#include <string.h>

#pragma warning (disable:4996)

int main()
{
	int strCount;
	char text[MAX_STR_COUNT][MAX_STR_LENGTH];

	if (scanf("%d", &strCount) != 1)
	{
		printf("invalid input data: expected string count\n");
		return 0;
	}

	if (strCount < 1 || strCount > MAX_STR_COUNT)
	{
		printf("invalid input data: string count %d is out of range [1, %d]\n", strCount, MAX_STR_COUNT);
		return 0;
	}

	// Очищаем буфер ввода от символа перевода строки после ввода числа
	int ch = getchar();
	while (ch != '\n' && ch != EOF)
	{
		ch = getchar();
	}

	for (int i = 0; i < strCount; ++i)
	{
		if (gets_s(text[i], MAX_STR_LENGTH) != NULL)
		{
			// Удаляем возможные символы переноса
			text[i][strcspn(text[i], "\n\r")] = '\0';
		}
		else
		{
			// Пустая строка
			text[i][0] = '\0';
		}
	}

	int result = findFirstNestedLoop(text, strCount, 0);

	if (result > 0)
	{
		printf("1\n");
	}
	else
	{
		printf("0\n");
	}

	return 0;
}
