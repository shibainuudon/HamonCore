/**
 *	@file	make_orthographic_matrix.hpp
 *
 *	@brief	make_orthographic_matrix の定義
 */

#ifndef HAMON_QVM_MATRIX_DETAIL_MAKE_ORTHOGRAPHIC_MATRIX_HPP
#define HAMON_QVM_MATRIX_DETAIL_MAKE_ORTHOGRAPHIC_MATRIX_HPP

#include <hamon/config.hpp>

namespace hamon
{

namespace qvm
{

namespace detail
{

template <typename Matrix, typename T>
HAMON_NODISCARD inline HAMON_CONSTEXPR Matrix
make_orthographic_matrix_lh_impl(T l, T r, T b, T t, T zn, T zf) HAMON_NOEXCEPT
{
	return
	{
		 2/(r-l),      0,            0,           0,
		 0,            2/(t-b),      0,           0,
		 0,            0,           -1/(zn-zf),   0,
		-(l+r)/(r-l), -(t+b)/(t-b),  zn/(zn-zf),  1,
	};
}

template <
	typename Matrix,
	typename T1, typename T2, typename T3, typename T4, typename T5, typename T6
>
HAMON_NODISCARD inline HAMON_CONSTEXPR Matrix
make_orthographic_matrix_lh(T1 left, T2 right, T3 bottom, T4 top, T5 near_z, T6 far_z) HAMON_NOEXCEPT
{
	using T = vector_element_t<Matrix>;
	return make_orthographic_matrix_lh_impl<Matrix>(
		static_cast<T>(left),
		static_cast<T>(right),
		static_cast<T>(bottom),
		static_cast<T>(top),
		static_cast<T>(near_z),
		static_cast<T>(far_z));
}

template <typename Matrix, typename T>
HAMON_NODISCARD inline HAMON_CONSTEXPR Matrix
make_orthographic_matrix_rh_impl(T l, T r, T b, T t, T zn, T zf) HAMON_NOEXCEPT
{
	return
	{
		 2/(r-l),      0,            0,           0,
		 0,            2/(t-b),      0,           0,
		 0,            0,            1/(zn-zf),   0,
		-(l+r)/(r-l), -(t+b)/(t-b),  zn/(zn-zf),  1,
	};
}

template <
	typename Matrix,
	typename T1, typename T2, typename T3, typename T4, typename T5, typename T6
>
HAMON_NODISCARD inline HAMON_CONSTEXPR Matrix
make_orthographic_matrix_rh(T1 left, T2 right, T3 bottom, T4 top, T5 near_z, T6 far_z) HAMON_NOEXCEPT
{
	using T = vector_element_t<Matrix>;
	return make_orthographic_matrix_rh_impl<Matrix>(
		static_cast<T>(left),
		static_cast<T>(right),
		static_cast<T>(bottom),
		static_cast<T>(top),
		static_cast<T>(near_z),
		static_cast<T>(far_z));
}

}	// namespace detail

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_MATRIX_DETAIL_MAKE_ORTHOGRAPHIC_MATRIX_HPP
