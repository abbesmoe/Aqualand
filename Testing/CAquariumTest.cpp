#include "pch.h"
#include "CppUnitTest.h"

#include "Aquarium.h"
#include <FishBeta.h>
#include <regex>
#include <string>
#include <fstream>
#include <streambuf>
#include <AnglerFish.h>
#include <Carp.h>
#include <DecorCastle.h>
#include <Dory.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

const unsigned int RandomSeed = 1238197374;

namespace Testing
{
	TEST_CLASS(CAquariumTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestCAquariumConstruct)
		{
			CAquarium aquarium;
		}

		TEST_METHOD(TestCAquariumHitTest)
		{
			CAquarium aquarium;

			Assert::IsTrue(aquarium.HitTest(100, 200) == nullptr,
				L"Testing empty aquarium");

			shared_ptr<CFishBeta> fish1 = make_shared<CFishBeta>(&aquarium);
			fish1->SetLocation(100, 200);
			aquarium.Add(fish1);

			Assert::IsTrue(aquarium.HitTest(100, 200) == fish1,
				L"Testing fish at 100, 200");

			/// 1. If two images are on top of each other, it finds the image on top.
			shared_ptr<CFishBeta> fish2 = make_shared<CFishBeta>(&aquarium);
			fish2->SetLocation(150, 150);
			aquarium.Add(fish2);
			shared_ptr<CFishBeta> fish3 = make_shared<CFishBeta>(&aquarium);
			fish3->SetLocation(150, 150);
			aquarium.Add(fish3);
			Assert::IsTrue(aquarium.HitTest(150, 150) == fish3,
				L"Testing top fish is returned");
			
			/// 2. It returns nullptr if you test where there is no image.
			Assert::IsTrue(aquarium.HitTest(1000, 1000) == nullptr,
				L"Testing where there is no image");
			
			/// since fish3 was added after fish2 HitTest returns fish3, but when we use
			/// MoveToFront function on fish2 HitTest should return fish2 instead.
			aquarium.MoveToFront(fish2);
			Assert::IsTrue(aquarium.HitTest(150, 150) == fish2,
				L"Testing MoveToFront");

		}

		/**
		* Create a path to a place to put temporary files
		*/
		wstring TempPath()
		{
			// Create a path to temporary files
			wchar_t path_nts[MAX_PATH];
			GetTempPath(MAX_PATH, path_nts);

			// Convert null terminated string to wstring
			return wstring(path_nts);
		}

		/**
		* Read a file into a wstring and return it.
		* \param filename Name of the file to read
		* \return File contents
		*/
		wstring ReadFile(const wstring& filename)
		{
			ifstream t(filename);
			wstring str((istreambuf_iterator<char>(t)),
				istreambuf_iterator<char>());

			return str;
		}

		/**
		* Test to ensure an aquarium .aqua file is empty
		*/
		void TestEmpty(wstring filename)
		{
			Logger::WriteMessage(filename.c_str());

			wstring xml = ReadFile(filename);
			Logger::WriteMessage(xml.c_str());
			Assert::IsTrue(regex_search(xml, wregex(L"<\\?xml.*\\?>")));
			Assert::IsTrue(regex_search(xml, wregex(L"<aqua/>")));
		}

		/**
		 *  Populate an aquarium with three Beta fish
		 */
		void PopulateThreeBetas(CAquarium* aquarium)
		{
			shared_ptr<CFishBeta> fish1 = make_shared<CFishBeta>(aquarium);
			fish1->SetLocation(100, 200);
			aquarium->Add(fish1);

			shared_ptr<CFishBeta> fish2 = make_shared<CFishBeta>(aquarium);
			fish2->SetLocation(400, 400);
			aquarium->Add(fish2);

			shared_ptr<CFishBeta> fish3 = make_shared<CFishBeta>(aquarium);
			fish3->SetLocation(600, 100);
			aquarium->Add(fish3);
		}

		void TestThreeBetas(wstring filename)
		{
			srand(RandomSeed);

			Logger::WriteMessage(filename.c_str());

			wstring xml = ReadFile(filename);
			Logger::WriteMessage(xml.c_str());

			// Ensure three items
			Assert::IsTrue(regex_search(xml, wregex(L"<aqua><item.*<item.*<item.*</aqua>")));

			// Ensure the positions are correct
			Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"100\" y=\"200\" speedx=\"45\\.9318826868496.*\" speedy=\"36\\.7885372478408.*\"")));
			Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"400\" y=\"400\" speedx=\"20\\.0491348002564.*\" speedy=\"1\\.18106631672109.*\"")));
			Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"600\" y=\"100\" speedx=\"44\\.7965941343425.*\" speedy=\"38\\.6364329966124.*\"")));

			// Ensure the types are correct
			Assert::IsTrue(regex_search(xml,
				wregex(L"<aqua><item.* type=\"beta\"/><item.* type=\"beta\"/><item.* type=\"beta\"/></aqua>")));
		}

		void TestThreeBetasCopy(wstring filename)
		{
			srand(RandomSeed);

			Logger::WriteMessage(filename.c_str());

			wstring xml = ReadFile(filename);
			Logger::WriteMessage(xml.c_str());

			// Ensure three items
			Assert::IsTrue(regex_search(xml, wregex(L"<aqua><item.*<item.*<item.*</aqua>")));

			// Ensure the positions are correct
			Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"100\" y=\"200\" speedx=\"17\\.5145725882748.*\" speedy=\"44\\.7981200598163.*\"")));
			Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"400\" y=\"400\" speedx=\"41\\.1420026245918.*\" speedy=\"37\\.3302407910398.*\"")));
			Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"600\" y=\"100\" speedx=\"8\\.7054048280282.*\" speedy=\"42\\.9471724600971.*\"")));

			// Ensure the types are correct
			Assert::IsTrue(regex_search(xml,
				wregex(L"<aqua><item.* type=\"beta\"/><item.* type=\"beta\"/><item.* type=\"beta\"/></aqua>")));
		}

		/**
		 *  Populate an aquarium with all types of items
		 */
		void PopulateAllTypes(CAquarium* aquarium)
		{
			srand(RandomSeed);

			shared_ptr<CFishBeta> fish1 = make_shared<CFishBeta>(aquarium);
			fish1->SetLocation(100, 200);
			aquarium->Add(fish1);

			shared_ptr<CAnglerFish> fish2 = make_shared<CAnglerFish>(aquarium);
			fish2->SetLocation(400, 400);
			aquarium->Add(fish2);

			shared_ptr<CCarp> fish3 = make_shared<CCarp>(aquarium);
			fish3->SetLocation(600, 100);
			aquarium->Add(fish3);

			shared_ptr<CDecorCastle> decor1 = make_shared<CDecorCastle>(aquarium);
			decor1->SetLocation(200, 300);
			aquarium->Add(decor1);

			shared_ptr<CDory> fish4 = make_shared<CDory>(aquarium);
			fish4->SetLocation(500, 200);
			aquarium->Add(fish4);
		}

		void TestAllTypes(wstring filename)
		{
			Logger::WriteMessage(filename.c_str());

			wstring xml = ReadFile(filename);
			Logger::WriteMessage(xml.c_str());

			// Ensure three items
			Assert::IsTrue(regex_search(xml, wregex(L"<aqua><item.*<item.*<item.*<item.*<item.*</aqua>")));

			// Ensure the positions are correct
			Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"100\" y=\"200\" speedx=\"37\\.0754112369152.*\" speedy=\"25\\.4814294869839.*\"")));
			Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"400\" y=\"400\" speedx=\"31\\.2540055543687.*\" speedy=\"44\\.6958830530717.*\"")));
			Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"600\" y=\"100\" speedx=\"5\\.91601306192206.*\" speedy=\"11\\.1438337351604.*\"")));
			Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"200\" y=\"300\"")));
			Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"500\" y=\"200\" speedx=\"23\\.1955931272317.*\" speedy=\"45\\.6205938901944.*\"")));

			// Ensure the types are correct
			Assert::IsTrue(regex_search(xml, wregex(L"<aqua><item.* type=\"beta\"/><item.* type=\"angler\"/><item.* type=\"carp\"/><item.* type=\"castle\"/><item.* type=\"dory\"/></aqua>")));
		}

		void TestAllTypesCopy(wstring filename)
		{
			Logger::WriteMessage(filename.c_str());

			wstring xml = ReadFile(filename);
			Logger::WriteMessage(xml.c_str());

			// Ensure three items
			Assert::IsTrue(regex_search(xml, wregex(L"<aqua><item.*<item.*<item.*<item.*<item.*</aqua>")));

			// Ensure the positions are correct
			Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"100\" y=\"200\" speedx=\"37\\.0754112369152.*\" speedy=\"25\\.4814294869839.*\"")));
			Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"400\" y=\"400\" speedx=\"31\\.2540055543687.*\" speedy=\"44\\.6958830530717.*\"")));
			Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"600\" y=\"100\" speedx=\"5\\.91601306192206.*\" speedy=\"11\\.1438337351604.*\"")));
			Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"200\" y=\"300\"")));
			Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"500\" y=\"200\" speedx=\"23\\.1955931272317.*\" speedy=\"45\\.6205938901944.*\"")));

			// Ensure the types are correct
			Assert::IsTrue(regex_search(xml, wregex(L"<aqua><item.* type=\"beta\"/><item.* type=\"angler\"/><item.* type=\"carp\"/><item.* type=\"castle\"/><item.* type=\"dory\"/></aqua>")));
		}

		TEST_METHOD(TestCAquariumSave)
		{
			// Create a path to temporary files
			wstring path = TempPath();

			// Create an aquarium
			CAquarium aquarium;

			//
			// First test, saving an empty aquarium
			//
			wstring file1 = path + L"test1.aqua";
			aquarium.Save(file1);

			TestEmpty(file1);

			//
			// Now populate the aquarium
			//

			PopulateThreeBetas(&aquarium);

			wstring file2 = path + L"test2.aqua";
			aquarium.Save(file2);

			TestThreeBetas(file2);

			//
			// Test all types
			//
			CAquarium aquarium3;
			PopulateAllTypes(&aquarium3);

			wstring file3 = path + L"test3.aqua";
			aquarium3.Save(file3);

			TestAllTypes(file3);

			//
			// Test clear function
			//
			CAquarium aquarium4;
			PopulateAllTypes(&aquarium4);

			aquarium4.Clear();

			wstring file4 = path + L"test4.aqua";
			aquarium4.Save(file4);

			TestEmpty(file4);
		}

		TEST_METHOD(TestCAquariumLoad)
		{
			// Create a path to temporary files
			wstring path = TempPath();

			// Create two aquariums
			CAquarium aquarium, aquarium2;

			//
			// First test, saving an empty aquarium
			//
			wstring file1 = path + L"test1.aqua";

			aquarium.Save(file1);
			TestEmpty(file1);

			aquarium2.Load(file1);
			aquarium2.Save(file1);
			TestEmpty(file1);

			//
			// Now populate the aquarium
			//

			PopulateThreeBetas(&aquarium);

			wstring file2 = path + L"test2.aqua";
			aquarium.Save(file2);
			TestThreeBetasCopy(file2);

			aquarium2.Load(file2);
			aquarium2.Save(file2);
			TestThreeBetasCopy(file2);

			//
			// Test all types
			//
			CAquarium aquarium3;
			PopulateAllTypes(&aquarium3);

			wstring file3 = path + L"test3.aqua";
			aquarium3.Save(file3);
			TestAllTypesCopy(file3);

			aquarium2.Load(file3);
			aquarium2.Save(file3);
			TestAllTypesCopy(file3);
		}
	};
}