/**
 *	@file	__make_32_64_or_128_bit_t.hpp
 *
 *	@brief	__make_32_64_or_128_bit_t の定義
 */

#ifndef HAMON_FORMAT_OTHER___MAKE_32_64_OR_128_BIT_T_HPP
#define HAMON_FORMAT_OTHER___MAKE_32_64_OR_128_BIT_T_HPP

#include <hamon/type_traits/is_signed.hpp>
#include <hamon/type_traits/is_unsigned.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/make_unsigned.hpp>

namespace hamon
{

template <class _Tp, class _Up>
using __copy_unsigned_t = hamon::conditional_t<hamon::is_unsigned<_Tp>::value, hamon::make_unsigned_t<_Up>, _Up>;


/// Helper to promote an integral to smallest 32, 64, or 128 bit representation.
///
/// The restriction is the same as the integral version of to_char.
template <class _Tp>
#if 1//_LIBCPP_STD_VER >= 20
  requires(hamon::is_signed_v<_Tp> || hamon::is_unsigned_v<_Tp> || hamon::is_same_v<_Tp, char>)
#endif
// clang-format off
using __make_32_64_or_128_bit_t =
    __copy_unsigned_t<_Tp,
        hamon::conditional_t<sizeof(_Tp) <= sizeof(int32_t),    int32_t,
        hamon::conditional_t<sizeof(_Tp) <= sizeof(int64_t),    int64_t,
        /* else */                                         void
    > > >;
// clang-format on

}	// namespace hamon

#endif // HAMON_FORMAT_OTHER___MAKE_32_64_OR_128_BIT_T_HPP
