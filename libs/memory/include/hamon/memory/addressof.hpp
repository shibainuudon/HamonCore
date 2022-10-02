/**
 *	@file	addressof.hpp
 *
 *	@brief	addressof の定義
 */

#ifndef HAMON_MEMORY_ADDRESSOF_HPP
#define HAMON_MEMORY_ADDRESSOF_HPP

#include <memory>

#if defined(__cpp_lib_addressof_constexpr) && (__cpp_lib_addressof_constexpr >= 201603)

namespace hamon
{

using std::addressof;

}	// namespace hamon

#else

#include <hamon/memory/detail/addressof_impl.hpp>
#include <hamon/type_traits/remove_cv.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief	変数のアドレスを必ず取得する
 *
 *	operator&をオーバーロードしたクラスであっても、そのオブジェクトのアドレスを取得できる。
 *
 *	operator&がオーバーロードされていない場合、constexprにできる。
 *	operator&がオーバーロードされている場合、constexprにできない。
 *	(C++17以降はstd::addressofがconstexprになるのでconstexprにできる)
 */
template <typename T>
HAMON_CONSTEXPR T* addressof(T& r) HAMON_NOEXCEPT
{
	return detail::addressof_impl<hamon::remove_cv_t<T>>::get(r);
}

}	// namespace hamon

#endif

#endif // HAMON_MEMORY_ADDRESSOF_HPP
