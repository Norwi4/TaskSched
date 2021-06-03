#include "pch.h"
#include "CppUnitTest.h"



using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TaskSchedulerTESTS
{
	TEST_CLASS(TaskSchedulerTESTS)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			valid_date(2002,10,10);
		}

		TEST_METHOD(TestMethod2)
		{
			valid_date(-1, 10, 10);
		}
	};
}
