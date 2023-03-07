/**
 *	@file	normalize.hpp
 *
 *	@brief	normalize の定義
 */

#ifndef HAMON_QVM_VECTOR_NORMALIZE_HPP
#define HAMON_QVM_VECTOR_NORMALIZE_HPP

#include <hamon/qvm/vector/vector.hpp>
#include <hamon/qvm/vector/length_sq.hpp>
#include <hamon/qvm/vector/length.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace qvm
{

/**
 *	@brief	ベクトルを正規化.
 *
 *	引数vは変更しません。
 *	vがゼロベクトルの時はゼロベクトルを返します。
 *
 *	@param	v	対象となるベクトル
 *	@return	vを正規化したベクトル
 */
template <typename T, hamon::size_t N>
HAMON_NODISCARD inline HAMON_CONSTEXPR vector<T, N>
normalize(vector<T, N> const& v)
{
	return length_sq(v) == 0 ?
		vector<T, N>{} :
		vector<T, N>{v / length(v)};
}

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_VECTOR_NORMALIZE_HPP
