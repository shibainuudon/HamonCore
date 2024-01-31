/**
 *	@file	unit_test_ranges_lazy_split_view_end.cpp
 *
 *	@brief	end() のテスト
 *
 *	constexpr auto end() requires forward_range<V> && common_range<V>;
 *	constexpr auto end() const;
 */

#include <hamon/ranges/adaptors/lazy_split_view.hpp>
#include <hamon/ranges/utility/detail/simple_view.hpp>
#include <hamon/ranges/concepts.hpp>
#include <hamon/iterator/default_sentinel_t.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace lazy_split_view_test
{
namespace end_test
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
struct has_end
	: public hamon::false_type {};

template <typename T>
struct has_end<T, hamon::void_t<decltype(hamon::declval<T>().end())>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using V = test_forward_view<int>;
		using P = test_forward_view<int>;
		using RV = hamon::ranges::lazy_split_view<V, P>;

		static_assert( has_end<RV&>::value, "");
		static_assert( has_end<RV const&>::value, "");

		static_assert(hamon::is_same<decltype(hamon::declval<RV&>().end()), hamon::default_sentinel_t>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<RV const&>().end()), hamon::default_sentinel_t>::value, "");

		{
			RV rv{};
			auto it = rv.end();
			(void)it;
		}
		{
			RV const rv{};
			auto it = rv.end();
			(void)it;
		}
	}
	{
		using V = NotSimpleView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>>;
		using P = NotSimpleView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>>;
		using RV = hamon::ranges::lazy_split_view<V, P>;

		static_assert(hamon::ranges::forward_range_t<V>::value, "");
		static_assert(hamon::ranges::forward_range_t<V const>::value, "");
		static_assert(hamon::ranges::common_range_t<V>::value, "");
		static_assert(hamon::ranges::common_range_t<V const>::value, "");
		static_assert(hamon::ranges::detail::simple_view_t<V>::value, "");
		static_assert(hamon::ranges::detail::simple_view_t<P>::value, "");

		static_assert( has_end<RV&>::value, "");
		static_assert( has_end<RV const&>::value, "");

		//static_assert(hamon::is_same<decltype(hamon::declval<RV&>().end()), typename RV::outer_iterator<true>>::value, "");
		//static_assert(hamon::is_same<decltype(hamon::declval<RV const&>().end()), typename RV::outer_iterator<true>>::value, "");

		{
			RV rv{};
			auto it = rv.end();
			(void)it;
		}
		{
			RV const rv{};
			auto it = rv.end();
			(void)it;
		}
	}
	{
		using V = NotSimpleView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int const>,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int const>>;
		using P = NotSimpleView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>>;
		using RV = hamon::ranges::lazy_split_view<V, P>;

		static_assert(hamon::ranges::forward_range_t<V>::value, "");
		static_assert(hamon::ranges::forward_range_t<V const>::value, "");
		static_assert(hamon::ranges::common_range_t<V>::value, "");
		static_assert(hamon::ranges::common_range_t<V const>::value, "");
		static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
		static_assert(hamon::ranges::detail::simple_view_t<P>::value, "");

		static_assert( has_end<RV&>::value, "");
		static_assert( has_end<RV const&>::value, "");

		//static_assert(hamon::is_same<decltype(hamon::declval<RV&>().end()), typename RV::outer_iterator<false>>::value, "");
		//static_assert(hamon::is_same<decltype(hamon::declval<RV const&>().end()), typename RV::outer_iterator<true>>::value, "");

		{
			RV rv{};
			auto it = rv.end();
			(void)it;
		}
		{
			RV const rv{};
			auto it = rv.end();
			(void)it;
		}
	}
	{
		using V = NotSimpleView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>>;
		using P = NotSimpleView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int const>>;
		using RV = hamon::ranges::lazy_split_view<V, P>;

		static_assert(hamon::ranges::forward_range_t<V>::value, "");
		static_assert(hamon::ranges::forward_range_t<V const>::value, "");
		static_assert(hamon::ranges::common_range_t<V>::value, "");
		static_assert(hamon::ranges::common_range_t<V const>::value, "");
		static_assert(hamon::ranges::detail::simple_view_t<V>::value, "");
		static_assert(!hamon::ranges::detail::simple_view_t<P>::value, "");

		static_assert( has_end<RV&>::value, "");
		static_assert( has_end<RV const&>::value, "");

		//static_assert(hamon::is_same<decltype(hamon::declval<RV&>().end()), typename RV::outer_iterator<false>>::value, "");
		//static_assert(hamon::is_same<decltype(hamon::declval<RV const&>().end()), typename RV::outer_iterator<true>>::value, "");

		{
			RV rv{};
			auto it = rv.end();
			(void)it;
		}
		{
			RV const rv{};
			auto it = rv.end();
			(void)it;
		}
	}
	{
		using V = NotSimpleView<int,
			input_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			input_iterator_wrapper<int>,
			forward_iterator_wrapper<int>>;
		using P = test_forward_static_sized_view<int, 1>;
		using RV = hamon::ranges::lazy_split_view<V, P>;

		static_assert(!hamon::ranges::forward_range_t<V>::value, "");
		static_assert(hamon::ranges::forward_range_t<V const>::value, "");
		static_assert(hamon::ranges::common_range_t<V>::value, "");
		static_assert(hamon::ranges::common_range_t<V const>::value, "");

		static_assert( has_end<RV&>::value, "");
		static_assert( has_end<RV const&>::value, "");

		static_assert(hamon::is_same<decltype(hamon::declval<RV&>().end()), hamon::default_sentinel_t>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<RV const&>().end()), hamon::default_sentinel_t>::value, "");

		{
			RV rv{};
			auto it = rv.end();
			(void)it;
		}
		{
			RV const rv{};
			auto it = rv.end();
			(void)it;
		}
	}
	{
		using V = NotSimpleView<int,
			forward_iterator_wrapper<int>,
			input_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			input_iterator_wrapper<int>>;
		using P = test_forward_view<int>;
		using RV = hamon::ranges::lazy_split_view<V, P>;

		static_assert(hamon::ranges::forward_range_t<V>::value, "");
		static_assert(!hamon::ranges::forward_range_t<V const>::value, "");
		static_assert(hamon::ranges::common_range_t<V>::value, "");
		static_assert(hamon::ranges::common_range_t<V const>::value, "");

		static_assert( has_end<RV&>::value, "");
		static_assert( has_end<RV const&>::value, "");

		//static_assert(hamon::is_same<decltype(hamon::declval<RV&>().end()), typename RV::outer_iterator<false>>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<RV const&>().end()), hamon::default_sentinel_t>::value, "");

		{
			RV rv{};
			auto it = rv.end();
			(void)it;
		}
		{
			RV const rv{};
			auto it = rv.end();
			(void)it;
		}
	}
	{
		using V = NotSimpleView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			test_sentinel<forward_iterator_wrapper<int>>,
			forward_iterator_wrapper<int>>;
		using P = test_forward_view<int>;
		using RV = hamon::ranges::lazy_split_view<V, P>;

		static_assert(hamon::ranges::forward_range_t<V>::value, "");
		static_assert(hamon::ranges::forward_range_t<V const>::value, "");
		static_assert(!hamon::ranges::common_range_t<V>::value, "");
		static_assert(hamon::ranges::common_range_t<V const>::value, "");

		static_assert( has_end<RV&>::value, "");
		static_assert( has_end<RV const&>::value, "");

		//static_assert(hamon::is_same<decltype(hamon::declval<RV&>().end()), typename RV::outer_iterator<true>>::value, "");
		//static_assert(hamon::is_same<decltype(hamon::declval<RV const&>().end()), typename RV::outer_iterator<true>>::value, "");

		{
			RV rv{};
			auto it = rv.end();
			(void)it;
		}
		{
			RV const rv{};
			auto it = rv.end();
			(void)it;
		}
	}
	{
		using V = NotSimpleView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			test_sentinel<forward_iterator_wrapper<int>>>;
		using P = test_forward_view<int>;
		using RV = hamon::ranges::lazy_split_view<V, P>;

		static_assert(hamon::ranges::forward_range_t<V>::value, "");
		static_assert(hamon::ranges::forward_range_t<V const>::value, "");
		static_assert(hamon::ranges::common_range_t<V>::value, "");
		static_assert(!hamon::ranges::common_range_t<V const>::value, "");

		static_assert( has_end<RV&>::value, "");
		static_assert( has_end<RV const&>::value, "");

		//static_assert(hamon::is_same<decltype(hamon::declval<RV&>().end()), typename RV::outer_iterator<false>>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<RV const&>().end()), hamon::default_sentinel_t>::value, "");

		{
			RV rv{};
			auto it = rv.end();
			(void)it;
		}
		{
			RV const rv{};
			auto it = rv.end();
			(void)it;
		}
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, LazySplitViewEndTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace end_test
}	// namespace lazy_split_view_test
}	// namespace hamon_ranges_test
