/**
 *	@file	make_look_at_quaternion.hpp
 *
 *	@brief	make_look_at_quaternion の定義
 */

#ifndef HAMON_QVM_QUATERNION_DETAIL_MAKE_LOOK_AT_QUATERNION_HPP
#define HAMON_QVM_QUATERNION_DETAIL_MAKE_LOOK_AT_QUATERNION_HPP

#include <hamon/qvm/quaternion/quaternion.hpp>
#include <hamon/qvm/matrix/matrix.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace qvm
{

namespace detail
{

template <typename Quaternion, typename Vector3>
HAMON_NODISCARD inline HAMON_CONSTEXPR Quaternion
make_look_at_quaternion_impl_2(
	Vector3 const& xaxis,
	Vector3 const& yaxis,
	Vector3 const& zaxis) HAMON_NOEXCEPT
{
	return normalize(Quaternion
	{
		yaxis.z() - zaxis.y(),
		zaxis.x() - xaxis.z(),
		xaxis.y() - yaxis.x(),
		xaxis.x() + yaxis.y() + zaxis.z() + 1.0f
	});
}

template <typename Quaternion, typename Vector3>
HAMON_NODISCARD inline HAMON_CONSTEXPR Quaternion
make_look_at_quaternion_impl_1(
	Vector3 const& xaxis,
	Vector3 const& zaxis) HAMON_NOEXCEPT
{
	return make_look_at_quaternion_impl_2<Quaternion>(
		xaxis,
		cross(zaxis, xaxis),
		zaxis);
}

template <typename Quaternion, typename Vector3>
HAMON_NODISCARD inline HAMON_CONSTEXPR Quaternion
make_look_at_quaternion_impl(
	Vector3 const& up,
	Vector3 const& zaxis) HAMON_NOEXCEPT
{
	return make_look_at_quaternion_impl_1<Quaternion>(
		normalize(cross(up, zaxis)),
		zaxis);
}

template <typename Quaternion, typename Vector3>
HAMON_NODISCARD inline HAMON_CONSTEXPR Quaternion
make_look_at_quaternion(
	Vector3 const& eye,
	Vector3 const& lookat,
	Vector3 const& up) HAMON_NOEXCEPT
{
	// 以下のコードをC++11でもconstexprになるようにします
	//auto const zaxis = normalize(eye - lookat);
	//auto const xaxis = normalize(cross(up, zaxis));
	//auto const yaxis = cross(zaxis, xaxis);
	//quaternion const q
	//{
	//	yaxis.z() - zaxis.y(),
	//	zaxis.x() - xaxis.z(),
	//	xaxis.y() - yaxis.x(),
	//	xaxis.x() + yaxis.y() + zaxis.z() + 1.0f
	//};
	//return normalize(q);

	return make_look_at_quaternion_impl<Quaternion>(
		up,
		normalize(eye - lookat));
}

}	// namespace detail

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_QUATERNION_DETAIL_MAKE_LOOK_AT_QUATERNION_HPP
