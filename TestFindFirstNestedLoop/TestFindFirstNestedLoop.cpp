#include "CppUnitTest.h"

#include "findFirstNestedLoop/findFirstNestedLoop.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestFindFirstNestedLoop
{
	TEST_CLASS(TestFindFirstNestedLoop)
	{
	public:
		
		// 1) Типовой тест
		TEST_METHOD(typicalTest)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"int main(void)",
				"{",
				"int i, j;",
				"for (i = 0; i < 3; i++)",
				"{",
				"while (j < 3)",
				"{",
				"j++;",
				"}",
				"}",
				"return 0;",
				"}"
			};

			const int in_strCount = 12;
			const int in_startLine = 0;

			const int exp_result = 5;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 2) Минимальная по размеру программа, циклов нет
		TEST_METHOD(minimalProgramNoLoops)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"void main()",
				"{",
				"}"
			};

			const int in_strCount = 3;
			const int in_startLine = 0;

			const int exp_result = NO_NESTED_LOOPS;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 3) Циклов нет
		TEST_METHOD(noLoops)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"void main(void)",
				"{",
				"int a = 1;",
				"a++;",
				"return 0;",
				"}"
			};

			const int in_strCount = 6;
			const int in_startLine = 0;

			const int exp_result = NO_NESTED_LOOPS;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 4) Один цикл
		TEST_METHOD(singleLoopNoNesting)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"int main(void)",
				"{",
				"int i;",
				"for (i = 0; i < 3; i++)",
				"{",
				"i++;",
				"}",
				"return 0;",
				"}"
			};

			const int in_strCount = 9;
			const int in_startLine = 0;

			const int exp_result = NO_NESTED_LOOPS;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 5) Два последовательных цикла
		TEST_METHOD(twoSequentialLoopsNoNesting)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"int main(void)",
				"{",
				"int i = 0;",
				"for (i = 0; i < 3; i++)",
				"{",
				"i += 2;",
				"}",
				"while (i > 0)",
				"{",
				"i--;",
				"}",
				"return 0;",
				"}"
			};

			const int in_strCount = 13;
			const int in_startLine = 0;

			const int exp_result = NO_NESTED_LOOPS;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 6) Максимум строк, вложенный в конце
		TEST_METHOD(maxStrCountNestedAtEnd)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"void main(void)",
				"{",
				"int i, j;",
				"i++;",
				"i++;",
				"i++;",
				"i++;",
				"i++;",
				"i++;",
				"i++;",
				"i++;",
				"i++;",
				"for (i = 0; i < 3; i++)",
				"{",
				"while (j < 3)",
				"{",
				"j++;",
				"}",
				"}",
				"}"
			};

			const int in_strCount = 20;
			const int in_startLine = 0;

			const int exp_result = 14;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 7) Пустые строки и строки из пробелов/табуляций
		TEST_METHOD(emptyAndWhitespaceLines)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"void main(void)",
				"",
				"{",
				"   ",
				"int i, j;",
				"for (i = 0; i < 3; i++)",
				"{",
				"\t",
				"while (j < 3)",
				"{",
				"j++;",
				"}",
				"",
				"}",
				"}"
			};

			const int in_strCount = 15;
			const int in_startLine = 0;

			const int exp_result = 8;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 8) Директивы препроцессора
		TEST_METHOD(preprocessorDirectives)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"#include <stdio.h>",
				"#define COUNT 3",
				"void main(void)",
				"{",
				"int i, j;",
				"for (i = 0; i < COUNT; i++)",
				"{",
				"while (j < COUNT)",
				"{",
				"j++;",
				"}",
				"}",
				"}"
			};

			const int in_strCount = 13;
			const int in_startLine = 0;

			const int exp_result = 7;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 9) Вложенный цикл во второй из двух функций
		TEST_METHOD(nestedInSecondOfSeveralFunctions)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"void f(void)",
				"{",
				"int i = 0;",
				"i++;",
				"}",
				"void main(void)",
				"{",
				"int i, j;",
				"for (i = 0; i < 3; i++)",
				"{",
				"while (j < 3)",
				"{",
				"j++;",
				"}",
				"}",
				"}"
			};

			const int in_strCount = 16;
			const int in_startLine = 0;

			const int exp_result = 10;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 10) Циклы в разных функциях (конец одной и начало другой)
		TEST_METHOD(loopsInDifferentFunctionsNoNesting)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"void f(void)",
				"{",
				"int i;",
				"for (i = 0; i < 3; i++)",
				"{",
				"i++;",
				"}",
				"}",
				"void main(void)",
				"{",
				"int j;",
				"while (j < 3)",
				"{",
				"j++;",
				"}",
				"}"
			};

			const int in_strCount = 16;
			const int in_startLine = 0;

			const int exp_result = NO_NESTED_LOOPS;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 11) Цикл вызывает функцию с циклом
		TEST_METHOD(loopCallsFunctionWithLoopNoNesting)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"void f(void)",
				"{",
				"int i;",
				"for (i = 0; i < 3; i++)",
				"{",
				"i++;",
				"}",
				"}",
				"void main(void)",
				"{",
				"int j;",
				"while (j < 3)",
				"{",
				"f();",
				"j++;",
				"}",
				"}"
			};

			const int in_strCount = 17;
			const int in_startLine = 0;

			const int exp_result = NO_NESTED_LOOPS;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 12) for во внешнем for
		TEST_METHOD(forInFor)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"int main(void)",
				"{",
				"int i, j;",
				"for (i = 0; i < 3; i++)",
				"{",
				"for (j = 0; j < 3; j++)",
				"{",
				"j++;",
				"}",
				"}",
				"return 0;",
				"}"
			};

			const int in_strCount = 12;
			const int in_startLine = 0;

			const int exp_result = 5;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 13) while во внешнем for
		TEST_METHOD(whileInFor)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"int main(void)",
				"{",
				"int i, j;",
				"for (i = 0; i < 3; i++)",
				"{",
				"while (j < 3)",
				"{",
				"j++;",
				"}",
				"}",
				"return 0;",
				"}"
			};

			const int in_strCount = 12;
			const int in_startLine = 0;

			const int exp_result = 5;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 14) do...while во внешнем for
		TEST_METHOD(doInFor)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"int main(void)",
				"{",
				"int i, j;",
				"for (i = 0; i < 3; i++)",
				"{",
				"do",
				"{",
				"j++;",
				"}",
				"while (j < 3);",
				"}",
				"return 0;",
				"}"
			};

			const int in_strCount = 13;
			const int in_startLine = 0;

			const int exp_result = 5;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 15) for во внешнем while
		TEST_METHOD(forInWhile)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"int main(void)",
				"{",
				"int i, j;",
				"while (i < 3)",
				"{",
				"for (j = 0; j < 3; j++)",
				"{",
				"j++;",
				"}",
				"}",
				"return 0;",
				"}"
			};

			const int in_strCount = 12;
			const int in_startLine = 0;

			const int exp_result = 5;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 16) while во внешнем while
		TEST_METHOD(whileInWhile)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"int main(void)",
				"{",
				"int i, j;",
				"while (i < 3)",
				"{",
				"while (j < 3)",
				"{",
				"j++;",
				"}",
				"}",
				"return 0;",
				"}"
			};

			const int in_strCount = 12;
			const int in_startLine = 0;

			const int exp_result = 5;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 17) do...while во внешнем while
		TEST_METHOD(doInWhile)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"int main(void)",
				"{",
				"int i, j;",
				"while (i < 3)",
				"{",
				"do",
				"{",
				"j++;",
				"}",
				"while (j < 3);",
				"}",
				"return 0;",
				"}"
			};

			const int in_strCount = 13;
			const int in_startLine = 0;

			const int exp_result = 5;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 18) for во внешнем do...while
		TEST_METHOD(forInDo)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"int main(void)",
				"{",
				"int i, j;",
				"do",
				"{",
				"for (j = 0; j < 3; j++)",
				"{",
				"j++;",
				"}",
				"}",
				"while (i < 3);",
				"return 0;",
				"}"
			};

			const int in_strCount = 13;
			const int in_startLine = 0;

			const int exp_result = 5;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 19) while во внешнем do...while
		TEST_METHOD(whileInDo)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"int main(void)",
				"{",
				"int i, j;",
				"do",
				"{",
				"while (j < 3)",
				"{",
				"j++;",
				"}",
				"}",
				"while (i < 3);",
				"return 0;",
				"}"
			};

			const int in_strCount = 13;
			const int in_startLine = 0;

			const int exp_result = 5;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 20) do...while во внешнем do...while
		TEST_METHOD(doInDo)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"int main(void)",
				"{",
				"int i, j;",
				"do",
				"{",
				"do",
				"{",
				"j++;",
				"}",
				"while (j < 3);",
				"}",
				"while (i < 3);",
				"return 0;",
				"}"
			};

			const int in_strCount = 14;
			const int in_startLine = 0;

			const int exp_result = 5;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 21) Три уровня, возвращается первый вложенный
		TEST_METHOD(threeLevelsReturnsFirstNested)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"int main(void)",
				"{",
				"int i, j, k;",
				"for (i = 0; i < 3; i++)",
				"{",
				"while (j < 3)",
				"{",
				"do",
				"{",
				"k++;",
				"}",
				"while (k < 3);",
				"}",
				"}",
				"return 0;",
				"}"
			};

			const int in_strCount = 16;
			const int in_startLine = 0;

			const int exp_result = 5;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 22) Несколько вложенных пар, возвращается первая
		TEST_METHOD(severalNestedPairsReturnsFirst)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"void main(void)",
				"{",
				"int i, j;",
				"for (i = 0; i < 3; i++)",
				"{",
				"while (j < 3)",
				"{",
				"j++;",
				"}",
				"}",
				"for (i = 0; i < 3; i++)",
				"{",
				"while (j < 3)",
				"{",
				"j++;",
				"}",
				"}",
				"}"
			};

			const int in_strCount = 18;
			const int in_startLine = 0;

			const int exp_result = 5;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 23) Вложенная пара после последовательных циклов
		TEST_METHOD(nestedAfterSequentialLoops)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"void main(void)",
				"{",
				"int i, j;",
				"for (i = 0; i < 3; i++)",
				"{",
				"j++;",
				"}",
				"while (j > 0)",
				"{",
				"j--;",
				"}",
				"for (i = 0; i < 3; i++)",
				"{",
				"while (j < 3)",
				"{",
				"j++;",
				"}",
				"}",
				"}"
			};

			const int in_strCount = 19;
			const int in_startLine = 0;

			const int exp_result = 13;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 24) Вложенные бесконечные циклы в начале текста
		TEST_METHOD(nestedNearBeginningInfiniteLoops)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"void f(void)",
				"{",
				"for (;;)",
				"{",
				"while (1)",
				"{",
				"break;",
				"}",
				"}",
				"}"
			};

			const int in_strCount = 10;
			const int in_startLine = 0;

			const int exp_result = 4;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 25) Внутренний цикл между операторами
		TEST_METHOD(innerBetweenStatements)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"void main(void)",
				"{",
				"int i, j;",
				"for (i = 0; i < 3; i++)",
				"{",
				"j = 0;",
				"while (j < 3)",
				"{",
				"j++;",
				"}",
				"i++;",
				"}",
				"}"
			};

			const int in_strCount = 13;
			const int in_startLine = 0;

			const int exp_result = 6;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 26) Внутренний цикл последним в теле
		TEST_METHOD(innerLastInBody)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"void main(void)",
				"{",
				"int i, j;",
				"for (i = 0; i < 3; i++)",
				"{",
				"j = 0;",
				"i += 2;",
				"while (j < 3)",
				"{",
				"j++;",
				"}",
				"}",
				"}"
			};

			const int in_strCount = 13;
			const int in_startLine = 0;

			const int exp_result = 7;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 27) Внутренний цикл в if
		TEST_METHOD(innerInIfBranch)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"void main(void)",
				"{",
				"int i, j;",
				"for (i = 0; i < 3; i++)",
				"{",
				"if (i > 1)",
				"{",
				"while (j < 3)",
				"{",
				"j++;",
				"}",
				"}",
				"}",
				"}"
			};

			const int in_strCount = 14;
			const int in_startLine = 0;

			const int exp_result = 7;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 28) Внутренний цикл в else
		TEST_METHOD(innerInElseBranch)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"void main(void)",
				"{",
				"int i, j;",
				"for (i = 0; i < 3; i++)",
				"{",
				"if (i > 1)",
				"{",
				"j++;",
				"}",
				"else",
				"{",
				"while (j < 3)",
				"{",
				"j++;",
				"}",
				"}",
				"}",
				"}"
			};

			const int in_strCount = 18;
			const int in_startLine = 0;

			const int exp_result = 11;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 29) Внутренний цикл в else if
		TEST_METHOD(innerInElseIfBranch)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"void main(void)",
				"{",
				"int i, j;",
				"for (i = 0; i < 3; i++)",
				"{",
				"if (i > 1)",
				"{",
				"j++;",
				"}",
				"else if (i > 0)",
				"{",
				"while (j < 3)",
				"{",
				"j++;",
				"}",
				"}",
				"}",
				"}"
			};

			const int in_strCount = 18;
			const int in_startLine = 0;

			const int exp_result = 11;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 30) Внутренний цикл в case
		TEST_METHOD(innerInSwitchCase)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"void main(void)",
				"{",
				"int i, j;",
				"for (i = 0; i < 3; i++)",
				"{",
				"switch (i)",
				"{",
				"case 1:",
				"while (j < 3)",
				"{",
				"j++;",
				"}",
				"break;",
				"default:",
				"j = 0;",
				"}",
				"}",
				"}"
			};

			const int in_strCount = 18;
			const int in_startLine = 0;

			const int exp_result = 8;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 31) Внутренний цикл в блоке {}
		TEST_METHOD(innerInPlainBlock)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"void main(void)",
				"{",
				"int i, j;",
				"for (i = 0; i < 3; i++)",
				"{",
				"{",
				"while (j < 3)",
				"{",
				"j++;",
				"}",
				"}",
				"}",
				"}"
			};

			const int in_strCount = 13;
			const int in_startLine = 0;

			const int exp_result = 6;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 32) Внешний цикл в if
		TEST_METHOD(outerInIfBranch)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"void main(void)",
				"{",
				"int i, j;",
				"if (i == 0)",
				"{",
				"for (i = 0; i < 3; i++)",
				"{",
				"while (j < 3)",
				"{",
				"j++;",
				"}",
				"}",
				"}",
				"}"
			};

			const int in_strCount = 14;
			const int in_startLine = 0;

			const int exp_result = 7;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 33) Внешний цикл в else
		TEST_METHOD(outerInElseBranch)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"void main(void)",
				"{",
				"int i, j;",
				"if (i == 0)",
				"{",
				"i++;",
				"}",
				"else",
				"{",
				"while (i < 3)",
				"{",
				"for (j = 0; j < 3; j++)",
				"{",
				"j++;",
				"}",
				"}",
				"}",
				"}"
			};

			const int in_strCount = 18;
			const int in_startLine = 0;

			const int exp_result = 11;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 34) Внешний цикл в case
		TEST_METHOD(outerInSwitchCase)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"void main(void)",
				"{",
				"int i, j;",
				"switch (i)",
				"{",
				"case 0:",
				"for (i = 0; i < 3; i++)",
				"{",
				"while (j < 3)",
				"{",
				"j++;",
				"}",
				"}",
				"break;",
				"default:",
				"i = 0;",
				"}",
				"}"
			};

			const int in_strCount = 18;
			const int in_startLine = 0;

			const int exp_result = 8;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 35) Внешний цикл в блоке {}
		TEST_METHOD(outerInPlainBlock)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"void main(void)",
				"{",
				"int i, j;",
				"{",
				"for (i = 0; i < 3; i++)",
				"{",
				"while (j < 3)",
				"{",
				"j++;",
				"}",
				"}",
				"}",
				"}"
			};

			const int in_strCount = 13;
			const int in_startLine = 0;

			const int exp_result = 6;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 36) Пустое тело внутреннего цикла
		TEST_METHOD(emptyInnerBody)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"void main(void)",
				"{",
				"int i, j;",
				"for (i = 0; i < 3; i++)",
				"{",
				"while (j < 3)",
				"{",
				"}",
				"}",
				"}"
			};

			const int in_strCount = 10;
			const int in_startLine = 0;

			const int exp_result = 5;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 37) Сложные заголовки циклов
		TEST_METHOD(complexLoopHeaders)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"void main(void)",
				"{",
				"int i, j;",
				"while (f(g(i), (j + 1) * 2) > 0)",
				"{",
				"for (i = f(1); i < g(2, 3); i += h(4))",
				"{",
				"j++;",
				"}",
				"}",
				"}"
			};

			const int in_strCount = 11;
			const int in_startLine = 0;

			const int exp_result = 5;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 38) do...while без вложенного цикла
		TEST_METHOD(doWhileNoNested)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"void main(void)",
				"{",
				"int j;",
				"do",
				"{",
				"j++;",
				"}",
				"while (j < 3);",
				"}"
			};

			const int in_strCount = 9;
			const int in_startLine = 0;

			const int exp_result = NO_NESTED_LOOPS;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 39) while после do...while не является вложенным
		TEST_METHOD(whileAfterDoWhileIsNotNested)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"void main(void)",
				"{",
				"int i, j;",
				"do",
				"{",
				"j++;",
				"}",
				"while (j < 3);",
				"while (i < 3)",
				"{",
				"i++;",
				"}",
				"}"
			};

			const int in_strCount = 13;
			const int in_startLine = 0;

			const int exp_result = NO_NESTED_LOOPS;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 40) do...while внутри внешнего цикла
		TEST_METHOD(doWhileInsideOuterLoop)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"void main(void)",
				"{",
				"int i, j;",
				"for (i = 0; i < 3; i++)",
				"{",
				"do",
				"{",
				"j++;",
				"}",
				"while (j < 3);",
				"}",
				"}"
			};

			const int in_strCount = 12;
			const int in_startLine = 0;

			const int exp_result = 5;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 41) Вложенный цикл в теле do...while
		TEST_METHOD(doWhileWithNestedLoopInBody)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"void main(void)",
				"{",
				"int i, j;",
				"do",
				"{",
				"while (j < 3)",
				"{",
				"j++;",
				"}",
				"}",
				"while (i < 3);",
				"}"
			};

			const int in_strCount = 12;
			const int in_startLine = 0;

			const int exp_result = 5;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 42) break/continue/goto/метка, вложенности нет
		TEST_METHOD(controlOperatorsNoNesting)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"int main(void)",
				"{",
				"int i;",
				"start:",
				"for (i = 0; i < 3; i++)",
				"{",
				"if (i == 1)",
				"{",
				"continue;",
				"}",
				"if (i == 2)",
				"{",
				"break;",
				"}",
				"}",
				"goto start;",
				"return 0;",
				"}"
			};

			const int in_strCount = 18;
			const int in_startLine = 0;

			const int exp_result = NO_NESTED_LOOPS;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 43) break/continue/return во вложенных циклах
		TEST_METHOD(controlOperatorsInNestedLoops)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"int main(void)",
				"{",
				"int i, j;",
				"for (i = 0; i < 3; i++)",
				"{",
				"while (j < 3)",
				"{",
				"if (j == 1)",
				"{",
				"break;",
				"}",
				"continue;",
				"}",
				"return 0;",
				"}",
				"}"
			};

			const int in_strCount = 16;
			const int in_startLine = 0;

			const int exp_result = 5;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 44) startLine до внешнего цикла
		TEST_METHOD(startBeforeOuterLoop)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"int main(void)",
				"{",
				"int i, j;",
				"for (i = 0; i < 3; i++)",
				"{",
				"while (j < 3)",
				"{",
				"j++;",
				"}",
				"}",
				"return 0;",
				"}"
			};

			const int in_strCount = 12;
			const int in_startLine = 2;

			const int exp_result = 5;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 45) startLine на внешнем цикле
		TEST_METHOD(startOnOuterLoop)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"int main(void)",
				"{",
				"int i, j;",
				"for (i = 0; i < 3; i++)",
				"{",
				"while (j < 3)",
				"{",
				"j++;",
				"}",
				"}",
				"return 0;",
				"}"
			};

			const int in_strCount = 12;
			const int in_startLine = 3;

			const int exp_result = 5;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 46) startLine на { внешнего цикла
		TEST_METHOD(startOnOuterLoopBrace)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"int main(void)",
				"{",
				"int i, j;",
				"for (i = 0; i < 3; i++)",
				"{",
				"while (j < 3)",
				"{",
				"j++;",
				"}",
				"}",
				"return 0;",
				"}"
			};

			const int in_strCount = 12;
			const int in_startLine = 4;

			const int exp_result = NO_NESTED_LOOPS;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 47) startLine на внутреннем цикле (он становится внешним)
		TEST_METHOD(startOnInnerLoopBecomesOuter)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"int main(void)",
				"{",
				"int i, j;",
				"for (i = 0; i < 3; i++)",
				"{",
				"while (j < 3)",
				"{",
				"j++;",
				"}",
				"}",
				"return 0;",
				"}"
			};

			const int in_strCount = 12;
			const int in_startLine = 5;

			const int exp_result = NO_NESTED_LOOPS;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 48) startLine на последней строке
		TEST_METHOD(startOnLastLine)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"int main(void)",
				"{",
				"int i, j;",
				"for (i = 0; i < 3; i++)",
				"{",
				"while (j < 3)",
				"{",
				"j++;",
				"}",
				"}",
				"return 0;",
				"}"
			};

			const int in_strCount = 12;
			const int in_startLine = 11;

			const int exp_result = NO_NESTED_LOOPS;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 49) startLine на втором уровне при глубине 3
		TEST_METHOD(startOnSecondLevelWithDeeperLoop)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"int main(void)",
				"{",
				"int i, j, k;",
				"for (i = 0; i < 3; i++)",
				"{",
				"while (j < 3)",
				"{",
				"do",
				"{",
				"k++;",
				"}",
				"while (k < 3);",
				"}",
				"}",
				"return 0;",
				"}"
			};

			const int in_strCount = 16;
			const int in_startLine = 5;

			const int exp_result = 7;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 50) startLine на третьем уровне
		TEST_METHOD(startOnThirdLevel)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"int main(void)",
				"{",
				"int i, j, k;",
				"for (i = 0; i < 3; i++)",
				"{",
				"while (j < 3)",
				"{",
				"do",
				"{",
				"k++;",
				"}",
				"while (k < 3);",
				"}",
				"}",
				"return 0;",
				"}"
			};

			const int in_strCount = 16;
			const int in_startLine = 7;

			const int exp_result = NO_NESTED_LOOPS;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 51) startLine внутри тела внешнего цикла до внутреннего
		TEST_METHOD(startInsideOuterBodyBeforeInner)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"void main(void)",
				"{",
				"int i, j;",
				"for (i = 0; i < 3; i++)",
				"{",
				"j = 0;",
				"while (j < 3)",
				"{",
				"j++;",
				"}",
				"i++;",
				"}",
				"}"
			};

			const int in_strCount = 13;
			const int in_startLine = 5;

			const int exp_result = NO_NESTED_LOOPS;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 52) startLine на закрывающей } первой пары
		TEST_METHOD(startOnClosingBraceOfFirstPair)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"void main(void)",
				"{",
				"int i, j;",
				"for (i = 0; i < 3; i++)",
				"{",
				"while (j < 3)",
				"{",
				"j++;",
				"}",
				"}",
				"for (i = 0; i < 3; i++)",
				"{",
				"while (j < 3)",
				"{",
				"j++;",
				"}",
				"}",
				"}"
			};

			const int in_strCount = 18;
			const int in_startLine = 9;

			const int exp_result = 12;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 53) startLine внутри первой пары, лишние }
		TEST_METHOD(startInsideFirstPairWithExtraClosingBraces)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"void main(void)",
				"{",
				"int i, j;",
				"for (i = 0; i < 3; i++)",
				"{",
				"while (j < 3)",
				"{",
				"j++;",
				"}",
				"}",
				"for (i = 0; i < 3; i++)",
				"{",
				"while (j < 3)",
				"{",
				"j++;",
				"}",
				"}",
				"}"
			};

			const int in_strCount = 18;
			const int in_startLine = 6;

			const int exp_result = 12;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 54) startLine на завершающей while (...); у do...while
		TEST_METHOD(startOnDoWhileTail)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"void main(void)",
				"{",
				"int i, j;",
				"do",
				"{",
				"j++;",
				"}",
				"while (j < 3);",
				"while (i < 3)",
				"{",
				"i++;",
				"}",
				"}"
			};

			const int in_strCount = 13;
			const int in_startLine = 7;

			const int exp_result = NO_NESTED_LOOPS;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 55) startLine на else
		TEST_METHOD(startOnElse)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"void main(void)",
				"{",
				"int i, j;",
				"if (i == 0)",
				"{",
				"i++;",
				"}",
				"else",
				"{",
				"while (i < 3)",
				"{",
				"for (j = 0; j < 3; j++)",
				"{",
				"j++;",
				"}",
				"}",
				"}",
				"}"
			};

			const int in_strCount = 18;
			const int in_startLine = 7;

			const int exp_result = 11;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 56) Комментарии со словами for/while/do
		TEST_METHOD(commentsWithLoopKeywords)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"int main(void)",
				"{",
				"int i = 0;",
				"// for (i = 0; i < 3; i++)",
				"    // while (i < 3)",
				"//do",
				"i++;// while (1)",
				"return 0;",
				"}"
			};

			const int in_strCount = 9;
			const int in_startLine = 0;

			const int exp_result = NO_NESTED_LOOPS;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 57) Закомментированный вложенный цикл
		TEST_METHOD(commentedOutInnerLoop)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"void main(void)",
				"{",
				"int i, j;",
				"for (i = 0; i < 3; i++)",
				"{",
				"// while (j < 3)",
				"// {",
				"// j++;",
				"// }",
				"}",
				"}"
			};

			const int in_strCount = 11;
			const int in_startLine = 0;

			const int exp_result = NO_NESTED_LOOPS;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 58) Скобки { и } в комментариях не влияют на структуру
		TEST_METHOD(bracesInCommentsDoNotChangeStructure)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"void main(void)",
				"{",
				"int i, j;",
				"for (i = 0; i < 3; i++)",
				"{ // }",
				"i++; // }",
				"while (j < 3) // {",
				"{",
				"j++;",
				"}",
				"}",
				"}"
			};

			const int in_strCount = 12;
			const int in_startLine = 0;

			const int exp_result = 6;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 59) Скобка { в комментарии не открывает блок
		TEST_METHOD(openBraceInCommentDoesNotOpenBlock)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"void main(void)",
				"{",
				"int i, j;",
				"for (i = 0; i < 3; i++)",
				"{",
				"i++;",
				"}",
				"// {",
				"while (j < 3)",
				"{",
				"j++;",
				"}",
				"}"
			};

			const int in_strCount = 13;
			const int in_startLine = 0;

			const int exp_result = NO_NESTED_LOOPS;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 60) Комментарии в строках с заголовками и скобками
		TEST_METHOD(commentsOnLoopHeadersAndBraces)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"void main(void)",
				"{",
				"int i, j;",
				"for (i = 0; i < 3; i++) // outer loop",
				"{ // begin",
				"while (j < 3) // inner loop",
				"{ // begin inner",
				"j++; // inc",
				"} // end inner",
				"} // end outer",
				"}"
			};

			const int in_strCount = 11;
			const int in_startLine = 0;

			const int exp_result = 5;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 61) Комментарий в строке с do
		TEST_METHOD(commentAfterDo)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"void main(void)",
				"{",
				"int i, j;",
				"for (i = 0; i < 3; i++)",
				"{",
				"do // inner",
				"{",
				"j++;",
				"}",
				"while (j < 3); // end",
				"}",
				"}"
			};

			const int in_strCount = 12;
			const int in_startLine = 0;

			const int exp_result = 5;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 62) Пустые комментарии
		TEST_METHOD(emptyComments)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"void main(void)",
				"{",
				"//",
				"int i, j;",
				"for (i = 0; i < 3; i++)",
				"{",
				"//",
				"while (j < 3)",
				"{",
				"j++;",
				"}",
				"}",
				"}"
			};

			const int in_strCount = 13;
			const int in_startLine = 0;

			const int exp_result = 7;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 63) Идентификаторы с частями ключевых слов
		TEST_METHOD(identifiersWithKeywordParts)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"int main(void)",
				"{",
				"int format, forward, whileFlag, doWork, todo, undo, endfor, for1, _while;",
				"double dbl;",
				"format = 0;",
				"forward = 1;",
				"whileFlag = 2;",
				"doWork = 3;",
				"for1 = 4;",
				"_while = 5;",
				"todo = 6;",
				"undo = 7;",
				"endfor = 8;",
				"return 0;",
				"}"
			};

			const int in_strCount = 15;
			const int in_startLine = 0;

			const int exp_result = NO_NESTED_LOOPS;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 64) Идентификаторы с частями ключевых слов внутри цикла
		TEST_METHOD(identifiersWithKeywordPartsInsideLoop)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"void main(void)",
				"{",
				"int i, whileFlag, doWork, format;",
				"for (i = 0; i < 3; i++)",
				"{",
				"whileFlag = 1;",
				"doWork = 2;",
				"format = 3;",
				"}",
				"}"
			};

			const int in_strCount = 10;
			const int in_startLine = 0;

			const int exp_result = NO_NESTED_LOOPS;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 65) Части ключевых слов в заголовках циклов
		TEST_METHOD(keywordPartsInLoopHeaders)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"void main(void)",
				"{",
				"int i, j, done, forward;",
				"for (i = 0; i < forward; i++)",
				"{",
				"while (done < 3)",
				"{",
				"done++;",
				"}",
				"}",
				"}"
			};

			const int in_strCount = 11;
			const int in_startLine = 0;

			const int exp_result = 5;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 66) Отступы пробелами
		TEST_METHOD(indentWithSpaces)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"int main(void)",
				"{",
				"    int i, j;",
				"    for (i = 0; i < 3; i++)",
				"    {",
				"        while (j < 3)",
				"        {",
				"            j++;",
				"        }",
				"    }",
				"    return 0;",
				"}"
			};

			const int in_strCount = 12;
			const int in_startLine = 0;

			const int exp_result = 5;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 67) Отступы табуляциями
		TEST_METHOD(indentWithTabs)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"int main(void)",
				"{",
				"\tint i, j;",
				"\tfor (i = 0; i < 3; i++)",
				"\t{",
				"\t\twhile (j < 3)",
				"\t\t{",
				"\t\t\tj++;",
				"\t\t}",
				"\t}",
				"\treturn 0;",
				"}"
			};

			const int in_strCount = 12;
			const int in_startLine = 0;

			const int exp_result = 5;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 68) Смешанные отступы
		TEST_METHOD(indentMixedSpacesAndTabs)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"int main(void)",
				"{",
				" \t int i, j;",
				"\t  for (i = 0; i < 3; i++)",
				" {",
				"  \t while (j < 3)",
				"\t {",
				"\t\t  j++;",
				" \t}",
				"  }",
				"\t return 0;",
				"}"
			};

			const int in_strCount = 12;
			const int in_startLine = 0;

			const int exp_result = 5;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 69) Отступы не соответствуют вложенности
		TEST_METHOD(indentDoesNotMatchNesting)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"int main(void)",
				"{",
				"int i, j;",
				"            for (i = 0; i < 3; i++)",
				"            {",
				"while (j < 3)",
				"{",
				"j++;",
				"}",
				"            }",
				"return 0;",
				"}"
			};

			const int in_strCount = 12;
			const int in_startLine = 0;

			const int exp_result = 5;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 70) Максимальная длина строк и максимальный отступ
		TEST_METHOD(maxLengthLinesAndMaxIndent)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"int main(void)",
				"{",
				"int i, j;",
				"for (i = 0; i < 3; i++)                                                                                                        ",
				"{",
				"                                                                                                                  while (j < 3)",
				"{",
				"j++; //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
				"}",
				"}",
				"return 0;",
				"}"
			};

			const int in_strCount = 12;
			const int in_startLine = 0;

			const int exp_result = 5;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 71) Нет пробелов в заголовках
		TEST_METHOD(noSpacesInHeaders)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"int main(void)",
				"{",
				"int i,j;",
				"for(i=0;i<3;i++)",
				"{",
				"while(j<3)",
				"{",
				"j++;",
				"}",
				"}",
				"return 0;",
				"}"
			};

			const int in_strCount = 12;
			const int in_startLine = 0;

			const int exp_result = 5;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 72) Много пробелов в заголовках
		TEST_METHOD(manySpacesInHeaders)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"int main(void)",
				"{",
				"int i, j;",
				"for    (    i = 0 ;  i < 3 ;  i++   )",
				"{",
				"while   (   j < 3   )",
				"{",
				"j++;",
				"}",
				"}",
				"return 0;",
				"}"
			};

			const int in_strCount = 12;
			const int in_startLine = 0;

			const int exp_result = 5;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 73) Табуляции в заголовках
		TEST_METHOD(tabsInHeaders)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"int main(void)",
				"{",
				"int i, j;",
				"for\t(i = 0;\ti < 3;\ti++)",
				"{",
				"while\t(j < 3)",
				"{",
				"j++;",
				"}",
				"}",
				"return 0;",
				"}"
			};

			const int in_strCount = 12;
			const int in_startLine = 0;

			const int exp_result = 5;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 74) Пробелы и табуляции вокруг do и while (...) ;
		TEST_METHOD(trailingSpacesAroundDoAndWhileTail)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"void main(void)",
				"{",
				"int i, j;",
				"for (i = 0; i < 3; i++)",
				"{",
				"do \t",
				"{",
				"j++;",
				"}",
				"while ( j < 3 ) ;",
				"}",
				"}"
			};

			const int in_strCount = 12;
			const int in_startLine = 0;

			const int exp_result = 5;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 75) else if с пробелами и табуляцией
		TEST_METHOD(elseIfWithSpacesAndTabs)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"void main(void)",
				"{",
				"int i, j;",
				"for (i = 0; i < 3; i++)",
				"{",
				"if (i > 1)",
				"{",
				"j++;",
				"}",
				"else   if\t(i > 0)",
				"{",
				"while (j < 3)",
				"{",
				"j++;",
				"}",
				"}",
				"}",
				"}"
			};

			const int in_strCount = 18;
			const int in_startLine = 0;

			const int exp_result = 11;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 76) else с пробелами и табуляцией
		TEST_METHOD(elseWithSpacesAndTabs)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"void main(void)",
				"{",
				"int i, j;",
				"if (i == 0)",
				"{",
				"i++;",
				"}",
				"\telse  \t",
				"{",
				"while (i < 3)",
				"{",
				"for (j = 0; j < 3; j++)",
				"{",
				"j++;",
				"}",
				"}",
				"}",
				"}"
			};

			const int in_strCount = 18;
			const int in_startLine = 0;

			const int exp_result = 11;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 77) Лишние пробелы в объявлениях и заголовке функции
		TEST_METHOD(declarationsWithExtraSpaces)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"int   main  (  void  )",
				"{",
				"int   i  ,  j;",
				"unsigned  long\tint  k=0;",
				"for (i = 0; i < 3; i++)",
				"{",
				"while (j < 3)",
				"{",
				"j++;",
				"}",
				"}",
				"return 0;",
				"}"
			};

			const int in_strCount = 13;
			const int in_startLine = 0;

			const int exp_result = 6;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 78) Пробелы и табуляции в конце каждой строки
		TEST_METHOD(trailingWhitespaceOnEveryLine)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"int main(void)  ",
				"{\t",
				"int i, j;   ",
				"for (i = 0; i < 3; i++) \t",
				"{  ",
				"while (j < 3)\t",
				"{ ",
				"j++; ",
				"}\t",
				"}  ",
				"return 0;  ",
				"} "
			};

			const int in_strCount = 12;
			const int in_startLine = 0;

			const int exp_result = 5;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 79) Окончания строк \n
		TEST_METHOD(lineEndingLF)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"int main(void)\n",
				"{\n",
				"int i, j;\n",
				"for (i = 0; i < 3; i++)\n",
				"{\n",
				"while (j < 3)\n",
				"{\n",
				"j++;\n",
				"}\n",
				"}\n",
				"return 0;\n",
				"}\n"
			};

			const int in_strCount = 12;
			const int in_startLine = 0;

			const int exp_result = 5;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 80) Окончания строк \r\n
		TEST_METHOD(lineEndingCRLF)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"int main(void)\r\n",
				"{\r\n",
				"int i, j;\r\n",
				"for (i = 0; i < 3; i++)\r\n",
				"{\r\n",
				"while (j < 3)\r\n",
				"{\r\n",
				"j++;\r\n",
				"}\r\n",
				"}\r\n",
				"return 0;\r\n",
				"}\r\n"
			};

			const int in_strCount = 12;
			const int in_startLine = 0;

			const int exp_result = 5;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 81) Окончания строк \r
		TEST_METHOD(lineEndingCR)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"int main(void)\r",
				"{\r",
				"int i, j;\r",
				"for (i = 0; i < 3; i++)\r",
				"{\r",
				"while (j < 3)\r",
				"{\r",
				"j++;\r",
				"}\r",
				"}\r",
				"return 0;\r",
				"}\r"
			};

			const int in_strCount = 12;
			const int in_startLine = 0;

			const int exp_result = 5;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 82) Смешанные окончания строк
		TEST_METHOD(lineEndingsMixed)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"int main(void)\n",
				"{\r\n",
				"int i, j;\r",
				"for (i = 0; i < 3; i++)",
				"{\n",
				"while (j < 3)\r\n",
				"{\r",
				"j++;\n",
				"}\r\n",
				"}",
				"return 0;\r\n",
				"}\n"
			};

			const int in_strCount = 12;
			const int in_startLine = 0;

			const int exp_result = 5;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 83) Окончания строк вместе с комментариями
		TEST_METHOD(lineEndingsWithComments)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"void main(void)\r\n",
				"{\r\n",
				"int i, j;\r\n",
				"for (i = 0; i < 3; i++) // outer\r\n",
				"{\r\n",
				"// while (1)\r\n",
				"while (j < 3) // inner  \r\n",
				"{\r\n",
				"j++; //\n",
				"}\r",
				"}\r\n",
				"}\r\n"
			};

			const int in_strCount = 12;
			const int in_startLine = 0;

			const int exp_result = 6;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}

		// 84) Окончания строк \r\n вместе с do...while
		TEST_METHOD(lineEndingCRLFWithDoWhile)
		{
			const char in_text[MAX_STR_COUNT][MAX_STR_LENGTH] =
			{
				"void main(void)\r\n",
				"{\r\n",
				"int i, j;\r\n",
				"for (i = 0; i < 3; i++)\r\n",
				"{\r\n",
				"do\r\n",
				"{\r\n",
				"j++;\r\n",
				"}\r\n",
				"while (j < 3);\r\n",
				"}\r\n",
				"}\r\n"
			};

			const int in_strCount = 12;
			const int in_startLine = 0;

			const int exp_result = 5;

			int result = findFirstNestedLoop(in_text, in_strCount, in_startLine);

			Assert::AreEqual(exp_result, result);
		}
	};
}
