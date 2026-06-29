/**
 *	@file	unit_test_ranges_concat_view_iterator_typedefs.cpp
 *
 *	@brief	concat_view::iterator のテスト
 *
 *	using iterator_category = see below;                                // not always present
 *	using iterator_concept = see below;
 *	using value_type = concat-value-t<maybe-const<Const, Views>...>;
 *	using difference_type = common_type_t<range_difference_t<maybe-const<Const, Views>>...>;
 */

#include <hamon/ranges/adaptors/concat_view.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/iterator/random_access_iterator_tag.hpp>
#include <hamon/iterator/bidirectional_iterator_tag.hpp>
#include <hamon/iterator/input_iterator_tag.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"
#include "range_test_helper.hpp"

namespace hamon_ranges_test
{
namespace concat_view_test
{
namespace iterator_typedefs_test
{

template <typename T, typename Iterator, typename Sentinel, typename ConstIterator, typename ConstSentinel>
struct TestView : hamon::ranges::view_base
{
	T* m_first;
	T* m_last;

	HAMON_CXX11_CONSTEXPR TestView() : m_first(nullptr), m_last(nullptr) {}

	template <hamon::size_t N>
	explicit HAMON_CXX11_CONSTEXPR TestView(T (&arr)[N]) : TestView(arr, arr+N) {}

	HAMON_CXX11_CONSTEXPR TestView(T* first, T* last) : m_first(first), m_last(last) {}

	HAMON_CXX14_CONSTEXPR Iterator      begin()       noexcept { return Iterator{m_first}; }
	HAMON_CXX11_CONSTEXPR ConstIterator begin() const noexcept { return ConstIterator{m_first}; }
	HAMON_CXX14_CONSTEXPR Sentinel      end()         noexcept { return Sentinel{m_last}; }
	HAMON_CXX11_CONSTEXPR ConstSentinel end()   const noexcept { return ConstSentinel{m_last}; }
};

template <typename T, typename ValueType = T, typename Reference = T&>
struct TestIterator
{
	T*	m_ptr;

	using iterator_category = hamon::forward_iterator_tag;
	using value_type        = ValueType;
	using difference_type   = short;

	TestIterator& operator++();
	TestIterator  operator++(int);
	Reference     operator*() const;
	bool operator==(const TestIterator& rhs) const;
	bool operator!=(const TestIterator& rhs) const;
};

HAMON_CXX14_CONSTEXPR bool test_iterator_concept()
{
	{
		using V1 = TestView<int,
			contiguous_iterator_wrapper<int>,
			contiguous_iterator_wrapper<int>,
			contiguous_iterator_wrapper<int>,
			contiguous_iterator_wrapper<int>
		>;

		using V2 = TestView<int,
			contiguous_iterator_wrapper<int>,
			contiguous_iterator_wrapper<int>,
			contiguous_iterator_wrapper<int const>,
			contiguous_iterator_wrapper<int const>
		>;

		using CV = hamon::ranges::concat_view<V1, V2>;

		using I  = decltype(hamon::declval<CV&>().begin());
		using CI = decltype(hamon::declval<CV const&>().begin());
		//static_assert(hamon::is_same<I,  CV::iterator<false>>::value, "");
		//static_assert(hamon::is_same<CI, CV::iterator<true>>::value, "");

		static_assert(hamon::is_same<typename I::iterator_concept,  hamon::random_access_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename CI::iterator_concept, hamon::random_access_iterator_tag>::value, "");
	}
	{
		using V1 = TestView<int,
			contiguous_iterator_wrapper<int>,
			contiguous_iterator_wrapper<int>,
			contiguous_iterator_wrapper<int>,
			contiguous_iterator_wrapper<int>
		>;

		using V2 = TestView<int,
			random_access_iterator_wrapper<int>,
			random_access_iterator_wrapper<int>,
			bidirectional_iterator_wrapper<int const>,
			bidirectional_iterator_wrapper<int const>
		>;

		using CV = hamon::ranges::concat_view<V1, V2>;

		using I  = decltype(hamon::declval<CV&>().begin());
		using CI = decltype(hamon::declval<CV const&>().begin());
		//static_assert(hamon::is_same<I,  CV::iterator<false>>::value, "");
		//static_assert(hamon::is_same<CI, CV::iterator<true>>::value, "");

		static_assert(hamon::is_same<typename I::iterator_concept,  hamon::random_access_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename CI::iterator_concept, hamon::bidirectional_iterator_tag>::value, "");
	}
	{
		using V1 = TestView<int,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>
		>;

		using V2 = TestView<int,
			contiguous_iterator_wrapper<int>,
			contiguous_iterator_wrapper<int>,
			contiguous_iterator_wrapper<int const>,
			contiguous_iterator_wrapper<int const>
		>;

		using CV = hamon::ranges::concat_view<V1, V2>;

		using I  = decltype(hamon::declval<CV&>().begin());
		using CI = decltype(hamon::declval<CV const&>().begin());
		//static_assert(hamon::is_same<I,  CV::iterator<false>>::value, "");
		//static_assert(hamon::is_same<CI, CV::iterator<true>>::value, "");

		static_assert(hamon::is_same<typename I::iterator_concept,  hamon::input_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename CI::iterator_concept, hamon::forward_iterator_tag>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test_iterator_category()
{
	{
		using V1 = TestView<int,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>
		>;

		using V2 = TestView<int,
			contiguous_iterator_wrapper<int>,
			contiguous_iterator_wrapper<int>,
			contiguous_iterator_wrapper<int const>,
			contiguous_iterator_wrapper<int const>
		>;

		using CV = hamon::ranges::concat_view<V1, V2>;

		using I  = decltype(hamon::declval<CV&>().begin());
		using CI = decltype(hamon::declval<CV const&>().begin());
		//static_assert(hamon::is_same<I,  CV::iterator<false>>::value, "");
		//static_assert(hamon::is_same<CI, CV::iterator<true>>::value, "");

		static_assert(!has_iterator_category<I>::value, "");
		static_assert(!has_iterator_category<CI>::value, "");
	}
	{
		using V1 = TestView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			bidirectional_iterator_wrapper<int>,
			bidirectional_iterator_wrapper<int>
		>;

		using V2 = TestView<int,
			contiguous_iterator_wrapper<int>,
			contiguous_iterator_wrapper<int>,
			contiguous_iterator_wrapper<int const>,
			contiguous_iterator_wrapper<int const>
		>;

		using CV = hamon::ranges::concat_view<V1, V2>;

		using I  = decltype(hamon::declval<CV&>().begin());
		using CI = decltype(hamon::declval<CV const&>().begin());
		//static_assert(hamon::is_same<I,  CV::iterator<false>>::value, "");
		//static_assert(hamon::is_same<CI, CV::iterator<true>>::value, "");

		static_assert( has_iterator_category<I>::value, "");
		static_assert( has_iterator_category<CI>::value, "");

		static_assert(hamon::is_same<typename I::iterator_category,  hamon::forward_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename CI::iterator_category, hamon::bidirectional_iterator_tag>::value, "");
	}
	{
		using V1 = TestView<int,
			random_access_iterator_wrapper<int>,
			random_access_iterator_wrapper<int>,
			contiguous_iterator_wrapper<int>,
			contiguous_iterator_wrapper<int>
		>;

		using V2 = TestView<int,
			contiguous_iterator_wrapper<int>,
			contiguous_iterator_wrapper<int>,
			contiguous_iterator_wrapper<int const>,
			contiguous_iterator_wrapper<int const>
		>;

		using CV = hamon::ranges::concat_view<V1, V2>;

		using I  = decltype(hamon::declval<CV&>().begin());
		using CI = decltype(hamon::declval<CV const&>().begin());
		//static_assert(hamon::is_same<I,  CV::iterator<false>>::value, "");
		//static_assert(hamon::is_same<CI, CV::iterator<true>>::value, "");

		static_assert( has_iterator_category<I>::value, "");
		static_assert( has_iterator_category<CI>::value, "");

		static_assert(hamon::is_same<typename I::iterator_category,  hamon::random_access_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename CI::iterator_category, hamon::random_access_iterator_tag>::value, "");
	}
	{
		using V1 = TestView<int,
			TestIterator<int, int, int&>,
			TestIterator<int, int, int&>,
			TestIterator<int, int, int>,
			TestIterator<int, int, int>
		>;

		using V2 = TestView<int,
			contiguous_iterator_wrapper<int>,
			contiguous_iterator_wrapper<int>,
			contiguous_iterator_wrapper<int const>,
			contiguous_iterator_wrapper<int const>
		>;

		using CV = hamon::ranges::concat_view<V1, V2>;

		using I  = decltype(hamon::declval<CV&>().begin());
		using CI = decltype(hamon::declval<CV const&>().begin());
		//static_assert(hamon::is_same<I,  CV::iterator<false>>::value, "");
		//static_assert(hamon::is_same<CI, CV::iterator<true>>::value, "");

		static_assert( has_iterator_category<I>::value, "");
		static_assert( has_iterator_category<CI>::value, "");

		static_assert(hamon::is_same<typename I::iterator_category,  hamon::forward_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename CI::iterator_category, hamon::input_iterator_tag>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test_value_type()
{
	{
		using V1 = TestView<int,
			input_iterator_wrapper<long>,
			input_iterator_wrapper<long>,
			input_iterator_wrapper<char>,
			input_iterator_wrapper<char>
		>;

		using V2 = TestView<int,
			input_iterator_wrapper<char>,
			input_iterator_wrapper<char>,
			input_iterator_wrapper<int const>,
			input_iterator_wrapper<int const>
		>;

		using CV = hamon::ranges::concat_view<V1, V2>;

		using I  = decltype(hamon::declval<CV&>().begin());
		using CI = decltype(hamon::declval<CV const&>().begin());
		//static_assert(hamon::is_same<I,  CV::iterator<false>>::value, "");
		//static_assert(hamon::is_same<CI, CV::iterator<true>>::value, "");

		static_assert(hamon::is_same<typename I::value_type,  long>::value, "");
		static_assert(hamon::is_same<typename CI::value_type, int>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test_difference_type()
{
	{
		using V1 = TestView<int,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>,
			TestIterator<int>,
			TestIterator<int>
		>;

		using V2 = TestView<int,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>,
			TestIterator<int const>,
			TestIterator<int const>
		>;

		using CV = hamon::ranges::concat_view<V1, V2>;

		using I  = decltype(hamon::declval<CV&>().begin());
		using CI = decltype(hamon::declval<CV const&>().begin());
		//static_assert(hamon::is_same<I,  CV::iterator<false>>::value, "");
		//static_assert(hamon::is_same<CI, CV::iterator<true>>::value, "");

		static_assert(hamon::is_same<typename I::difference_type,  hamon::ptrdiff_t>::value, "");
		static_assert(hamon::is_same<typename CI::difference_type, short>::value, "");
	}
	return true;
}

GTEST_TEST(RangesTest, ConcatViewIteratorTypedefsTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_iterator_concept());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_iterator_category());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_value_type());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_difference_type());
}

}	// namespace iterator_typedefs_test
}	// namespace concat_view_test
}	// namespace hamon_ranges_test
