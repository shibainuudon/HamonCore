/**
 *	@file	comparison_common_type_with.hpp
 *
 *	@brief	comparison_common_type_with の定義
 */

#ifndef HAMON_CONCEPTS_DETAIL_COMPARISON_COMMON_TYPE_WITH_HPP
#define HAMON_CONCEPTS_DETAIL_COMPARISON_COMMON_TYPE_WITH_HPP

#include <hamon/concepts/same_as.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/type_traits/common_reference.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

// 18.5.3 Comparison common types	[concept.comparisoncommontype]

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T, typename U, typename C = hamon::common_reference_t<T const&, U const&>>
concept comparison_common_type_with_impl =
	hamon::same_as<
		hamon::common_reference_t<T const&, U const&>,
		hamon::common_reference_t<U const&, T const&>
	> &&
	requires {
		requires hamon::convertible_to<T const&, C const&> || hamon::convertible_to<T, C const&>;
		requires hamon::convertible_to<U const&, C const&> || hamon::convertible_to<U, C const&>;
	};

template <typename T, typename U>
concept comparison_common_type_with =
	comparison_common_type_with_impl<hamon::remove_cvref_t<T>, hamon::remove_cvref_t<U>>;

#else

template <typename T, typename U>
struct comparison_common_type_with_impl
{
private:
	template <
		typename T2, typename U2,
		typename C = hamon::common_reference_t<T2 const&, U2 const&>,
		typename = hamon::enable_if_t<
			hamon::same_as<
				hamon::common_reference_t<T2 const&, U2 const&>,
				hamon::common_reference_t<U2 const&, T2 const&>
			>::value
		>,
		typename = hamon::enable_if_t<
			hamon::convertible_to<T2 const&, C const&>::value ||
			hamon::convertible_to<T2, C const&>::value
		>,
		typename = hamon::enable_if_t<
			hamon::convertible_to<U2 const&, C const&>::value ||
			hamon::convertible_to<U2, C const&>::value
		>
	>
	static auto test(int) -> hamon::true_type;

	template <typename T2, typename U2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T, U>(0));
};

template <typename T, typename U>
using comparison_common_type_with =
	typename comparison_common_type_with_impl<hamon::remove_cvref_t<T>, hamon::remove_cvref_t<U>>::type;

#endif

template <typename T, typename U>
using comparison_common_type_with_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::detail::comparison_common_type_with<T, U>>;
#else
	hamon::detail::comparison_common_type_with<T, U>;
#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CONCEPTS_DETAIL_COMPARISON_COMMON_TYPE_WITH_HPP
