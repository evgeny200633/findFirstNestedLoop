#include "findFirstNestedLoop/findFirstNestedLoop.h"

#include <stdio.h>
#include <string.h>

#pragma warning (disable:4996)
#pragma warning (disable:6031) // Возвращаемое значение пропущено : "scanf".

int main()
{
	int M;
	scanf("%d", &M);

	if (M < 1 || M > MAX_STR_COUNT)
	{
		printf("invalid input data: str count %d is out of range [1, %d]\n", M, MAX_STR_COUNT);
		return 0;
	}

	while (getchar() != '\n');

	char text[MAX_STR_COUNT][MAX_STR_LENGTH];

	for (int i = 0; i < M; ++i)
	{
		if (gets_s(text[i], MAX_STR_LENGTH) != NULL)
		{
			text[i][strcspn(text[i], "\n")] = '\0';
		}
	}

	int ret = findFirstNestedLoop(text, M, 0);

	if (ret > 0)
	{
		printf("1\n");
	}
	else
	{
		printf("0\n");
	}

	return 0;
}
