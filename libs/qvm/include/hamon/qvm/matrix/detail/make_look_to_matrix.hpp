/**
 *	@file	make_look_to_matrix.hpp
 *
 *	@brief	make_look_to_matrix の定義
 */

#ifndef HAMON_QVM_MATRIX_DETAIL_MAKE_LOOK_TO_MATRIX_HPP
#define HAMON_QVM_MATRIX_DETAIL_MAKE_LOOK_TO_MATRIX_HPP

#include <hamon/config.hpp>
#include <cstddef>

namespace hamon
{

namespace qvm
{

namespace detail
{

template <typename Matrix, typename Vector3>
HAMON_NODISCARD inline HAMON_CONSTEXPR Matrix
make_look_to_matrix_impl_2(
	Vector3 const& eye,
	Vector3 const& xaxis,
	Vector3 const& yaxis,
	Vector3 const& zaxis) HAMON_NOEXCEPT
{
	return
	{
		xaxis.x(), yaxis.x(), zaxis.x(), 0,
		xaxis.y(), yaxis.y(), zaxis.y(), 0,
		xaxis.z(), yaxis.z(), zaxis.z(), 0,
		-dot(xaxis, eye), -dot(yaxis, eye), -dot(zaxis, eye), 1,
	};
}

template <typename Matrix, typename Vector3>
HAMON_NODISCARD inline HAMON_CONSTEXPR Matrix
make_look_to_matrix_impl_1(
	Vector3 const& eye,
	Vector3 const& xaxis,
	Vector3 const& zaxis) HAMON_NOEXCEPT
{
	return make_look_to_matrix_impl_2<Matrix>(
		eye, xaxis, cross(zaxis, xaxis), zaxis);
}

template <typename Matrix, typename Vector3>
HAMON_NODISCARD inline HAMON_CONSTEXPR Matrix
make_look_to_matrix_impl(
	Vector3 const& eye,
	Vector3 const& up,
	Vector3 const& zaxis) HAMON_NOEXCEPT
{
	return make_look_to_matrix_impl_1<Matrix>(
		eye, normalize(cross(up, zaxis)), zaxis);
}

template <typename Matrix, typename Vector3>
HAMON_NODISCARD inline HAMON_CONSTEXPR Matrix
make_look_to_matrix(
	Vector3 const& eye,
	Vector3 const& dir,
	Vector3 const& up) HAMON_NOEXCEPT
{
	// 以下のコードをC++11でもconstexprになるようにします
	//auto const zaxis = normalize(dir);
	//auto const xaxis = normalize(cross(up, zaxis));
	//auto const yaxis = cross(zaxis, xaxis);

	//return
	//{
	//	xaxis.x(), yaxis.x(), zaxis.x(), 0,
	//	xaxis.y(), yaxis.y(), zaxis.y(), 0,
	//	xaxis.z(), yaxis.z(), zaxis.z(), 0,
	//	-dot(xaxis, eye), -dot(yaxis, eye), -dot(zaxis, eye), 1,
	//};

	return make_look_to_matrix_impl<Matrix>(
		eye, up, normalize(dir));
}

}	// namespace detail

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_MATRIX_DETAIL_MAKE_LOOK_TO_MATRIX_HPP
