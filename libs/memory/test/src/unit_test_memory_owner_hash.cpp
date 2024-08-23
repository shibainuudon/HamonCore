/**
 *	@file	unit_test_memory_owner_hash.cpp
 *
 *	@brief	owner_hash のテスト
 */

#include <hamon/memory/owner_hash.hpp>
#include <hamon/memory/shared_ptr.hpp>
#include <hamon/memory/weak_ptr.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace owner_hash_test
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

		static_assert(noexcept(hamon::owner_hash{}(sp1)), "");
		static_assert(noexcept(hamon::owner_hash{}(wp1)), "");
		static_assert(hamon::is_same<decltype(hamon::owner_hash{}(sp1)), hamon::size_t>::value, "");
		static_assert(hamon::is_same<decltype(hamon::owner_hash{}(wp1)), hamon::size_t>::value, "");

		VERIFY( (hamon::owner_hash{}(sp1) == hamon::owner_hash{}(sp1)));
		VERIFY( (hamon::owner_hash{}(sp1) == hamon::owner_hash{}(sp2)));
		VERIFY(!(hamon::owner_hash{}(sp1) == hamon::owner_hash{}(sp3)));
		VERIFY(!(hamon::owner_hash{}(sp1) == hamon::owner_hash{}(sp4)));
		VERIFY( (hamon::owner_hash{}(sp1) == hamon::owner_hash{}(sp5)));
		VERIFY( (hamon::owner_hash{}(sp1) == hamon::owner_hash{}(sp6)));
		VERIFY(!(hamon::owner_hash{}(sp1) == hamon::owner_hash{}(sp7)));
		VERIFY(!(hamon::owner_hash{}(sp1) == hamon::owner_hash{}(sp8)));

		VERIFY(!(hamon::owner_hash{}(sp3) == hamon::owner_hash{}(sp1)));
		VERIFY(!(hamon::owner_hash{}(sp3) == hamon::owner_hash{}(sp2)));
		VERIFY( (hamon::owner_hash{}(sp3) == hamon::owner_hash{}(sp3)));
		VERIFY(!(hamon::owner_hash{}(sp3) == hamon::owner_hash{}(sp4)));
		VERIFY(!(hamon::owner_hash{}(sp3) == hamon::owner_hash{}(sp5)));
		VERIFY(!(hamon::owner_hash{}(sp3) == hamon::owner_hash{}(sp6)));
		VERIFY(!(hamon::owner_hash{}(sp3) == hamon::owner_hash{}(sp7)));
		VERIFY( (hamon::owner_hash{}(sp3) == hamon::owner_hash{}(sp8)));

		VERIFY(!(hamon::owner_hash{}(sp4) == hamon::owner_hash{}(sp1)));
		VERIFY(!(hamon::owner_hash{}(sp4) == hamon::owner_hash{}(sp2)));
		VERIFY(!(hamon::owner_hash{}(sp4) == hamon::owner_hash{}(sp3)));
		VERIFY( (hamon::owner_hash{}(sp4) == hamon::owner_hash{}(sp4)));
		VERIFY(!(hamon::owner_hash{}(sp4) == hamon::owner_hash{}(sp5)));
		VERIFY(!(hamon::owner_hash{}(sp4) == hamon::owner_hash{}(sp6)));
		VERIFY( (hamon::owner_hash{}(sp4) == hamon::owner_hash{}(sp7)));
		VERIFY(!(hamon::owner_hash{}(sp4) == hamon::owner_hash{}(sp8)));

		VERIFY( (hamon::owner_hash{}(sp1) == hamon::owner_hash{}(wp1)));
		VERIFY( (hamon::owner_hash{}(sp1) == hamon::owner_hash{}(wp2)));
		VERIFY(!(hamon::owner_hash{}(sp1) == hamon::owner_hash{}(wp3)));
		VERIFY(!(hamon::owner_hash{}(sp1) == hamon::owner_hash{}(wp4)));
		VERIFY( (hamon::owner_hash{}(sp1) == hamon::owner_hash{}(wp5)));
		VERIFY( (hamon::owner_hash{}(sp1) == hamon::owner_hash{}(wp6)));
		VERIFY(!(hamon::owner_hash{}(sp1) == hamon::owner_hash{}(wp7)));
		VERIFY(!(hamon::owner_hash{}(sp1) == hamon::owner_hash{}(wp8)));

		VERIFY(!(hamon::owner_hash{}(sp3) == hamon::owner_hash{}(wp1)));
		VERIFY(!(hamon::owner_hash{}(sp3) == hamon::owner_hash{}(wp2)));
		VERIFY( (hamon::owner_hash{}(sp3) == hamon::owner_hash{}(wp3)));
		VERIFY(!(hamon::owner_hash{}(sp3) == hamon::owner_hash{}(wp4)));
		VERIFY(!(hamon::owner_hash{}(sp3) == hamon::owner_hash{}(wp5)));
		VERIFY(!(hamon::owner_hash{}(sp3) == hamon::owner_hash{}(wp6)));
		VERIFY(!(hamon::owner_hash{}(sp3) == hamon::owner_hash{}(wp7)));
		VERIFY( (hamon::owner_hash{}(sp3) == hamon::owner_hash{}(wp8)));

		VERIFY(!(hamon::owner_hash{}(sp4) == hamon::owner_hash{}(wp1)));
		VERIFY(!(hamon::owner_hash{}(sp4) == hamon::owner_hash{}(wp2)));
		VERIFY(!(hamon::owner_hash{}(sp4) == hamon::owner_hash{}(wp3)));
		VERIFY( (hamon::owner_hash{}(sp4) == hamon::owner_hash{}(wp4)));
		VERIFY(!(hamon::owner_hash{}(sp4) == hamon::owner_hash{}(wp5)));
		VERIFY(!(hamon::owner_hash{}(sp4) == hamon::owner_hash{}(wp6)));
		VERIFY( (hamon::owner_hash{}(sp4) == hamon::owner_hash{}(wp7)));
		VERIFY(!(hamon::owner_hash{}(sp4) == hamon::owner_hash{}(wp8)));

		VERIFY( (hamon::owner_hash{}(wp1) == hamon::owner_hash{}(sp1)));
		VERIFY( (hamon::owner_hash{}(wp1) == hamon::owner_hash{}(sp2)));
		VERIFY(!(hamon::owner_hash{}(wp1) == hamon::owner_hash{}(sp3)));
		VERIFY(!(hamon::owner_hash{}(wp1) == hamon::owner_hash{}(sp4)));
		VERIFY( (hamon::owner_hash{}(wp1) == hamon::owner_hash{}(sp5)));
		VERIFY( (hamon::owner_hash{}(wp1) == hamon::owner_hash{}(sp6)));
		VERIFY(!(hamon::owner_hash{}(wp1) == hamon::owner_hash{}(sp7)));
		VERIFY(!(hamon::owner_hash{}(wp1) == hamon::owner_hash{}(sp8)));

		VERIFY(!(hamon::owner_hash{}(wp3) == hamon::owner_hash{}(sp1)));
		VERIFY(!(hamon::owner_hash{}(wp3) == hamon::owner_hash{}(sp2)));
		VERIFY( (hamon::owner_hash{}(wp3) == hamon::owner_hash{}(sp3)));
		VERIFY(!(hamon::owner_hash{}(wp3) == hamon::owner_hash{}(sp4)));
		VERIFY(!(hamon::owner_hash{}(wp3) == hamon::owner_hash{}(sp5)));
		VERIFY(!(hamon::owner_hash{}(wp3) == hamon::owner_hash{}(sp6)));
		VERIFY(!(hamon::owner_hash{}(wp3) == hamon::owner_hash{}(sp7)));
		VERIFY( (hamon::owner_hash{}(wp3) == hamon::owner_hash{}(sp8)));

		VERIFY(!(hamon::owner_hash{}(wp4) == hamon::owner_hash{}(sp1)));
		VERIFY(!(hamon::owner_hash{}(wp4) == hamon::owner_hash{}(sp2)));
		VERIFY(!(hamon::owner_hash{}(wp4) == hamon::owner_hash{}(sp3)));
		VERIFY( (hamon::owner_hash{}(wp4) == hamon::owner_hash{}(sp4)));
		VERIFY(!(hamon::owner_hash{}(wp4) == hamon::owner_hash{}(sp5)));
		VERIFY(!(hamon::owner_hash{}(wp4) == hamon::owner_hash{}(sp6)));
		VERIFY( (hamon::owner_hash{}(wp4) == hamon::owner_hash{}(sp7)));
		VERIFY(!(hamon::owner_hash{}(wp4) == hamon::owner_hash{}(sp8)));

		VERIFY( (hamon::owner_hash{}(wp1) == hamon::owner_hash{}(wp1)));
		VERIFY( (hamon::owner_hash{}(wp1) == hamon::owner_hash{}(wp2)));
		VERIFY(!(hamon::owner_hash{}(wp1) == hamon::owner_hash{}(wp3)));
		VERIFY(!(hamon::owner_hash{}(wp1) == hamon::owner_hash{}(wp4)));
		VERIFY( (hamon::owner_hash{}(wp1) == hamon::owner_hash{}(wp5)));
		VERIFY( (hamon::owner_hash{}(wp1) == hamon::owner_hash{}(wp6)));
		VERIFY(!(hamon::owner_hash{}(wp1) == hamon::owner_hash{}(wp7)));
		VERIFY(!(hamon::owner_hash{}(wp1) == hamon::owner_hash{}(wp8)));

		VERIFY(!(hamon::owner_hash{}(wp3) == hamon::owner_hash{}(wp1)));
		VERIFY(!(hamon::owner_hash{}(wp3) == hamon::owner_hash{}(wp2)));
		VERIFY( (hamon::owner_hash{}(wp3) == hamon::owner_hash{}(wp3)));
		VERIFY(!(hamon::owner_hash{}(wp3) == hamon::owner_hash{}(wp4)));
		VERIFY(!(hamon::owner_hash{}(wp3) == hamon::owner_hash{}(wp5)));
		VERIFY(!(hamon::owner_hash{}(wp3) == hamon::owner_hash{}(wp6)));
		VERIFY(!(hamon::owner_hash{}(wp3) == hamon::owner_hash{}(wp7)));
		VERIFY( (hamon::owner_hash{}(wp3) == hamon::owner_hash{}(wp8)));

		VERIFY(!(hamon::owner_hash{}(wp4) == hamon::owner_hash{}(wp1)));
		VERIFY(!(hamon::owner_hash{}(wp4) == hamon::owner_hash{}(wp2)));
		VERIFY(!(hamon::owner_hash{}(wp4) == hamon::owner_hash{}(wp3)));
		VERIFY( (hamon::owner_hash{}(wp4) == hamon::owner_hash{}(wp4)));
		VERIFY(!(hamon::owner_hash{}(wp4) == hamon::owner_hash{}(wp5)));
		VERIFY(!(hamon::owner_hash{}(wp4) == hamon::owner_hash{}(wp6)));
		VERIFY( (hamon::owner_hash{}(wp4) == hamon::owner_hash{}(wp7)));
		VERIFY(!(hamon::owner_hash{}(wp4) == hamon::owner_hash{}(wp8)));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(MemoryTest, OwnerHashTest)
{
	// std::hash が constexpr に対応していない TODO
	/*HAMON_CXX20_CONSTEXPR_*/EXPECT_TRUE(test());
}

}	// namespace owner_hash_test

}	// namespace hamon_memory_test
