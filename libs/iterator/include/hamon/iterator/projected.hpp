/**
 *	@file	projected.hpp
 *
 *	@brief	projected の定義
 */

#ifndef HAMON_ITERATOR_PROJECTED_HPP
#define HAMON_ITERATOR_PROJECTED_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ITERATOR)

namespace hamon
{

using std::projected;

}	// namespace hamon

#else

#include <hamon/iterator/indirect_result_t.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/iterator/concepts/indirectly_readable.hpp>
#include <hamon/iterator/concepts/indirectly_regular_unary_invocable.hpp>
#include <hamon/iterator/concepts/weakly_incrementable.hpp>
#include <hamon/iterator/detail/indirect_value_t.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/invoke_result.hpp>
#include <hamon/config.hpp>

namespace hamon
{

template <
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::indirectly_readable I,
	hamon::indirectly_regular_unary_invocable<I> Proj
#else
	typename I,
	typename Proj,
	typename = hamon::enable_if_t<
		hamon::indirectly_readable<I>::value &&
		hamon::indirectly_regular_unary_invocable<Proj, I>::value
	>
#endif
>
struct projected
{
	using value_type = hamon::remove_cvref_t<hamon::indirect_result_t<Proj&, I>>;

	hamon::indirect_result_t<Proj&, I> operator*() const; // not defined
};

template <
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::weakly_incrementable I,
#else
	typename I,
#endif
	typename Proj
>
struct incrementable_traits<projected<I, Proj>>
{
	using difference_type = hamon::iter_difference_t<I>;
};

namespace detail
{

// 25.3.6.2 Indirect callable traits[indirectcallable.traits]

template <
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::weakly_incrementable I,
#else
	typename I,
#endif
	typename Proj
>
struct indirect_value_impl<hamon::projected<I, Proj>>
{
	// [indirectcallable.traits]/1.1
	using type = hamon::invoke_result_t<Proj&, hamon::detail::indirect_value_t<I>>;
};

}	// namespace detail

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_PROJECTED_HPP
