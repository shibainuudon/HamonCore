/**
 *	@file	swappable_with.hpp
 *
 *	@brief	swappable_with の定義
 */

#ifndef HAMON_CONCEPTS_SWAPPABLE_WITH_HPP
#define HAMON_CONCEPTS_SWAPPABLE_WITH_HPP

#include <hamon/concepts/config.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#if !defined(HAMON_USE_STD_CONCEPTS)
#include <hamon/concepts/common_reference_with.hpp>
#include <hamon/concepts/swap.hpp>
#include <hamon/utility/declval.hpp>
#endif

namespace hamon
{

// 18.4.9 Concept swappable	[concept.swappable]

#if defined(HAMON_USE_STD_CONCEPTS)

using std::swappable_with;

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T, typename U>
concept swappable_with =
	hamon::common_reference_with<T, U> &&
	requires(T&& t, U&& u)
	{
		ranges::swap(static_cast<T&&>(t), static_cast<T&&>(t));
		ranges::swap(static_cast<U&&>(u), static_cast<U&&>(u));
		ranges::swap(static_cast<T&&>(t), static_cast<U&&>(u));
		ranges::swap(static_cast<U&&>(u), static_cast<T&&>(t));
	};

#else

namespace detail
{

template <typename T, typename U>
struct swappable_with_impl
{
private:
	template <typename T2, typename U2,
		typename = decltype(
			ranges::swap(hamon::declval<T2>(), hamon::declval<T2>()),
			ranges::swap(hamon::declval<U2>(), hamon::declval<U2>()),
			ranges::swap(hamon::declval<T2>(), hamon::declval<U2>()),
			ranges::swap(hamon::declval<U2>(), hamon::declval<T2>()))
	>
	static auto test(int) -> hamon::common_reference_with<T2, U2>;

	template <typename T2, typename U2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T, U>(0));
};

}	// namespace detail

template <typename T, typename U>
using swappable_with =
	typename detail::swappable_with_impl<T, U>::type;

#endif

template <typename T, typename U>
using swappable_with_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::swappable_with<T, U>>;
#else
	hamon::swappable_with<T, U>;
#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_SWAPPABLE_WITH_HPP
