/**
 *	@file	incrementable.hpp
 *
 *	@brief	incrementable の定義
 */

#ifndef HAMON_ITERATOR_CONCEPTS_INCREMENTABLE_HPP
#define HAMON_ITERATOR_CONCEPTS_INCREMENTABLE_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ITERATOR)

namespace hamon
{

using std::incrementable;

}	// namespace hamon

#else

#include <hamon/iterator/concepts/weakly_incrementable.hpp>
#include <hamon/concepts/regular.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename Iter>
concept incrementable =
	hamon::regular<Iter> &&
	hamon::weakly_incrementable<Iter> &&
	requires(Iter i) { { i++ } -> hamon::same_as<Iter>; };

#else

namespace detail
{

template <typename Iter>
struct incrementable_impl
{
private:
	template <typename I2,
		typename = hamon::enable_if_t<hamon::regular<I2>::value>,
		typename = hamon::enable_if_t<hamon::weakly_incrementable<I2>::value>,
		typename T = decltype(std::declval<I2&>()++)
	>
	static auto test(int) -> hamon::same_as<T, I2>;

	template <typename I2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<Iter>(0));
};

}	// namespace detail

template <typename Iter>
using incrementable =
	typename detail::incrementable_impl<Iter>::type;

#endif

}	// namespace hamon

#endif

#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{

template <typename Iter>
using incrementable_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::incrementable<Iter>>;
#else
	hamon::incrementable<Iter>;
#endif

}	// namespace hamon

#endif // HAMON_ITERATOR_CONCEPTS_INCREMENTABLE_HPP
