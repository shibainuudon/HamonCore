/**
 *	@file	make_perspective_matrix.hpp
 *
 *	@brief	make_perspective_matrix の定義
 */

#ifndef HAMON_QVM_MATRIX_DETAIL_MAKE_PERSPECTIVE_MATRIX_HPP
#define HAMON_QVM_MATRIX_DETAIL_MAKE_PERSPECTIVE_MATRIX_HPP

#include <hamon/config.hpp>
#include <cstddef>
#include <cmath>

namespace hamon
{

namespace qvm
{

namespace detail
{

// make_perspective_matrix_lh
template <typename Matrix>
struct make_perspective_matrix_lh;

template <
	template <typename, std::size_t, std::size_t> class Matrix,
	typename T
>
struct make_perspective_matrix_lh<Matrix<T, 4, 4>>
{
private:
	HAMON_NODISCARD static HAMON_CONSTEXPR Matrix<T, 4, 4>
	impl(T yscale, T aspect, T zn, T zf) HAMON_NOEXCEPT
	{
		return
		{
			yscale / aspect, 0,       0,              0,
			0,               yscale,  0,              0,
			0,               0,      -zf/(zn-zf),     1,
			0,               0,       zn*zf/(zn-zf),  0,
		};
	}

public:
	template <typename Angle>
	HAMON_NODISCARD static HAMON_CONSTEXPR Matrix<T, 4, 4>
	invoke(Angle const& fovy, T const& aspect, T const& near_z, T const& far_z) HAMON_NOEXCEPT
	{
		using std::tan;
		return impl(static_cast<T>(T(1) / tan(fovy * T(0.5))), aspect, near_z, far_z);
	}
};

// make_perspective_matrix_rh
template <typename Matrix>
struct make_perspective_matrix_rh;

template <
	template <typename, std::size_t, std::size_t> class Matrix,
	typename T
>
struct make_perspective_matrix_rh<Matrix<T, 4, 4>>
{
private:
	HAMON_NODISCARD static HAMON_CONSTEXPR Matrix<T, 4, 4>
	impl(T yscale, T aspect, T zn, T zf) HAMON_NOEXCEPT
	{
		return
		{
			yscale / aspect, 0,       0,              0,
			0,               yscale,  0,              0,
			0,               0,       zf/(zn-zf),    -1,
			0,               0,       zn*zf/(zn-zf),  0,
		};
	}

public:
	template <typename Angle>
	HAMON_NODISCARD static HAMON_CONSTEXPR Matrix<T, 4, 4>
	invoke(Angle const& fovy, T const& aspect, T const& near_z, T const& far_z) HAMON_NOEXCEPT
	{
		using std::tan;
		return impl(static_cast<T>(T(1) / tan(fovy * T(0.5))), aspect, near_z, far_z);
	}
};

}	// namespace detail

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_MATRIX_DETAIL_MAKE_PERSPECTIVE_MATRIX_HPP
