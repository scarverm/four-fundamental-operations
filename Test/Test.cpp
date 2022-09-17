#include "pch.h"
#include "CppUnitTest.h"
#include "../Four-Fundamental-Operations/question.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test
{
	TEST_CLASS(Test)
	{
	public:
		
		TEST_METHOD(RemoveBracketTest)
		{
			Question* ques = new Question();
			string expression = "(2/3)¡Â(3/14)*11/12";
			ques->RemoveExcessBracket(expression);
			Assert::AreEqual(expression, (string)"2/3¡Â(3/14)*11/12");
			expression = "(2+3)-(5*6)/(2+3)";
			ques->RemoveExcessBracket(expression);
			Assert::AreEqual(expression, (string)"2+3-5*6/(2+3)");
		}
	};
}
