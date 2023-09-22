/**
 *	@file	indirectly_copyable_storable.hpp
 *
 *	@brief	indirectly_copyable_storable の定義
 */

#ifndef HAMON_ITERATOR_CONCEPTS_INDIRECTLY_COPYABLE_STORABLE_HPP
#define HAMON_ITERATOR_CONCEPTS_INDIRECTLY_COPYABLE_STORABLE_HPP

#include <hamon/iterator/config.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

#if !defined(HAMON_USE_STD_RANGES_ITERATOR)
#include <hamon/iterator/concepts/indirectly_copyable.hpp>
#include <hamon/iterator/concepts/indirectly_writable.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/concepts/copyable.hpp>
#include <hamon/concepts/constructible_from.hpp>
#include <hamon/concepts/assignable_from.hpp>
#include <hamon/type_traits/enable_if.hpp>
#endif

namespace hamon
{

#if defined(HAMON_USE_STD_RANGES_ITERATOR)

using std::indirectly_copyable_storable;

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename In, typename Out>
concept indirectly_copyable_storable =
	hamon::indirectly_copyable<In, Out>                                             &&
	hamon::indirectly_writable<Out, hamon::iter_value_t<In>&>                       &&
	hamon::indirectly_writable<Out, hamon::iter_value_t<In> const&>                 &&
	hamon::indirectly_writable<Out, hamon::iter_value_t<In>&&>                      &&
	hamon::indirectly_writable<Out, hamon::iter_value_t<In> const&&>                &&
	hamon::copyable<hamon::iter_value_t<In>>                                        &&
	hamon::constructible_from<hamon::iter_value_t<In>, hamon::iter_reference_t<In>> &&
	hamon::assignable_from<hamon::iter_value_t<In>&, hamon::iter_reference_t<In>>;

#else

namespace detail
{

template <typename In, typename Out>
struct indirectly_copyable_storable_impl
{
private:
	template <typename I, typename O,
		typename = hamon::enable_if_t<hamon::indirectly_copyable<I, O>::value>,
		typename V = hamon::iter_value_t<I>,
		typename = hamon::enable_if_t<hamon::indirectly_writable<O, V&>::value>,
		typename = hamon::enable_if_t<hamon::indirectly_writable<O, V const&>::value>,
		typename = hamon::enable_if_t<hamon::indirectly_writable<O, V&&>::value>,
		typename = hamon::enable_if_t<hamon::indirectly_writable<O, V const&&>::value>,
		typename = hamon::enable_if_t<hamon::copyable<V>::value>,
		typename R = hamon::iter_reference_t<I>,
		typename = hamon::enable_if_t<hamon::constructible_from<V, R>::value>,
		typename = hamon::enable_if_t<hamon::assignable_from<V&, R>::value>
	>
	static auto test(int) -> hamon::true_type;

	template <typename I, typename O>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<In, Out>(0));
};

}	// namespace detail

template <typename In, typename Out>
using indirectly_copyable_storable =
	typename detail::indirectly_copyable_storable_impl<In, Out>::type;

#endif

template <typename In, typename Out>
using indirectly_copyable_storable_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::indirectly_copyable_storable<In, Out>>;
#else
	hamon::indirectly_copyable_storable<In, Out>;
#endif

}	// namespace hamon

#endif // HAMON_ITERATOR_CONCEPTS_INDIRECTLY_COPYABLE_STORABLE_HPP
