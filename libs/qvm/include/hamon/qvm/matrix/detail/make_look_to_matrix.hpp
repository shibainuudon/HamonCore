/**
 *	@file	make_look_to_matrix.hpp
 *
 *	@brief	make_look_to_matrix の定義
 */

#ifndef HAMON_QVM_MATRIX_DETAIL_MAKE_LOOK_TO_MATRIX_HPP
#define HAMON_QVM_MATRIX_DETAIL_MAKE_LOOK_TO_MATRIX_HPP

#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace qvm
{

namespace detail
{

// make_look_to_matrix
template <typename Matrix>
struct make_look_to_matrix;

template <
	template <typename, hamon::size_t, hamon::size_t> class Matrix,
	typename T
>
struct make_look_to_matrix<Matrix<T, 4, 4>>
{
private:
	template <typename Vector3>
	HAMON_NODISCARD static HAMON_CONSTEXPR Matrix<T, 4, 4>
	impl_2(
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

	template <typename Vector3>
	HAMON_NODISCARD static HAMON_CONSTEXPR Matrix<T, 4, 4>
	impl_1(
		Vector3 const& eye,
		Vector3 const& xaxis,
		Vector3 const& zaxis) HAMON_NOEXCEPT
	{
		return impl_2(eye, xaxis, cross(zaxis, xaxis), zaxis);
	}

	template <typename Vector3>
	HAMON_NODISCARD static HAMON_CONSTEXPR Matrix<T, 4, 4>
	impl(
		Vector3 const& eye,
		Vector3 const& up,
		Vector3 const& zaxis) HAMON_NOEXCEPT
	{
		return impl_1(eye, normalize(cross(up, zaxis)), zaxis);
	}

public:
	template <typename Vector3>
	HAMON_NODISCARD static HAMON_CONSTEXPR Matrix<T, 4, 4>
	invoke(
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

		return impl(eye, up, normalize(dir));
	}
};

}	// namespace detail

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_MATRIX_DETAIL_MAKE_LOOK_TO_MATRIX_HPP
