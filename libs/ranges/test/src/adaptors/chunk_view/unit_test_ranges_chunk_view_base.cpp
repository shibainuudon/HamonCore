/**
 *	@file	unit_test_ranges_chunk_view_base.cpp
 *
 *	@brief	base() のテスト
 *
 *	constexpr V base() const & requires copy_constructible<V>;
 *	constexpr V base() &&
 */

#include <hamon/ranges/adaptors/chunk_view.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

#include <hamon/ranges/concepts.hpp>

namespace hamon_ranges_test
{
namespace chunk_view_test
{
namespace base_test
{

template <typename T, typename Iterator, typename Sentinel = test_sentinel<Iterator>>
struct MoveOnlyView : hamon::ranges::view_base
{
	T* m_first;
	T* m_last;

	using iterator = Iterator;
	using sentinel = Sentinel;

	HAMON_CONSTEXPR MoveOnlyView() : m_first(nullptr), m_last(nullptr) {}
	HAMON_CONSTEXPR MoveOnlyView(T* first, T* last) : m_first(first), m_last(last) {}

	template <hamon::size_t N>
	explicit HAMON_CONSTEXPR MoveOnlyView(T (&arr)[N]) : MoveOnlyView(arr, arr+N) {}

	MoveOnlyView(MoveOnlyView&&) = default;
	MoveOnlyView& operator=(MoveOnlyView&&) = default;

	HAMON_CONSTEXPR iterator begin() const noexcept { return iterator{m_first}; }
	HAMON_CONSTEXPR sentinel end()   const noexcept { return sentinel{iterator{m_last}}; }
};

template <typename T> using MoveOnlyContiguousView    = MoveOnlyView<T, contiguous_iterator_wrapper<T>>;
template <typename T> using MoveOnlyRandomAccessView  = MoveOnlyView<T, random_access_iterator_wrapper<T>>;
template <typename T> using MoveOnlyBidirectionalView = MoveOnlyView<T, bidirectional_iterator_wrapper<T>>;
template <typename T> using MoveOnlyForwardView       = MoveOnlyView<T, forward_iterator_wrapper<T>>;
template <typename T> using MoveOnlyInputView         = MoveOnlyView<T, input_iterator_wrapper<T>>;
template <typename T> using MoveOnlyOutputView        = MoveOnlyView<T, output_iterator_wrapper<T>>;

static_assert( hamon::ranges::input_range_t<MoveOnlyInputView<int>>::value, "");
static_assert(!hamon::ranges::forward_range_t<MoveOnlyInputView<int>>::value, "");
static_assert( hamon::ranges::forward_range_t<MoveOnlyForwardView<int>>::value, "");

template <typename T, typename = void>
struct has_base
	: public hamon::false_type {};

template <typename T>
struct has_base<T, hamon::void_t<decltype(hamon::declval<T>().base())>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using V = test_input_view<int>;
		using CV = hamon::ranges::chunk_view<V>;

		static_assert( has_base<CV&>::value, "");
		static_assert( has_base<CV&&>::value, "");
		static_assert( has_base<CV const&>::value, "");
		static_assert( has_base<CV const&&>::value, "");

		static_assert(hamon::is_same<V, decltype(hamon::declval<CV&>().base())>::value, "");
		static_assert(hamon::is_same<V, decltype(hamon::declval<CV&&>().base())>::value, "");
		static_assert(hamon::is_same<V, decltype(hamon::declval<CV const&>().base())>::value, "");
		static_assert(hamon::is_same<V, decltype(hamon::declval<CV const&&>().base())>::value, "");
	}
	{
		using V = test_forward_view<int>;
		using CV = hamon::ranges::chunk_view<V>;

		static_assert( has_base<CV&>::value, "");
		static_assert( has_base<CV&&>::value, "");
		static_assert( has_base<CV const&>::value, "");
		static_assert( has_base<CV const&&>::value, "");

		static_assert(hamon::is_same<V, decltype(hamon::declval<CV&>().base())>::value, "");
		static_assert(hamon::is_same<V, decltype(hamon::declval<CV&&>().base())>::value, "");
		static_assert(hamon::is_same<V, decltype(hamon::declval<CV const&>().base())>::value, "");
		static_assert(hamon::is_same<V, decltype(hamon::declval<CV const&&>().base())>::value, "");
	}
	{
		using V = MoveOnlyInputView<int>;
		using CV = hamon::ranges::chunk_view<V>;

		static_assert(!has_base<CV&>::value, "");
		static_assert( has_base<CV&&>::value, "");
		static_assert(!has_base<CV const&>::value, "");
		static_assert(!has_base<CV const&&>::value, "");

//		static_assert(hamon::is_same<V, decltype(hamon::declval<CV&>().base())>::value, "");
		static_assert(hamon::is_same<V, decltype(hamon::declval<CV&&>().base())>::value, "");
//		static_assert(hamon::is_same<V, decltype(hamon::declval<CV const&>().base())>::value, "");
//		static_assert(hamon::is_same<V, decltype(hamon::declval<CV const&&>().base())>::value, "");
	}
	{
		using V = MoveOnlyForwardView<int>;
		using CV = hamon::ranges::chunk_view<V>;

		static_assert(!has_base<CV&>::value, "");
		static_assert( has_base<CV&&>::value, "");
		static_assert(!has_base<CV const&>::value, "");
		static_assert(!has_base<CV const&&>::value, "");

//		static_assert(hamon::is_same<V, decltype(hamon::declval<CV&>().base())>::value, "");
		static_assert(hamon::is_same<V, decltype(hamon::declval<CV&&>().base())>::value, "");
//		static_assert(hamon::is_same<V, decltype(hamon::declval<CV const&>().base())>::value, "");
//		static_assert(hamon::is_same<V, decltype(hamon::declval<CV const&&>().base())>::value, "");
	}
	return true;
}

template <template <typename> class View>
HAMON_CXX14_CONSTEXPR bool test01()
{
	using V = View<int>;
	using CV = hamon::ranges::chunk_view<V>;

	int a[] = {1,2,3,4,5};
	V v(a);
	CV cv{v, 3};
	{
		auto b = cv.base();
		static_assert(hamon::is_same<decltype(b), decltype(v)>::value, "");
		VERIFY(b.begin() == v.begin());
	}
	{
		auto b = hamon::move(cv).base();
		static_assert(hamon::is_same<decltype(b), decltype(v)>::value, "");
		VERIFY(b.begin() == v.begin());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ChunkViewBaseTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01<test_input_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01<test_forward_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01<test_bidirectional_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01<test_random_access_view>());
}

}	// namespace base_test
}	// namespace chunk_view_test
}	// namespace hamon_ranges_test
