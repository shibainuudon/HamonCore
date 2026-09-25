/**
 *	@file	atomic_alias.hpp
 *
 *	@brief	[atomics.alias] の定義
 */

#ifndef HAMON_ATOMIC_ATOMIC_ALIAS_HPP
#define HAMON_ATOMIC_ATOMIC_ALIAS_HPP

#include <hamon/atomic/atomic.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/cstddef.hpp>

namespace hamon
{

// 32.5.3 Type aliases[atomics.alias]

using atomic_bool           = atomic<bool>;
using atomic_char           = atomic<char>;
using atomic_schar          = atomic<signed char>;
using atomic_uchar          = atomic<unsigned char>;
using atomic_short          = atomic<short>;
using atomic_ushort         = atomic<unsigned short>;
using atomic_int            = atomic<int>;
using atomic_uint           = atomic<unsigned int>;
using atomic_long           = atomic<long>;
using atomic_ulong          = atomic<unsigned long>;
using atomic_llong          = atomic<long long>;
using atomic_ullong         = atomic<unsigned long long>;
#if defined(HAMON_HAS_CXX20_CHAR8_T)
using atomic_char8_t        = atomic<char8_t>;
#endif
#if defined(HAMON_HAS_CXX11_CHAR16_T)
using atomic_char16_t       = atomic<char16_t>;
#endif
#if defined(HAMON_HAS_CXX11_CHAR32_T)
using atomic_char32_t       = atomic<char32_t>;
#endif
using atomic_wchar_t        = atomic<wchar_t>;

// [atomics.alias]/1
using atomic_int8_t         = atomic<hamon::int8_t>;
using atomic_uint8_t        = atomic<hamon::uint8_t>;
using atomic_int16_t        = atomic<hamon::int16_t>;
using atomic_uint16_t       = atomic<hamon::uint16_t>;
using atomic_int32_t        = atomic<hamon::int32_t>;
using atomic_uint32_t       = atomic<hamon::uint32_t>;
using atomic_int64_t        = atomic<hamon::int64_t>;
using atomic_uint64_t       = atomic<hamon::uint64_t>;

using atomic_int_least8_t   = atomic<hamon::int_least8_t>;
using atomic_uint_least8_t  = atomic<hamon::uint_least8_t>;
using atomic_int_least16_t  = atomic<hamon::int_least16_t>;
using atomic_uint_least16_t = atomic<hamon::uint_least16_t>;
using atomic_int_least32_t  = atomic<hamon::int_least32_t>;
using atomic_uint_least32_t = atomic<hamon::uint_least32_t>;
using atomic_int_least64_t  = atomic<hamon::int_least64_t>;
using atomic_uint_least64_t = atomic<hamon::uint_least64_t>;

using atomic_int_fast8_t    = atomic<hamon::int_fast8_t>;
using atomic_uint_fast8_t   = atomic<hamon::uint_fast8_t>;
using atomic_int_fast16_t   = atomic<hamon::int_fast16_t>;
using atomic_uint_fast16_t  = atomic<hamon::uint_fast16_t>;
using atomic_int_fast32_t   = atomic<hamon::int_fast32_t>;
using atomic_uint_fast32_t  = atomic<hamon::uint_fast32_t>;
using atomic_int_fast64_t   = atomic<hamon::int_fast64_t>;
using atomic_uint_fast64_t  = atomic<hamon::uint_fast64_t>;

using atomic_intptr_t       = atomic<hamon::intptr_t>;
using atomic_uintptr_t      = atomic<hamon::uintptr_t>;
using atomic_size_t         = atomic<hamon::size_t>;
using atomic_ptrdiff_t      = atomic<hamon::ptrdiff_t>;
using atomic_intmax_t       = atomic<hamon::intmax_t>;
using atomic_uintmax_t      = atomic<hamon::uintmax_t>;

// [atomics.alias]/2
using atomic_signed_lock_free   = atomic<signed int>;
using atomic_unsigned_lock_free = atomic<unsigned int>;

}	// namespace hamon

#endif // HAMON_ATOMIC_ATOMIC_ALIAS_HPP
