/**
 *	@file	cref.hpp
 *
 *	@brief	cref 関数テンプレートの定義
 */

#ifndef HAMON_FUNCTIONAL_CREF_HPP
#define HAMON_FUNCTIONAL_CREF_HPP

#include <hamon/functional/reference_wrapper.hpp>
#include <hamon/config.hpp>

namespace hamon
{

template <typename T>
HAMON_CONSTEXPR
inline hamon::reference_wrapper<T const>
cref(T const& t) noexcept
{
	return hamon::reference_wrapper<T const>(t);
}

template <typename T>
void cref(T const&&) = delete;

template <typename T>
HAMON_CONSTEXPR
inline hamon::reference_wrapper<T const>
cref(hamon::reference_wrapper<T> t) noexcept
{
	return { t.get() };
}

}	// namespace hamon

#endif // HAMON_FUNCTIONAL_CREF_HPP
