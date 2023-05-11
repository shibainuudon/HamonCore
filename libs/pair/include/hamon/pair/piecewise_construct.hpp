/**
 *	@file	piecewise_construct.hpp
 *
 *	@brief	piecewise_construct の定義
 */

#ifndef HAMON_PAIR_PIECEWISE_CONSTRUCT_HPP
#define HAMON_PAIR_PIECEWISE_CONSTRUCT_HPP

#include <hamon/pair/config.hpp>

#if defined(HAMON_USE_STD_PAIR)

#include <utility>

namespace hamon
{

using std::piecewise_construct_t;
using std::piecewise_construct;

}	// namespace hamon

#else

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

#endif

#endif // HAMON_PAIR_PIECEWISE_CONSTRUCT_HPP
