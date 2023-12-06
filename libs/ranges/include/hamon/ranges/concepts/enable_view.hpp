/**
 *	@file	enable_view.hpp
 *
 *	@brief	enable_view の定義
 */

#ifndef HAMON_RANGES_CONCEPTS_ENABLE_VIEW_HPP
#define HAMON_RANGES_CONCEPTS_ENABLE_VIEW_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES)

namespace hamon
{
namespace ranges
{

using std::ranges::enable_view;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/view_base.hpp>
#include <hamon/ranges/utility/view_interface_fwd.hpp>
#include <hamon/concepts/derived_from.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_detected.hpp>
#include <hamon/type_traits/is_convertible.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace ranges
{

namespace detail
{

// [range.view]/6

template <
	typename O, typename Y
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
	, typename = hamon::enable_if_t<
		hamon::is_convertible<O*, hamon::ranges::view_interface<Y>*>::value
	>
#endif
>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
requires hamon::is_convertible<O*, hamon::ranges::view_interface<Y>*>::value
#endif
void is_derived_from_view_interface_fn(const O*, const hamon::ranges::view_interface<Y>*);

template <typename T>
using is_derived_from_view_interface =
	decltype(is_derived_from_view_interface_fn((T*)nullptr, (T*)nullptr));

}	// namespace_detail

// [range.view]/7

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool enable_view =
	derived_from_t<T, hamon::ranges::view_base>::value ||
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	requires { detail::is_derived_from_view_interface_fn((T*)nullptr, (T*)nullptr); };
#else
	hamon::is_detected<detail::is_derived_from_view_interface, T>::value;
#endif

#else

template <typename T>
struct enable_view
{
	HAMON_STATIC_CONSTEXPR bool value =
		derived_from_t<T, hamon::ranges::view_base>::value ||
		hamon::is_detected<detail::is_derived_from_view_interface, T>::value;
};

#endif

}	// namespace ranges
}	// namespace hamon

#endif

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_RANGES_ENABLE_VIEW(...)	\
	::hamon::ranges::enable_view<__VA_ARGS__>

#define HAMON_RANGES_SPECIALIZE_ENABLE_VIEW(Value, ...)		\
	HAMON_INLINE_VAR HAMON_CONSTEXPR						\
	bool enable_view<__VA_ARGS__> = Value

#else

#define HAMON_RANGES_ENABLE_VIEW(...)	\
	::hamon::ranges::enable_view<__VA_ARGS__>::value

#define HAMON_RANGES_SPECIALIZE_ENABLE_VIEW(Value, ...)	\
	struct enable_view<__VA_ARGS__>	                    \
	{	                                                \
		HAMON_STATIC_CONSTEXPR bool value = Value;	    \
	}

#endif

#endif // HAMON_RANGES_CONCEPTS_ENABLE_VIEW_HPP
