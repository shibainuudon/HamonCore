/**
 *	@file	unit_test_span_assign.cpp
 *
 *	@brief	span& operator=(const span& other) のテスト
 */

#include <hamon/span.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/iterator/size.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/string.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "noexcept_test.hpp"

namespace hamon_span_test
{

namespace assign_test
{

template <typename T>
HAMON_CXX14_CONSTEXPR bool do_assign(T lhs, T rhs)
{
	HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<T&>() = rhs);
	lhs = rhs;
	return
		lhs.data() == rhs.data() &&
		lhs.size() == rhs.size();
}

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool
test1()
{
	int carr1[] ={1, 2, 3, 4};
	int carr2[] ={3, 4, 5};
	int carr3[] ={7, 8};

	// dynamically sized assignment
	{
		hamon::span<const int> spans[] =
		{
			{},
			{carr1, static_cast<hamon::size_t>(0)},
			{carr1, 1U},
			{carr1, 2U},
			{carr1, 3U},
			{carr1, 4U},
			{carr2, static_cast<hamon::size_t>(0)},
			{carr2, 1U},
			{carr2, 2U},
			{carr2, 3U},
			{carr3, static_cast<hamon::size_t>(0)},
			{carr3, 1U},
			{carr3, 2U},
		};

		for (hamon::size_t i = 0; i < hamon::size(spans); ++i)
		{
			for (hamon::size_t j = i; j < hamon::size(spans); ++j)
			{
				VERIFY(do_assign(spans[i], spans[j]));
			}
		}
	}

	// statically sized assignment
	{
		using spanType = hamon::span<const int, 2>;
		spanType spans[] =
		{
			spanType{carr1, 2},
			spanType{carr1 + 1, 2},
			spanType{carr1 + 2, 2},
			spanType{carr2, 2},
			spanType{carr2 + 1, 2},
			spanType{carr3, 2},
		};

		for (hamon::size_t i = 0; i < hamon::size(spans); ++i)
		{
			for (hamon::size_t j = i; j < hamon::size(spans); ++j)
			{
				VERIFY(do_assign(spans[i], spans[j]));
			}
		}
	}

	return true;
}

inline bool test2()
{
	hamon::string strs[] = {"ABC", "DEF", "GHI"};

	//  dynamically sized assignment
	{
		hamon::span<hamon::string> spans[] =
		{
			{strs, strs},
			{strs, strs + 1},
			{strs, strs + 2},
			{strs, strs + 3},
			{strs + 1, strs + 1},
			{strs + 1, strs + 2},
			{strs + 1, strs + 3},
			{strs + 2, strs + 2},
			{strs + 2, strs + 3},
			{strs + 3, strs + 3},
		};

		for (hamon::size_t i = 0; i < hamon::size(spans); ++i)
		{
			for (hamon::size_t j = i; j < hamon::size(spans); ++j)
			{
				VERIFY((do_assign(spans[i], spans[j])));
			}
		}
	}

	// statically sized assignment
	{
		using spanType = hamon::span<hamon::string, 1>;
		spanType spans[] =
		{
			spanType{strs, strs + 1},
			spanType{strs + 1, strs + 2},
			spanType{strs + 2, strs + 3},
		};

		for (hamon::size_t i = 0; i < hamon::size(spans); ++i)
		{
			for (hamon::size_t j = i; j < hamon::size(spans); ++j)
			{
				VERIFY((do_assign(spans[i], spans[j])));
			}
		}
	}

	return true;
}

#undef VERIFY

GTEST_TEST(SpanTest, AssignTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test1()));
	EXPECT_TRUE((test2()));
}

}	// namespace assign_test

}	// namespace hamon_span_test
