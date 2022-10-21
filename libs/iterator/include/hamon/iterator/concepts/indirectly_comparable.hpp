/**
 *	@file	indirectly_comparable.hpp
 *
 *	@brief	indirectly_comparable の定義
 */

#ifndef HAMON_ITERATOR_CONCEPTS_INDIRECTLY_COMPARABLE_HPP
#define HAMON_ITERATOR_CONCEPTS_INDIRECTLY_COMPARABLE_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ITERATOR)

namespace hamon
{

using std::indirectly_comparable;

}	// namespace hamon

#else

#include <hamon/iterator/concepts/indirect_binary_predicate.hpp>
#include <hamon/iterator/projected.hpp>
#include <hamon/functional/identity.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <
	typename I1,
	typename I2,
	typename Rel,
	typename P1 = hamon::identity,
	typename P2 = hamon::identity
>
concept indirectly_comparable =
	hamon::indirect_binary_predicate<Rel, hamon::projected<I1, P1>, hamon::projected<I2, P2>>;

#else

namespace detail
{

template <typename I1, typename I2, typename Rel, typename P1, typename P2>
struct indirectly_comparable_impl
{
private:
	template <typename J1, typename J2, typename R2, typename Q1, typename Q2>
	static auto test(int) -> hamon::indirect_binary_predicate<
		R2, hamon::projected<J1, Q1>, hamon::projected<J2, Q2>>;

	template <typename J1, typename J2, typename R2, typename Q1, typename Q2>
	static auto test(...) -> std::false_type;

public:
	using type = decltype(test<I1, I2, Rel, P1, P2>(0));
};

}	// namespace detail

template <
	typename I1,
	typename I2,
	typename Rel,
	typename P1 = hamon::identity,
	typename P2 = hamon::identity
>
using indirectly_comparable =
	typename detail::indirectly_comparable_impl<I1, I2, Rel, P1, P2>::type;

#endif

}	// namespace hamon

#endif

#include <hamon/functional/identity.hpp>
#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{

template <
	typename I1,
	typename I2,
	typename Rel,
	typename P1 = hamon::identity,
	typename P2 = hamon::identity
>
using indirectly_comparable_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::indirectly_comparable<I1, I2, Rel, P1, P2>>;
#else
	hamon::indirectly_comparable<I1, I2, Rel, P1, P2>;
#endif

}	// namespace hamon

#endif // HAMON_ITERATOR_CONCEPTS_INDIRECTLY_COMPARABLE_HPP
