/**
 *	@file	unit_test_ranges_subrange_size.cpp
 *
 *	@brief	ranges::subrange::sizeのテスト
 */

#include <hamon/ranges/utility/subrange.hpp>
#include <hamon/ranges/utility/subrange_kind.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace subrange_test
{
namespace size_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename S>
struct HasSizeImpl
{
private:
	template <typename S2,
		typename = decltype(hamon::declval<const S2&>().size())
	>
	static auto test(int) -> hamon::true_type;

	template <typename S2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<S>(0));
};

template <typename S>
using HasSize = typename HasSizeImpl<S>::type;

static_assert( HasSize<hamon::ranges::subrange<int*>>::value, "");
static_assert( HasSize<hamon::ranges::subrange<int*, int*, hamon::ranges::subrange_kind::sized>>::value, "");
static_assert(!HasSize<hamon::ranges::subrange<forward_iterator_wrapper<int>>>::value, "");
static_assert( HasSize<hamon::ranges::subrange<forward_iterator_wrapper<int>, forward_iterator_wrapper<int>, hamon::ranges::subrange_kind::sized>>::value, "");
static_assert(!HasSize<hamon::ranges::subrange<bidirectional_iterator_wrapper<int>>>::value, "");
static_assert( HasSize<hamon::ranges::subrange<bidirectional_iterator_wrapper<int>, bidirectional_iterator_wrapper<int>, hamon::ranges::subrange_kind::sized>>::value, "");
static_assert( HasSize<hamon::ranges::subrange<random_access_iterator_wrapper<int>>>::value, "");
static_assert( HasSize<hamon::ranges::subrange<random_access_iterator_wrapper<int>>>::value, "");
static_assert( HasSize<hamon::ranges::subrange<contiguous_iterator_wrapper<int>>>::value, "");

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	{
		int x[] = {1, 2, 3, 4, 5};
		hamon::ranges::subrange<int*> sr(x, x+5);
		VERIFY(sr.size() == 5);
	}
	{
		int x[] = {1, 2, 3, 4, 5};
		hamon::ranges::subrange<int*> sr(x, x);
		VERIFY(sr.size() == 0);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test02()
{
	{
		int x[] = {1, 2, 3, 4, 5};
		hamon::ranges::subrange<int*> sr(x, x+5, 5);
		VERIFY(sr.size() == 5);
	}
	{
		int x[] = {1, 2, 3, 4, 5};
		hamon::ranges::subrange<int*> sr(x, x, 0);
		VERIFY(sr.size() == 0);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test03()
{
	{
		int x[] = {1, 2, 3, 4, 5};
		using Iter = random_access_iterator_wrapper<int>;
		hamon::ranges::subrange<Iter, Iter, hamon::ranges::subrange_kind::sized> sr(Iter{x}, Iter{x+5});
		VERIFY(sr.size() == 5);
	}
	{
		int x[] = {1, 2, 3, 4, 5};
		using Iter = random_access_iterator_wrapper<int>;
		hamon::ranges::subrange<Iter, Iter, hamon::ranges::subrange_kind::sized> sr(Iter{x}, Iter{x});
		VERIFY(sr.size() == 0);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test04()
{
	{
		int x[] = {1, 2, 3, 4, 5};
		using Iter = forward_iterator_wrapper<int>;
		hamon::ranges::subrange<Iter, Iter, hamon::ranges::subrange_kind::sized> sr(Iter{x}, Iter{x+5}, 5);
		VERIFY(sr.size() == 5);
	}
	{
		int x[] = {1, 2, 3, 4, 5};
		using Iter = forward_iterator_wrapper<int>;
		hamon::ranges::subrange<Iter, Iter, hamon::ranges::subrange_kind::sized> sr(Iter{x}, Iter{x}, 0);
		VERIFY(sr.size() == 0);
	}
	return true;
}

GTEST_TEST(RangesTest, SubrangeSizeTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
}

#undef VERIFY

}	// namespace size_test
}	// namespace subrange_test
}	// namespace hamon_ranges_test
