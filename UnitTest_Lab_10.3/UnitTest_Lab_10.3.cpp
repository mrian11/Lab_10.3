#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_10.3/LAB.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLab103
{
	TEST_CLASS(UnitTestLab103)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
		
			Tramvai* p = new Tramvai[2];
			p[0].punkt = "Львів";
			p[0].tup = Train::P_COMF;
			p[0].chas = 5,44;
			p[1].punkt = "Київ";
			p[1].tup = Train::Z_V;
			p[1].chas = 4,55;

			int N = 2;

			Add(p, N, "test.bin");

			Assert::AreEqual(N, 3);

			Assert::IsTrue(p[N - 1].punkt == "Одеса");
			Assert::AreEqual(p[N].tup, Train::SPEED_E);
			Assert::AreEqual(p[N].chas, 7.55);
			Assert::AreEqual(N, 3);

			delete[] p;
		}
	};
}
