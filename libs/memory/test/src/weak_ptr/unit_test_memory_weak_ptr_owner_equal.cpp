/**
 *	@file	unit_test_memory_weak_ptr_owner_equal.cpp
 *
 *	@brief	owner_equalのテスト
 *
 *	template<class U>
 *	bool owner_equal(const shared_ptr<U>& b) const noexcept;
 *
 *	template<class U>
 *	bool owner_equal(const weak_ptr<U>& b) const noexcept;
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

namespace owner_equal_test
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

		static_assert(noexcept(wp1.owner_equal(sp1)), "");
		static_assert(noexcept(wp1.owner_equal(wp1)), "");
		static_assert(hamon::is_same<decltype(wp1.owner_equal(sp1)), bool>::value, "");
		static_assert(hamon::is_same<decltype(wp1.owner_equal(wp1)), bool>::value, "");

		VERIFY( (wp1.owner_equal(sp1)));
		VERIFY( (wp1.owner_equal(sp2)));
		VERIFY(!(wp1.owner_equal(sp3)));
		VERIFY(!(wp1.owner_equal(sp4)));
		VERIFY( (wp1.owner_equal(sp5)));
		VERIFY( (wp1.owner_equal(sp6)));
		VERIFY(!(wp1.owner_equal(sp7)));
		VERIFY( (wp1.owner_equal(wp1)));
		VERIFY( (wp1.owner_equal(wp2)));
		VERIFY(!(wp1.owner_equal(wp3)));
		VERIFY(!(wp1.owner_equal(wp4)));
		VERIFY( (wp1.owner_equal(wp5)));
		VERIFY( (wp1.owner_equal(wp6)));
		VERIFY(!(wp1.owner_equal(wp7)));
	}
	return true;
}

#undef VERIFY

#if defined(HAMON_HAS_CXX20_CONSTEXPR_DYNAMIC_ALLOC) && \
	!(defined(HAMON_GCC_VERSION) && (HAMON_GCC_VERSION < 130000))
#define MEMORY_TEST_CONSTEXPR_EXPECT_TRUE	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#else
#define MEMORY_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#endif

GTEST_TEST(WeakPtrTest, OwnerEqualTest)
{
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(test());
}

#undef MEMORY_TEST_CONSTEXPR_EXPECT_TRUE

}	// namespace owner_equal_test

}	// namespace weak_ptr_test

}	// namespace hamon_memory_test
