/**
 *	@file	convertible_to.hpp
 *
 *	@brief	convertible_to の定義
 */

#ifndef HAMON_CONCEPTS_CONVERTIBLE_TO_HPP
#define HAMON_CONCEPTS_CONVERTIBLE_TO_HPP

#include <hamon/concepts/config.hpp>
#if !defined(HAMON_USE_STD_CONCEPTS)
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_convertible.hpp>
#include <hamon/utility/declval.hpp>
#endif
#include <hamon/config.hpp>

namespace hamon
{

// 18.4.4 Concept convertible_to	[concept.convertible]

#if defined(HAMON_USE_STD_CONCEPTS)

using std::convertible_to;

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename From, typename To>
HAMON_CONCEPT_OR_BOOL convertible_to =
	hamon::is_convertible<From, To>::value &&
	requires
	{
		static_cast<To>(hamon::declval<From>());
	};

#else

namespace detail
{

template <typename From, typename To>
struct convertible_to_impl
{
private:
	template <typename F, typename T,
		typename = hamon::enable_if_t<hamon::is_convertible<F, T>::value>,
		typename = decltype(static_cast<T>(hamon::declval<F>()))
	>
	static auto test(int) -> hamon::true_type;

	template <typename F, typename T>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<From, To>(0));
};

}	// namespace detail

template <typename From, typename To>
HAMON_CONCEPT_OR_BOOL convertible_to =
	detail::convertible_to_impl<From, To>::type::value;

#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_CONVERTIBLE_TO_HPP
