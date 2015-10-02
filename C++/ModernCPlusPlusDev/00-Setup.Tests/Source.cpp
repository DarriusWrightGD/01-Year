#include <gtest\gtest.h>
#include "Tests.h"

int main(int argc, char ** argv)
{
	testing::InitGoogleTest(&argc, argv);
	int testResult = RUN_ALL_TESTS();
	system("pause");
	return testResult;
}