/**
 *	@file	unit_test_list_assign_range.cpp
 *
 *	@brief	assign_range のテスト
 *
 *	template<container-compatible-range<T> R>
 *	void assign_range(R&& rg);
 */

#include <hamon/list/list.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_list_test
{

namespace assign_range_test
{

#if !defined(HAMON_USE_STD_LIST) && \
	!(defined(HAMON_MSVC) && (HAMON_MSVC < 1930))// VS2019でconstexprにすると内部コンパイラエラーになってしまう
#define LIST_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define LIST_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define LIST_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define LIST_TEST_CONSTEXPR             /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, template <typename> class RangeWrapper>
LIST_TEST_CONSTEXPR bool test_impl()
{
	using List = hamon::list<T>;
	using Range = RangeWrapper<T>;

	{
		List v;
		Range r;
		static_assert(hamon::is_same<decltype(v.assign_range(r)), void>::value, "");
		static_assert(!noexcept(v.assign_range(r)), "");
	}
	{
		List v;
		VERIFY(v.empty());

		{
			T a[] = {{1},{2},{3},{4}};
			Range r(a);
			v.assign_range(r);
			VERIFY(v.size() == 4);
			VERIFY(v.begin() != v.end());
			VERIFY(v.rbegin() != v.rend());
			{
				auto it = v.begin();
				VERIFY(*it++ == a[0]);
				VERIFY(*it++ == a[1]);
				VERIFY(*it++ == a[2]);
				VERIFY(*it++ == a[3]);
				VERIFY(it == v.end());
			}
			{
				auto it = v.rbegin();
				VERIFY(*it++ == a[3]);
				VERIFY(*it++ == a[2]);
				VERIFY(*it++ == a[1]);
				VERIFY(*it++ == a[0]);
				VERIFY(it == v.rend());
			}
		}
		{
			T a[] = {{10},{20}};
			v.assign_range(Range(a));
			VERIFY(v.size() == 2);
			VERIFY(v.begin() != v.end());
			VERIFY(v.rbegin() != v.rend());
			{
				auto it = v.begin();
				VERIFY(*it++ == a[0]);
				VERIFY(*it++ == a[1]);
				VERIFY(it == v.end());
			}
			{
				auto it = v.rbegin();
				VERIFY(*it++ == a[1]);
				VERIFY(*it++ == a[0]);
				VERIFY(it == v.rend());
			}
		}
	}

	return true;
}

template <typename T>
LIST_TEST_CONSTEXPR bool test()
{
	return
		test_impl<T, test_input_range>() &&
		test_impl<T, test_forward_range>() &&
		test_impl<T, test_bidirectional_range>() &&
		test_impl<T, test_random_access_range>() &&
		test_impl<T, test_contiguous_range>() &&
		test_impl<T, test_input_sized_range>() &&
		test_impl<T, test_forward_sized_range>() &&
		test_impl<T, test_bidirectional_sized_range>() &&
		test_impl<T, test_random_access_sized_range>() &&
		test_impl<T, test_contiguous_sized_range>();
}

#undef VERIFY

GTEST_TEST(ListTest, AssignRangeTest)
{
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<int>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<char>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<float>());
}

#undef LIST_TEST_CONSTEXPR_EXPECT_TRUE
#undef LIST_TEST_CONSTEXPR

}	// namespace assign_range_test

}	// namespace hamon_list_test
