/**
 *	@file	make_perspective_matrix.hpp
 *
 *	@brief	make_perspective_matrix の定義
 */

#ifndef HAMON_QVM_MATRIX_DETAIL_MAKE_PERSPECTIVE_MATRIX_HPP
#define HAMON_QVM_MATRIX_DETAIL_MAKE_PERSPECTIVE_MATRIX_HPP

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
make_perspective_matrix_lh_impl(T yscale, T aspect, T zn, T zf) HAMON_NOEXCEPT
{
	return
	{
		yscale / aspect, 0,       0,              0,
		0,               yscale,  0,              0,
		0,               0,      -zf/(zn-zf),     1,
		0,               0,       zn*zf/(zn-zf),  0,
	};
}

template <
	typename Matrix,
	typename T1, typename T2, typename T3, typename T4
>
HAMON_NODISCARD inline HAMON_CONSTEXPR Matrix
make_perspective_matrix_lh(T1 const& fovy, T2 const& aspect, T3 const& near_z, T4 const& far_z) HAMON_NOEXCEPT
{
	using std::tan;
	using T = vector_element_t<Matrix>;
	return make_perspective_matrix_lh_impl<Matrix>(
		static_cast<T>(T(1) / tan(fovy * T(0.5))),
		static_cast<T>(aspect),
		static_cast<T>(near_z),
		static_cast<T>(far_z));
}

template <typename Matrix, typename T>
HAMON_NODISCARD inline HAMON_CONSTEXPR Matrix
make_perspective_matrix_rh_impl(T yscale, T aspect, T zn, T zf) HAMON_NOEXCEPT
{
	return
	{
		yscale / aspect, 0,       0,              0,
		0,               yscale,  0,              0,
		0,               0,       zf/(zn-zf),    -1,
		0,               0,       zn*zf/(zn-zf),  0,
	};
}

template <
	typename Matrix,
	typename T1, typename T2, typename T3, typename T4
>
HAMON_NODISCARD inline HAMON_CONSTEXPR Matrix
make_perspective_matrix_rh(T1 const& fovy, T2 const& aspect, T3 const& near_z, T4 const& far_z) HAMON_NOEXCEPT
{
	using std::tan;
	using T = vector_element_t<Matrix>;
	return make_perspective_matrix_rh_impl<Matrix>(
		static_cast<T>(T(1) / tan(fovy * T(0.5))),
		static_cast<T>(aspect),
		static_cast<T>(near_z),
		static_cast<T>(far_z));
}

}	// namespace detail

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_MATRIX_DETAIL_MAKE_PERSPECTIVE_MATRIX_HPP
