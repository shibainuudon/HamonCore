/**
 *	@file	make_rotation_y_matrix.hpp
 *
 *	@brief	make_rotation_y_matrix の定義
 */

#ifndef HAMON_QVM_MATRIX_DETAIL_MAKE_ROTATION_Y_MATRIX_HPP
#define HAMON_QVM_MATRIX_DETAIL_MAKE_ROTATION_Y_MATRIX_HPP

#include <hamon/config.hpp>
#include <cstddef>
#include <cmath>

namespace hamon
{

namespace qvm
{

namespace detail
{

// make_rotation_y_matrix
template <typename Matrix>
struct make_rotation_y_matrix;

template <
	template <typename, std::size_t, std::size_t> class Matrix,
	typename T
>
struct make_rotation_y_matrix<Matrix<T, 3, 3>>
{
private:
	HAMON_NODISCARD static HAMON_CONSTEXPR Matrix<T, 3, 3>
	impl(T const& s, T const& c) HAMON_NOEXCEPT
	{
		return
		{
			c,  0, -s,
			0,  1,  0,
			s,  0,  c,
		};
	}

public:
	template <typename AngleType>
	HAMON_NODISCARD static HAMON_CONSTEXPR Matrix<T, 3, 3>
	invoke(AngleType const& angle) HAMON_NOEXCEPT
	{
		using std::sin;
		using std::cos;
		return impl(
			static_cast<T>(sin(angle)),
			static_cast<T>(cos(angle)));
	}
};

}	// namespace detail

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_MATRIX_DETAIL_MAKE_ROTATION_Y_MATRIX_HPP
