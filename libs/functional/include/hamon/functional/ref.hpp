/**
 *	@file	ref.hpp
 *
 *	@brief	ref 関数テンプレートの定義
 */

#ifndef HAMON_FUNCTIONAL_REF_HPP
#define HAMON_FUNCTIONAL_REF_HPP

#include <hamon/functional/reference_wrapper.hpp>
#include <hamon/config.hpp>

namespace hamon
{

template <typename T>
HAMON_CONSTEXPR
inline hamon::reference_wrapper<T>
ref(T& t) noexcept
{
	return hamon::reference_wrapper<T>(t);
}

template <typename T>
void ref(T const&&) = delete;

template <typename T>
HAMON_CONSTEXPR
inline hamon::reference_wrapper<T>
ref(hamon::reference_wrapper<T> t) noexcept
{
	return t;
}

}	// namespace hamon

#endif // HAMON_FUNCTIONAL_REF_HPP
