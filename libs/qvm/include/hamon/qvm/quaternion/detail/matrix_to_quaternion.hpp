/**
 *	@file	matrix_to_quaternion.hpp
 *
 *	@brief	matrix_to_quaternion の定義
 */

#ifndef HAMON_QVM_QUATERNION_DETAIL_MATRIX_TO_QUATERNION_HPP
#define HAMON_QVM_QUATERNION_DETAIL_MATRIX_TO_QUATERNION_HPP

#include <hamon/qvm/quaternion/quaternion.hpp>
#include <hamon/qvm/matrix/matrix.hpp>
#include <hamon/algorithm/ranges/max_element.hpp>
#include <hamon/cmath/sqrt.hpp>
#include <hamon/iterator/ranges/distance.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace qvm
{

namespace detail
{

template <typename T>
inline HAMON_CXX14_CONSTEXPR quaternion<T>
matrix_to_quaternion(matrix<T, 3, 3> const& m) HAMON_NOEXCEPT
{
	// 最大成分を検索
	T const elem[] =
	{
		 m[0][0] - m[1][1] - m[2][2] + T(1),	// x
		-m[0][0] + m[1][1] - m[2][2] + T(1),	// y
		-m[0][0] - m[1][1] + m[2][2] + T(1),	// z
		 m[0][0] + m[1][1] + m[2][2] + T(1),	// w
	};

	auto const max_it = hamon::ranges::max_element(elem);

	if (*max_it < 0)
	{
		// 引数の行列に間違いあり！
		return quaternion<T>::identity();
	}

	// 最大要素の値を算出
	auto const v = hamon::sqrt(*max_it) * 0.5f;
	auto const mult = 0.25f / v;

	switch (hamon::ranges::distance(elem, max_it))
	{
	case 0: // x
		return
		{
			v,
			(m[0][1] + m[1][0]) * mult,
			(m[2][0] + m[0][2]) * mult,
			(m[1][2] - m[2][1]) * mult,
		};
	case 1: // y
		return
		{
			(m[0][1] + m[1][0]) * mult,
			v,
			(m[1][2] + m[2][1]) * mult,
			(m[2][0] - m[0][2]) * mult,
		};
	case 2: // z
		return
		{
			(m[2][0] + m[0][2]) * mult,
			(m[1][2] + m[2][1]) * mult,
			v,
			(m[0][1] - m[1][0]) * mult,
		};
	case 3: // w
		return
		{
			(m[1][2] - m[2][1]) * mult,
			(m[2][0] - m[0][2]) * mult,
			(m[0][1] - m[1][0]) * mult,
			v,
		};
	default:
		// ここには来るはずがない
		return quaternion<T>::identity();
	}
}

}	// namespace detail

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_QUATERNION_DETAIL_MATRIX_TO_QUATERNION_HPP
