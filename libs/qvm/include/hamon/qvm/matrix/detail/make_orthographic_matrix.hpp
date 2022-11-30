/**
 *	@file	make_orthographic_matrix.hpp
 *
 *	@brief	make_orthographic_matrix の定義
 */

#ifndef HAMON_QVM_MATRIX_DETAIL_MAKE_ORTHOGRAPHIC_MATRIX_HPP
#define HAMON_QVM_MATRIX_DETAIL_MAKE_ORTHOGRAPHIC_MATRIX_HPP

#include <hamon/config.hpp>
#include <cstddef>

namespace hamon
{

namespace qvm
{

namespace detail
{

// make_orthographic_matrix_lh
template <typename Matrix>
struct make_orthographic_matrix_lh;

template <
	template <typename, std::size_t, std::size_t> class Matrix,
	typename T
>
struct make_orthographic_matrix_lh<Matrix<T, 4, 4>>
{
	HAMON_NODISCARD static HAMON_CONSTEXPR Matrix<T, 4, 4>
	invoke(T l, T r, T b, T t, T zn, T zf) HAMON_NOEXCEPT
	{
		return
		{
			 2/(r-l),      0,            0,           0,
			 0,            2/(t-b),      0,           0,
			 0,            0,           -1/(zn-zf),   0,
			-(l+r)/(r-l), -(t+b)/(t-b),  zn/(zn-zf),  1,
		};
	}
};

// make_orthographic_matrix_rh
template <typename Matrix>
struct make_orthographic_matrix_rh;

template <
	template <typename, std::size_t, std::size_t> class Matrix,
	typename T
>
struct make_orthographic_matrix_rh<Matrix<T, 4, 4>>
{
	HAMON_NODISCARD static HAMON_CONSTEXPR Matrix<T, 4, 4>
	invoke(T l, T r, T b, T t, T zn, T zf) HAMON_NOEXCEPT
	{
		return
		{
			 2/(r-l),      0,            0,           0,
			 0,            2/(t-b),      0,           0,
			 0,            0,            1/(zn-zf),   0,
			-(l+r)/(r-l), -(t+b)/(t-b),  zn/(zn-zf),  1,
		};
	}
};

}	// namespace detail

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_MATRIX_DETAIL_MAKE_ORTHOGRAPHIC_MATRIX_HPP
