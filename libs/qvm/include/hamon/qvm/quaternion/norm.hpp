/**
 *	@file	norm.hpp
 *
 *	@brief	norm の定義
 */

#ifndef HAMON_QVM_QUATERNION_NORM_HPP
#define HAMON_QVM_QUATERNION_NORM_HPP

#include <hamon/qvm/quaternion/quaternion.hpp>
#include <hamon/qvm/quaternion/length.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace qvm
{

/**
 *	@brief	クォータニオンのノルムを取得します
 */
template <typename T>
HAMON_NODISCARD inline HAMON_CONSTEXPR auto
norm(quaternion<T> const& q) HAMON_NOEXCEPT
->decltype(length(q))
{
	return length(q);
}

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_QUATERNION_NORM_HPP
