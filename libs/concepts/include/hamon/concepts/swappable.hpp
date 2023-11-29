/**
 *	@file	swappable.hpp
 *
 *	@brief	swappable の定義
 */

#ifndef HAMON_CONCEPTS_SWAPPABLE_HPP
#define HAMON_CONCEPTS_SWAPPABLE_HPP

#include <hamon/concepts/config.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#if !defined(HAMON_USE_STD_CONCEPTS)
#include <hamon/concepts/swap.hpp>
#include <hamon/utility/declval.hpp>
#endif

namespace hamon
{

// 18.4.9 Concept swappable	[concept.swappable]

#if defined(HAMON_USE_STD_CONCEPTS)

using std::swappable;

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept swappable =
	requires(T& a, T& b) { ranges::swap(a, b); };

#else

namespace detail
{

template <typename T>
struct swappable_impl
{
private:
	template <typename U,
		typename = decltype(
			ranges::swap(hamon::declval<U&>(), hamon::declval<U&>()))
	>
	static auto test(int) -> hamon::true_type;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

}	// namespace detail

template <typename T>
using swappable =
	typename detail::swappable_impl<T>::type;

#endif

template <typename T>
using swappable_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::swappable<T>>;
#else
	hamon::swappable<T>;
#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_SWAPPABLE_HPP
