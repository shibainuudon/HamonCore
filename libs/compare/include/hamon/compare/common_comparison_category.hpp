/**
 *	@file	common_comparison_category.hpp
 *
 *	@brief	common_comparison_category の定義
 */

#ifndef HAMON_COMPARE_COMMON_COMPARISON_CATEGORY_HPP
#define HAMON_COMPARE_COMMON_COMPARISON_CATEGORY_HPP

#include <hamon/compare/config.hpp>

#if defined(HAMON_USE_STD_COMPARE)

#include <compare>

namespace hamon
{

using std::common_comparison_category;
using std::common_comparison_category_t;

}	// namespace hamon

#else

#include <hamon/compare/partial_ordering.hpp>
#include <hamon/compare/weak_ordering.hpp>
#include <hamon/compare/strong_ordering.hpp>
#include <hamon/compare/detail/cmp_cat_id.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/config.hpp>

namespace hamon
{

template <typename... Ts>
struct common_comparison_category
{
private:
#if defined(HAMON_HAS_CXX17_FOLD_EXPRESSIONS) && !(defined(HAMON_MSVC) && (HAMON_MSVC < 1920))
	static constexpr unsigned cats = (detail::cmp_cat_id<Ts>::value | ...);
#else
	template <typename A0, typename A1, typename... Args>
	static constexpr unsigned int get_cats(A0 a0, A1 a1, Args... args)
	{
		return get_cats(a0 | a1, args...);
	}
	template <typename A0>
	static constexpr unsigned int get_cats(A0 a0)
	{
		return a0;
	}
	static constexpr unsigned cats = get_cats(detail::cmp_cat_id<Ts>::value...);
#endif

public:
	using type =
		hamon::conditional_t<
			// If any Ti is not a comparison category type, U is void.
			bool(cats & 1),
			void,
		hamon::conditional_t<
			// Otherwise, if at least one Ti is std::partial_ordering,
			// U is std::partial_ordering.
			bool(cats & detail::cmp_cat_id<hamon::partial_ordering>::value),
			hamon::partial_ordering,
		hamon::conditional_t<
			// Otherwise, if at least one Ti is std::weak_ordering,
			// U is std::weak_ordering.
			bool(cats & detail::cmp_cat_id<hamon::weak_ordering>::value),
			hamon::weak_ordering,
			// Otherwise, U is std::strong_ordering.
			hamon::strong_ordering
		>>>;
};

// Partial specializations for one and zero argument cases.

template <typename T>
struct common_comparison_category<T>
{
	using type = void;
};

template <>
struct common_comparison_category<hamon::partial_ordering>
{
	using type = hamon::partial_ordering;
};

template <>
struct common_comparison_category<hamon::weak_ordering>
{
	using type = hamon::weak_ordering;
};

template <>
struct common_comparison_category<hamon::strong_ordering>
{
	using type = hamon::strong_ordering;
};

template <>
struct common_comparison_category<>
{
	using type = hamon::strong_ordering;
};

template <typename... Ts>
using common_comparison_category_t =
	typename common_comparison_category<Ts...>::type;


}	// namespace hamon

#endif

#endif // HAMON_COMPARE_COMMON_COMPARISON_CATEGORY_HPP
