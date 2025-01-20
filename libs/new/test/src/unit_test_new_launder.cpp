/**
 *	@file	unit_test_new_launder.cpp
 *
 *	@brief	launder のテスト
 */

#include <hamon/new/launder.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

#if defined(HAMON_HAS_LAUNDER)
namespace hamon_new_test
{

namespace launder_test
{

constexpr int gi = 5;
constexpr float gf = 8.f;

GTEST_TEST(NewTest, LaunderTest)
{
	{
		static_assert(hamon::launder(&gi) == &gi, "");
		static_assert(hamon::launder(&gf) == &gf, "");

		const int *i = &gi;
		const float *f = &gf;
		static_assert(hamon::is_same<decltype(i), decltype(hamon::launder(i))>::value, "");
		static_assert(hamon::is_same<decltype(f), decltype(hamon::launder(f))>::value, "");

		EXPECT_TRUE(hamon::launder(i) == i);
		EXPECT_TRUE(hamon::launder(f) == f);
	}
	{
		struct X { int n; };
		const X *p = new const X {3};
		const int a = p->n;
		EXPECT_TRUE(a == 3);
		new (const_cast<X*>(p)) const X {5}; // p does not point to new object ([basic.life]) because its type is const
//		const int b = p->n;                  // undefined behavior
		const int c = hamon::launder(p)->n;  // OK
		EXPECT_TRUE(c == 5);
	}
	{
		struct X { const int n; };
		union U { X x; float f; };
		U u = {{ 1 }};
		u.f = 5.f;                                 // OK, u の新しいサブオブジェクトを生成
		X *p = new (&u.x) X {2};                   // OK, u の新しいサブオブジェクトを生成
		EXPECT_TRUE(p->n == 2);                    // OK
		EXPECT_TRUE(*hamon::launder(&u.x.n) == 2); // OK
//		EXPECT_TRUE(u.x.n == 2);                   // 未定義動作, u.xは 新しいサブオブジェクトを指定しない
	}
}

}	// namespace launder_test

}	// namespace hamon_new_test
#endif
