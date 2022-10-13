/**
 *	@file	lerp.hpp
 *
 *	@brief	lerp の定義
 */

#ifndef HAMON_QVM_VECTOR_LERP_HPP
#define HAMON_QVM_VECTOR_LERP_HPP

#include <hamon/qvm/vector/vector.hpp>
#include <hamon/qvm/detail/transform.hpp>
#include <hamon/qvm/detail/lerp_fn.hpp>
#include <hamon/concepts/arithmetic.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace qvm
{

/**
 *	@brief	lerp
 */
template <
	typename T1, std::size_t N,
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, T2)
>
HAMON_NODISCARD inline HAMON_CONSTEXPR auto
lerp(vector<T1, N> const& from, vector<T1, N> const& to, T2 const& t) HAMON_NOEXCEPT
->decltype(hamon::qvm::transform(from, to, hamon::qvm::detail::lerp_fn<T2>{t}))
{
	return hamon::qvm::transform(from, to, hamon::qvm::detail::lerp_fn<T2>{t});
}

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_VECTOR_LERP_HPP
