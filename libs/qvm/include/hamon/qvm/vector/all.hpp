/**
 *	@file	all.hpp
 *
 *	@brief	all の定義
 */

#ifndef HAMON_QVM_VECTOR_ALL_HPP
#define HAMON_QVM_VECTOR_ALL_HPP

#include <hamon/qvm/vector/vector.hpp>
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
template <std::size_t N>
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
all(vector<bool, N> const& vec) HAMON_NOEXCEPT
{
	return hamon::qvm::reduce(vec, true, hamon::logical_and<>{});
}

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_VECTOR_ALL_HPP
