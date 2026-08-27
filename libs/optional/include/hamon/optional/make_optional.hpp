/**
 *	@file	make_optional.hpp
 *
 *	@brief	make_optional の定義
 */

#ifndef HAMON_OPTIONAL_MAKE_OPTIONAL_HPP
#define HAMON_OPTIONAL_MAKE_OPTIONAL_HPP

#include <hamon/optional/optional.hpp>
#include <hamon/initializer_list.hpp>
#include <hamon/type_traits/decay.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/in_place_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{

template <typename T>
HAMON_NODISCARD	// extension
inline HAMON_CXX11_CONSTEXPR hamon::optional<hamon::decay_t<T>>
make_optional(T&& v)
{
	return hamon::optional<hamon::decay_t<T>>(hamon::forward<T>(v));
}

template <typename T, typename... Args>
HAMON_NODISCARD	// extension
inline HAMON_CXX11_CONSTEXPR hamon::optional<T>
make_optional(Args&&... args)
{
	return hamon::optional<T>(hamon::in_place, hamon::forward<Args>(args)...);
}

template <typename T, typename U, typename... Args>
HAMON_NODISCARD	// extension
inline HAMON_CXX14_CONSTEXPR hamon::optional<T>
make_optional(hamon::initializer_list<U> il, Args&&... args)
{
	return hamon::optional<T>(hamon::in_place, il, hamon::forward<Args>(args)...);
}

}	// namespace hamon

#endif // HAMON_OPTIONAL_MAKE_OPTIONAL_HPP
