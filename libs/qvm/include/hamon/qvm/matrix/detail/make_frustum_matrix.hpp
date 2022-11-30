/**
 *	@file	make_frustum_matrix.hpp
 *
 *	@brief	make_frustum_matrix の定義
 */

#ifndef HAMON_QVM_MATRIX_DETAIL_MAKE_FRUSTUM_MATRIX_HPP
#define HAMON_QVM_MATRIX_DETAIL_MAKE_FRUSTUM_MATRIX_HPP

#include <hamon/config.hpp>
#include <cstddef>

namespace hamon
{

namespace qvm
{

namespace detail
{

// make_frustum_matrix_lh
template <typename Matrix>
struct make_frustum_matrix_lh;

template <
	template <typename, std::size_t, std::size_t> class Matrix,
	typename T
>
struct make_frustum_matrix_lh<Matrix<T, 4, 4>>
{
	HAMON_NODISCARD static HAMON_CONSTEXPR Matrix<T, 4, 4>
	invoke(T l, T r, T b, T t, T zn, T zf) HAMON_NOEXCEPT
	{
		return
		{
			 2*zn/(r-l),   0,            0,             0,
			 0,            2*zn/(t-b),   0,             0,
			-(l+r)/(r-l), -(t+b)/(t-b), -zf/(zn-zf),    1,
			 0,            0,            zn*zf/(zn-zf), 0,
		};
	}
};

// make_frustum_matrix_rh
template <typename Matrix>
struct make_frustum_matrix_rh;

template <
	template <typename, std::size_t, std::size_t> class Matrix,
	typename T
>
struct make_frustum_matrix_rh<Matrix<T, 4, 4>>
{
	HAMON_NODISCARD static HAMON_CONSTEXPR Matrix<T, 4, 4>
	invoke(T l, T r, T b, T t, T zn, T zf) HAMON_NOEXCEPT
	{
		return
		{
			2*zn/(r-l),  0,           0,             0,
			0,           2*zn/(t-b),  0,             0,
			(l+r)/(r-l), (t+b)/(t-b), zf/(zn-zf),   -1,
			0,           0,           zn*zf/(zn-zf), 0,
		};
	}
};

}	// namespace detail

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_MATRIX_DETAIL_MAKE_FRUSTUM_MATRIX_HPP
