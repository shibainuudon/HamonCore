/**
 *	@file	all.hpp
 *
 *	@brief	all の定義
 */

#ifndef HAMON_QVM_MATRIX_ALL_HPP
#define HAMON_QVM_MATRIX_ALL_HPP

#include <hamon/qvm/matrix/matrix.hpp>
#include <hamon/qvm/detail/reduce.hpp>
#include <hamon/functional/logical_and.hpp>
#include <hamon/config.hpp>
#include <cstddef>

namespace hamon
{

namespace qvm
{

/**
 *	@brief	all
 */
template <std::size_t R, std::size_t C>
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
all(matrix<bool, R, C> const& m) HAMON_NOEXCEPT
{
	return hamon::qvm::reduce(m, true, hamon::logical_and<>{});
}

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_MATRIX_ALL_HPP
