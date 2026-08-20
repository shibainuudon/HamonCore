/**
 *	@file	totally_ordered_with.hpp
 *
 *	@brief	totally_ordered_with の定義
 */

#ifndef HAMON_CONCEPTS_TOTALLY_ORDERED_WITH_HPP
#define HAMON_CONCEPTS_TOTALLY_ORDERED_WITH_HPP

#include <hamon/compare/detail/partially_ordered_with.hpp>
#include <hamon/concepts/totally_ordered.hpp>
#include <hamon/concepts/equality_comparable_with.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/common_reference.hpp>
#include <hamon/type_traits/remove_reference.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 18.5.5 Concept totally_ordered	[concept.totallyordered]

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T, typename U>
HAMON_CONCEPT_OR_BOOL totally_ordered_with =
	hamon::totally_ordered<T> &&
	hamon::totally_ordered<U> &&
	hamon::equality_comparable_with<T, U> &&
	hamon::totally_ordered<
		hamon::common_reference_t<
			hamon::remove_reference_t<T> const&,
			hamon::remove_reference_t<U> const&
		>
	> &&
	detail::partially_ordered_with<T, U>;

#else

namespace detail
{

template <typename T, typename U>
struct totally_ordered_with_impl
{
private:
	template <typename T2, typename U2,
		typename = hamon::enable_if_t<
			hamon::totally_ordered<T2> &&
			hamon::totally_ordered<U2> &&
			hamon::equality_comparable_with<T2, U2> &&
			hamon::totally_ordered<
				hamon::common_reference_t<
					hamon::remove_reference_t<T2> const&,
					hamon::remove_reference_t<U2> const&
				>
			> &&
			detail::partially_ordered_with<T2, U2>
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
HAMON_CONCEPT_OR_BOOL totally_ordered_with =
	detail::totally_ordered_with_impl<T, U>::type::value;

#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_TOTALLY_ORDERED_WITH_HPP
