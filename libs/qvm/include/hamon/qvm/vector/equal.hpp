/**
 *	@file	equal.hpp
 *
 *	@brief	equal の定義
 */

#ifndef HAMON_QVM_VECTOR_EQUAL_HPP
#define HAMON_QVM_VECTOR_EQUAL_HPP

#include <hamon/qvm/vector/vector.hpp>
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
template <typename T1, typename T2, std::size_t N>
HAMON_NODISCARD inline HAMON_CONSTEXPR auto
equal(vector<T1, N> const& lhs, vector<T2, N> const& rhs) HAMON_NOEXCEPT
->decltype(hamon::qvm::transform(lhs, rhs, hamon::equal_to<>{}))
{
	return hamon::qvm::transform(lhs, rhs, hamon::equal_to<>{});
}

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_VECTOR_EQUAL_HPP
