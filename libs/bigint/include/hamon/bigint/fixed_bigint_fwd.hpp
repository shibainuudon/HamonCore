/**
 *	@file	fixed_bigint_fwd.hpp
 *
 *	@brief	fixed_bigint クラスの前方宣言
 */

#ifndef HAMON_BIGINT_FIXED_BIGINT_FWD_HPP
#define HAMON_BIGINT_FIXED_BIGINT_FWD_HPP

#include <hamon/cstddef/size_t.hpp>

namespace hamon
{

template <hamon::size_t Bits, bool Signed>
class fixed_bigint;

// 固定ビット・符号付き
using int128_t  = hamon::fixed_bigint< 128, true>;
using int256_t  = hamon::fixed_bigint< 256, true>;
using int512_t  = hamon::fixed_bigint< 512, true>;
using int1024_t = hamon::fixed_bigint<1024, true>;
using int2048_t = hamon::fixed_bigint<2048, true>;

// 固定ビット・符号なし
using uint128_t  = hamon::fixed_bigint< 128, false>;
using uint256_t  = hamon::fixed_bigint< 256, false>;
using uint512_t  = hamon::fixed_bigint< 512, false>;
using uint1024_t = hamon::fixed_bigint<1024, false>;
using uint2048_t = hamon::fixed_bigint<2048, false>;

}	// namespace hamon

#endif // HAMON_BIGINT_FIXED_BIGINT_FWD_HPP
