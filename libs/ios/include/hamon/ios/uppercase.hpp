/**
 *	@file	uppercase.hpp
 *
 *	@brief	uppercase の定義
 */

#ifndef HAMON_IOS_UPPERCASE_HPP
#define HAMON_IOS_UPPERCASE_HPP

#include <ios>

namespace hamon
{

using std::uppercase;
using std::nouppercase;

#if 0	// TODO
// [std.ios.manip], manipulators
ios_base& uppercase(ios_base& str);
ios_base& nouppercase(ios_base& str);
#endif

}	// namespace hamon

#endif // HAMON_IOS_UPPERCASE_HPP
