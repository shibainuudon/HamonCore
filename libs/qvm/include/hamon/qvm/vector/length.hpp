/**
 *	@file	length.hpp
 *
 *	@brief	length の定義
 */

#ifndef HAMON_QVM_VECTOR_LENGTH_HPP
#define HAMON_QVM_VECTOR_LENGTH_HPP

#include <hamon/qvm/vector/vector.hpp>
#include <hamon/qvm/vector/length_sq.hpp>
#include <hamon/cmath/sqrt.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace qvm
{

/**
 *	@brief	ベクトルの長さを取得.
 *
 *	@param	v	対象となるベクトル
 *	@return	vの長さ
 */
template <typename T, hamon::size_t N>
HAMON_NODISCARD inline HAMON_CONSTEXPR auto
length(vector<T, N> const& v)
->decltype(hamon::sqrt(length_sq(v)))
{
	return hamon::sqrt(length_sq(v));
}

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_VECTOR_LENGTH_HPP
