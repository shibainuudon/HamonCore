/**
 *	@file	bigint_fwd.hpp
 *
 *	@brief	bigint クラスの前方宣言
 */

#ifndef HAMON_BIGINT_BIGINT_FWD_HPP
#define HAMON_BIGINT_BIGINT_FWD_HPP

#include <hamon/bigint/basic_bigint_fwd.hpp>
#include <hamon/cstdint/uint32_t.hpp>
#include <hamon/vector.hpp>

namespace hamon
{

// 任意の要素数のbigint(動的なメモリ確保が発生する)
using bigint = basic_bigint<hamon::vector<hamon::uint32_t>>;

}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_FWD_HPP
