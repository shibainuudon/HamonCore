/**
 *	@file	unit_test_memory_weak_ptr_owner_before.cpp
 *
 *	@brief	owner_beforeのテスト
 *
 *	template<class U>
 *	bool owner_before(const shared_ptr<U>& b) const noexcept;
 *
 *	template<class U>
 *	bool owner_before(const weak_ptr<U>& b) const noexcept;
 */

#include <hamon/memory/weak_ptr.hpp>
#include <hamon/memory/shared_ptr.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace weak_ptr_test
{

namespace owner_before_test
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
		hamon::weak_ptr<X> wp1(sp1);
		hamon::weak_ptr<X> wp2(wp1);
		hamon::weak_ptr<X> wp3;
		hamon::weak_ptr<X> wp4(sp4);
		hamon::weak_ptr<int> wp5(sp5);
		hamon::weak_ptr<int> wp6(sp6);
		hamon::weak_ptr<int> wp7(sp7);

		static_assert(noexcept(wp1.owner_before(sp1)), "");
		static_assert(noexcept(wp1.owner_before(wp1)), "");
		static_assert(hamon::is_same<decltype(wp1.owner_before(sp1)), bool>::value, "");
		static_assert(hamon::is_same<decltype(wp1.owner_before(wp1)), bool>::value, "");

		VERIFY(!(wp1.owner_before(sp1) || wp1.owner_before(sp1)));
		VERIFY(!(wp1.owner_before(sp2) || wp2.owner_before(sp1)));
		VERIFY( (wp1.owner_before(sp3) || wp3.owner_before(sp1)));
		VERIFY( (wp1.owner_before(sp4) || wp4.owner_before(sp1)));
		VERIFY(!(wp1.owner_before(sp5) || wp5.owner_before(sp1)));
		VERIFY(!(wp1.owner_before(sp6) || wp6.owner_before(sp1)));
		VERIFY( (wp1.owner_before(sp7) || wp7.owner_before(sp1)));
		VERIFY(!(wp1.owner_before(wp1) || wp1.owner_before(wp1)));
		VERIFY(!(wp1.owner_before(wp2) || wp2.owner_before(wp1)));
		VERIFY( (wp1.owner_before(wp3) || wp3.owner_before(wp1)));
		VERIFY( (wp1.owner_before(wp4) || wp4.owner_before(wp1)));
		VERIFY(!(wp1.owner_before(wp5) || wp5.owner_before(wp1)));
		VERIFY(!(wp1.owner_before(wp6) || wp6.owner_before(wp1)));
		VERIFY( (wp1.owner_before(wp7) || wp7.owner_before(wp1)));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(WeakPtrTest, OwnerBeforeTest)
{
	// ポインタの大小比較はconstexprにできない
	EXPECT_TRUE(test());
}

}	// namespace owner_before_test

}	// namespace weak_ptr_test

}	// namespace hamon_memory_test
