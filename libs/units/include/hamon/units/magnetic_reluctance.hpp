/**
 *	@file	magnetic_reluctance.hpp
 *
 *	@brief	magnetic_reluctance の定義
 */

#ifndef HAMON_UNITS_MAGNETIC_RELUCTANCE_HPP
#define HAMON_UNITS_MAGNETIC_RELUCTANCE_HPP

#include <hamon/units/ampere.hpp>
#include <hamon/units/weber.hpp>
#include <hamon/units/henry.hpp>

namespace hamon
{

namespace units
{

// アンペア毎ウェーバ(磁気抵抗の単位)
template <typename T> using ampere_per_weber  = decltype(ampere<T>() / weber<T>());
template <typename T> using amperes_per_weber = ampere_per_weber<T>;

// 毎ヘンリー(磁気抵抗の単位)
template <typename T> using reciprocal_henry   = decltype(T() / henry<T>());
template <typename T> using reciprocal_henries = reciprocal_henry<T>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_MAGNETIC_RELUCTANCE_HPP
