/**
 *	@file	inplace_bigint_fwd.hpp
 *
 *	@brief	inplace_bigint クラスの前方宣言
 */

#ifndef HAMON_BIGINT_INPLACE_BIGINT_FWD_HPP
#define HAMON_BIGINT_INPLACE_BIGINT_FWD_HPP

#include <hamon/bigint/basic_bigint_fwd.hpp>
#include <hamon/bit/bitsof.hpp>
#include <hamon/cmath/round_up.hpp>
#include <hamon/cstdint/uint32_t.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/inplace_vector.hpp>

namespace hamon
{

// 最大要素数を指定したbigint(動的なメモリ確保が発生しない)
template <hamon::size_t Bits, typename T = hamon::uint32_t>
using inplace_bigint = basic_bigint<hamon::inplace_vector<T, hamon::round_up(Bits, hamon::bitsof<T>()) / hamon::bitsof<T>()>>;

}	// namespace hamon

#endif // HAMON_BIGINT_INPLACE_BIGINT_FWD_HPP
