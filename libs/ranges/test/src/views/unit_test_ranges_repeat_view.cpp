/**
 *	@file	unit_test_ranges_repeat_view.cpp
 *
 *	@brief	ranges::repeat_view のテスト
 */

#include <hamon/ranges/views/repeat_view.hpp>
#include <hamon/ranges/concepts.hpp>
#include <hamon/compare.hpp>
#include <hamon/cstddef.hpp>
#include <hamon/iterator.hpp>
#include <hamon/pair.hpp>	// piecewise_construct_t
#include <hamon/tuple.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_ranges_test
{
namespace repeat_view_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct MoveOnly
{
	MoveOnly() = delete;
	MoveOnly(MoveOnly const&) = delete;
	MoveOnly(MoveOnly &&) = default;
	MoveOnly& operator=(MoveOnly const&) = delete;
	MoveOnly& operator=(MoveOnly &&) = default;
};

struct ThrowOnMoveCtor
{
	ThrowOnMoveCtor() = default;
	ThrowOnMoveCtor(ThrowOnMoveCtor const&) = default;
	ThrowOnMoveCtor(ThrowOnMoveCtor &&) {}
	ThrowOnMoveCtor& operator=(ThrowOnMoveCtor const&) = default;
	ThrowOnMoveCtor& operator=(ThrowOnMoveCtor &&) = default;
};

struct ThrowOnCopyCtor
{
	ThrowOnCopyCtor() = default;
	ThrowOnCopyCtor(ThrowOnCopyCtor const&) {}
	ThrowOnCopyCtor(ThrowOnCopyCtor &&) = default;
	ThrowOnCopyCtor& operator=(ThrowOnCopyCtor const&) = default;
	ThrowOnCopyCtor& operator=(ThrowOnCopyCtor &&) = default;
};

struct ThrowOnDefaultCtor
{
	ThrowOnDefaultCtor() {}
};

struct Point
{
	float x, y;
	constexpr Point(float x_, float y_) : x(x_), y(y_) {}
};

// requirements
HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using V = hamon::ranges::repeat_view<Point>;
		static_assert(!hamon::is_constructible<V, hamon::piecewise_construct_t, hamon::tuple<int>>::value, "");
		static_assert( hamon::is_constructible<V, hamon::piecewise_construct_t, hamon::tuple<int, int>>::value, "");
		static_assert(!hamon::is_constructible<V, hamon::piecewise_construct_t, hamon::tuple<int, int, int>>::value, "");

		static_assert(!hamon::is_constructible<V, hamon::piecewise_construct_t, hamon::tuple<int, int>, hamon::tuple<int>>::value, "");
		static_assert(!hamon::is_constructible<V, hamon::piecewise_construct_t, hamon::tuple<int, int>, hamon::tuple<int, int>>::value, "");
		static_assert(!hamon::is_constructible<V, hamon::piecewise_construct_t, hamon::tuple<int, int>, hamon::tuple<int, int, int>>::value, "");

		static_assert(!hamon::is_implicitly_constructible<V, hamon::piecewise_construct_t, hamon::tuple<int, int>>::value, "");
#if !defined(HAMON_USE_STD_RANGES_REPEAT_VIEW)
		static_assert(!hamon::is_nothrow_constructible<V, hamon::piecewise_construct_t, hamon::tuple<int, int>>::value, "");
#endif
	}
	{
		using V = hamon::ranges::repeat_view<Point, int>;
		static_assert(!hamon::is_constructible<V, hamon::piecewise_construct_t, hamon::tuple<int>>::value, "");
		static_assert( hamon::is_constructible<V, hamon::piecewise_construct_t, hamon::tuple<int, int>>::value, "");
		static_assert(!hamon::is_constructible<V, hamon::piecewise_construct_t, hamon::tuple<int, int, int>>::value, "");

		static_assert( hamon::is_constructible<V, hamon::piecewise_construct_t, hamon::tuple<int, int>, hamon::tuple<int>>::value, "");
		static_assert(!hamon::is_constructible<V, hamon::piecewise_construct_t, hamon::tuple<int, int>, hamon::tuple<int, int>>::value, "");
		static_assert(!hamon::is_constructible<V, hamon::piecewise_construct_t, hamon::tuple<int, int>, hamon::tuple<int, int, int>>::value, "");

		static_assert(!hamon::is_implicitly_constructible<V, hamon::piecewise_construct_t, hamon::tuple<int, int>>::value, "");
		static_assert(!hamon::is_implicitly_constructible<V, hamon::piecewise_construct_t, hamon::tuple<int, int>, hamon::tuple<int>>::value, "");
#if !defined(HAMON_USE_STD_RANGES_REPEAT_VIEW)
		static_assert(!hamon::is_nothrow_constructible<V, hamon::piecewise_construct_t, hamon::tuple<int, int>>::value, "");
		static_assert(!hamon::is_nothrow_constructible<V, hamon::piecewise_construct_t, hamon::tuple<int, int>, hamon::tuple<int>>::value, "");
#endif
	}
	{
		using V = hamon::ranges::repeat_view<int>;
		static_assert( hamon::is_constructible<V, hamon::piecewise_construct_t, hamon::tuple<int>>::value, "");
		static_assert(!hamon::is_implicitly_constructible<V, hamon::piecewise_construct_t, hamon::tuple<int>>::value, "");
#if !defined(HAMON_USE_STD_RANGES_REPEAT_VIEW)
		static_assert( hamon::is_nothrow_constructible<V, hamon::piecewise_construct_t, hamon::tuple<int>>::value, "");
#endif
	}
	{
		using V = hamon::ranges::repeat_view<MoveOnly>;
		static_assert(!hamon::is_default_constructible<V>::value, "");
		static_assert(!hamon::is_nothrow_default_constructible<V>::value, "");
		static_assert(!hamon::is_constructible<V, int>::value, "");
		static_assert(!hamon::is_constructible<V, MoveOnly const&>::value, "");
		static_assert( hamon::is_constructible<V, MoveOnly &&>::value, "");
#if !defined(HAMON_USE_STD_RANGES_REPEAT_VIEW)
		static_assert( hamon::is_nothrow_constructible<V, MoveOnly &&>::value, "");
#endif
		static_assert( hamon::ranges::view_t<V>::value, "");
		static_assert( hamon::ranges::range_t<V>::value, "");
		static_assert(!hamon::ranges::sized_range_t<V>::value, "");
		static_assert(!hamon::ranges::common_range_t<V>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<V>::value, "");
		static_assert( hamon::ranges::random_access_range_t<V>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<V>::value, "");

		static_assert(noexcept(hamon::declval<V>().begin()), "");
		static_assert(noexcept(hamon::declval<V>().end()), "");

		using I = decltype(hamon::declval<V>().begin());
		static_assert( hamon::is_same<typename I::iterator_concept, hamon::random_access_iterator_tag>::value, "");
		static_assert( hamon::is_same<typename I::iterator_category, hamon::random_access_iterator_tag>::value, "");
		static_assert( hamon::is_same<typename I::value_type, MoveOnly>::value, "");
		static_assert( hamon::is_same<typename I::difference_type, hamon::ptrdiff_t>::value, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert( hamon::three_way_comparable<I>, "");
#endif

		using D = typename I::difference_type;
		static_assert(noexcept(*hamon::declval<I>()), "");
		static_assert(noexcept(++hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>()++), "");
		static_assert(noexcept(--hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>()--), "");
		static_assert(noexcept(hamon::declval<I>() += hamon::declval<D>()), "");
		static_assert(noexcept(hamon::declval<I>() -= hamon::declval<D>()), "");
		static_assert(noexcept(hamon::declval<I>()[hamon::declval<D>()]), "");
		static_assert(noexcept(hamon::declval<I>() == hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>() != hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>() <  hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>() <= hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>() >  hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>() >= hamon::declval<I>()), "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert(noexcept(hamon::declval<I>() <=> hamon::declval<I>()), "");
#endif
		static_assert(noexcept(hamon::declval<I>() + hamon::declval<D>()), "");
		static_assert(noexcept(hamon::declval<D>() + hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>() - hamon::declval<D>()), "");
		static_assert(noexcept(hamon::declval<I>() - hamon::declval<I>()), "");

		using S = decltype(hamon::declval<V>().end());
		static_assert( hamon::same_as_t<S, hamon::unreachable_sentinel_t>::value, "");
		static_assert( noexcept(hamon::declval<V>().end()), "");
	}
	{
		using V = hamon::ranges::repeat_view<ThrowOnMoveCtor>;
		static_assert( hamon::is_default_constructible<V>::value, "");
		static_assert( hamon::is_nothrow_default_constructible<V>::value, "");
		static_assert(!hamon::is_constructible<V, int>::value, "");
		static_assert( hamon::is_constructible<V, ThrowOnMoveCtor const&>::value, "");
		static_assert( hamon::is_constructible<V, ThrowOnMoveCtor &&>::value, "");
#if !defined(HAMON_USE_STD_RANGES_REPEAT_VIEW)
		static_assert( hamon::is_nothrow_constructible<V, ThrowOnMoveCtor const&>::value, "");
		static_assert(!hamon::is_nothrow_constructible<V, ThrowOnMoveCtor &&>::value, "");
#endif
		static_assert( hamon::ranges::view_t<V>::value, "");
		static_assert( hamon::ranges::range_t<V>::value, "");
		static_assert(!hamon::ranges::sized_range_t<V>::value, "");
		static_assert(!hamon::ranges::common_range_t<V>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<V>::value, "");
		static_assert( hamon::ranges::random_access_range_t<V>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<V>::value, "");

		static_assert(noexcept(hamon::declval<V>().begin()), "");
		static_assert(noexcept(hamon::declval<V>().end()), "");

		using I = decltype(hamon::declval<V>().begin());
		static_assert( hamon::is_same<typename I::iterator_concept, hamon::random_access_iterator_tag>::value, "");
		static_assert( hamon::is_same<typename I::iterator_category, hamon::random_access_iterator_tag>::value, "");
		static_assert( hamon::is_same<typename I::value_type, ThrowOnMoveCtor>::value, "");
		static_assert( hamon::is_same<typename I::difference_type, hamon::ptrdiff_t>::value, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert( hamon::three_way_comparable<I>, "");
#endif

		using D = typename I::difference_type;
		static_assert(noexcept(*hamon::declval<I>()), "");
		static_assert(noexcept(++hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>()++), "");
		static_assert(noexcept(--hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>()--), "");
		static_assert(noexcept(hamon::declval<I>() += hamon::declval<D>()), "");
		static_assert(noexcept(hamon::declval<I>() -= hamon::declval<D>()), "");
		static_assert(noexcept(hamon::declval<I>()[hamon::declval<D>()]), "");
		static_assert(noexcept(hamon::declval<I>() == hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>() != hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>() <  hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>() <= hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>() >  hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>() >= hamon::declval<I>()), "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert(noexcept(hamon::declval<I>() <=> hamon::declval<I>()), "");
#endif
		static_assert(noexcept(hamon::declval<I>() + hamon::declval<D>()), "");
		static_assert(noexcept(hamon::declval<D>() + hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>() - hamon::declval<D>()), "");
		static_assert(noexcept(hamon::declval<I>() - hamon::declval<I>()), "");

		using S = decltype(hamon::declval<V>().end());
		static_assert( hamon::same_as_t<S, hamon::unreachable_sentinel_t>::value, "");
		static_assert( noexcept(hamon::declval<V>().end()), "");
	}
	{
		using V = hamon::ranges::repeat_view<ThrowOnCopyCtor>;
		static_assert( hamon::is_default_constructible<V>::value, "");
		static_assert( hamon::is_nothrow_default_constructible<V>::value, "");
		static_assert(!hamon::is_constructible<V, int>::value, "");
		static_assert( hamon::is_constructible<V, ThrowOnCopyCtor const&>::value, "");
		static_assert( hamon::is_constructible<V, ThrowOnCopyCtor &&>::value, "");
#if !defined(HAMON_USE_STD_RANGES_REPEAT_VIEW)
		static_assert(!hamon::is_nothrow_constructible<V, ThrowOnCopyCtor const&>::value, "");
		static_assert( hamon::is_nothrow_constructible<V, ThrowOnCopyCtor &&>::value, "");
#endif
		static_assert( hamon::ranges::view_t<V>::value, "");
		static_assert( hamon::ranges::range_t<V>::value, "");
		static_assert(!hamon::ranges::sized_range_t<V>::value, "");
		static_assert(!hamon::ranges::common_range_t<V>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<V>::value, "");
		static_assert( hamon::ranges::random_access_range_t<V>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<V>::value, "");

		static_assert(noexcept(hamon::declval<V>().begin()), "");
		static_assert(noexcept(hamon::declval<V>().end()), "");

		using I = decltype(hamon::declval<V>().begin());
		static_assert( hamon::is_same<typename I::iterator_concept, hamon::random_access_iterator_tag>::value, "");
		static_assert( hamon::is_same<typename I::iterator_category, hamon::random_access_iterator_tag>::value, "");
		static_assert( hamon::is_same<typename I::value_type, ThrowOnCopyCtor>::value, "");
		static_assert( hamon::is_same<typename I::difference_type, hamon::ptrdiff_t>::value, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert( hamon::three_way_comparable<I>, "");
#endif

		using D = typename I::difference_type;
		static_assert(noexcept(*hamon::declval<I>()), "");
		static_assert(noexcept(++hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>()++), "");
		static_assert(noexcept(--hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>()--), "");
		static_assert(noexcept(hamon::declval<I>() += hamon::declval<D>()), "");
		static_assert(noexcept(hamon::declval<I>() -= hamon::declval<D>()), "");
		static_assert(noexcept(hamon::declval<I>()[hamon::declval<D>()]), "");
		static_assert(noexcept(hamon::declval<I>() == hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>() != hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>() <  hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>() <= hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>() >  hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>() >= hamon::declval<I>()), "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert(noexcept(hamon::declval<I>() <=> hamon::declval<I>()), "");
#endif
		static_assert(noexcept(hamon::declval<I>() + hamon::declval<D>()), "");
		static_assert(noexcept(hamon::declval<D>() + hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>() - hamon::declval<D>()), "");
		static_assert(noexcept(hamon::declval<I>() - hamon::declval<I>()), "");

		using S = decltype(hamon::declval<V>().end());
		static_assert( hamon::same_as_t<S, hamon::unreachable_sentinel_t>::value, "");
		static_assert( noexcept(hamon::declval<V>().end()), "");
	}
	{
		using V = hamon::ranges::repeat_view<ThrowOnDefaultCtor>;
		static_assert( hamon::is_default_constructible<V>::value, "");
		static_assert(!hamon::is_nothrow_default_constructible<V>::value, "");
		static_assert(!hamon::is_constructible<V, int>::value, "");
		static_assert( hamon::is_constructible<V, ThrowOnDefaultCtor const&>::value, "");
		static_assert( hamon::is_constructible<V, ThrowOnDefaultCtor &&>::value, "");
		static_assert( hamon::ranges::view_t<V>::value, "");
		static_assert( hamon::ranges::range_t<V>::value, "");
		static_assert(!hamon::ranges::sized_range_t<V>::value, "");
		static_assert(!hamon::ranges::common_range_t<V>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<V>::value, "");
		static_assert( hamon::ranges::random_access_range_t<V>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<V>::value, "");

		static_assert(noexcept(hamon::declval<V>().begin()), "");
		static_assert(noexcept(hamon::declval<V>().end()), "");

		using I = decltype(hamon::declval<V>().begin());
		static_assert( hamon::is_same<typename I::iterator_concept, hamon::random_access_iterator_tag>::value, "");
		static_assert( hamon::is_same<typename I::iterator_category, hamon::random_access_iterator_tag>::value, "");
		static_assert( hamon::is_same<typename I::value_type, ThrowOnDefaultCtor>::value, "");
		static_assert( hamon::is_same<typename I::difference_type, hamon::ptrdiff_t>::value, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert( hamon::three_way_comparable<I>, "");
#endif

		using D = typename I::difference_type;
		static_assert(noexcept(*hamon::declval<I>()), "");
		static_assert(noexcept(++hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>()++), "");
		static_assert(noexcept(--hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>()--), "");
		static_assert(noexcept(hamon::declval<I>() += hamon::declval<D>()), "");
		static_assert(noexcept(hamon::declval<I>() -= hamon::declval<D>()), "");
		static_assert(noexcept(hamon::declval<I>()[hamon::declval<D>()]), "");
		static_assert(noexcept(hamon::declval<I>() == hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>() != hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>() <  hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>() <= hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>() >  hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>() >= hamon::declval<I>()), "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert(noexcept(hamon::declval<I>() <=> hamon::declval<I>()), "");
#endif
		static_assert(noexcept(hamon::declval<I>() + hamon::declval<D>()), "");
		static_assert(noexcept(hamon::declval<D>() + hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>() - hamon::declval<D>()), "");
		static_assert(noexcept(hamon::declval<I>() - hamon::declval<I>()), "");

		using S = decltype(hamon::declval<V>().end());
		static_assert( hamon::same_as_t<S, hamon::unreachable_sentinel_t>::value, "");
		static_assert( noexcept(hamon::declval<V>().end()), "");
	}
	{
		using V = hamon::ranges::repeat_view<int>;
		static_assert( hamon::is_default_constructible<V>::value, "");
		static_assert( hamon::is_nothrow_default_constructible<V>::value, "");
		static_assert( hamon::is_constructible<V, int>::value, "");
		static_assert(!hamon::is_constructible<V, int, int>::value, "");
		static_assert(!hamon::is_implicitly_constructible<V, int>::value, "");
		static_assert( hamon::ranges::view_t<V>::value, "");
		static_assert( hamon::ranges::range_t<V>::value, "");
		static_assert(!hamon::ranges::sized_range_t<V>::value, "");
		static_assert(!hamon::ranges::common_range_t<V>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<V>::value, "");
		static_assert( hamon::ranges::random_access_range_t<V>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<V>::value, "");

		static_assert(noexcept(hamon::declval<V>().begin()), "");
		static_assert(noexcept(hamon::declval<V>().end()), "");

		using I = decltype(hamon::declval<V>().begin());
		static_assert( hamon::is_same<typename I::iterator_concept, hamon::random_access_iterator_tag>::value, "");
		static_assert( hamon::is_same<typename I::iterator_category, hamon::random_access_iterator_tag>::value, "");
		static_assert( hamon::is_same<typename I::value_type, int>::value, "");
		static_assert( hamon::is_same<typename I::difference_type, hamon::ptrdiff_t>::value, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert( hamon::three_way_comparable<I>, "");
#endif

		using D = typename I::difference_type;
		static_assert(noexcept(*hamon::declval<I>()), "");
		static_assert(noexcept(++hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>()++), "");
		static_assert(noexcept(--hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>()--), "");
		static_assert(noexcept(hamon::declval<I>() += hamon::declval<D>()), "");
		static_assert(noexcept(hamon::declval<I>() -= hamon::declval<D>()), "");
		static_assert(noexcept(hamon::declval<I>()[hamon::declval<D>()]), "");
		static_assert(noexcept(hamon::declval<I>() == hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>() != hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>() <  hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>() <= hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>() >  hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>() >= hamon::declval<I>()), "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert(noexcept(hamon::declval<I>() <=> hamon::declval<I>()), "");
#endif
		static_assert(noexcept(hamon::declval<I>() + hamon::declval<D>()), "");
		static_assert(noexcept(hamon::declval<D>() + hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>() - hamon::declval<D>()), "");
		static_assert(noexcept(hamon::declval<I>() - hamon::declval<I>()), "");

		using S = decltype(hamon::declval<V>().end());
		static_assert( hamon::same_as_t<S, hamon::unreachable_sentinel_t>::value, "");
		static_assert( noexcept(hamon::declval<V>().end()), "");
	}
	{
		using V = hamon::ranges::repeat_view<int, int>;
		static_assert( hamon::is_default_constructible<V>::value, "");
		static_assert( hamon::is_nothrow_default_constructible<V>::value, "");
		static_assert( hamon::is_constructible<V, int>::value, "");
		static_assert( hamon::is_constructible<V, int, int>::value, "");
		static_assert(!hamon::is_implicitly_constructible<V, int>::value, "");
		static_assert(!hamon::is_implicitly_constructible<V, int, int>::value, "");
		static_assert( hamon::ranges::view_t<V>::value, "");
		static_assert( hamon::ranges::range_t<V>::value, "");
		static_assert( hamon::ranges::sized_range_t<V>::value, "");
		static_assert( hamon::ranges::common_range_t<V>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<V>::value, "");
		static_assert( hamon::ranges::random_access_range_t<V>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<V>::value, "");

		static_assert(noexcept(hamon::declval<V>().begin()), "");
		static_assert(noexcept(hamon::declval<V>().end()), "");
		static_assert(noexcept(hamon::declval<V>().size()), "");

		using I = decltype(hamon::declval<V>().begin());
		static_assert( hamon::is_same<typename I::iterator_concept, hamon::random_access_iterator_tag>::value, "");
		static_assert( hamon::is_same<typename I::iterator_category, hamon::random_access_iterator_tag>::value, "");
		static_assert( hamon::is_same<typename I::value_type, int>::value, "");
		static_assert( hamon::is_same<typename I::difference_type, int>::value, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert( hamon::three_way_comparable<I>, "");
#endif

		using D = typename I::difference_type;
		static_assert(noexcept(*hamon::declval<I>()), "");
		static_assert(noexcept(++hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>()++), "");
		static_assert(noexcept(--hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>()--), "");
		static_assert(noexcept(hamon::declval<I>() += hamon::declval<D>()), "");
		static_assert(noexcept(hamon::declval<I>() -= hamon::declval<D>()), "");
		static_assert(noexcept(hamon::declval<I>()[hamon::declval<D>()]), "");
		static_assert(noexcept(hamon::declval<I>() == hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>() != hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>() <  hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>() <= hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>() >  hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>() >= hamon::declval<I>()), "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert(noexcept(hamon::declval<I>() <=> hamon::declval<I>()), "");
#endif
		static_assert(noexcept(hamon::declval<I>() + hamon::declval<D>()), "");
		static_assert(noexcept(hamon::declval<D>() + hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>() - hamon::declval<D>()), "");
		static_assert(noexcept(hamon::declval<I>() - hamon::declval<I>()), "");

		using S = decltype(hamon::declval<V>().end());
		static_assert( hamon::same_as_t<S, I>::value, "");
	}
	{
		using V = hamon::ranges::repeat_view<int, long>;
		static_assert( hamon::is_default_constructible<V>::value, "");
		static_assert( hamon::is_nothrow_default_constructible<V>::value, "");
		static_assert( hamon::ranges::view_t<V>::value, "");
		static_assert( hamon::ranges::range_t<V>::value, "");
		static_assert( hamon::ranges::sized_range_t<V>::value, "");
		static_assert( hamon::ranges::common_range_t<V>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<V>::value, "");
		static_assert( hamon::ranges::random_access_range_t<V>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<V>::value, "");

		static_assert(noexcept(hamon::declval<V>().begin()), "");
		static_assert(noexcept(hamon::declval<V>().end()), "");
		static_assert(noexcept(hamon::declval<V>().size()), "");

		using I = decltype(hamon::declval<V>().begin());
		static_assert( hamon::is_same<typename I::iterator_concept, hamon::random_access_iterator_tag>::value, "");
		static_assert( hamon::is_same<typename I::iterator_category, hamon::random_access_iterator_tag>::value, "");
		static_assert( hamon::is_same<typename I::value_type, int>::value, "");
		static_assert( hamon::is_same<typename I::difference_type, long>::value, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert( hamon::three_way_comparable<I>, "");
#endif

		using D = typename I::difference_type;
		static_assert(noexcept(*hamon::declval<I>()), "");
		static_assert(noexcept(++hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>()++), "");
		static_assert(noexcept(--hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>()--), "");
		static_assert(noexcept(hamon::declval<I>() += hamon::declval<D>()), "");
		static_assert(noexcept(hamon::declval<I>() -= hamon::declval<D>()), "");
		static_assert(noexcept(hamon::declval<I>()[hamon::declval<D>()]), "");
		static_assert(noexcept(hamon::declval<I>() == hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>() != hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>() <  hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>() <= hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>() >  hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>() >= hamon::declval<I>()), "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert(noexcept(hamon::declval<I>() <=> hamon::declval<I>()), "");
#endif
		static_assert(noexcept(hamon::declval<I>() + hamon::declval<D>()), "");
		static_assert(noexcept(hamon::declval<D>() + hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>() - hamon::declval<D>()), "");
		static_assert(noexcept(hamon::declval<I>() - hamon::declval<I>()), "");

		using S = decltype(hamon::declval<V>().end());
		static_assert( hamon::same_as_t<S, I>::value, "");
	}
	{
		using V = hamon::ranges::repeat_view<long, int>;
		static_assert( hamon::is_default_constructible<V>::value, "");
		static_assert( hamon::is_nothrow_default_constructible<V>::value, "");
		static_assert( hamon::ranges::view_t<V>::value, "");
		static_assert( hamon::ranges::range_t<V>::value, "");
		static_assert( hamon::ranges::sized_range_t<V>::value, "");
		static_assert( hamon::ranges::common_range_t<V>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<V>::value, "");
		static_assert( hamon::ranges::random_access_range_t<V>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<V>::value, "");

		static_assert(noexcept(hamon::declval<V>().begin()), "");
		static_assert(noexcept(hamon::declval<V>().end()), "");
		static_assert(noexcept(hamon::declval<V>().size()), "");

		using I = decltype(hamon::declval<V>().begin());
		static_assert( hamon::is_same<typename I::iterator_concept, hamon::random_access_iterator_tag>::value, "");
		static_assert( hamon::is_same<typename I::iterator_category, hamon::random_access_iterator_tag>::value, "");
		static_assert( hamon::is_same<typename I::value_type, long>::value, "");
		static_assert( hamon::is_same<typename I::difference_type, int>::value, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert( hamon::three_way_comparable<I>, "");
#endif

		using D = typename I::difference_type;
		static_assert(noexcept(*hamon::declval<I>()), "");
		static_assert(noexcept(++hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>()++), "");
		static_assert(noexcept(--hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>()--), "");
		static_assert(noexcept(hamon::declval<I>() += hamon::declval<D>()), "");
		static_assert(noexcept(hamon::declval<I>() -= hamon::declval<D>()), "");
		static_assert(noexcept(hamon::declval<I>()[hamon::declval<D>()]), "");
		static_assert(noexcept(hamon::declval<I>() == hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>() != hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>() <  hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>() <= hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>() >  hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>() >= hamon::declval<I>()), "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert(noexcept(hamon::declval<I>() <=> hamon::declval<I>()), "");
#endif
		static_assert(noexcept(hamon::declval<I>() + hamon::declval<D>()), "");
		static_assert(noexcept(hamon::declval<D>() + hamon::declval<I>()), "");
		static_assert(noexcept(hamon::declval<I>() - hamon::declval<D>()), "");
		static_assert(noexcept(hamon::declval<I>() - hamon::declval<I>()), "");

		using S = decltype(hamon::declval<V>().end());
		static_assert( hamon::same_as_t<S, I>::value, "");
	}
	return true;
}

// hamon::ranges::repeat_view<int>
HAMON_CXX14_CONSTEXPR bool test01()
{
	{
		hamon::ranges::repeat_view<int> v{};
		auto it = v.begin();
		VERIFY(*it == 0);
		VERIFY(it != v.end());
		++it;
		VERIFY(*it == 0);
		VERIFY(it != v.end());
	}
	{
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
		hamon::ranges::repeat_view v{42};
#else
		hamon::ranges::repeat_view<int> v{42};
#endif

		auto it = v.begin();
		VERIFY(*it == 42);
		VERIFY(it != v.end());
		++it;
		VERIFY(*it == 42);
		VERIFY(it != v.end());
	}
	{
		auto v = hamon::ranges::views::repeat(43);
		static_assert(hamon::same_as_t<decltype(v), hamon::ranges::repeat_view<int>>::value, "");

		auto it = v.begin();
		VERIFY(*it == 43);
		VERIFY(it != v.end());
		++it;
		VERIFY(*it == 43);
		VERIFY(it != v.end());
	}

	return true;
}

// hamon::ranges::repeat_view<int, int>
HAMON_CXX14_CONSTEXPR bool test02()
{
	{
		hamon::ranges::repeat_view<int, int> v{};
		VERIFY(v.size() == 0);

		auto it = v.begin();
		VERIFY(*it == 0);
		VERIFY(it == v.end());
	}
	{
		const int a = 42;
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
		hamon::ranges::repeat_view v{a, 2};
#else
		hamon::ranges::repeat_view<int, int> v{a, 2};
#endif

		VERIFY(v.size() == 2);

		auto it = v.begin();
		VERIFY(*it == 42);
		VERIFY(it != v.end());
		++it;
		VERIFY(*it == 42);
		VERIFY(it != v.end());
		++it;
		VERIFY(it == v.end());
	}
	{
		auto v = hamon::ranges::views::repeat(43, 3);
		static_assert(hamon::same_as_t<decltype(v), hamon::ranges::repeat_view<int, int>>::value, "");

		VERIFY(v.size() == 3);

		auto it = v.begin();
		VERIFY(*it == 43);
		VERIFY(it != v.end());
		++it;
		VERIFY(*it == 43);
		VERIFY(it != v.end());
		++it;
		VERIFY(*it == 43);
		VERIFY(it != v.end());
		++it;
		VERIFY(it == v.end());
	}

	return true;
}

// iterator
HAMON_CXX14_CONSTEXPR bool test03()
{
	{
		auto v = hamon::ranges::views::repeat(13);
		auto it = v.begin();
		VERIFY(*it == 13);
		VERIFY(it == v.begin());
		VERIFY(it != v.end());
		auto t1 = ++it;
		VERIFY(*it == 13);
		VERIFY(it == v.begin() + 1);
		VERIFY(it != v.end());
		VERIFY(t1 == it);
		auto t2 = it++;
		VERIFY(*it == 13);
		VERIFY(it == v.begin() + 2);
		VERIFY(it != v.end());
		VERIFY(t2 != it);
		auto t3 = --it;
		VERIFY(*it == 13);
		VERIFY(it == v.begin() + 1);
		VERIFY(it != v.end());
		VERIFY(t3 == it);
		auto t4 = it--;
		VERIFY(*it == 13);
		VERIFY(it == v.begin() + 0);
		VERIFY(it != v.end());
		VERIFY(t4 != it);
		auto t5 = it += 10;
		VERIFY(*it == 13);
		VERIFY(it == v.begin() + 10);
		VERIFY(it != v.end());
		VERIFY(t5 == it);
		auto t6 = it -= 3;
		VERIFY(*it == 13);
		VERIFY(it == v.begin() + 7);
		VERIFY(it != v.end());
		VERIFY(t6 == it);

		VERIFY(it[0] == 13);
		VERIFY(it[1] == 13);
		VERIFY(it[2] == 13);

		auto t7 = it + 100;
		VERIFY(t7 == v.begin() + 107);
		VERIFY(*t7 == 13);

		auto t8 = 123 + it;
		VERIFY(t8 == v.begin() + 130);
		VERIFY(*t8 == 13);

		auto t9 = it - 2;
		VERIFY(t9 == v.begin() + 5);
		VERIFY(*t9 == 13);

		VERIFY(it - v.begin() == 7);
		VERIFY(v.begin() - it == -7);

		VERIFY(!(t7 == t8));
		VERIFY( (t7 != t8));
		VERIFY( (t7 <  t8));
		VERIFY( (t7 <= t8));
		VERIFY(!(t7 >  t8));
		VERIFY(!(t7 >= t8));

		VERIFY(!(t7 == t9));
		VERIFY( (t7 != t9));
		VERIFY(!(t7 <  t9));
		VERIFY(!(t7 <= t9));
		VERIFY( (t7 >  t9));
		VERIFY( (t7 >= t9));

		VERIFY( (t1 == t3));
		VERIFY(!(t1 != t3));
		VERIFY(!(t1 <  t3));
		VERIFY( (t1 <= t3));
		VERIFY(!(t1 >  t3));
		VERIFY( (t1 >= t3));
	}
	{
		auto v = hamon::ranges::views::repeat(14, 3);
		auto it = v.begin();
		VERIFY(!(it + 0 == v.end()));
		VERIFY(!(it + 1 == v.end()));
		VERIFY(!(it + 2 == v.end()));
		VERIFY( (it + 3 == v.end()));
		VERIFY(it[0] == 14);
		VERIFY(it[1] == 14);
		VERIFY(it[2] == 14);

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		VERIFY(hamon::is_eq(it <=> v.begin()));
		VERIFY(hamon::is_neq(it <=> v.end()));
#endif

		it += 3;
		VERIFY( (it - 3 == v.begin()));
		VERIFY(!(it - 2 == v.begin()));

		--it;
		VERIFY( (it - 2 == v.begin()));
		VERIFY(!(it - 1 == v.begin()));
	}
	return true;
}

// piecewise_construct
HAMON_CXX14_CONSTEXPR bool test04()
{
	{
		hamon::ranges::repeat_view<Point, int> const v
		{
			hamon::piecewise_construct,
			hamon::make_tuple(1.0f, 2.0f),
			hamon::make_tuple(4)
		};

		int count = 0;
		for (auto t : v)
		{
			VERIFY(t.x == 1.0f);
			VERIFY(t.y == 2.0f);
			++count;
		}
		VERIFY(count == 4);
	}
	{
		hamon::ranges::repeat_view<Point> const v
		{
			hamon::piecewise_construct,
			hamon::make_tuple(3.0f, 4.0f)
		};

		auto it = v.begin();
		VERIFY((*it).x == 3.0f);
		VERIFY((*it).y == 4.0f);
		++it;
		VERIFY((*it).x == 3.0f);
		VERIFY((*it).y == 4.0f);
		++it;
		VERIFY((*it).x == 3.0f);
		VERIFY((*it).y == 4.0f);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, RepeatViewTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
}

}	// namespace repeat_view_test
}	// namespace hamon_ranges_test
