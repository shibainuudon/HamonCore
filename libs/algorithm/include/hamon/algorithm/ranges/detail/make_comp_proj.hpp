/**
 *	@file	make_comp_proj.hpp
 *
 *	@brief	ranges::detail::make_comp_proj の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_DETAIL_MAKE_COMP_PROJ_HPP
#define HAMON_ALGORITHM_RANGES_DETAIL_MAKE_COMP_PROJ_HPP

#include <hamon/functional/invoke.hpp>
#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

namespace ranges
{

namespace detail
{

template <typename Comp, typename Proj>
struct CompProjT
{
	Comp& m_comp;
	Proj& m_proj;

	template <typename T, typename U>
	HAMON_CXX14_CONSTEXPR bool operator()(T&& lhs, U&& rhs) const
	{
		return hamon::invoke(m_comp,
			hamon::invoke(m_proj, std::forward<T>(lhs)),
			hamon::invoke(m_proj, std::forward<U>(rhs)));
	}
};

template <typename Comp, typename Proj>
HAMON_CXX14_CONSTEXPR CompProjT<Comp, Proj>
make_comp_proj(Comp& comp, Proj& proj)
{
	return CompProjT<Comp, Proj>{comp, proj};
}

}	// namespace detail

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_ALGORITHM_RANGES_DETAIL_MAKE_COMP_PROJ_HPP
