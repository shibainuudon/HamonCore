/**
 *	@file	bidirectional_iterator.hpp
 *
 *	@brief	bidirectional_iterator の定義
 */

#ifndef HAMON_ITERATOR_CONCEPTS_BIDIRECTIONAL_ITERATOR_HPP
#define HAMON_ITERATOR_CONCEPTS_BIDIRECTIONAL_ITERATOR_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ITERATOR)

namespace hamon
{

using std::bidirectional_iterator;

}	// namespace hamon

#else

#include <hamon/iterator/concepts/forward_iterator.hpp>
#include <hamon/iterator/concepts/detail/iter_concept.hpp>
#include <hamon/concepts/derived_from.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>
#include <iterator>
#include <utility>

namespace hamon
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename Iter>
concept bidirectional_iterator =
	hamon::forward_iterator<Iter> &&
	hamon::derived_from<
		hamon::detail::iter_concept<Iter>,
		std::bidirectional_iterator_tag> &&
	requires(Iter i)
	{
		{ --i } -> hamon::same_as<Iter&>;
		{ i-- } -> hamon::same_as<Iter>;
	};

#else

namespace detail
{

template <typename Iter>
struct bidirectional_iterator_impl
{
private:
	template <typename I2,
		typename = hamon::enable_if_t<
			hamon::forward_iterator<I2>::value
		>,
		typename = hamon::enable_if_t<
			hamon::derived_from<
				hamon::detail::iter_concept<I2>,
				std::bidirectional_iterator_tag
			>::value
		>,
		typename T1 = decltype(--std::declval<I2&>()),
		typename T2 = decltype(  std::declval<I2&>()--)
	>
	static auto test(int) -> hamon::conjunction<
		hamon::same_as<T1, I2&>,
		hamon::same_as<T2, I2>
	>;

	template <typename I2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<Iter>(0));
};

}	// namespace detail

template <typename Iter>
using bidirectional_iterator =
	typename detail::bidirectional_iterator_impl<Iter>::type;

#endif

}	// namespace hamon

#endif

#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{

template <typename Iter>
using bidirectional_iterator_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::bidirectional_iterator<Iter>>;
#else
	hamon::bidirectional_iterator<Iter>;
#endif

}	// namespace hamon

#endif // HAMON_ITERATOR_CONCEPTS_BIDIRECTIONAL_ITERATOR_HPP
