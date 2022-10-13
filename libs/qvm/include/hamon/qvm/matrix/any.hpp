/**
 *	@file	any.hpp
 *
 *	@brief	any の定義
 */

#ifndef HAMON_QVM_MATRIX_ANY_HPP
#define HAMON_QVM_MATRIX_ANY_HPP

#include <hamon/qvm/matrix/matrix.hpp>
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
template <std::size_t R, std::size_t C>
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
any(matrix<bool, R, C> const& m) HAMON_NOEXCEPT
{
	return hamon::qvm::reduce(m, false, hamon::logical_or<>{});
}

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_MATRIX_ANY_HPP
