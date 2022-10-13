/**
 *	@file	equal.hpp
 *
 *	@brief	equal の定義
 */

#ifndef HAMON_QVM_MATRIX_EQUAL_HPP
#define HAMON_QVM_MATRIX_EQUAL_HPP

#include <hamon/qvm/matrix/matrix.hpp>
#include <hamon/qvm/detail/transform.hpp>
#include <hamon/functional/equal_to.hpp>
#include <hamon/config.hpp>
#include <cstddef>

namespace hamon
{

namespace qvm
{

/**
 *	@brief	equal
 */
template <typename T, typename T2, std::size_t R, std::size_t C>
HAMON_NODISCARD inline HAMON_CONSTEXPR auto
equal(matrix<T, R, C> const& lhs, matrix<T2, R, C> const& rhs) HAMON_NOEXCEPT
->decltype(hamon::qvm::transform(lhs, rhs, hamon::equal_to<>{}))
{
	return hamon::qvm::transform(lhs, rhs, hamon::equal_to<>{});
}

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_MATRIX_EQUAL_HPP
