/**
 *	@file	output_iterator.hpp
 *
 *	@brief	output_iterator の定義
 */

#ifndef HAMON_ITERATOR_CONCEPTS_OUTPUT_ITERATOR_HPP
#define HAMON_ITERATOR_CONCEPTS_OUTPUT_ITERATOR_HPP

#include <hamon/iterator/concepts/indirectly_writable.hpp>
#include <hamon/iterator/concepts/input_or_output_iterator.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename Iter, typename T>
HAMON_CONCEPT_OR_BOOL output_iterator =
	hamon::input_or_output_iterator<Iter> &&
	hamon::indirectly_writable<Iter, T> &&
	requires(Iter i, T&& t) { *i++ = hamon::forward<T>(t); };

#else

namespace detail
{

template <typename Iter, typename T>
struct output_iterator_impl
{
private:
	template <typename I2, typename T2,
		typename = hamon::enable_if_t<hamon::input_or_output_iterator<I2>>,
		typename = hamon::enable_if_t<hamon::indirectly_writable<I2, T2>>,
		typename = decltype(*hamon::declval<I2&>()++ = hamon::declval<T2&&>())
	>
	static auto test(int) -> hamon::true_type;

	template <typename I2, typename T2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<Iter, T>(0));
};

}	// namespace detail

template <typename Iter, typename T>
HAMON_CONCEPT_OR_BOOL output_iterator =
	detail::output_iterator_impl<Iter, T>::type::value;

#endif

}	// namespace hamon

#endif // HAMON_ITERATOR_CONCEPTS_OUTPUT_ITERATOR_HPP
