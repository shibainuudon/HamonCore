/**
 *	@file	cross.hpp
 *
 *	@brief	cross の定義
 */

#ifndef HAMON_QVM_VECTOR_CROSS_HPP
#define HAMON_QVM_VECTOR_CROSS_HPP

#include <hamon/qvm/vector/vector.hpp>
#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

namespace qvm
{

/**
 *	@brief	外積
 */
template <typename T1, typename T2>
HAMON_NODISCARD inline HAMON_CONSTEXPR
vector<decltype(std::declval<T1>() * std::declval<T2>()), 3>
cross(vector<T1, 3> const& v1, vector<T2, 3> const& v2) HAMON_NOEXCEPT
{
	return
	{
		(v1.y() * v2.z()) - (v1.z() * v2.y()),
		(v1.z() * v2.x()) - (v1.x() * v2.z()),
		(v1.x() * v2.y()) - (v1.y() * v2.x()),
	};
}

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_VECTOR_CROSS_HPP
