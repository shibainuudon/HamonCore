/**
 *	@file	unit_test_ranges_iota_view.cpp
 *
 *	@brief	ranges::iota_view のテスト
 */

#include <hamon/ranges/factories/iota_view.hpp>
#include <hamon/ranges/concepts.hpp>
#include <hamon/compare/is_eq.hpp>
#include <hamon/compare/is_neq.hpp>
#include <hamon/compare/concepts/three_way_comparable.hpp>
#include <hamon/concepts.hpp>
#include <hamon/concepts/detail/weakly_equality_comparable_with.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/iterator.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <hamon/vector.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace iota_view_test
{

template <typename T, typename = void>
struct has_iterator_category
	: public hamon::false_type {};

template <typename T>
struct has_iterator_category<T, hamon::void_t<typename T::iterator_category>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct NoDefaultCtor
{
	NoDefaultCtor() = delete;

	using difference_type = hamon::ptrdiff_t;
	HAMON_CXX14_CONSTEXPR NoDefaultCtor& operator++() { return *this; }
	HAMON_CXX14_CONSTEXPR void           operator++(int);
};

struct ThrowOnDefaultCtor
{
	ThrowOnDefaultCtor() {}

	using difference_type = hamon::ptrdiff_t;
	HAMON_CXX14_CONSTEXPR ThrowOnDefaultCtor& operator++() { return *this; }
	HAMON_CXX14_CONSTEXPR void                operator++(int);
};

struct ThrowOnMoveCtor
{
	ThrowOnMoveCtor() = default;
	ThrowOnMoveCtor(ThrowOnMoveCtor const&) = default;
	ThrowOnMoveCtor(ThrowOnMoveCtor&&) {}
	ThrowOnMoveCtor& operator=(ThrowOnMoveCtor const&) = default;
	ThrowOnMoveCtor& operator=(ThrowOnMoveCtor&&) {return *this;}

	using difference_type = hamon::ptrdiff_t;
	HAMON_CXX14_CONSTEXPR ThrowOnMoveCtor& operator++() { return *this; }
	HAMON_CXX14_CONSTEXPR void             operator++(int);
};

static_assert( hamon::is_default_constructible<hamon::ranges::iota_view<int>>::value, "");
static_assert(!hamon::is_default_constructible<hamon::ranges::iota_view<NoDefaultCtor>>::value, "");
static_assert( hamon::is_default_constructible<hamon::ranges::iota_view<ThrowOnDefaultCtor>>::value, "");
static_assert( hamon::is_default_constructible<hamon::ranges::iota_view<int, int>>::value, "");

static_assert( hamon::is_constructible<hamon::ranges::iota_view<int>, int>::value, "");
static_assert( hamon::is_constructible<hamon::ranges::iota_view<ThrowOnMoveCtor>, ThrowOnMoveCtor>::value, "");
static_assert( hamon::is_constructible<hamon::ranges::iota_view<int, int>, int, int>::value, "");

static_assert( hamon::is_nothrow_default_constructible<hamon::ranges::iota_view<int>>::value, "");
static_assert(!hamon::is_nothrow_default_constructible<hamon::ranges::iota_view<NoDefaultCtor>>::value, "");
static_assert(!hamon::is_nothrow_default_constructible<hamon::ranges::iota_view<ThrowOnDefaultCtor>>::value, "");
static_assert( hamon::is_nothrow_default_constructible<hamon::ranges::iota_view<int, int>>::value, "");

static_assert( hamon::is_nothrow_constructible<hamon::ranges::iota_view<int>, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::ranges::iota_view<ThrowOnMoveCtor>, ThrowOnMoveCtor>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::ranges::iota_view<int, int>, int, int>::value, "");

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename I>
concept pre_decrementable =
	requires(I i)
	{
		{ --i } -> hamon::same_as<I&>;
	};

template <typename I>
concept post_decrementable =
	requires(I i)
	{
		{ i-- } -> hamon::same_as<I>;
	};

template <typename I>
concept advanceable_forward =
	requires(I i, typename I::difference_type const n)
	{
		{ i += n } -> hamon::same_as<I&>;
	};

template <typename I>
concept advanceable_backward =
	requires(I i, typename I::difference_type const n)
	{
		{ i -= n } -> hamon::same_as<I&>;
	};

template <typename I>
concept index_accessible =
	requires(I const i, typename I::difference_type const n)
	{
		{ i[n] } -> hamon::same_as<typename I::value_type>;
	};

template <typename I>
concept addable1 =
	requires(I const i, typename I::difference_type const n)
	{
		{ i + n } -> hamon::same_as<I>;
	};

template <typename I>
concept addable2 =
	requires(I const i, typename I::difference_type const n)
	{
		{ n + i } -> hamon::same_as<I>;
	};

template <typename I>
concept subtractable1 =
	requires(I const i, typename I::difference_type const n)
	{
		{ i - n } -> hamon::same_as<I>;
	};

template <typename I, typename J, typename D = typename I::difference_type>
concept subtractable2 =
	requires(I const i, J const j)
	{
		{ i - j } -> hamon::same_as<D>;
	};

template <typename T>
concept invocable_size =
	requires(T const t)
	{
		{ t.size() } -> hamon::unsigned_integral;
	};

template <typename I>
using pre_decrementable_t = hamon::bool_constant<pre_decrementable<I>>;

template <typename I>
using post_decrementable_t = hamon::bool_constant<post_decrementable<I>>;

template <typename I>
using advanceable_forward_t = hamon::bool_constant<advanceable_forward<I>>;

template <typename I>
using advanceable_backward_t = hamon::bool_constant<advanceable_backward<I>>;

template <typename I>
using index_accessible_t = hamon::bool_constant<index_accessible<I>>;

template <typename I>
using addable1_t = hamon::bool_constant<addable1<I>>;

template <typename I>
using addable2_t = hamon::bool_constant<addable2<I>>;

template <typename I>
using subtractable1_t = hamon::bool_constant<subtractable1<I>>;

template <typename I, typename J, typename D = typename I::difference_type>
using subtractable2_t = hamon::bool_constant<subtractable2<I, J, D>>;

template <typename T>
using invocable_size_t = hamon::bool_constant<invocable_size<T>>;

#else

template <typename I>
struct pre_decrementable_impl
{
private:
	template <typename I2,
		typename R = decltype(--hamon::declval<I2>())
	>
	static auto test(int) -> hamon::bool_constant<hamon::same_as<R, I2&>>;

	template <typename I2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<I>(0));
};

template <typename I>
struct post_decrementable_impl
{
private:
	template <typename I2,
		typename R = decltype(hamon::declval<I2>()--)
	>
	static auto test(int) -> hamon::bool_constant<hamon::same_as<R, I2>>;

	template <typename I2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<I>(0));
};

template <typename I>
struct advanceable_forward_impl
{
private:
	template <typename I2,
		typename D = typename I2::difference_type,
		typename R = decltype(hamon::declval<I2>() += hamon::declval<D>())
	>
	static auto test(int) -> hamon::bool_constant<hamon::same_as<R, I2&>>;

	template <typename I2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<I>(0));
};

template <typename I>
struct advanceable_backward_impl
{
private:
	template <typename I2,
		typename D = typename I2::difference_type,
		typename R = decltype(hamon::declval<I2>() -= hamon::declval<D>())
	>
	static auto test(int) -> hamon::bool_constant<hamon::same_as<R, I2&>>;

	template <typename I2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<I>(0));
};

template <typename I>
struct index_accessible_impl
{
private:
	template <typename I2,
		typename D = typename I2::difference_type,
		typename R = decltype(hamon::declval<I2>()[hamon::declval<D>()])
	>
	static auto test(int) -> hamon::bool_constant<hamon::same_as<R, typename I2::value_type>>;

	template <typename I2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<I>(0));
};

template <typename I>
struct addable1_impl
{
private:
	template <typename I2,
		typename D = typename I2::difference_type,
		typename R = decltype(hamon::declval<I2>() + hamon::declval<D>())
	>
	static auto test(int) -> hamon::bool_constant<hamon::same_as<R, I2>>;

	template <typename I2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<I>(0));
};

template <typename I>
struct addable2_impl
{
private:
	template <typename I2,
		typename D = typename I2::difference_type,
		typename R = decltype(hamon::declval<D>() + hamon::declval<I2>())
	>
	static auto test(int) -> hamon::bool_constant<hamon::same_as<R, I2>>;

	template <typename I2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<I>(0));
};

template <typename I>
struct subtractable1_impl
{
private:
	template <typename I2,
		typename D = typename I2::difference_type,
		typename R = decltype(hamon::declval<I2>() - hamon::declval<D>())
	>
	static auto test(int) -> hamon::bool_constant<hamon::same_as<R, I2>>;

	template <typename I2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<I>(0));
};

template <typename I, typename J, typename D>
struct subtractable2_impl
{
private:
	template <typename I2, typename J2, typename D2,
		typename R = decltype(hamon::declval<I2>() - hamon::declval<J2>())
	>
	static auto test(int) -> hamon::bool_constant<hamon::same_as<R, D2>>;

	template <typename I2, typename J2, typename D2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<I, J, D>(0));
};

template <typename T>
struct invocable_size_impl
{
private:
	template <typename T2,
		typename R = decltype(hamon::declval<T2>().size())
	>
	static auto test(int) -> hamon::bool_constant<hamon::unsigned_integral<R>>;

	template <typename T2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename I>
using pre_decrementable_t =
	typename pre_decrementable_impl<I>::type;
template <typename I>

using post_decrementable_t =
	typename post_decrementable_impl<I>::type;

template <typename I>
using advanceable_forward_t =
	typename advanceable_forward_impl<I>::type;

template <typename I>
using advanceable_backward_t =
	typename advanceable_backward_impl<I>::type;

template <typename I>
using index_accessible_t =
	typename index_accessible_impl<I>::type;

template <typename I>
using addable1_t =
	typename addable1_impl<I>::type;

template <typename I>
using addable2_t =
	typename addable2_impl<I>::type;

template <typename I>
using subtractable1_t =
	typename subtractable1_impl<I>::type;

template <typename I, typename J, typename D = typename I::difference_type>
using subtractable2_t =
	typename subtractable2_impl<I, J, D>::type;

template <typename T>
using invocable_size_t =
	typename invocable_size_impl<T>::type;

#endif

inline HAMON_CXX14_CONSTEXPR bool test00()
{
#if 1
	{
		using V = decltype(hamon::views::iota(hamon::declval<int>()));
		static_assert(hamon::is_same<V, hamon::ranges::iota_view<int>>::value, "");
		static_assert(noexcept(hamon::views::iota(hamon::declval<int>())), "");
	}
	{
		using V = decltype(hamon::views::iota(hamon::declval<int&>()));
		static_assert(hamon::is_same<V, hamon::ranges::iota_view<int>>::value, "");
		static_assert(noexcept(hamon::views::iota(hamon::declval<int&>())), "");
	}
	{
		using V = decltype(hamon::views::iota(hamon::declval<int const&>()));
		static_assert(hamon::is_same<V, hamon::ranges::iota_view<int>>::value, "");
		static_assert(noexcept(hamon::views::iota(hamon::declval<int const&>())), "");
	}
	{
		using V = decltype(hamon::views::iota(hamon::declval<int&&>()));
		static_assert(hamon::is_same<V, hamon::ranges::iota_view<int>>::value, "");
		static_assert(noexcept(hamon::views::iota(hamon::declval<int&&>())), "");
	}
	{
		using V = decltype(hamon::views::iota(hamon::declval<int const&&>()));
		static_assert(hamon::is_same<V, hamon::ranges::iota_view<int>>::value, "");
		static_assert(noexcept(hamon::views::iota(hamon::declval<int const&&>())), "");
	}
	{
		using V = decltype(hamon::views::iota(hamon::declval<int*>()));
		static_assert(hamon::is_same<V, hamon::ranges::iota_view<int*>>::value, "");
		static_assert(noexcept(hamon::views::iota(hamon::declval<int*>())), "");
	}
	{
		using V = decltype(hamon::views::iota(hamon::declval<int const*>()));
		static_assert(hamon::is_same<V, hamon::ranges::iota_view<int const*>>::value, "");
		static_assert(noexcept(hamon::views::iota(hamon::declval<int const*>())), "");
	}
	{
		using V = decltype(hamon::views::iota(hamon::declval<int>(), hamon::declval<long>()));
		static_assert(hamon::is_same<V, hamon::ranges::iota_view<int, long>>::value, "");
		static_assert(noexcept(hamon::views::iota(hamon::declval<int>(), hamon::declval<long>())), "");
	}
	{
		using V = decltype(hamon::views::iota(hamon::declval<int&>(), hamon::declval<long&>()));
		static_assert(hamon::is_same<V, hamon::ranges::iota_view<int, long>>::value, "");
		static_assert(noexcept(hamon::views::iota(hamon::declval<int&>(), hamon::declval<long&>())), "");
	}
	{
		using V = decltype(hamon::views::iota(hamon::declval<int const&>(), hamon::declval<long const&>()));
		static_assert(hamon::is_same<V, hamon::ranges::iota_view<int, long>>::value, "");
		static_assert(noexcept(hamon::views::iota(hamon::declval<int const&>(), hamon::declval<long const&>())), "");
	}
	{
		using V = decltype(hamon::views::iota(hamon::declval<int&&>(), hamon::declval<long&&>()));
		static_assert(hamon::is_same<V, hamon::ranges::iota_view<int, long>>::value, "");
		static_assert(noexcept(hamon::views::iota(hamon::declval<int&&>(), hamon::declval<long&&>())), "");
	}
	{
		using V = decltype(hamon::views::iota(hamon::declval<int const&&>(), hamon::declval<long const&&>()));
		static_assert(hamon::is_same<V, hamon::ranges::iota_view<int, long>>::value, "");
		static_assert(noexcept(hamon::views::iota(hamon::declval<int const&&>(), hamon::declval<long const&&>())), "");
	}
	{
		using V = decltype(hamon::views::iota(hamon::declval<int*>(), hamon::declval<int*>()));
		static_assert(hamon::is_same<V, hamon::ranges::iota_view<int*, int*>>::value, "");
		static_assert(noexcept(hamon::views::iota(hamon::declval<int*>(), hamon::declval<int*>())), "");
	}
	{
		using V = decltype(hamon::views::iota(hamon::declval<int const*>(), hamon::declval<int const*>()));
		static_assert(hamon::is_same<V, hamon::ranges::iota_view<int const*, int const*>>::value, "");
		static_assert(noexcept(hamon::views::iota(hamon::declval<int const*>(), hamon::declval<int const*>())), "");
	}
	{
		using V = hamon::ranges::iota_view<int>;
		static_assert( hamon::is_default_constructible<V>::value, "");
		static_assert( hamon::is_nothrow_default_constructible<V>::value, "");
		static_assert( hamon::ranges::range<V>, "");
		static_assert(!hamon::ranges::sized_range<V>, "");
		static_assert(!hamon::ranges::common_range<V>, "");
		static_assert( hamon::ranges::borrowed_range<V>, "");
		static_assert(!invocable_size_t<V>::value, "");

		using I = decltype(hamon::declval<V>().begin());
		static_assert( hamon::is_same<typename I::iterator_concept, hamon::random_access_iterator_tag>::value, "");
		static_assert( has_iterator_category<I>::value, "");
		static_assert( hamon::is_default_constructible<I>::value, "");
		static_assert( hamon::is_nothrow_default_constructible<I>::value, "");
		static_assert( hamon::is_same<decltype(hamon::declval<I>()++), I>::value, "");
		static_assert( pre_decrementable_t<I>::value, "");
		static_assert( post_decrementable_t<I>::value, "");
		static_assert( advanceable_forward_t<I>::value, "");
		static_assert( advanceable_backward_t<I>::value, "");
		static_assert( index_accessible_t<I>::value, "");
		static_assert( hamon::equality_comparable<I>, "");
		static_assert( hamon::totally_ordered<I>, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert( hamon::three_way_comparable<I>, "");
#endif
		static_assert( addable1_t<I>::value, "");
		static_assert( addable2_t<I>::value, "");
		static_assert( subtractable1_t<I>::value, "");
		static_assert( subtractable2_t<I, I>::value, "");

		using S = decltype(hamon::declval<V>().end());
		static_assert( hamon::same_as<S, hamon::unreachable_sentinel_t>, "");
	}
	{
		using V = hamon::ranges::iota_view<int, int>;
		static_assert( hamon::is_default_constructible<V>::value, "");
		static_assert( hamon::is_nothrow_default_constructible<V>::value, "");
		static_assert( hamon::ranges::range<V>, "");
		static_assert( hamon::ranges::sized_range<V>, "");
		static_assert( hamon::ranges::common_range<V>, "");
		static_assert( hamon::ranges::borrowed_range<V>, "");
		static_assert( invocable_size_t<V>::value, "");

		using I = decltype(hamon::declval<V>().begin());
		static_assert( hamon::is_same<typename I::iterator_concept, hamon::random_access_iterator_tag>::value, "");
		static_assert( has_iterator_category<I>::value, "");
		static_assert( hamon::is_default_constructible<I>::value, "");
		static_assert( hamon::is_nothrow_default_constructible<I>::value, "");
		static_assert( hamon::is_same<decltype(hamon::declval<I>()++), I>::value, "");
		static_assert( pre_decrementable_t<I>::value, "");
		static_assert( post_decrementable_t<I>::value, "");
		static_assert( advanceable_forward_t<I>::value, "");
		static_assert( advanceable_backward_t<I>::value, "");
		static_assert( index_accessible_t<I>::value, "");
		static_assert( hamon::equality_comparable<I>, "");
		static_assert( hamon::totally_ordered<I>, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert( hamon::three_way_comparable<I>, "");
#endif
		static_assert( addable1_t<I>::value, "");
		static_assert( addable2_t<I>::value, "");
		static_assert( subtractable1_t<I>::value, "");
		static_assert( subtractable2_t<I, I>::value, "");

		using S = decltype(hamon::declval<V>().end());
		static_assert( hamon::same_as<S, I>, "");
	}
	{
		using V = hamon::ranges::iota_view<int, long>;
		static_assert( hamon::is_default_constructible<V>::value, "");
		static_assert( hamon::is_nothrow_default_constructible<V>::value, "");
		static_assert( hamon::ranges::range<V>, "");
		static_assert( hamon::ranges::sized_range<V>, "");
		static_assert(!hamon::ranges::common_range<V>, "");
		static_assert( hamon::ranges::borrowed_range<V>, "");
		static_assert( invocable_size_t<V>::value, "");

		using I = decltype(hamon::declval<V>().begin());
		static_assert( hamon::is_same<typename I::iterator_concept, hamon::random_access_iterator_tag>::value, "");
		static_assert( has_iterator_category<I>::value, "");
		static_assert( hamon::is_default_constructible<I>::value, "");
		static_assert( hamon::is_nothrow_default_constructible<I>::value, "");
		static_assert( hamon::is_same<decltype(hamon::declval<I>()++), I>::value, "");
		static_assert( pre_decrementable_t<I>::value, "");
		static_assert( post_decrementable_t<I>::value, "");
		static_assert( advanceable_forward_t<I>::value, "");
		static_assert( advanceable_backward_t<I>::value, "");
		static_assert( index_accessible_t<I>::value, "");
		static_assert( hamon::equality_comparable<I>, "");
		static_assert( hamon::totally_ordered<I>, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert( hamon::three_way_comparable<I>, "");
#endif
		static_assert( addable1_t<I>::value, "");
		static_assert( addable2_t<I>::value, "");
		static_assert( subtractable1_t<I>::value, "");
		static_assert( subtractable2_t<I, I>::value, "");

		using S = decltype(hamon::declval<V>().end());
//		static_assert( hamon::same_as<S, typename V::​sentinel>, "");
		static_assert(!hamon::same_as<S, I>, "");
		static_assert(!hamon::same_as<S, hamon::unreachable_sentinel_t>, "");
		static_assert( hamon::is_default_constructible<S>::value, "");
		static_assert( hamon::is_nothrow_default_constructible<S>::value, "");
		static_assert( hamon::detail::weakly_equality_comparable_with<I, S>, "");
		static_assert(!subtractable2_t<I, S>::value, "");
		static_assert(!subtractable2_t<S, I, typename I::difference_type>::value, "");
	}
	{
		using V = hamon::ranges::iota_view<NoDefaultCtor>;
		static_assert(!hamon::is_default_constructible<V>::value, "");
		static_assert(!hamon::is_nothrow_default_constructible<V>::value, "");
		static_assert( hamon::ranges::range<V>, "");
		static_assert(!hamon::ranges::sized_range<V>, "");
		static_assert(!hamon::ranges::common_range<V>, "");
		static_assert( hamon::ranges::borrowed_range<V>, "");
		static_assert(!invocable_size_t<V>::value, "");

		using I = decltype(hamon::declval<V>().begin());
		static_assert( hamon::is_same<typename I::iterator_concept, hamon::input_iterator_tag>::value, "");
		static_assert(!has_iterator_category<I>::value, "");
		static_assert(!hamon::is_default_constructible<I>::value, "");
		static_assert(!hamon::is_nothrow_default_constructible<I>::value, "");
		static_assert( hamon::is_same<decltype(hamon::declval<I>()++), void>::value, "");
		static_assert(!pre_decrementable_t<I>::value, "");
		static_assert(!post_decrementable_t<I>::value, "");
		static_assert(!advanceable_forward_t<I>::value, "");
		static_assert(!advanceable_backward_t<I>::value, "");
		static_assert(!index_accessible_t<I>::value, "");
		static_assert(!hamon::equality_comparable<I>, "");
		static_assert(!hamon::totally_ordered<I>, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert(!hamon::three_way_comparable<I>, "");
#endif
		static_assert(!addable1_t<I>::value, "");
		static_assert(!addable2_t<I>::value, "");
		static_assert(!subtractable1_t<I>::value, "");
		static_assert(!subtractable2_t<I, I>::value, "");

		using S = decltype(hamon::declval<V>().end());
		static_assert( hamon::same_as<S, hamon::unreachable_sentinel_t>, "");
	}
	{
		using V = hamon::ranges::iota_view<weakly_incrementable_wrapper<int>>;
		static_assert( hamon::is_default_constructible<V>::value, "");
		static_assert( hamon::is_nothrow_default_constructible<V>::value, "");
		static_assert( hamon::ranges::range<V>, "");
		static_assert(!hamon::ranges::sized_range<V>, "");
		static_assert(!hamon::ranges::common_range<V>, "");
		static_assert( hamon::ranges::borrowed_range<V>, "");
		static_assert(!invocable_size_t<V>::value, "");

		using I = decltype(hamon::declval<V>().begin());
		static_assert( hamon::is_same<typename I::iterator_concept, hamon::input_iterator_tag>::value, "");
		static_assert(!has_iterator_category<I>::value, "");
		static_assert( hamon::is_default_constructible<I>::value, "");
		static_assert( hamon::is_nothrow_default_constructible<I>::value, "");
		static_assert( hamon::is_same<decltype(hamon::declval<I>()++), void>::value, "");
		static_assert(!pre_decrementable_t<I>::value, "");
		static_assert(!post_decrementable_t<I>::value, "");
		static_assert(!advanceable_forward_t<I>::value, "");
		static_assert(!advanceable_backward_t<I>::value, "");
		static_assert(!index_accessible_t<I>::value, "");
		static_assert(!hamon::equality_comparable<I>, "");
		static_assert(!hamon::totally_ordered<I>, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert(!hamon::three_way_comparable<I>, "");
#endif
		static_assert(!addable1_t<I>::value, "");
		static_assert(!addable2_t<I>::value, "");
		static_assert(!subtractable1_t<I>::value, "");
		static_assert(!subtractable2_t<I, I>::value, "");

		using S = decltype(hamon::declval<V>().end());
		static_assert( hamon::same_as<S, hamon::unreachable_sentinel_t>, "");
	}
	{
		using V = hamon::ranges::iota_view<input_iterator_wrapper<int>, test_sentinel<input_iterator_wrapper<int>>>;
		static_assert( hamon::is_default_constructible<V>::value, "");
		static_assert( hamon::is_nothrow_default_constructible<V>::value, "");
		static_assert( hamon::ranges::range<V>, "");
		static_assert(!hamon::ranges::sized_range<V>, "");
		static_assert(!hamon::ranges::common_range<V>, "");
		static_assert( hamon::ranges::borrowed_range<V>, "");
		static_assert(!invocable_size_t<V>::value, "");

		using I = decltype(hamon::declval<V>().begin());
		static_assert( hamon::is_same<typename I::iterator_concept, hamon::input_iterator_tag>::value, "");
		static_assert(!has_iterator_category<I>::value, "");
		static_assert( hamon::is_default_constructible<I>::value, "");
		static_assert( hamon::is_nothrow_default_constructible<I>::value, "");
		static_assert( hamon::is_same<decltype(hamon::declval<I>()++), void>::value, "");
		static_assert(!pre_decrementable_t<I>::value, "");
		static_assert(!post_decrementable_t<I>::value, "");
		static_assert(!advanceable_forward_t<I>::value, "");
		static_assert(!advanceable_backward_t<I>::value, "");
		static_assert(!index_accessible_t<I>::value, "");
		static_assert( hamon::equality_comparable<I>, "");
		static_assert(!hamon::totally_ordered<I>, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert(!hamon::three_way_comparable<I>, "");
#endif
		static_assert(!addable1_t<I>::value, "");
		static_assert(!addable2_t<I>::value, "");
		static_assert(!subtractable1_t<I>::value, "");
		static_assert(!subtractable2_t<I, I>::value, "");

		using S = decltype(hamon::declval<V>().end());
//		static_assert( hamon::same_as<S, typename V::​sentinel>, "");
		static_assert(!hamon::same_as<S, I>, "");
		static_assert(!hamon::same_as<S, hamon::unreachable_sentinel_t>, "");
		static_assert( hamon::is_default_constructible<S>::value, "");
		static_assert( hamon::is_nothrow_default_constructible<S>::value, "");
		static_assert( hamon::detail::weakly_equality_comparable_with<I, S>, "");
		static_assert(!subtractable2_t<I, S>::value, "");
		static_assert(!subtractable2_t<S, I, typename I::difference_type>::value, "");
	}
	{
		using V = hamon::ranges::iota_view<forward_iterator_wrapper<int>, test_sentinel<forward_iterator_wrapper<int>>>;
		static_assert( hamon::is_default_constructible<V>::value, "");
		static_assert( hamon::is_nothrow_default_constructible<V>::value, "");
		static_assert( hamon::ranges::range<V>, "");
		static_assert(!hamon::ranges::sized_range<V>, "");
		static_assert(!hamon::ranges::common_range<V>, "");
		static_assert( hamon::ranges::borrowed_range<V>, "");
		static_assert(!invocable_size_t<V>::value, "");

		using I = decltype(hamon::declval<V>().begin());
		static_assert( hamon::is_same<typename I::iterator_concept, hamon::forward_iterator_tag>::value, "");
		static_assert( has_iterator_category<I>::value, "");
		static_assert( hamon::is_default_constructible<I>::value, "");
		static_assert( hamon::is_nothrow_default_constructible<I>::value, "");
		static_assert( hamon::is_same<decltype(hamon::declval<I>()++), I>::value, "");
		static_assert(!pre_decrementable_t<I>::value, "");
		static_assert(!post_decrementable_t<I>::value, "");
		static_assert(!advanceable_forward_t<I>::value, "");
		static_assert(!advanceable_backward_t<I>::value, "");
		static_assert(!index_accessible_t<I>::value, "");
		static_assert( hamon::equality_comparable<I>, "");
		static_assert(!hamon::totally_ordered<I>, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert(!hamon::three_way_comparable<I>, "");
#endif
		static_assert(!addable1_t<I>::value, "");
		static_assert(!addable2_t<I>::value, "");
		static_assert(!subtractable1_t<I>::value, "");
		static_assert(!subtractable2_t<I, I>::value, "");

		using S = decltype(hamon::declval<V>().end());
//		static_assert( hamon::same_as<S, typename V::​sentinel>, "");
		static_assert(!hamon::same_as<S, I>, "");
		static_assert(!hamon::same_as<S, hamon::unreachable_sentinel_t>, "");
		static_assert( hamon::is_default_constructible<S>::value, "");
		static_assert( hamon::is_nothrow_default_constructible<S>::value, "");
		static_assert( hamon::detail::weakly_equality_comparable_with<I, S>, "");
		static_assert(!subtractable2_t<I, S>::value, "");
		static_assert(!subtractable2_t<S, I, typename I::difference_type>::value, "");
	}
	{
		using V = hamon::ranges::iota_view<bidirectional_iterator_wrapper<int>, test_sentinel<bidirectional_iterator_wrapper<int>>>;
		static_assert( hamon::is_default_constructible<V>::value, "");
		static_assert( hamon::is_nothrow_default_constructible<V>::value, "");
		static_assert( hamon::ranges::range<V>, "");
		static_assert(!hamon::ranges::sized_range<V>, "");
		static_assert(!hamon::ranges::common_range<V>, "");
		static_assert( hamon::ranges::borrowed_range<V>, "");
		static_assert(!invocable_size_t<V>::value, "");

		using I = decltype(hamon::declval<V>().begin());
		static_assert( hamon::is_same<typename I::iterator_concept, hamon::bidirectional_iterator_tag>::value, "");
		static_assert( has_iterator_category<I>::value, "");
		static_assert( hamon::is_default_constructible<I>::value, "");
		static_assert( hamon::is_nothrow_default_constructible<I>::value, "");
		static_assert( hamon::is_same<decltype(hamon::declval<I>()++), I>::value, "");
		static_assert( pre_decrementable_t<I>::value, "");
		static_assert( post_decrementable_t<I>::value, "");
		static_assert(!advanceable_forward_t<I>::value, "");
		static_assert(!advanceable_backward_t<I>::value, "");
		static_assert(!index_accessible_t<I>::value, "");
		static_assert( hamon::equality_comparable<I>, "");
		static_assert(!hamon::totally_ordered<I>, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert(!hamon::three_way_comparable<I>, "");
#endif
		static_assert(!addable1_t<I>::value, "");
		static_assert(!addable2_t<I>::value, "");
		static_assert(!subtractable1_t<I>::value, "");
		static_assert(!subtractable2_t<I, I>::value, "");

		using S = decltype(hamon::declval<V>().end());
//		static_assert( hamon::same_as<S, typename V::​sentinel>, "");
		static_assert(!hamon::same_as<S, I>, "");
		static_assert(!hamon::same_as<S, hamon::unreachable_sentinel_t>, "");
		static_assert( hamon::is_default_constructible<S>::value, "");
		static_assert( hamon::is_nothrow_default_constructible<S>::value, "");
		static_assert( hamon::detail::weakly_equality_comparable_with<I, S>, "");
		static_assert(!subtractable2_t<I, S>::value, "");
		static_assert(!subtractable2_t<S, I, typename I::difference_type>::value, "");
	}
	{
		using V = hamon::ranges::iota_view<random_access_iterator_wrapper<int>, test_sentinel<random_access_iterator_wrapper<int>>>;
		static_assert( hamon::is_default_constructible<V>::value, "");
		static_assert( hamon::is_nothrow_default_constructible<V>::value, "");
		static_assert( hamon::ranges::range<V>, "");
		static_assert( hamon::ranges::sized_range<V>, "");
		static_assert(!hamon::ranges::common_range<V>, "");
		static_assert( hamon::ranges::borrowed_range<V>, "");
		static_assert( invocable_size_t<V>::value, "");

		using I = decltype(hamon::declval<V>().begin());
		static_assert( hamon::is_same<typename I::iterator_concept, hamon::random_access_iterator_tag>::value, "");
		static_assert( has_iterator_category<I>::value, "");
		static_assert( hamon::is_default_constructible<I>::value, "");
		static_assert( hamon::is_nothrow_default_constructible<I>::value, "");
		static_assert( hamon::is_same<decltype(hamon::declval<I>()++), I>::value, "");
		static_assert( pre_decrementable_t<I>::value, "");
		static_assert( post_decrementable_t<I>::value, "");
		static_assert( advanceable_forward_t<I>::value, "");
		static_assert( advanceable_backward_t<I>::value, "");
		static_assert( index_accessible_t<I>::value, "");
		static_assert( hamon::equality_comparable<I>, "");
		static_assert( hamon::totally_ordered<I>, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert(!hamon::three_way_comparable<I>, "");
#endif
		static_assert( addable1_t<I>::value, "");
		static_assert( addable2_t<I>::value, "");
		static_assert( subtractable1_t<I>::value, "");
		static_assert( subtractable2_t<I, I>::value, "");

		using S = decltype(hamon::declval<V>().end());
//		static_assert( hamon::same_as<S, typename V::​sentinel>, "");
		static_assert(!hamon::same_as<S, I>, "");
		static_assert(!hamon::same_as<S, hamon::unreachable_sentinel_t>, "");
		static_assert( hamon::is_default_constructible<S>::value, "");
		static_assert( hamon::is_nothrow_default_constructible<S>::value, "");
		static_assert( hamon::detail::weakly_equality_comparable_with<I, S>, "");
		static_assert( subtractable2_t<I, S>::value, "");
		static_assert( subtractable2_t<S, I, typename I::difference_type>::value, "");
	}
#endif
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test01()
{
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	auto v = hamon::ranges::iota_view{1, 4};
#else
	auto v = hamon::ranges::iota_view<int, int>{1, 4};
#endif
	VERIFY(!v.empty());
	VERIFY(v.size() == 3);

	int vals[5] ={};
	int* out = vals;
	for (int i : v)
	{
		*out++ = i;
	}
	VERIFY(out == vals + 3);
	VERIFY(vals[0] == 1);
	VERIFY(vals[1] == 2);
	VERIFY(vals[2] == 3);
	VERIFY(vals[3] == 0);

	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test02()
{
	namespace ranges = hamon::ranges;

	auto v = hamon::views::iota(4);

	using R = decltype(v);
	static_assert( ranges::view_t<R>::value, "");
	static_assert( ranges::range<R>, "");
	static_assert(!ranges::sized_range<R>, "");
	static_assert(!ranges::common_range<R>, "");
	static_assert( ranges::random_access_range<R>, "");
	static_assert(!ranges::contiguous_range<R>, "");

	using I = decltype(v.begin());
	static_assert( has_iterator_category<I>::value, "");
	static_assert( hamon::same_as<typename I::iterator_category, hamon::input_iterator_tag>, "");
	static_assert( hamon::same_as<typename I::value_type, int>, "");
	static_assert( hamon::signed_integral<typename I::difference_type>, "");
	{
		I it;
		(void)it;
	}

	auto it = v.begin();
	VERIFY(*it == 4);
	++it;
	VERIFY(*it == 5);
	it++;
	VERIFY(*it == 6);
	--it;
	VERIFY(*it == 5);
	it--;
	VERIFY(*it == 4);

	VERIFY((it == v.end()) == false);
	VERIFY((it != v.end()) == true);

	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test03()
{
	namespace ranges = hamon::ranges;

	auto v = hamon::views::iota(10, 15);

	using R = decltype(v);
	static_assert( ranges::view_t<R>::value, "");
	static_assert( ranges::range<R>, "");
	static_assert( ranges::sized_range<R>, "");
	static_assert( ranges::common_range<R>, "");
	static_assert( ranges::random_access_range<R>, "");
	static_assert(!ranges::contiguous_range<R>, "");

	using I = decltype(v.begin());
	static_assert( has_iterator_category<I>::value, "");
	static_assert( hamon::same_as<typename I::iterator_category, hamon::input_iterator_tag>, "");
	static_assert( hamon::same_as<typename I::value_type, int>, "");
	static_assert( hamon::signed_integral<typename I::difference_type>, "");

	VERIFY(!v.empty());
	VERIFY(v.size() == 5);

	auto it = v.begin();
	VERIFY(it[0] == 10);
	VERIFY(it[1] == 11);
	VERIFY(*(it + 2) == 12);
	VERIFY(*(3 + it) == 13);

	VERIFY(*it == 10);
	it += 2;
	VERIFY(*it == 12);
	it += 2;
	VERIFY(*it == 14);

	VERIFY(*(it - 1) == 13);

	VERIFY((it - v.begin()) ==  4);
	VERIFY((it - v.end())   == -1);

	VERIFY((it == v.end()) == false);
	VERIFY((it != v.end()) == true);
	VERIFY((it <  v.end()) == true);
	VERIFY((it <= v.end()) == true);
	VERIFY((it >  v.end()) == false);
	VERIFY((it >= v.end()) == false);
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	VERIFY(hamon::is_neq(it <=> v.end()));
#endif

	++it;

	VERIFY((it == v.end()) == true);
	VERIFY((it != v.end()) == false);
	VERIFY((it <  v.end()) == false);
	VERIFY((it <= v.end()) == true);
	VERIFY((it >  v.end()) == false);
	VERIFY((it >= v.end()) == true);
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	VERIFY(hamon::is_eq(it <=> v.end()));
#endif

	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test04()
{
	namespace ranges = hamon::ranges;

	int a[2] ={};
	test_random_access_range<int> r(a);
	auto v = hamon::views::iota(r.begin(), r.end());

	using R = decltype(v);
	static_assert( ranges::random_access_range<R>, "");
	static_assert(!ranges::contiguous_range<R>, "");

	using I = decltype(v.begin());
	static_assert( has_iterator_category<I>::value, "");
	static_assert( hamon::same_as<typename I::iterator_category, hamon::input_iterator_tag>, "");
	static_assert( hamon::same_as<typename I::value_type, random_access_iterator_wrapper<int>>, "");
	static_assert( hamon::same_as<typename I::difference_type, hamon::iter_difference_t<random_access_iterator_wrapper<int>>>, "");

	VERIFY(!v.empty());
	VERIFY(v.size() == 2);

	auto it = v.begin();
	VERIFY((it - v.begin()) ==  0);
	VERIFY((it - v.end())   == -2);
	VERIFY((v.begin() - it) ==  0);
	VERIFY((v.end()   - it) ==  2);

	VERIFY((it == v.end()) == false);
	VERIFY((it != v.end()) == true);
	++it;
	VERIFY((it == v.end()) == false);
	VERIFY((it != v.end()) == true);
	it++;
	VERIFY((it == v.end()) == true);
	VERIFY((it != v.end()) == false);

	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test05()
{
	namespace ranges = hamon::ranges;

	int a[2] ={};
	test_bidirectional_range<int> r(a);
	auto v = hamon::views::iota(r.begin(), r.end());

	using R = decltype(v);
	static_assert( ranges::bidirectional_range<R>, "");
	static_assert(!ranges::random_access_range<R>, "");

	using I = decltype(v.begin());
	static_assert( has_iterator_category<I>::value, "");
	static_assert( hamon::same_as<typename I::iterator_category, hamon::input_iterator_tag>, "");
	static_assert( hamon::same_as<typename I::value_type, bidirectional_iterator_wrapper<int>>, "");
	static_assert( hamon::same_as<typename I::difference_type, hamon::iter_difference_t<bidirectional_iterator_wrapper<int>>>, "");

	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test06()
{
	namespace ranges = hamon::ranges;

	int a[2] ={};
	test_forward_range<int> r(a);
	auto v = hamon::views::iota(r.begin(), r.end());

	using R = decltype(v);
	static_assert( ranges::forward_range<R>, "");
	static_assert(!ranges::bidirectional_range<R>, "");

	using I = decltype(v.begin());
	static_assert( has_iterator_category<I>::value, "");
	static_assert( hamon::same_as<typename I::iterator_category, hamon::input_iterator_tag>, "");
	static_assert( hamon::same_as<typename I::value_type, forward_iterator_wrapper<int>>, "");
	static_assert( hamon::same_as<typename I::difference_type, hamon::iter_difference_t<forward_iterator_wrapper<int>>>, "");

	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test07()
{
	namespace ranges = hamon::ranges;

	int a[2] ={};
	test_input_range<int> r(a);
	auto v = hamon::views::iota(r.begin(), r.end());

	using R = decltype(v);
	static_assert( ranges::input_range<R>, "");
	static_assert(!ranges::forward_range<R>, "");

	using I = decltype(v.begin());
	static_assert(!has_iterator_category<I>::value, "");
	//static_assert( hamon::same_as<typename I::iterator_category, hamon::input_iterator_tag>, "");
	static_assert( hamon::same_as<typename I::value_type, input_iterator_wrapper<int>>, "");
	static_assert( hamon::same_as<typename I::difference_type, hamon::iter_difference_t<input_iterator_wrapper<int>>>, "");

	auto it = v.begin();
	VERIFY((it == v.end()) == false);
	VERIFY((it != v.end()) == true);
	++it;
	VERIFY((it == v.end()) == false);
	VERIFY((it != v.end()) == true);
	it++;
	VERIFY((it == v.end()) == true);
	VERIFY((it != v.end()) == false);

	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test08()
{
	namespace ranges = hamon::ranges;

	auto v = ranges::iota_view<unsigned int, unsigned int>{3u, 5u};

	using R = decltype(v);
	static_assert( ranges::random_access_range<R>, "");
	static_assert(!ranges::contiguous_range<R>, "");

	VERIFY(!v.empty());
	VERIFY(v.size() == 2);

	auto it = v.begin();
	VERIFY((it - v.begin()) ==  0);

	VERIFY(*it == 3u);
	it += 2;
	VERIFY(*it == 5u);
	it += -1;
	VERIFY(*it == 4u);
	it -= 1;
	VERIFY(*it == 3u);
	it -= -2;
	VERIFY(*it == 5u);

	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test09()
{
	namespace ranges = hamon::ranges;

	auto v1 = hamon::views::iota(10, 15);
	using R = decltype(v1);
	R v2{v1.begin() + 3, v1.end()};

	using I = decltype(v1.begin());
	static_assert( hamon::is_default_constructible<R>::value, "");
	static_assert( hamon::is_constructible<R, I, I>::value, "");
	static_assert( hamon::is_nothrow_default_constructible<R>::value, "");
	static_assert( hamon::is_nothrow_constructible<R, I, I>::value, "");

	auto it = v2.begin();
	VERIFY(it != v2.end());
	VERIFY(*it == 13);
	++it;
	VERIFY(it != v2.end());
	VERIFY(*it == 14);
	++it;
	VERIFY(it == v2.end());

	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test10()
{
	namespace ranges = hamon::ranges;

	auto v1 = hamon::views::iota(10);
	using R = decltype(v1);
	R v2{v1.begin() + 3, v1.end()};

	using I = decltype(v1.begin());
	static_assert( hamon::is_default_constructible<R>::value, "");
	static_assert( hamon::is_constructible<R, I, hamon::unreachable_sentinel_t>::value, "");
	static_assert( hamon::is_nothrow_default_constructible<R>::value, "");
	static_assert( hamon::is_nothrow_constructible<R, I, hamon::unreachable_sentinel_t>::value, "");

	auto it = v2.begin();
	VERIFY(it != v2.end());
	VERIFY(*it == 13);
	++it;
	VERIFY(it != v2.end());
	VERIFY(*it == 14);
	++it;

	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test11()
{
	namespace ranges = hamon::ranges;

	auto v1 = ranges::iota_view<int, long>{10, 15};
	using R = decltype(v1);
	R v2{v1.begin() + 3, v1.end()};

	using I = decltype(v1.begin());
	using S = decltype(v1.end());
	static_assert( hamon::is_default_constructible<R>::value, "");
	static_assert( hamon::is_constructible<R, I, S>::value, "");
	static_assert( hamon::is_nothrow_default_constructible<R>::value, "");
	static_assert( hamon::is_nothrow_constructible<R, I, S>::value, "");

	auto it = v2.begin();
	VERIFY(it != v2.end());
	VERIFY(*it == 13);
	++it;
	VERIFY(it != v2.end());
	VERIFY(*it == 14);
	++it;

	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test12()
{
	const int a[]{3,1,4,1,5};

	auto v = hamon::views::indices(hamon::ranges::size(a));

	auto it = v.begin();
	VERIFY(it != v.end());
	VERIFY(*it == 0);
	++it;
	VERIFY(it != v.end());
	VERIFY(*it == 1);
	++it;
	VERIFY(it != v.end());
	VERIFY(*it == 2);
	++it;
	VERIFY(it != v.end());
	VERIFY(*it == 3);
	++it;
	VERIFY(it != v.end());
	VERIFY(*it == 4);
	++it;
	VERIFY(it == v.end());

	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test13()
{
	auto v = hamon::views::iota(5, 5);

	VERIFY(v.empty());
	VERIFY(v.size() == 0);

	return true;
}

inline HAMON_CXX20_CONSTEXPR bool test14()
{
	hamon::vector<int> v;
	auto it = hamon::back_inserter(v);
//	auto s = hamon::ranges::subrange(it, hamon::unreachable_sentinel);
	auto r = hamon::views::iota(it);
//	VERIFY(!s.empty());
	VERIFY(!r.empty());

	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test15()
{
	//auto v = hamon::views::iota(hamon::views::iota(0));
	//(void)v;

	auto v1 = hamon::views::iota(0);
	static_assert(!hamon::invocable<decltype(hamon::views::iota), decltype(v1)>, "");

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, IotaViewTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test05());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test06());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test07());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test08());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test09());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test10());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test11());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test12());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test13());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test14());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test15());
}

}	// namespace iota_view_test
}	// namespace hamon_ranges_test
