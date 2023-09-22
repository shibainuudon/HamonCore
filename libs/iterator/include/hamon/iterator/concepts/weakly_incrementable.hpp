/**
 *	@file	weakly_incrementable.hpp
 *
 *	@brief	weakly_incrementable の定義
 */

#ifndef HAMON_ITERATOR_CONCEPTS_WEAKLY_INCREMENTABLE_HPP
#define HAMON_ITERATOR_CONCEPTS_WEAKLY_INCREMENTABLE_HPP

#include <hamon/iterator/config.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

#if !defined(HAMON_USE_STD_RANGES_ITERATOR)
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/concepts/movable.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/concepts/detail/signed_integer_like.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/utility/declval.hpp>
#endif

namespace hamon
{

#if defined(HAMON_USE_STD_RANGES_ITERATOR)

using std::weakly_incrementable;

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename Iter>
concept weakly_incrementable =
	hamon::movable<Iter> &&
	requires(Iter i)
	{
		typename hamon::iter_difference_t<Iter>;
		requires hamon::ranges::detail::signed_integer_like<hamon::iter_difference_t<Iter>>;
		{ ++i } -> hamon::same_as<Iter&>;
		i++;
	};

#else

namespace detail
{

template <typename Iter>
struct weakly_incrementable_impl
{
private:
	template <typename I2,
		typename = hamon::enable_if_t<hamon::movable<I2>::value>,
		typename D = hamon::iter_difference_t<I2>,
		typename = hamon::enable_if_t<hamon::ranges::detail::signed_integer_like<D>::value>,
		typename T = decltype(++hamon::declval<I2&>()),
		typename = hamon::enable_if_t<hamon::same_as<T, I2&>::value>,
		typename = decltype(hamon::declval<I2&>()++)
	>
	static auto test(int) -> hamon::true_type;

	template <typename I2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<Iter>(0));
};

}	// namespace detail

template <typename Iter>
using weakly_incrementable =
	typename detail::weakly_incrementable_impl<Iter>::type;

#endif

template <typename Iter>
using weakly_incrementable_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::weakly_incrementable<Iter>>;
#else
	hamon::weakly_incrementable<Iter>;
#endif

}	// namespace hamon

#endif // HAMON_ITERATOR_CONCEPTS_WEAKLY_INCREMENTABLE_HPP
