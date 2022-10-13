/**
 *	@file	normalize.hpp
 *
 *	@brief	normalize の定義
 */

#ifndef HAMON_QVM_QUATERNION_NORMALIZE_HPP
#define HAMON_QVM_QUATERNION_NORMALIZE_HPP

#include <hamon/qvm/quaternion/quaternion.hpp>
#include <hamon/qvm/quaternion/length_sq.hpp>
#include <hamon/qvm/quaternion/length.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace qvm
{

/**
 *	@brief	正規化したクォータニオンを取得します
 */
template <typename T>
HAMON_NODISCARD inline HAMON_CONSTEXPR quaternion<T>
normalize(quaternion<T> const& q) HAMON_NOEXCEPT
{
	return
		length_sq(q) == 0 ?
		quaternion<T>::identity() :
		q / length(q);
}

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_QUATERNION_NORMALIZE_HPP
