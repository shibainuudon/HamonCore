/**
 *	@file	sized_sentinel_for.hpp
 *
 *	@brief	sized_sentinel_for の定義
 */

#ifndef HAMON_ITERATOR_CONCEPTS_SIZED_SENTINEL_FOR_HPP
#define HAMON_ITERATOR_CONCEPTS_SIZED_SENTINEL_FOR_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ITERATOR)

namespace hamon
{

using std::sized_sentinel_for;

}	// namespace hamon

#else

#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/disable_sized_sentinel_for.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/type_traits/remove_cv.hpp>
#include <hamon/config.hpp>
#include <type_traits>
#include <utility>

namespace hamon
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename Sent, typename Iter>
concept sized_sentinel_for =
	hamon::sentinel_for<Sent, Iter> &&
	!HAMON_DISABLE_SIZED_SENTINEL_FOR(hamon::remove_cv_t<Sent>, hamon::remove_cv_t<Iter>) &&
	requires(Iter const& i, Sent const& s)
	{
		{ s - i } -> hamon::same_as<hamon::iter_difference_t<Iter>>;
		{ i - s } -> hamon::same_as<hamon::iter_difference_t<Iter>>;
	};

#else

namespace detail
{

template <typename Sent, typename Iter>
struct sized_sentinel_for_impl
{
private:
	template <typename S2, typename I2,
		typename = hamon::enable_if_t<hamon::sentinel_for<S2, I2>::value>,
		typename = hamon::enable_if_t<
			!HAMON_DISABLE_SIZED_SENTINEL_FOR(hamon::remove_cv_t<S2>, hamon::remove_cv_t<I2>)>,
		typename D1 = decltype(std::declval<S2 const&>() - std::declval<I2 const&>()),
		typename D2 = decltype(std::declval<I2 const&>() - std::declval<S2 const&>()),
		typename D3 = hamon::iter_difference_t<I2>
	>
	static auto test(int) -> hamon::conjunction<
		hamon::same_as<D1, D3>,
		hamon::same_as<D2, D3>
	>;

	template <typename S2, typename I2>
	static auto test(...) -> std::false_type;

public:
	using type = decltype(test<Sent, Iter>(0));
};

}	// namespace detail

template <typename Sent, typename Iter>
using sized_sentinel_for =
	typename detail::sized_sentinel_for_impl<Sent, Iter>::type;

#endif

}	// namespace hamon

#endif

#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{

template <typename Sent, typename Iter>
using sized_sentinel_for_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::sized_sentinel_for<Sent, Iter>>;
#else
	hamon::sized_sentinel_for<Sent, Iter>;
#endif

}	// namespace hamon

#endif // HAMON_ITERATOR_CONCEPTS_SIZED_SENTINEL_FOR_HPP
