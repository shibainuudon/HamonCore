/**
 *	@file	input_iterator.hpp
 *
 *	@brief	input_iterator の定義
 */

#ifndef HAMON_ITERATOR_CONCEPTS_INPUT_ITERATOR_HPP
#define HAMON_ITERATOR_CONCEPTS_INPUT_ITERATOR_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ITERATOR)

namespace hamon
{

using std::input_iterator;

}	// namespace hamon

#else

#include <hamon/iterator/concepts/input_or_output_iterator.hpp>
#include <hamon/iterator/concepts/indirectly_readable.hpp>
#include <hamon/iterator/concepts/detail/iter_concept.hpp>
#include <hamon/concepts/derived_from.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>
#include <iterator>

namespace hamon
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename Iter>
concept input_iterator =
	hamon::input_or_output_iterator<Iter> &&
	hamon::indirectly_readable<Iter> &&
	requires { typename hamon::detail::iter_concept<Iter>; } &&
	hamon::derived_from<hamon::detail::iter_concept<Iter>, std::input_iterator_tag>;

#else

namespace detail
{

template <typename Iter>
struct input_iterator_impl
{
private:
	template <typename I2,
		typename = hamon::enable_if_t<hamon::input_or_output_iterator<I2>::value>,
		typename = hamon::enable_if_t<hamon::indirectly_readable<I2>::value>,
		typename = hamon::enable_if_t<hamon::derived_from<hamon::detail::iter_concept<I2>, std::input_iterator_tag>::value>
	>
	static auto test(int) -> hamon::true_type;

	template <typename I2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<Iter>(0));
};

}	// namespace detail

template <typename Iter>
using input_iterator =
	typename detail::input_iterator_impl<Iter>::type;

#endif

}	// namespace hamon

#endif

#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{

template <typename Iter>
using input_iterator_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::input_iterator<Iter>>;
#else
	hamon::input_iterator<Iter>;
#endif

}	// namespace hamon

#endif // HAMON_ITERATOR_CONCEPTS_INPUT_ITERATOR_HPP
