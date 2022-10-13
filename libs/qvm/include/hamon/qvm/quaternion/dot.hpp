/**
 *	@file	dot.hpp
 *
 *	@brief	dot の定義
 */

#ifndef HAMON_QVM_QUATERNION_DOT_HPP
#define HAMON_QVM_QUATERNION_DOT_HPP

#include <hamon/qvm/quaternion/quaternion.hpp>
#include <hamon/qvm/detail/transform.hpp>
#include <hamon/qvm/detail/reduce.hpp>
#include <hamon/functional/multiplies.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace qvm
{

/**
 *	@brief	内積
 */
template <typename T1, typename T2>
HAMON_NODISCARD inline HAMON_CONSTEXPR auto
dot(quaternion<T1> const& v1, quaternion<T2> const& v2) HAMON_NOEXCEPT
->decltype(hamon::qvm::reduce(
		hamon::qvm::transform(v1, v2, hamon::multiplies<>{})))
{
	return hamon::qvm::reduce(
		hamon::qvm::transform(v1, v2, hamon::multiplies<>{}));
}

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_QUATERNION_DOT_HPP
