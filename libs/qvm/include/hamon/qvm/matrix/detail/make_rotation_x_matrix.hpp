﻿/**
 *	@file	make_rotation_x_matrix.hpp
 *
 *	@brief	make_rotation_x_matrix の定義
 */

#ifndef HAMON_QVM_MATRIX_DETAIL_MAKE_ROTATION_X_MATRIX_HPP
#define HAMON_QVM_MATRIX_DETAIL_MAKE_ROTATION_X_MATRIX_HPP

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
make_rotation_x_matrix_impl(T const& s, T const& c) HAMON_NOEXCEPT
{
	return
	{
		1,  0,  0,
		0,  c,  s,
		0, -s,  c,
	};
}

template <typename Matrix, typename AngleType>
HAMON_NODISCARD inline HAMON_CONSTEXPR Matrix
make_rotation_x_matrix(AngleType const& angle) HAMON_NOEXCEPT
{
	using std::sin;
	using std::cos;
	using T = qvm::detail::vector_element_t<Matrix>;
	return make_rotation_x_matrix_impl<Matrix>(
		static_cast<T>(sin(angle)),
		static_cast<T>(cos(angle)));
}

}	// namespace detail

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_MATRIX_DETAIL_MAKE_ROTATION_X_MATRIX_HPP
