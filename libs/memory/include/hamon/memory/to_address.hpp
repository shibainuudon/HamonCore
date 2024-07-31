/**
 *	@file	to_address.hpp
 *
 *	@brief	to_address の定義
 */

#ifndef HAMON_MEMORY_TO_ADDRESS_HPP
#define HAMON_MEMORY_TO_ADDRESS_HPP

#include <hamon/memory/pointer_traits.hpp>
#include <memory>

#if defined(__cpp_lib_to_address) && (__cpp_lib_to_address >= 201711) &&			\
	defined(__cpp_lib_constexpr_memory) && (__cpp_lib_constexpr_memory >= 201811L) &&	\
	defined(HAMON_USE_STD_POINTER_TRAITS)

namespace hamon
{

using std::to_address;

}	// namespace hamon

#else

#include <hamon/memory/detail/to_address_impl.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief		ポインタと見なせるオブジェクトからアドレスを取得する。
 *
 *	@param		p	仮想的なポインタ
 *
 *	@return		式pointer_traits<Ptr>::to_address(p)が有効であればその戻り値を返す。
 *				そうでなければ、to_address(p.operator->())を返す
 */
template <typename Ptr>
HAMON_CONSTEXPR auto
to_address(const Ptr& p) HAMON_NOEXCEPT
->decltype(detail::to_address_impl(p))
{
	return detail::to_address_impl(p);
}

/**
 *	@brief		ポインタと見なせるオブジェクトからアドレスを取得する。
 *
 *	@param		p	生ポインタ
 *
 *	@require	型Tが関数ではないこと
 *
 *	@return		pを返す
 */
template <typename T>
HAMON_CONSTEXPR T*
to_address(T* p) HAMON_NOEXCEPT
{
	return detail::to_address_impl(p);
}

}	// namespace hamon

#endif

#endif // HAMON_MEMORY_TO_ADDRESS_HPP
