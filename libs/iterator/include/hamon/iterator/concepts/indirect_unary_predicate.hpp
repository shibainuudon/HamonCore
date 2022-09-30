/**
 *	@file	indirect_unary_predicate.hpp
 *
 *	@brief	indirect_unary_predicate の定義
 */

#ifndef HAMON_ITERATOR_CONCEPTS_INDIRECT_UNARY_PREDICATE_HPP
#define HAMON_ITERATOR_CONCEPTS_INDIRECT_UNARY_PREDICATE_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ITERATOR)

namespace hamon
{

using std::indirect_unary_predicate;

}	// namespace hamon

#else

#include <hamon/iterator/concepts/indirectly_readable.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/iterator/iter_common_reference_t.hpp>
#include <hamon/concepts/copy_constructible.hpp>
#include <hamon/concepts/predicate.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename F, typename I>
concept indirect_unary_predicate =
	hamon::indirectly_readable<I> &&
	hamon::copy_constructible<F> &&
	hamon::predicate<F&, hamon::iter_value_t<I>&> &&
	hamon::predicate<F&, hamon::iter_reference_t<I>> &&
	hamon::predicate<F&, hamon::iter_common_reference_t<I>>;

#else

namespace detail
{

template <typename F, typename I>
struct indirect_unary_predicate_impl
{
private:
	template <typename F2, typename I2,
		typename = hamon::enable_if_t<hamon::indirectly_readable<I2>::value>,
		typename = hamon::enable_if_t<hamon::copy_constructible<F2>::value>,
		typename = hamon::enable_if_t<hamon::predicate<F2&, hamon::iter_value_t<I2>&>::value>,
		typename = hamon::enable_if_t<hamon::predicate<F2&, hamon::iter_reference_t<I2>>::value>,
		typename = hamon::enable_if_t<hamon::predicate<F2&, hamon::iter_common_reference_t<I2>>::value>
	>
	static auto test(int) -> std::true_type;

	template <typename F2, typename I2>
	static auto test(...) -> std::false_type;

public:
	using type = decltype(test<F, I>(0));
};

}	// namespace detail

template <typename F, typename I>
using indirect_unary_predicate =
	typename detail::indirect_unary_predicate_impl<F, I>::type;

#endif

}	// namespace hamon

#endif

#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{

template <typename F, typename I>
using indirect_unary_predicate_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::indirect_unary_predicate<F, I>>;
#else
	hamon::indirect_unary_predicate<F, I>;
#endif

}	// namespace hamon

#endif // HAMON_ITERATOR_CONCEPTS_INDIRECT_UNARY_PREDICATE_HPP
