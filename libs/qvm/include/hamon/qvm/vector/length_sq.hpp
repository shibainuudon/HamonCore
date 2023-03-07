/**
 *	@file	length_sq.hpp
 *
 *	@brief	length_sq の定義
 */

#ifndef HAMON_QVM_VECTOR_LENGTH_SQ_HPP
#define HAMON_QVM_VECTOR_LENGTH_SQ_HPP

#include <hamon/qvm/vector/vector.hpp>
#include <hamon/qvm/vector/dot.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace qvm
{

/**
 *	@brief	ベクトルの長さの２乗を取得.
 *
 *	@param	v	対象となるベクトル
 *	@return	vの長さの２乗
 */
template <typename T, hamon::size_t N>
HAMON_NODISCARD inline HAMON_CONSTEXPR T
length_sq(vector<T, N> const& v) HAMON_NOEXCEPT
{
	return dot(v, v);
}

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_VECTOR_LENGTH_SQ_HPP
