#include "pch.h"
#include "CppUnitTest.h"

#include "FishBeta.h"
#include "Item.h"
#include "Aquarium.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(CFishBetaTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestCFishBetaConstruct)
		{
			CAquarium aquarium;
			CFishBeta fishbeta(&aquarium);
		}
	};

}