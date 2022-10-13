/**
 *	@file	dot.hpp
 *
 *	@brief	dot の定義
 */

#ifndef HAMON_QVM_VECTOR_DOT_HPP
#define HAMON_QVM_VECTOR_DOT_HPP

#include <hamon/qvm/vector/vector.hpp>
#include <hamon/qvm/detail/transform.hpp>
#include <hamon/qvm/detail/reduce.hpp>
#include <hamon/functional/multiplies.hpp>
#include <hamon/config.hpp>
#include <cstddef>

namespace hamon
{

namespace qvm
{

/**
 *	@brief	内積
 *
 *	@param	v1	ベクトルその１
 *	@param	v2	ベクトルその２
 *	@return	v1とv2の内積
 */
template <typename T1, typename T2, std::size_t N>
HAMON_NODISCARD inline HAMON_CONSTEXPR auto
dot(vector<T1, N> const& v1, vector<T2, N> const& v2) HAMON_NOEXCEPT
->decltype(hamon::qvm::reduce(
		hamon::qvm::transform(v1, v2, hamon::multiplies<>{})))
{
	return hamon::qvm::reduce(
		hamon::qvm::transform(v1, v2, hamon::multiplies<>{}));
}

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_VECTOR_DOT_HPP
