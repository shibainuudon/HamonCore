/**
 *	@file	piecewise_construct_t.hpp
 *
 *	@brief	piecewise_construct_t の定義
 */

#ifndef HAMON_PAIR_PIECEWISE_CONSTRUCT_T_HPP
#define HAMON_PAIR_PIECEWISE_CONSTRUCT_T_HPP

#include <hamon/config.hpp>

namespace hamon
{

// Piecewise construction	[pair.piecewise]
struct piecewise_construct_t
{
	explicit piecewise_construct_t() = default;
};

HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR piecewise_construct_t piecewise_construct{};

}	// namespace hamon

#endif // HAMON_PAIR_PIECEWISE_CONSTRUCT_T_HPP
