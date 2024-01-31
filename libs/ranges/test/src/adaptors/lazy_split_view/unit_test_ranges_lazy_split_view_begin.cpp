/**
 *	@file	unit_test_ranges_lazy_split_view_begin.cpp
 *
 *	@brief	begin() のテスト
 *
 *	constexpr auto begin();
 *	constexpr auto begin() const requires forward_range<V> && forward_range<const V>;
 */

#include <hamon/ranges/adaptors/lazy_split_view.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace lazy_split_view_test
{
namespace begin_test
{

template <
	typename T,
	typename Iterator,
	typename ConstIterator,
	typename Sentinel = test_sentinel<Iterator>,
	typename ConstSentinel = test_sentinel<ConstIterator>
>
struct NotSimpleView : hamon::ranges::view_base
{
	T* m_first;
	T* m_last;

	using iterator = Iterator;
	using const_iterator = ConstIterator;
	using sentinel = Sentinel;
	using const_sentinel = ConstSentinel;

	HAMON_CXX11_CONSTEXPR NotSimpleView() : m_first(nullptr), m_last(nullptr) {}

	template <hamon::size_t N>
	explicit HAMON_CXX11_CONSTEXPR NotSimpleView(T (&arr)[N]) : NotSimpleView(arr, arr+N) {}

	HAMON_CXX11_CONSTEXPR NotSimpleView(T* first, T* last) : m_first(first), m_last(last) {}

	HAMON_CXX14_CONSTEXPR iterator       begin()       noexcept { return iterator{m_first}; }
	HAMON_CXX11_CONSTEXPR const_iterator begin() const noexcept { return const_iterator{m_first}; }
	HAMON_CXX14_CONSTEXPR sentinel       end()         noexcept { return sentinel{iterator{m_last}}; }
	HAMON_CXX11_CONSTEXPR const_sentinel end()   const noexcept { return const_sentinel{const_iterator{m_last}}; }
};

template <typename T, typename = void>
struct has_begin
	: public hamon::false_type {};

template <typename T>
struct has_begin<T, hamon::void_t<decltype(hamon::declval<T>().begin())>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using V = test_forward_view<int>;
		using P = test_forward_view<int>;
		using RV = hamon::ranges::lazy_split_view<V, P>;

		static_assert( has_begin<RV&>::value, "");
		static_assert( has_begin<RV const&>::value, "");

		//static_assert(hamon::is_same<decltype(hamon::declval<RV&>().begin()), typename RV::outer_iterator<true>>::value, "");
		//static_assert(hamon::is_same<decltype(hamon::declval<RV const&>().begin()), typename RV::outer_iterator<true>>::value, "");

		{
			RV rv{};
			auto it = rv.begin();
			(void)it;
		}
		{
			RV const rv{};
			auto it = rv.begin();
			(void)it;
		}
	}
	{
		using V = test_input_view<int>;
		using P = test_forward_static_sized_view<int, 1>;
		using RV = hamon::ranges::lazy_split_view<V, P>;

		static_assert( has_begin<RV&>::value, "");
		static_assert(!has_begin<RV const&>::value, "");

		//static_assert(hamon::is_same<decltype(hamon::declval<RV&>().begin()), typename RV::outer_iterator<false>>::value, "");

		{
			RV rv{};
			auto it = rv.begin();
			(void)it;
		}
	}
	{
		using V = NotSimpleView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>>;
		using P = NotSimpleView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>>;
		using RV = hamon::ranges::lazy_split_view<V, P>;

		static_assert( has_begin<RV&>::value, "");
		static_assert( has_begin<RV const&>::value, "");

		//static_assert(hamon::is_same<decltype(hamon::declval<RV&>().begin()), typename RV::outer_iterator<true>>::value, "");
		//static_assert(hamon::is_same<decltype(hamon::declval<RV const&>().begin()), typename RV::outer_iterator<true>>::value, "");

		{
			RV rv{};
			auto it = rv.begin();
			(void)it;
		}
		{
			RV const rv{};
			auto it = rv.begin();
			(void)it;
		}
	}
	{
		using V = NotSimpleView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int const>>;
		using P = NotSimpleView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>>;
		using RV = hamon::ranges::lazy_split_view<V, P>;

		static_assert( has_begin<RV&>::value, "");
		static_assert( has_begin<RV const&>::value, "");

		//static_assert(hamon::is_same<decltype(hamon::declval<RV&>().begin()), typename RV::outer_iterator<false>>::value, "");
		//static_assert(hamon::is_same<decltype(hamon::declval<RV const&>().begin()), typename RV::outer_iterator<true>>::value, "");

		{
			RV rv{};
			auto it = rv.begin();
			(void)it;
		}
		{
			RV const rv{};
			auto it = rv.begin();
			(void)it;
		}
	}
	{
		using V = NotSimpleView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>>;
		using P = NotSimpleView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int const>>;
		using RV = hamon::ranges::lazy_split_view<V, P>;

		static_assert( has_begin<RV&>::value, "");
		static_assert( has_begin<RV const&>::value, "");

		//static_assert(hamon::is_same<decltype(hamon::declval<RV&>().begin()), typename RV::outer_iterator<false>>::value, "");
		//static_assert(hamon::is_same<decltype(hamon::declval<RV const&>().begin()), typename RV::outer_iterator<true>>::value, "");

		{
			RV rv{};
			auto it = rv.begin();
			(void)it;
		}
		{
			RV const rv{};
			auto it = rv.begin();
			(void)it;
		}
	}
	{
		using V = NotSimpleView<int,
			forward_iterator_wrapper<int>,
			input_iterator_wrapper<int>>;
		using P = NotSimpleView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>>;
		using RV = hamon::ranges::lazy_split_view<V, P>;

		static_assert( has_begin<RV&>::value, "");
		static_assert(!has_begin<RV const&>::value, "");

		//static_assert(hamon::is_same<decltype(hamon::declval<RV&>().begin()), typename RV::outer_iterator<false>>::value, "");

		{
			RV rv{};
			auto it = rv.begin();
			(void)it;
		}
	}
	{
		using V = NotSimpleView<int,
			input_iterator_wrapper<int>,
			forward_iterator_wrapper<int>>;
		using P = test_forward_static_sized_view<int, 1>;
		using RV = hamon::ranges::lazy_split_view<V, P>;

		static_assert( has_begin<RV&>::value, "");
		static_assert(!has_begin<RV const&>::value, "");

		//static_assert(hamon::is_same<decltype(hamon::declval<RV&>().begin()), typename RV::outer_iterator<false>>::value, "");

		{
			RV rv{};
			auto it = rv.begin();
			(void)it;
		}
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, LazySplitViewBeginTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace begin_test
}	// namespace lazy_split_view_test
}	// namespace hamon_ranges_test
