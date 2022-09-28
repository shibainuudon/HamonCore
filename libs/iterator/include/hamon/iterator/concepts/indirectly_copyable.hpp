﻿/**
 *	@file	indirectly_copyable.hpp
 *
 *	@brief	indirectly_copyable の定義
 */

#ifndef HAMON_ITERATOR_CONCEPTS_INDIRECTLY_COPYABLE_HPP
#define HAMON_ITERATOR_CONCEPTS_INDIRECTLY_COPYABLE_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ITERATOR)

namespace hamon
{

using std::indirectly_copyable;

}	// namespace hamon

#else

#include <hamon/iterator/concepts/indirectly_readable.hpp>
#include <hamon/iterator/concepts/indirectly_writable.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename In, typename Out>
concept indirectly_copyable =
	hamon::indirectly_readable<In> &&
	hamon::indirectly_writable<Out, hamon::iter_reference_t<In>>;

#else

namespace detail
{

template <typename In, typename Out>
struct indirectly_copyable_impl
{
private:
	template <typename I, typename O,
		typename = hamon::enable_if_t<hamon::indirectly_readable<I>::value>,
		typename R = hamon::iter_reference_t<I>,
		typename = hamon::enable_if_t<hamon::indirectly_writable<O, R>::value>
	>
	static auto test(int) -> std::true_type;

	template <typename I, typename O>
	static auto test(...) -> std::false_type;

public:
	using type = decltype(test<In, Out>(0));
};

}	// namespace detail

template <typename In, typename Out>
using indirectly_copyable =
	typename detail::indirectly_copyable_impl<In, Out>::type;

#endif

}	// namespace hamon

#endif

#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{

template <typename In, typename Out>
using indirectly_copyable_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::indirectly_copyable<In, Out>>;
#else
	hamon::indirectly_copyable<In, Out>;
#endif

}	// namespace hamon

#endif // HAMON_ITERATOR_CONCEPTS_INDIRECTLY_COPYABLE_HPP