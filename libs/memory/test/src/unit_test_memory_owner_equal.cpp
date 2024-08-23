/**
 *	@file	unit_test_memory_owner_equal.cpp
 *
 *	@brief	owner_equal のテスト
 */

#include <hamon/memory/owner_equal.hpp>
#include <hamon/memory/shared_ptr.hpp>
#include <hamon/memory/weak_ptr.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
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
		hamon::shared_ptr<int> sp8;
		hamon::weak_ptr<X> wp1(sp1);
		hamon::weak_ptr<X> wp2(wp1);
		hamon::weak_ptr<X> wp3;
		hamon::weak_ptr<X> wp4(sp4);
		hamon::weak_ptr<int> wp5(sp5);
		hamon::weak_ptr<int> wp6(sp6);
		hamon::weak_ptr<int> wp7(sp7);
		hamon::weak_ptr<int> wp8;

		static_assert(noexcept(hamon::owner_equal{}(sp1, sp1)), "");
		static_assert(noexcept(hamon::owner_equal{}(sp1, wp1)), "");
		static_assert(noexcept(hamon::owner_equal{}(wp1, sp1)), "");
		static_assert(noexcept(hamon::owner_equal{}(wp1, wp1)), "");
		static_assert(hamon::is_same<decltype(hamon::owner_equal{}(sp1, sp1)), bool>::value, "");
		static_assert(hamon::is_same<decltype(hamon::owner_equal{}(sp1, wp1)), bool>::value, "");
		static_assert(hamon::is_same<decltype(hamon::owner_equal{}(wp1, sp1)), bool>::value, "");
		static_assert(hamon::is_same<decltype(hamon::owner_equal{}(wp1, wp1)), bool>::value, "");

		VERIFY( (hamon::owner_equal{}(sp1, sp1)));
		VERIFY( (hamon::owner_equal{}(sp1, sp2)));
		VERIFY(!(hamon::owner_equal{}(sp1, sp3)));
		VERIFY(!(hamon::owner_equal{}(sp1, sp4)));
		VERIFY( (hamon::owner_equal{}(sp1, sp5)));
		VERIFY( (hamon::owner_equal{}(sp1, sp6)));
		VERIFY(!(hamon::owner_equal{}(sp1, sp7)));
		VERIFY(!(hamon::owner_equal{}(sp1, sp8)));

		VERIFY(!(hamon::owner_equal{}(sp3, sp1)));
		VERIFY(!(hamon::owner_equal{}(sp3, sp2)));
		VERIFY( (hamon::owner_equal{}(sp3, sp3)));
		VERIFY(!(hamon::owner_equal{}(sp3, sp4)));
		VERIFY(!(hamon::owner_equal{}(sp3, sp5)));
		VERIFY(!(hamon::owner_equal{}(sp3, sp6)));
		VERIFY(!(hamon::owner_equal{}(sp3, sp7)));
		VERIFY( (hamon::owner_equal{}(sp3, sp8)));

		VERIFY(!(hamon::owner_equal{}(sp4, sp1)));
		VERIFY(!(hamon::owner_equal{}(sp4, sp2)));
		VERIFY(!(hamon::owner_equal{}(sp4, sp3)));
		VERIFY( (hamon::owner_equal{}(sp4, sp4)));
		VERIFY(!(hamon::owner_equal{}(sp4, sp5)));
		VERIFY(!(hamon::owner_equal{}(sp4, sp6)));
		VERIFY( (hamon::owner_equal{}(sp4, sp7)));
		VERIFY(!(hamon::owner_equal{}(sp4, sp8)));

		VERIFY( (hamon::owner_equal{}(sp1, wp1)));
		VERIFY( (hamon::owner_equal{}(sp1, wp2)));
		VERIFY(!(hamon::owner_equal{}(sp1, wp3)));
		VERIFY(!(hamon::owner_equal{}(sp1, wp4)));
		VERIFY( (hamon::owner_equal{}(sp1, wp5)));
		VERIFY( (hamon::owner_equal{}(sp1, wp6)));
		VERIFY(!(hamon::owner_equal{}(sp1, wp7)));
		VERIFY(!(hamon::owner_equal{}(sp1, wp8)));

		VERIFY(!(hamon::owner_equal{}(sp3, wp1)));
		VERIFY(!(hamon::owner_equal{}(sp3, wp2)));
		VERIFY( (hamon::owner_equal{}(sp3, wp3)));
		VERIFY(!(hamon::owner_equal{}(sp3, wp4)));
		VERIFY(!(hamon::owner_equal{}(sp3, wp5)));
		VERIFY(!(hamon::owner_equal{}(sp3, wp6)));
		VERIFY(!(hamon::owner_equal{}(sp3, wp7)));
		VERIFY( (hamon::owner_equal{}(sp3, wp8)));

		VERIFY(!(hamon::owner_equal{}(sp4, wp1)));
		VERIFY(!(hamon::owner_equal{}(sp4, wp2)));
		VERIFY(!(hamon::owner_equal{}(sp4, wp3)));
		VERIFY( (hamon::owner_equal{}(sp4, wp4)));
		VERIFY(!(hamon::owner_equal{}(sp4, wp5)));
		VERIFY(!(hamon::owner_equal{}(sp4, wp6)));
		VERIFY( (hamon::owner_equal{}(sp4, wp7)));
		VERIFY(!(hamon::owner_equal{}(sp4, wp8)));

		VERIFY( (hamon::owner_equal{}(wp1, sp1)));
		VERIFY( (hamon::owner_equal{}(wp1, sp2)));
		VERIFY(!(hamon::owner_equal{}(wp1, sp3)));
		VERIFY(!(hamon::owner_equal{}(wp1, sp4)));
		VERIFY( (hamon::owner_equal{}(wp1, sp5)));
		VERIFY( (hamon::owner_equal{}(wp1, sp6)));
		VERIFY(!(hamon::owner_equal{}(wp1, sp7)));
		VERIFY(!(hamon::owner_equal{}(wp1, sp8)));

		VERIFY(!(hamon::owner_equal{}(wp3, sp1)));
		VERIFY(!(hamon::owner_equal{}(wp3, sp2)));
		VERIFY( (hamon::owner_equal{}(wp3, sp3)));
		VERIFY(!(hamon::owner_equal{}(wp3, sp4)));
		VERIFY(!(hamon::owner_equal{}(wp3, sp5)));
		VERIFY(!(hamon::owner_equal{}(wp3, sp6)));
		VERIFY(!(hamon::owner_equal{}(wp3, sp7)));
		VERIFY( (hamon::owner_equal{}(wp3, sp8)));

		VERIFY(!(hamon::owner_equal{}(wp4, sp1)));
		VERIFY(!(hamon::owner_equal{}(wp4, sp2)));
		VERIFY(!(hamon::owner_equal{}(wp4, sp3)));
		VERIFY( (hamon::owner_equal{}(wp4, sp4)));
		VERIFY(!(hamon::owner_equal{}(wp4, sp5)));
		VERIFY(!(hamon::owner_equal{}(wp4, sp6)));
		VERIFY( (hamon::owner_equal{}(wp4, sp7)));
		VERIFY(!(hamon::owner_equal{}(wp4, sp8)));

		VERIFY( (hamon::owner_equal{}(wp1, wp1)));
		VERIFY( (hamon::owner_equal{}(wp1, wp2)));
		VERIFY(!(hamon::owner_equal{}(wp1, wp3)));
		VERIFY(!(hamon::owner_equal{}(wp1, wp4)));
		VERIFY( (hamon::owner_equal{}(wp1, wp5)));
		VERIFY( (hamon::owner_equal{}(wp1, wp6)));
		VERIFY(!(hamon::owner_equal{}(wp1, wp7)));
		VERIFY(!(hamon::owner_equal{}(wp1, wp8)));

		VERIFY(!(hamon::owner_equal{}(wp3, wp1)));
		VERIFY(!(hamon::owner_equal{}(wp3, wp2)));
		VERIFY( (hamon::owner_equal{}(wp3, wp3)));
		VERIFY(!(hamon::owner_equal{}(wp3, wp4)));
		VERIFY(!(hamon::owner_equal{}(wp3, wp5)));
		VERIFY(!(hamon::owner_equal{}(wp3, wp6)));
		VERIFY(!(hamon::owner_equal{}(wp3, wp7)));
		VERIFY( (hamon::owner_equal{}(wp3, wp8)));

		VERIFY(!(hamon::owner_equal{}(wp4, wp1)));
		VERIFY(!(hamon::owner_equal{}(wp4, wp2)));
		VERIFY(!(hamon::owner_equal{}(wp4, wp3)));
		VERIFY( (hamon::owner_equal{}(wp4, wp4)));
		VERIFY(!(hamon::owner_equal{}(wp4, wp5)));
		VERIFY(!(hamon::owner_equal{}(wp4, wp6)));
		VERIFY( (hamon::owner_equal{}(wp4, wp7)));
		VERIFY(!(hamon::owner_equal{}(wp4, wp8)));
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

GTEST_TEST(MemoryTest, OwnerEqualTest)
{
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(test());
}

#undef MEMORY_TEST_CONSTEXPR_EXPECT_TRUE

}	// namespace owner_equal_test

}	// namespace hamon_memory_test
