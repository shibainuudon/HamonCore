/**
 *	@file	any.hpp
 *
 *	@brief	any の定義
 */

#ifndef HAMON_QVM_VECTOR_ANY_HPP
#define HAMON_QVM_VECTOR_ANY_HPP

#include <hamon/qvm/vector/vector.hpp>
#include <hamon/qvm/detail/reduce.hpp>
#include <hamon/functional/logical_or.hpp>
#include <hamon/config.hpp>
#include <cstddef>

namespace hamon
{

namespace qvm
{

/**
 *	@brief	any
 */
template <std::size_t N>
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
any(vector<bool, N> const& vec) HAMON_NOEXCEPT
{
	return hamon::qvm::reduce(vec, false, hamon::logical_or<>{});
}

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_VECTOR_ANY_HPP
