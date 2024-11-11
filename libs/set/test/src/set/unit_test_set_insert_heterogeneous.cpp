/**
 *	@file	unit_test_set_insert_heterogeneous.cpp
 *
 *	@brief	insert のテスト
 *
 *	template<class K> pair<iterator, bool> insert(K&& x);
 */

#include <hamon/set/set.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

#if !defined(HAMON_USE_STD_SET) || \
	(defined(__cpp_lib_associative_heterogeneous_insertion) && (__cpp_lib_associative_heterogeneous_insertion >= 202306L))

namespace hamon_set_test
{

namespace insert_heterogeneous_test
{

#if !defined(HAMON_USE_STD_SET)
#define SET_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define SET_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define SET_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define SET_TEST_CONSTEXPR              /**/
#endif

struct HeterogeneousKey
{
	int value;
	HAMON_CXX11_CONSTEXPR operator int() const { return -value; }
};

struct Compare
{
	using is_transparent = void;

	HAMON_CXX11_CONSTEXPR bool
	operator()(int lhs, int rhs) const
	{
		return lhs < rhs;
	}

	HAMON_CXX11_CONSTEXPR bool
	operator()(int lhs, HeterogeneousKey rhs) const
	{
		return lhs < rhs.value;
	}

	HAMON_CXX11_CONSTEXPR bool
	operator()(HeterogeneousKey lhs, int rhs) const
	{
		return lhs.value < rhs;
	}
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

SET_TEST_CONSTEXPR bool test1()
{
	using Set = hamon::set<int, Compare>;
	using Iterator = typename Set::iterator;
#if defined(HAMON_USE_STD_SET)
	using Result = std::pair<Iterator, bool>;
#else
	using Result = hamon::pair<Iterator, bool>;
#endif

	Set v {1, -2};

	static_assert(hamon::is_same<decltype(v.insert(hamon::declval<HeterogeneousKey>())), Result>::value, "");
	static_assert(!noexcept(v.insert(hamon::declval<HeterogeneousKey>())), "");

	v.insert(HeterogeneousKey{2});
	VERIFY(v.size() == 2);
	{
		auto it = v.begin();
		VERIFY(*it++ == -2);
		VERIFY(*it++ ==  1);
		VERIFY(it == v.end());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(SetTest, InsertHeterogeneousTest)
{
	SET_TEST_CONSTEXPR_EXPECT_TRUE(test1());
}

#undef SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef SET_TEST_CONSTEXPR

}	// namespace insert_heterogeneous_test

}	// namespace hamon_set_test

#endif
