/**
 *	@file	forward_iterator.hpp
 *
 *	@brief	forward_iterator の定義
 */

#ifndef HAMON_ITERATOR_CONCEPTS_FORWARD_ITERATOR_HPP
#define HAMON_ITERATOR_CONCEPTS_FORWARD_ITERATOR_HPP

#include <hamon/iterator/config.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

#if !defined(HAMON_USE_STD_RANGES_ITERATOR)
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/iterator/concepts/incrementable.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/detail/iter_concept.hpp>
#include <hamon/concepts/derived_from.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#endif

namespace hamon
{

#if defined(HAMON_USE_STD_RANGES_ITERATOR)

using std::forward_iterator;

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename Iter>
HAMON_CONCEPT_OR_BOOL forward_iterator =
	hamon::input_iterator<Iter> &&
	hamon::derived_from<hamon::detail::iter_concept<Iter>, hamon::forward_iterator_tag> &&
	hamon::incrementable<Iter> &&
	hamon::sentinel_for<Iter, Iter>;

#else

namespace detail
{

template <typename Iter>
struct forward_iterator_impl
{
private:
	template <typename I2,
		typename = hamon::enable_if_t<
			hamon::input_iterator<I2>
		>,
		typename = hamon::enable_if_t<
			hamon::derived_from<
				hamon::detail::iter_concept<I2>,
				hamon::forward_iterator_tag
			>
		>,
		typename = hamon::enable_if_t<
			hamon::incrementable<I2>
		>,
		typename = hamon::enable_if_t<
			hamon::sentinel_for<I2, I2>
		>
	>
	static auto test(int) -> hamon::true_type;

	template <typename I2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<Iter>(0));
};

}	// namespace detail

template <typename Iter>
HAMON_CONCEPT_OR_BOOL forward_iterator =
	detail::forward_iterator_impl<Iter>::type::value;

#endif

}	// namespace hamon

#endif // HAMON_ITERATOR_CONCEPTS_FORWARD_ITERATOR_HPP
