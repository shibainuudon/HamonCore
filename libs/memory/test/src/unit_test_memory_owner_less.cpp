/**
 *	@file	unit_test_memory_owner_less.cpp
 *
 *	@brief	owner_less のテスト
 */

#include <hamon/memory/owner_less.hpp>
#include <hamon/memory/shared_ptr.hpp>
#include <hamon/memory/weak_ptr.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace owner_less_test
{

struct X
{
	int i;
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
	{
		hamon::shared_ptr<X> sp1(new X{3});
		hamon::shared_ptr<X> sp2(sp1);
		hamon::shared_ptr<X> sp3;
		hamon::shared_ptr<X> sp4(new X{3});
		hamon::shared_ptr<int> sp5(sp1, &(sp1->i));
		hamon::shared_ptr<int> sp6(sp1, nullptr);
		hamon::shared_ptr<int> sp7(sp4, &(sp1->i));
		hamon::shared_ptr<int> sp8;
		hamon::weak_ptr<X> wp1(sp1);
		hamon::weak_ptr<X> wp2(wp1);
		hamon::weak_ptr<X> wp3;
		hamon::weak_ptr<X> wp4(sp4);
		hamon::weak_ptr<int> wp5(sp5);
		hamon::weak_ptr<int> wp6(sp6);
		hamon::weak_ptr<int> wp7(sp7);
		hamon::weak_ptr<int> wp8;

		hamon::owner_less<void> fn1{};
		static_assert(noexcept(fn1(sp1, sp1)), "");
		static_assert(noexcept(fn1(sp1, wp1)), "");
		static_assert(noexcept(fn1(wp1, sp1)), "");
		static_assert(noexcept(fn1(wp1, wp1)), "");
		static_assert(hamon::is_same<decltype(fn1(sp1, sp1)), bool>::value, "");
		static_assert(hamon::is_same<decltype(fn1(sp1, wp1)), bool>::value, "");
		static_assert(hamon::is_same<decltype(fn1(wp1, sp1)), bool>::value, "");
		static_assert(hamon::is_same<decltype(fn1(wp1, wp1)), bool>::value, "");

		VERIFY(!(fn1(sp1, sp1) || fn1(sp1, sp1)));
		VERIFY(!(fn1(sp1, sp2) || fn1(sp2, sp1)));
		VERIFY( (fn1(sp1, sp3) || fn1(sp3, sp1)));
		VERIFY( (fn1(sp1, sp4) || fn1(sp4, sp1)));
		VERIFY(!(fn1(sp1, sp5) || fn1(sp5, sp1)));
		VERIFY(!(fn1(sp1, sp6) || fn1(sp6, sp1)));
		VERIFY( (fn1(sp1, sp7) || fn1(sp7, sp1)));
		VERIFY( (fn1(sp1, sp8) || fn1(sp8, sp1)));

		VERIFY(!(fn1(sp1, wp1) || fn1(sp1, wp1)));
		VERIFY(!(fn1(sp1, wp2) || fn1(sp2, wp1)));
		VERIFY( (fn1(sp1, wp3) || fn1(sp3, wp1)));
		VERIFY( (fn1(sp1, wp4) || fn1(sp4, wp1)));
		VERIFY(!(fn1(sp1, wp5) || fn1(sp5, wp1)));
		VERIFY(!(fn1(sp1, wp6) || fn1(sp6, wp1)));
		VERIFY( (fn1(sp1, wp7) || fn1(sp7, wp1)));
		VERIFY( (fn1(sp1, wp8) || fn1(sp8, wp1)));

		VERIFY(!(fn1(wp1, sp1) || fn1(wp1, sp1)));
		VERIFY(!(fn1(wp1, sp2) || fn1(wp2, sp1)));
		VERIFY( (fn1(wp1, sp3) || fn1(wp3, sp1)));
		VERIFY( (fn1(wp1, sp4) || fn1(wp4, sp1)));
		VERIFY(!(fn1(wp1, sp5) || fn1(wp5, sp1)));
		VERIFY(!(fn1(wp1, sp6) || fn1(wp6, sp1)));
		VERIFY( (fn1(wp1, sp7) || fn1(wp7, sp1)));
		VERIFY( (fn1(wp1, sp8) || fn1(wp8, sp1)));

		VERIFY(!(fn1(wp1, wp1) || fn1(wp1, wp1)));
		VERIFY(!(fn1(wp1, wp2) || fn1(wp2, wp1)));
		VERIFY( (fn1(wp1, wp3) || fn1(wp3, wp1)));
		VERIFY( (fn1(wp1, wp4) || fn1(wp4, wp1)));
		VERIFY(!(fn1(wp1, wp5) || fn1(wp5, wp1)));
		VERIFY(!(fn1(wp1, wp6) || fn1(wp6, wp1)));
		VERIFY( (fn1(wp1, wp7) || fn1(wp7, wp1)));
		VERIFY( (fn1(wp1, wp8) || fn1(wp8, wp1)));

		hamon::owner_less<hamon::shared_ptr<X>> fn2{};
		static_assert(noexcept(fn2(sp1, sp1)), "");
		static_assert(noexcept(fn2(sp1, wp1)), "");
		static_assert(noexcept(fn2(wp1, sp1)), "");
		static_assert(hamon::is_same<decltype(fn2(sp1, sp1)), bool>::value, "");
		static_assert(hamon::is_same<decltype(fn2(sp1, wp1)), bool>::value, "");
		static_assert(hamon::is_same<decltype(fn2(wp1, sp1)), bool>::value, "");

		VERIFY(!(fn2(sp1, sp1) || fn2(sp1, sp1)));
		VERIFY(!(fn2(sp1, sp2) || fn2(sp2, sp1)));
		VERIFY( (fn2(sp1, sp3) || fn2(sp3, sp1)));
		VERIFY( (fn2(sp1, sp4) || fn2(sp4, sp1)));

		VERIFY(!(fn2(sp1, wp1) || fn2(sp1, wp1)));
		VERIFY(!(fn2(sp1, wp2) || fn2(sp2, wp1)));
		VERIFY( (fn2(sp1, wp3) || fn2(sp3, wp1)));
		VERIFY( (fn2(sp1, wp4) || fn2(sp4, wp1)));

		VERIFY(!(fn2(wp1, sp1) || fn2(wp1, sp1)));
		VERIFY(!(fn2(wp1, sp2) || fn2(wp2, sp1)));
		VERIFY( (fn2(wp1, sp3) || fn2(wp3, sp1)));
		VERIFY( (fn2(wp1, sp4) || fn2(wp4, sp1)));

		hamon::owner_less<hamon::weak_ptr<X>> fn3{};
		static_assert(noexcept(fn3(sp1, wp1)), "");
		static_assert(noexcept(fn3(wp1, sp1)), "");
		static_assert(noexcept(fn3(wp1, wp1)), "");
		static_assert(hamon::is_same<decltype(fn3(sp1, wp1)), bool>::value, "");
		static_assert(hamon::is_same<decltype(fn3(wp1, sp1)), bool>::value, "");
		static_assert(hamon::is_same<decltype(fn3(wp1, wp1)), bool>::value, "");

		VERIFY(!(fn3(sp1, wp1) || fn3(sp1, wp1)));
		VERIFY(!(fn3(sp1, wp2) || fn3(sp2, wp1)));
		VERIFY( (fn3(sp1, wp3) || fn3(sp3, wp1)));
		VERIFY( (fn3(sp1, wp4) || fn3(sp4, wp1)));

		VERIFY(!(fn3(wp1, sp1) || fn3(wp1, sp1)));
		VERIFY(!(fn3(wp1, sp2) || fn3(wp2, sp1)));
		VERIFY( (fn3(wp1, sp3) || fn3(wp3, sp1)));
		VERIFY( (fn3(wp1, sp4) || fn3(wp4, sp1)));

		VERIFY(!(fn3(wp1, wp1) || fn3(wp1, wp1)));
		VERIFY(!(fn3(wp1, wp2) || fn3(wp2, wp1)));
		VERIFY( (fn3(wp1, wp3) || fn3(wp3, wp1)));
		VERIFY( (fn3(wp1, wp4) || fn3(wp4, wp1)));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(MemoryTest, OwnerLessTest)
{
	// ポインタの大小比較はconstexprにできない
	EXPECT_TRUE(test());
}

}	// namespace owner_less_test

}	// namespace hamon_memory_test
