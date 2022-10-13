/**
 *	@file	make_rotation_matrix.hpp
 *
 *	@brief	make_rotation_matrix の定義
 */

#ifndef HAMON_QVM_MATRIX_DETAIL_MAKE_ROTATION_MATRIX_HPP
#define HAMON_QVM_MATRIX_DETAIL_MAKE_ROTATION_MATRIX_HPP

#include <hamon/qvm/detail/vector_element.hpp>
#include <hamon/config.hpp>
#include <cmath>

namespace hamon
{

namespace qvm
{

namespace detail
{

template <typename Matrix, typename T>
HAMON_NODISCARD inline HAMON_CONSTEXPR Matrix
make_rotation_matrix_impl_1(T x, T y, T z, T s, T c) HAMON_NOEXCEPT
{
	return
	{
		(x*x)*(1-c)+c,     (x*y)*(1-c)+(z*s), (x*z)*(1-c)-(y*s),
		(y*x)*(1-c)-(z*s), (y*y)*(1-c)+c,     (y*z)*(1-c)+(x*s),
		(z*x)*(1-c)+(y*s), (z*y)*(1-c)-(x*s), (z*z)*(1-c)+c,
	};
}

template <typename Matrix, typename Vector3, typename AngleType>
HAMON_NODISCARD inline HAMON_CONSTEXPR Matrix
make_rotation_matrix_impl(Vector3 const& axis, AngleType const& angle) HAMON_NOEXCEPT
{
	using std::sin;
	using std::cos;
	using T = qvm::detail::vector_element_t<Matrix>;
	return make_rotation_matrix_impl_1<Matrix>(
		static_cast<T>(axis.x()),
		static_cast<T>(axis.y()),
		static_cast<T>(axis.z()),
		static_cast<T>(sin(angle)),
		static_cast<T>(cos(angle)));
}

template <typename Matrix, typename Vector3, typename AngleType>
HAMON_NODISCARD inline HAMON_CONSTEXPR Matrix
make_rotation_matrix(Vector3 const& axis, AngleType const& angle) HAMON_NOEXCEPT
{
	return make_rotation_matrix_impl<Matrix>(normalize(axis), angle);
}

}	// namespace detail

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_MATRIX_DETAIL_MAKE_ROTATION_MATRIX_HPP
