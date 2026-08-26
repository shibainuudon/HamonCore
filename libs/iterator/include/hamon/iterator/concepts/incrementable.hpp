/**
 *	@file	incrementable.hpp
 *
 *	@brief	incrementable の定義
 */

#ifndef HAMON_ITERATOR_CONCEPTS_INCREMENTABLE_HPP
#define HAMON_ITERATOR_CONCEPTS_INCREMENTABLE_HPP

#include <hamon/iterator/concepts/weakly_incrementable.hpp>
#include <hamon/concepts/regular.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename Iter>
HAMON_CONCEPT_OR_BOOL incrementable =
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
		typename = hamon::enable_if_t<hamon::regular<I2>>,
		typename = hamon::enable_if_t<hamon::weakly_incrementable<I2>>,
		typename T = decltype(hamon::declval<I2&>()++),
		typename = hamon::enable_if_t<hamon::same_as<T, I2>>
	>
	static auto test(int) -> hamon::true_type;

	template <typename I2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<Iter>(0));
};

}	// namespace detail

template <typename Iter>
HAMON_CONCEPT_OR_BOOL incrementable =
	detail::incrementable_impl<Iter>::type::value;

#endif

}	// namespace hamon

#endif // HAMON_ITERATOR_CONCEPTS_INCREMENTABLE_HPP
