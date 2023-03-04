/**
 *	@file	bit_cast.hpp
 *
 *	@brief	bit_cast 関数テンプレートを定義
 */

#ifndef HAMON_BIT_BIT_CAST_HPP
#define HAMON_BIT_BIT_CAST_HPP

#include <hamon/bit/config.hpp>

#if defined(HAMON_HAS_CXX_LIB_BIT_CAST)

// bit_cast が constexpr であることを定義
#define	HAMON_HAS_CONSTEXPR_BIT_CAST

#include <bit>

namespace hamon
{

using std::bit_cast;

}	// namespace hamon

#else

#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_trivially_copyable.hpp>
#include <hamon/config.hpp>
#include <cstring>	// memcpy

namespace hamon
{

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
		hamon::conjunction<
			hamon::bool_constant<sizeof(To) == sizeof(From)>,
			hamon::is_trivially_copyable<To>,
			hamon::is_trivially_copyable<From>
		>::value
	>
>
HAMON_NODISCARD inline HAMON_CONSTEXPR To
bit_cast(From const& src) HAMON_NOEXCEPT
{
#if HAMON_HAS_BUILTIN(__builtin_bit_cast)

// bit_cast が constexpr であることを定義
#define	HAMON_HAS_CONSTEXPR_BIT_CAST

	return __builtin_bit_cast(To, src);

#else

	To dst;
	std::memcpy(&dst, &src, sizeof(To));
	return dst;
#endif
}

}	// namespace hamon

#endif

#endif // HAMON_BIT_BIT_CAST_HPP
