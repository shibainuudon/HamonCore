/**
 *	@file	unit_test_ranges_cache_latest_view_sentinel_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 *
 *	sentinel() = default;
 */

#include <hamon/ranges/adaptors/cache_latest_view.hpp>
#include <hamon/ranges/sentinel_t.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <hamon/type_traits/is_implicitly_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"
#include "range_test_helper.hpp"

namespace hamon_ranges_test
{
namespace cache_latest_view_test
{
namespace sentinel_ctor_default_test
{

template <typename T>
struct ThrowOnDefaultIterator
{
	T*	m_ptr;

	using iterator_category = hamon::forward_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;

	explicit ThrowOnDefaultIterator() : m_ptr() {}
	explicit ThrowOnDefaultIterator(T* ptr) : m_ptr(ptr) {}

	ThrowOnDefaultIterator& operator++();
	ThrowOnDefaultIterator  operator++(int);
	T&                      operator*() const;
	bool operator==(const ThrowOnDefaultIterator& rhs) const;
	bool operator!=(const ThrowOnDefaultIterator& rhs) const;
};

template <typename Iterator, typename Sentinel>
struct TestView : hamon::ranges::view_base
{
	Iterator begin() const noexcept;
	Sentinel end()   const noexcept;
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using V = TestView<
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>
		>;

		using CV = hamon::ranges::cache_latest_view<V>;
		using S = hamon::ranges::sentinel_t<CV>;
		static_assert( hamon::is_default_constructible<S>::value, "");
		static_assert( hamon::is_implicitly_default_constructible<S>::value, "");
		static_assert( hamon::is_nothrow_default_constructible<S>::value, "");
	}
	{
		using V = TestView<
			ThrowOnDefaultIterator<int>,
			ThrowOnDefaultIterator<int>
		>;

		using CV = hamon::ranges::cache_latest_view<V>;
		using S = hamon::ranges::sentinel_t<CV>;
		static_assert( hamon::is_default_constructible<S>::value, "");
		static_assert( hamon::is_implicitly_default_constructible<S>::value, "");
		static_assert(!hamon::is_nothrow_default_constructible<S>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using T = int;
	using V = test_input_view<T>;
	using CLV = hamon::ranges::cache_latest_view<V>;
	using S  = decltype(hamon::declval<CLV&>().end());

	S sent{};
	(void)sent;

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, CacheLatestViewSentinelCtorDefaultTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace sentinel_ctor_default_test
}	// namespace cache_latest_view_test
}	// namespace hamon_ranges_test
