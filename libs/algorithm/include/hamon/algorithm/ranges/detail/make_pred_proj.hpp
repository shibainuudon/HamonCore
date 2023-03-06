/**
 *	@file	make_pred_proj.hpp
 *
 *	@brief	ranges::detail::make_pred_proj の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_DETAIL_MAKE_PRED_PROJ_HPP
#define HAMON_ALGORITHM_RANGES_DETAIL_MAKE_PRED_PROJ_HPP

#include <hamon/functional/invoke.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

namespace detail
{

template <typename Pred, typename Proj>
struct PredProjT
{
	Pred& m_pred;
	Proj& m_proj;

	template <typename T>
	HAMON_CXX14_CONSTEXPR bool operator()(T&& arg) const
	{
		return hamon::invoke(m_pred,
			hamon::invoke(m_proj, hamon::forward<T>(arg)));
	}
};

template <typename Pred, typename Proj>
HAMON_CXX14_CONSTEXPR PredProjT<Pred, Proj>
make_pred_proj(Pred& pred, Proj& proj)
{
	return PredProjT<Pred, Proj>{pred, proj};
}

}	// namespace detail

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_ALGORITHM_RANGES_DETAIL_MAKE_PRED_PROJ_HPP
