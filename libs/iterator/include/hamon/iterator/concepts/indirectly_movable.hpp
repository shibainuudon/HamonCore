/**
 *	@file	indirectly_movable.hpp
 *
 *	@brief	indirectly_movable の定義
 */

#ifndef HAMON_ITERATOR_CONCEPTS_INDIRECTLY_MOVABLE_HPP
#define HAMON_ITERATOR_CONCEPTS_INDIRECTLY_MOVABLE_HPP

#include <hamon/iterator/concepts/indirectly_readable.hpp>
#include <hamon/iterator/concepts/indirectly_writable.hpp>
#include <hamon/iterator/iter_rvalue_reference_t.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>

namespace hamon
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename In, typename Out>
HAMON_CONCEPT_OR_BOOL indirectly_movable =
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
		typename = hamon::enable_if_t<hamon::indirectly_readable<I>>,
		typename R = hamon::iter_rvalue_reference_t<I>,
		typename = hamon::enable_if_t<hamon::indirectly_writable<O, R>>
	>
	static auto test(int) -> hamon::true_type;

	template <typename I, typename O>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<In, Out>(0));
};

}	// namespace detail

template <typename In, typename Out>
HAMON_CONCEPT_OR_BOOL indirectly_movable =
	detail::indirectly_movable_impl<In, Out>::type::value;

#endif

}	// namespace hamon

#endif // HAMON_ITERATOR_CONCEPTS_INDIRECTLY_MOVABLE_HPP
