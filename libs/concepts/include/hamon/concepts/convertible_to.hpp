/**
 *	@file	convertible_to.hpp
 *
 *	@brief	convertible_to の定義
 */

#ifndef HAMON_CONCEPTS_CONVERTIBLE_TO_HPP
#define HAMON_CONCEPTS_CONVERTIBLE_TO_HPP

#include <hamon/concepts/config.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <type_traits>
#include <utility>

namespace hamon
{

#if defined(HAMON_USE_STD_CONCEPTS)

using std::convertible_to;

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename From, typename To>
concept convertible_to =
	std::is_convertible<From, To>::value &&
	requires(std::add_rvalue_reference_t<From> (&f)())
	{
		static_cast<To>(f());
	};

#else

namespace detail
{

template <typename From, typename To>
struct convertible_to_impl
{
private:
	template <typename F, typename T,
		typename = hamon::enable_if_t<std::is_convertible<F, T>::value>,
		typename Func = typename std::add_rvalue_reference<F>::type (&)(),
		typename = decltype(static_cast<T>(std::declval<Func>()()))
	>
	static auto test(int) -> std::true_type;

	template <typename F, typename T>
	static auto test(...) -> std::false_type;

public:
	using type = decltype(test<From, To>(0));
};

}	// namespace detail

template <typename From, typename To>
using convertible_to =
	typename detail::convertible_to_impl<From, To>::type;

#endif

template <typename From, typename To>
using convertible_to_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::convertible_to<From, To>>;
#else
	hamon::convertible_to<From, To>;
#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_CONVERTIBLE_TO_HPP
