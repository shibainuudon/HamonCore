/**
 *	@file	indirectly_movable.hpp
 *
 *	@brief	indirectly_movable の定義
 */

#ifndef HAMON_ITERATOR_CONCEPTS_INDIRECTLY_MOVABLE_HPP
#define HAMON_ITERATOR_CONCEPTS_INDIRECTLY_MOVABLE_HPP

#include <hamon/iterator/config.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

#if !defined(HAMON_USE_STD_RANGES_ITERATOR)
#include <hamon/iterator/concepts/indirectly_readable.hpp>
#include <hamon/iterator/concepts/indirectly_writable.hpp>
#include <hamon/iterator/iter_rvalue_reference_t.hpp>
#include <hamon/type_traits/enable_if.hpp>
#endif

namespace hamon
{

#if defined(HAMON_USE_STD_RANGES_ITERATOR)

using std::indirectly_movable;

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename In, typename Out>
concept indirectly_movable =
	hamon::indirectly_readable<In> &&
	hamon::indirectly_writable<Out, hamon::iter_rvalue_reference_t<In>>;

#else

namespace detail
{

template <typename In, typename Out>
struct indirectly_movable_impl
{
private:
	template <typename I, typename O,
		typename = hamon::enable_if_t<hamon::indirectly_readable<I>::value>,
		typename R = hamon::iter_rvalue_reference_t<I>,
		typename = hamon::enable_if_t<hamon::indirectly_writable<O, R>::value>
	>
	static auto test(int) -> hamon::true_type;

	template <typename I, typename O>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<In, Out>(0));
};

}	// namespace detail

template <typename In, typename Out>
using indirectly_movable =
	typename detail::indirectly_movable_impl<In, Out>::type;

#endif

template <typename In, typename Out>
using indirectly_movable_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::indirectly_movable<In, Out>>;
#else
	hamon::indirectly_movable<In, Out>;
#endif

}	// namespace hamon

#endif // HAMON_ITERATOR_CONCEPTS_INDIRECTLY_MOVABLE_HPP
