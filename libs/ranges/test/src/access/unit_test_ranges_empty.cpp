/**
 *	@file	unit_test_ranges_empty.cpp
 *
 *	@brief	ranges::empty のテスト
 */

#include <hamon/ranges/empty.hpp>
#include <hamon/concepts/same_as.hpp>
#include <gtest/gtest.h>
#include <utility>
#include <vector>
#include <list>
#include <forward_list>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{

namespace empty_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct R
{
	constexpr int empty() const & { return 0; }
	constexpr const void* empty() const && { return this; }
};

HAMON_CXX14_CONSTEXPR bool test01()
{
	constexpr R r;
	static_assert(!hamon::ranges::empty(r), "");
	static_assert(hamon::same_as_t<decltype(hamon::ranges::empty(r)), bool>::value, "");

	static_assert(!hamon::ranges::empty(std::move(r)), "");
	static_assert(hamon::same_as_t<decltype(hamon::ranges::empty(std::move(r))), bool>::value, "");

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	int a[] ={ 0, 1 };
	VERIFY(!hamon::ranges::empty(a));

	test_random_access_range<int> r(a);
	VERIFY(!hamon::ranges::empty(r));

	test_forward_range<int> i(a);
	VERIFY(!hamon::ranges::empty(i));

	test_random_access_sized_range<int> sr(a);
	VERIFY(!hamon::ranges::empty(sr));

	test_input_sized_range<int> si(a);
	VERIFY(!hamon::ranges::empty(si));

	test_output_sized_range<int> so(a);
	VERIFY(!hamon::ranges::empty(so));

	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	struct R1
	{
		HAMON_CXX14_CONSTEXPR bool empty() & { return true; }
	};

	struct R2
	{
		HAMON_CXX14_CONSTEXPR unsigned size() & { return 0; }
	};

	VERIFY(hamon::ranges::empty(R1{}));
	VERIFY(hamon::ranges::empty(R2{}));

	return true;
}

HAMON_CXX14_CONSTEXPR bool test04()
{
	struct E1
	{
		bool empty() const noexcept { return {}; }
	};

	struct E2
	{
		bool empty() const noexcept(false) { return {}; }
	};

	struct E3
	{
		struct B
		{
			explicit operator bool() const noexcept(false) { return true; }
		};

		B empty() const noexcept { return {}; }
	};

	static_assert( noexcept(hamon::ranges::empty(E1{})), "");
	static_assert(!noexcept(hamon::ranges::empty(E2{})), "");
	static_assert(!noexcept(hamon::ranges::empty(E3{})), "");

	return true;
}

GTEST_TEST(RangesTest, EmptyTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
}

#undef VERIFY

}	// namespace empty_test

}	// namespace hamon_ranges_test
