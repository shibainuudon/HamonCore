/**
 *	@file	make_viewport_matrix.hpp
 *
 *	@brief	make_viewport_matrix の定義
 */

#ifndef HAMON_QVM_MATRIX_DETAIL_MAKE_VIEWPORT_MATRIX_HPP
#define HAMON_QVM_MATRIX_DETAIL_MAKE_VIEWPORT_MATRIX_HPP

#include <hamon/config.hpp>

namespace hamon
{

namespace qvm
{

namespace detail
{

template <typename Matrix, typename T>
HAMON_NODISCARD inline HAMON_CONSTEXPR Matrix
make_viewport_matrix_impl(T x, T y, T w, T h, T minz, T maxz) HAMON_NOEXCEPT
{
	return
	{
		w,     0,     0,           0,
		0,     h,     0,           0,
		0,     0,     maxz - minz, 0,
		x + w, y + h, minz,        1,
	};
}

template <
	typename Matrix,
	typename T1, typename T2, typename T3, typename T4, typename T5, typename T6
>
HAMON_NODISCARD inline HAMON_CONSTEXPR Matrix
make_viewport_matrix(T1 x, T2 y, T3 width, T4 height, T5 min_depth, T6 max_depth) HAMON_NOEXCEPT
{
	using T = vector_element_t<Matrix>;
	return make_viewport_matrix_impl<Matrix>(
		static_cast<T>(x),
		static_cast<T>(y),
		static_cast<T>(width / 2),
		static_cast<T>(height / 2),
		static_cast<T>(min_depth),
		static_cast<T>(max_depth));
}

}	// namespace detail

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_MATRIX_DETAIL_MAKE_VIEWPORT_MATRIX_HPP
