/**
 *	@file	make_rotation_x_matrix.hpp
 *
 *	@brief	make_rotation_x_matrix の定義
 */

#ifndef HAMON_QVM_MATRIX_DETAIL_MAKE_ROTATION_X_MATRIX_HPP
#define HAMON_QVM_MATRIX_DETAIL_MAKE_ROTATION_X_MATRIX_HPP

#include <hamon/cmath/ranges/sin.hpp>
#include <hamon/cmath/ranges/cos.hpp>
#include <hamon/config.hpp>
#include <cstddef>

namespace hamon
{

namespace qvm
{

namespace detail
{

// make_rotation_x_matrix
template <typename Matrix>
struct make_rotation_x_matrix;

template <
	template <typename, std::size_t, std::size_t> class Matrix,
	typename T
>
struct make_rotation_x_matrix<Matrix<T, 3, 3>>
{
private:
	HAMON_NODISCARD static HAMON_CONSTEXPR Matrix<T, 3, 3>
	impl(T const& s, T const& c) HAMON_NOEXCEPT
	{
		return
		{
			1,  0,  0,
			0,  c,  s,
			0, -s,  c,
		};
	}

public:
	template <typename AngleType>
	HAMON_NODISCARD static HAMON_CONSTEXPR Matrix<T, 3, 3>
	invoke(AngleType const& angle) HAMON_NOEXCEPT
	{
		return impl(
			static_cast<T>(hamon::ranges::sin(angle)),
			static_cast<T>(hamon::ranges::cos(angle)));
	}
};

}	// namespace detail

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_MATRIX_DETAIL_MAKE_ROTATION_X_MATRIX_HPP
