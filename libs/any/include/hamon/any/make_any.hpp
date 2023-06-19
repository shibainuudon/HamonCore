/**
 *	@file	make_any.hpp
 *
 *	@brief	make_any の定義
 */

#ifndef HAMON_ANY_MAKE_ANY_HPP
#define HAMON_ANY_MAKE_ANY_HPP

#include <hamon/any/config.hpp>

#if defined(HAMON_USE_STD_ANY)

#include <any>

namespace hamon
{

using std::make_any;

}	// namespace hamon

#else

#include <hamon/any/any.hpp>
#include <hamon/utility/in_place_type.hpp>
#include <hamon/utility/forward.hpp>
#include <initializer_list>

namespace hamon
{

template <typename T, typename... Args>
HAMON_NODISCARD inline hamon::any
make_any(Args&&... args)
{
	// [any.nonmembers]/2
	return hamon::any(hamon::in_place_type_t<T>{}, hamon::forward<Args>(args)...);
}

template <typename T, typename U, typename... Args>
HAMON_NODISCARD inline hamon::any
make_any(std::initializer_list<U> il, Args&&... args)
{
	// [any.nonmembers]/3
	return hamon::any(hamon::in_place_type_t<T>{}, il, hamon::forward<Args>(args)...);
}

}	// namespace hamon

#endif

#endif // HAMON_ANY_MAKE_ANY_HPP
