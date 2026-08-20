/**
 *	@file	equality_comparable_with.hpp
 *
 *	@brief	equality_comparable_with の定義
 */

#ifndef HAMON_CONCEPTS_EQUALITY_COMPARABLE_WITH_HPP
#define HAMON_CONCEPTS_EQUALITY_COMPARABLE_WITH_HPP

#include <hamon/concepts/equality_comparable.hpp>
#include <hamon/concepts/detail/comparison_common_type_with.hpp>
#include <hamon/concepts/detail/weakly_equality_comparable_with.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/common_reference.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/remove_reference.hpp>

namespace hamon
{

// 18.5.4 Concept equality_comparable	[concept.equalitycomparable]

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T, typename U>
HAMON_CONCEPT_OR_BOOL equality_comparable_with =
	hamon::equality_comparable<T> &&
	hamon::equality_comparable<U> &&
	detail::comparison_common_type_with<T, U> &&
	hamon::equality_comparable<
		hamon::common_reference_t<
			hamon::remove_reference_t<T> const&,
			hamon::remove_reference_t<U> const&
		>
	> &&
	detail::weakly_equality_comparable_with<T, U>;

#else

namespace detail
{

template <typename T, typename U>
struct equality_comparable_with_impl
{
private:
	template <typename T2, typename U2,
		typename = hamon::enable_if_t<
			hamon::equality_comparable<T2> &&
			hamon::equality_comparable<U2> &&
			detail::comparison_common_type_with<T2, U2> &&
			hamon::equality_comparable<
				hamon::common_reference_t<
					hamon::remove_reference_t<T2> const&,
					hamon::remove_reference_t<U2> const&
				>
			> &&
			detail::weakly_equality_comparable_with<T2, U2>
		>
	>
	static auto test(int) -> hamon::true_type;

	template <typename T2, typename U2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T, U>(0));
};

}	// namespace detail

template <typename T, typename U>
HAMON_CONCEPT_OR_BOOL equality_comparable_with =
	detail::equality_comparable_with_impl<T, U>::type::value;

#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_EQUALITY_COMPARABLE_WITH_HPP
