/**
 *	@file	unit_test_ranges_stride_view_iterator_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 *
 *	iterator() requires default_initializable<iterator_t<Base>> = default;
 */

#include <hamon/ranges/adaptors/stride_view.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <hamon/type_traits/is_implicitly_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/iterator/unreachable_sentinel_t.hpp>
#include <hamon/utility/declval.hpp>
//#include <hamon/tuple.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace stride_view_test
{
namespace iterator_ctor_default_test
{

template <typename T>
struct NoDefaultIterator
{
	T*	m_ptr;

	using iterator_category = hamon::forward_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;

	//NoDefaultIterator() : m_ptr() {}
	explicit NoDefaultIterator(T* ptr) : m_ptr(ptr) {}

	NoDefaultIterator& operator++();
	NoDefaultIterator  operator++(int);
	T&                 operator*() const;
	bool operator==(const NoDefaultIterator& rhs) const;
	bool operator!=(const NoDefaultIterator& rhs) const;
};
static_assert(!hamon::is_default_constructible<NoDefaultIterator<int>>::value, "");

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
static_assert(hamon::is_default_constructible<ThrowOnDefaultIterator<int>>::value, "");
static_assert(!hamon::is_nothrow_default_constructible<ThrowOnDefaultIterator<int>>::value, "");

template <typename Iterator, typename Sentinel>
struct TestView : hamon::ranges::view_base
{
	Iterator begin() const noexcept;
	Sentinel end()   const noexcept;
};

static_assert(!hamon::ranges::input_range_t<TestView<NoDefaultIterator<int>, NoDefaultIterator<int>>>::value, "");
static_assert( hamon::ranges::input_range_t<TestView<NoDefaultIterator<int>, hamon::unreachable_sentinel_t>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using V = TestView<
			input_iterator_wrapper<int>,
			hamon::unreachable_sentinel_t
		>;

		using SV = hamon::ranges::stride_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert( hamon::is_default_constructible<I>::value, "");
		static_assert( hamon::is_implicitly_default_constructible<I>::value, "");
		static_assert( hamon::is_nothrow_default_constructible<I>::value, "");
	}
	{
		using V = TestView<
			NoDefaultIterator<int>,
			hamon::unreachable_sentinel_t
		>;

		using SV = hamon::ranges::stride_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert(!hamon::is_default_constructible<I>::value, "");
	}
	{
		using V = TestView<
			ThrowOnDefaultIterator<int>,
			hamon::unreachable_sentinel_t
		>;

		using SV = hamon::ranges::stride_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert( hamon::is_default_constructible<I>::value, "");
		static_assert( hamon::is_implicitly_default_constructible<I>::value, "");
		static_assert(!hamon::is_nothrow_default_constructible<I>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using V = test_input_view<int>;
	using SV = hamon::ranges::stride_view<V>;
	using I = decltype(hamon::declval<SV&>().begin());
	I it{};
	VERIFY(it.base().m_ptr == nullptr);
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, StrideViewIteratorCtorDefaultTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace iterator_ctor_default_test
}	// namespace stride_view_test
}	// namespace hamon_ranges_test
