/**
 *	@file	henry.hpp
 *
 *	@brief	henry の定義
 */

#ifndef HAMON_UNITS_HENRY_HPP
#define HAMON_UNITS_HENRY_HPP

#include <hamon/units/volt.hpp>
#include <hamon/units/ampere.hpp>
#include <hamon/units/second.hpp>
#include <hamon/units/detail/si_prefix.hpp>

namespace hamon
{

namespace units
{

// ヘンリー(インダクタンスの単位)
template <typename T> using henry   = decltype(volt<T>() / ampere<T>() * second<T>());
template <typename T> using henries = henry<T>;
HAMON_UNITS_SI_PREFIX(henry);
HAMON_UNITS_SI_PREFIX(henries);

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_HENRY_HPP
