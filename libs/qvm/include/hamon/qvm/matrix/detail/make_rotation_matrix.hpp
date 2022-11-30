/**
 *	@file	make_rotation_matrix.hpp
 *
 *	@brief	make_rotation_matrix の定義
 */

#ifndef HAMON_QVM_MATRIX_DETAIL_MAKE_ROTATION_MATRIX_HPP
#define HAMON_QVM_MATRIX_DETAIL_MAKE_ROTATION_MATRIX_HPP

#include <hamon/config.hpp>
#include <cstddef>
#include <cmath>

namespace hamon
{

namespace qvm
{

namespace detail
{

// make_rotation_matrix
template <typename Matrix>
struct make_rotation_matrix;

template <
	template <typename, std::size_t, std::size_t> class Matrix,
	typename T
>
struct make_rotation_matrix<Matrix<T, 3, 3>>
{
private:
	HAMON_NODISCARD static HAMON_CONSTEXPR Matrix<T, 3, 3>
	impl_1(T x, T y, T z, T s, T c) HAMON_NOEXCEPT
	{
		return
		{
			(x*x)*(1-c)+c,     (x*y)*(1-c)+(z*s), (x*z)*(1-c)-(y*s),
			(y*x)*(1-c)-(z*s), (y*y)*(1-c)+c,     (y*z)*(1-c)+(x*s),
			(z*x)*(1-c)+(y*s), (z*y)*(1-c)-(x*s), (z*z)*(1-c)+c,
		};
	}

	template <typename Vector3, typename AngleType>
	HAMON_NODISCARD static HAMON_CONSTEXPR Matrix<T, 3, 3>
	impl(Vector3 const& axis, AngleType const& angle) HAMON_NOEXCEPT
	{
		using std::sin;
		using std::cos;
		return impl_1(
			static_cast<T>(axis.x()),
			static_cast<T>(axis.y()),
			static_cast<T>(axis.z()),
			static_cast<T>(sin(angle)),
			static_cast<T>(cos(angle)));
	}

public:
	template <typename Vector3, typename AngleType>
	HAMON_NODISCARD static HAMON_CONSTEXPR Matrix<T, 3, 3>
	invoke(Vector3 const& axis, AngleType const& angle) HAMON_NOEXCEPT
	{
		return impl(normalize(axis), angle);
	}
};

}	// namespace detail

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_MATRIX_DETAIL_MAKE_ROTATION_MATRIX_HPP
