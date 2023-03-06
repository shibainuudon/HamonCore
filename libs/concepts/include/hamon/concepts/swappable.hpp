/**
 *	@file	swappable.hpp
 *
 *	@brief	swappable の定義
 */

#ifndef HAMON_CONCEPTS_SWAPPABLE_HPP
#define HAMON_CONCEPTS_SWAPPABLE_HPP

#include <hamon/concepts/config.hpp>
#include <hamon/concepts/swap.hpp>

#if defined(HAMON_USE_STD_CONCEPTS)

namespace hamon
{

using std::swappable;

}	// namespace hamon

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

namespace hamon
{

template <typename T>
concept swappable =
	requires(T& a, T& b) { ranges::swap(a, b); };

}	// namespace hamon

#else

#include <hamon/type_traits/bool_constant.hpp>
#include <utility>

namespace hamon
{

namespace detail
{

template <typename T>
struct swappable_impl
{
private:
	template <typename U,
		typename = decltype(
			ranges::swap(std::declval<U&>(), std::declval<U&>()))
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

}	// namespace hamon

#endif

#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{

template <typename T>
using swappable_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::swappable<T>>;
#else
	hamon::swappable<T>;
#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_SWAPPABLE_HPP
