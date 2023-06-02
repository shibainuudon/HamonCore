/**
 *	@file	make_optional.hpp
 *
 *	@brief	make_optional の定義
 */

#ifndef HAMON_OPTIONAL_MAKE_OPTIONAL_HPP
#define HAMON_OPTIONAL_MAKE_OPTIONAL_HPP

#include <hamon/optional/config.hpp>

#if defined(HAMON_USE_STD_OPTIONAL)

#include <optional>

namespace hamon
{

using std::make_optional;

}	// namespace hamon

#else

#include <hamon/optional/optional.hpp>
#include <hamon/type_traits/decay.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/in_place.hpp>
#include <hamon/config.hpp>
#include <initializer_list>

namespace hamon
{

template <typename T>
inline HAMON_CXX11_CONSTEXPR hamon::optional<hamon::decay_t<T>>
make_optional(T&& v)
{
	return hamon::optional<hamon::decay_t<T>>(hamon::forward<T>(v));
}

template <typename T, typename... Args>
inline HAMON_CXX11_CONSTEXPR hamon::optional<T>
make_optional(Args&&... args)
{
	return hamon::optional<T>(hamon::in_place, hamon::forward<Args>(args)...);
}

template <typename T, typename U, typename... Args>
inline HAMON_CXX14_CONSTEXPR hamon::optional<T>
make_optional(std::initializer_list<U> il, Args&&... args)
{
	return hamon::optional<T>(hamon::in_place, il, hamon::forward<Args>(args)...);
}

}	// namespace hamon

#endif

#endif // HAMON_OPTIONAL_MAKE_OPTIONAL_HPP
