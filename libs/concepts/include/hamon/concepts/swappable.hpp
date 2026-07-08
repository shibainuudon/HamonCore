/**
 *	@file	swappable.hpp
 *
 *	@brief	swappable の定義
 */

#ifndef HAMON_CONCEPTS_SWAPPABLE_HPP
#define HAMON_CONCEPTS_SWAPPABLE_HPP

#include <hamon/concepts/config.hpp>
#if !defined(HAMON_USE_STD_CONCEPTS)
#include <hamon/concepts/swap.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/utility/declval.hpp>
#endif
#include <hamon/config.hpp>

namespace hamon
{

// 18.4.9 Concept swappable	[concept.swappable]

#if defined(HAMON_USE_STD_CONCEPTS)

using std::swappable;

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
HAMON_CONCEPT_OR_BOOL swappable =
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
HAMON_CONCEPT_OR_BOOL swappable =
	detail::swappable_impl<T>::type::value;

#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_SWAPPABLE_HPP
