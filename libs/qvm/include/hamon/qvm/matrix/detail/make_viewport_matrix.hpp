/**
 *	@file	make_viewport_matrix.hpp
 *
 *	@brief	make_viewport_matrix の定義
 */

#ifndef HAMON_QVM_MATRIX_DETAIL_MAKE_VIEWPORT_MATRIX_HPP
#define HAMON_QVM_MATRIX_DETAIL_MAKE_VIEWPORT_MATRIX_HPP

#include <hamon/config.hpp>
#include <cstddef>

namespace hamon
{

namespace qvm
{

namespace detail
{

// make_viewport_matrix
template <typename Matrix>
struct make_viewport_matrix;

template <
	template <typename, std::size_t, std::size_t> class Matrix,
	typename T
>
struct make_viewport_matrix<Matrix<T, 4, 4>>
{
	HAMON_NODISCARD static HAMON_CONSTEXPR Matrix<T, 4, 4>
	invoke(T x, T y, T w, T h, T minz, T maxz) HAMON_NOEXCEPT
	{
		return
		{
			w/2,     0,       0,           0,
			0,       h/2,     0,           0,
			0,       0,       maxz - minz, 0,
			x + w/2, y + h/2, minz,        1,
		};
	}
};

}	// namespace detail

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_MATRIX_DETAIL_MAKE_VIEWPORT_MATRIX_HPP
