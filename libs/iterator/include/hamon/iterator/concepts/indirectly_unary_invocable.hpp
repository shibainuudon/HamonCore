/**
 *	@file	indirectly_unary_invocable.hpp
 *
 *	@brief	indirectly_unary_invocable の定義
 */

#ifndef HAMON_ITERATOR_CONCEPTS_INDIRECTLY_UNARY_INVOCABLE_HPP
#define HAMON_ITERATOR_CONCEPTS_INDIRECTLY_UNARY_INVOCABLE_HPP

#include <hamon/iterator/config.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

#if !defined(HAMON_USE_STD_RANGES_ITERATOR)
#include <hamon/iterator/concepts/indirectly_readable.hpp>
#include <hamon/iterator/detail/indirect_value_t.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/iterator/iter_common_reference_t.hpp>
#include <hamon/concepts/copy_constructible.hpp>
#include <hamon/concepts/invocable.hpp>
#include <hamon/concepts/common_reference_with.hpp>
#include <hamon/type_traits/invoke_result.hpp>
#include <hamon/type_traits/enable_if.hpp>
#endif

namespace hamon
{

#if defined(HAMON_USE_STD_RANGES_ITERATOR)

using std::indirectly_unary_invocable;

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename F, typename I>
concept indirectly_unary_invocable =
	hamon::indirectly_readable<I> &&
	hamon::copy_constructible<F> &&
	hamon::invocable<F&, hamon::detail::indirect_value_t<I>> &&
	hamon::invocable<F&, hamon::iter_reference_t<I>> &&
	hamon::invocable<F&, hamon::iter_common_reference_t<I>> &&
	hamon::common_reference_with<
		hamon::invoke_result_t<F&, hamon::detail::indirect_value_t<I>>,
		hamon::invoke_result_t<F&, hamon::iter_reference_t<I>>
	>;

#else

namespace detail
{

template <typename F, typename I>
struct indirectly_unary_invocable_impl
{
private:
	template <typename F2, typename I2,
		typename = hamon::enable_if_t<hamon::indirectly_readable<I2>::value>,
		typename = hamon::enable_if_t<hamon::copy_constructible<F2>::value>,
		typename V = hamon::detail::indirect_value_t<I2>,
		typename = hamon::enable_if_t<hamon::invocable<F2&, V>::value>,
		typename R = hamon::iter_reference_t<I2>,
		typename = hamon::enable_if_t<hamon::invocable<F2&, R>::value>,
		typename C = hamon::iter_common_reference_t<I2>,
		typename = hamon::enable_if_t<hamon::invocable<F2&, C>::value>,
		typename = hamon::enable_if_t<
			hamon::common_reference_with<
				hamon::invoke_result_t<F2&, V>,
				hamon::invoke_result_t<F2&, R>
			>::value
		>
	>
	static auto test(int) -> hamon::true_type;

	template <typename F2, typename I2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<F, I>(0));
};

}	// namespace detail

template <typename F, typename I>
using indirectly_unary_invocable =
	typename detail::indirectly_unary_invocable_impl<F, I>::type;

#endif

template <typename F, typename I>
using indirectly_unary_invocable_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::indirectly_unary_invocable<F, I>>;
#else
	hamon::indirectly_unary_invocable<F, I>;
#endif

}	// namespace hamon

#endif // HAMON_ITERATOR_CONCEPTS_INDIRECTLY_UNARY_INVOCABLE_HPP
