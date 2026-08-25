/**
 *	@file	bit_cast.hpp
 *
 *	@brief	bit_cast 関数テンプレートを定義
 */

#ifndef HAMON_BIT_BIT_CAST_HPP
#define HAMON_BIT_BIT_CAST_HPP

#include <hamon/cstring/memcpy.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_trivially_copyable.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 22.11.3 Function template bit_cast[bit.cast]

/**
 *	@brief	ビットレベルの再解釈キャスト
 *
 *	@tparam	To		キャスト先の型
 *	@tparam	From	キャスト元の型
 *
 *	@param	src		キャストする値
 *
 *	@return	srcのビット値を維持したまま型Toの値を返す
 *
 *	以下の条件のいずれかを満たさない場合、この関数はオーバーロード解決の候補から除外される：
 *	・sizeof(To) == sizeof(From)であること
 *	・is_trivially_copyable_v<To> == trueであること
 *	・is_trivially_copyable_v<From> == trueであること
 *
 *	型ToとFrom、およびその全てのサブオブジェクトが以下の条件を全て満たす場合、constexpr関数として評価される：
 *	・is_union_v<T> == false
 *	・is_pointer_v<T> == false
 *	・is_member_pointer_v<T> == false
 *	・is_volatile_v<T> == false
 *	・Tが参照の非静的メンバ変数を持たないこと
 */
template <
	typename To,
	typename From,
	typename = hamon::enable_if_t<
		(sizeof(To) == sizeof(From)) &&			// [bit.cast]/1.1
		hamon::is_trivially_copyable_v<To> &&	// [bit.cast]/1.2
		hamon::is_trivially_copyable_v<From>	// [bit.cast]/1.3
	>
>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
To bit_cast(From const& src) HAMON_NOEXCEPT
{
	// [bit.cast]/3
#if HAMON_HAS_BUILTIN(__builtin_bit_cast) || defined(HAMON_MSVC)
	return __builtin_bit_cast(To, src);
#else
	alignas(To) unsigned char dst[sizeof(To)];
	hamon::memcpy(dst, &src, sizeof(To));
	return *(reinterpret_cast<To*>(&dst));
#endif
}

}	// namespace hamon

#endif // HAMON_BIT_BIT_CAST_HPP
