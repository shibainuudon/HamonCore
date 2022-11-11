/**
 *	@file	chain.hpp
 *
 *	@brief	chain の定義
 */

#ifndef HAMON_UNITS_CHAIN_HPP
#define HAMON_UNITS_CHAIN_HPP

#include <hamon/units/foot.hpp>
#include <ratio>

namespace hamon
{

namespace units
{

// 国際チェーン = 66フィート(正確に20.1168m)
template <typename T> using chain  = decltype(foot<T>() * std::ratio<66>());
template <typename T> using chains = chain<T>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_CHAIN_HPP
