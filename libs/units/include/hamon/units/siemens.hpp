/**
 *	@file	siemens.hpp
 *
 *	@brief	siemens の定義
 */

#ifndef HAMON_UNITS_SIEMENS_HPP
#define HAMON_UNITS_SIEMENS_HPP

#include <hamon/units/volt.hpp>
#include <hamon/units/ampere.hpp>
#include <hamon/units/detail/si_prefix.hpp>

namespace hamon
{

namespace units
{

// ジーメンス(コンダクタンスの単位)
template <typename T> using siemens  = decltype(ampere<T>() / volt<T>());
HAMON_UNITS_SI_PREFIX(siemens);
// ※単数形・複数形ともsiemens

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_SIEMENS_HPP
