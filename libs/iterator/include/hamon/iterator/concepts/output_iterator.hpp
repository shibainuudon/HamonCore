/**
 *	@file	output_iterator.hpp
 *
 *	@brief	output_iterator の定義
 */

#ifndef HAMON_ITERATOR_CONCEPTS_OUTPUT_ITERATOR_HPP
#define HAMON_ITERATOR_CONCEPTS_OUTPUT_ITERATOR_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ITERATOR)

namespace hamon
{

using std::output_iterator;

}	// namespace hamon

#else

#include <hamon/iterator/concepts/input_or_output_iterator.hpp>
#include <hamon/iterator/concepts/indirectly_writable.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>
#include <type_traits>
#include <utility>

namespace hamon
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename Iter, typename T>
concept output_iterator =
	hamon::input_or_output_iterator<Iter> &&
	hamon::indirectly_writable<Iter, T> &&
	requires(Iter i, T&& t) { *i++ = std::forward<T>(t); };

#else

namespace detail
{

template <typename Iter, typename T>
struct output_iterator_impl
{
private:
	template <typename I2, typename T2,
		typename = hamon::enable_if_t<hamon::input_or_output_iterator<I2>::value>,
		typename = hamon::enable_if_t<hamon::indirectly_writable<I2, T2>::value>,
		typename = decltype(*std::declval<I2&>()++ = std::declval<T2&&>())
	>
	static auto test(int) -> std::true_type;

	template <typename I2, typename T2>
	static auto test(...) -> std::false_type;

public:
	using type = decltype(test<Iter, T>(0));
};

}	// namespace detail

template <typename Iter, typename T>
using output_iterator =
	typename detail::output_iterator_impl<Iter, T>::type;

#endif

}	// namespace hamon

#endif

#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{

template <typename Iter, typename T>
using output_iterator_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::output_iterator<Iter, T>>;
#else
	hamon::output_iterator<Iter, T>;
#endif

}	// namespace hamon


#endif // HAMON_ITERATOR_CONCEPTS_OUTPUT_ITERATOR_HPP
