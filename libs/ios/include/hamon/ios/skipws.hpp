/**
 *	@file	skipws.hpp
 *
 *	@brief	skipws の定義
 */

#ifndef HAMON_IOS_SKIPWS_HPP
#define HAMON_IOS_SKIPWS_HPP

#include <ios>

namespace hamon
{

using std::skipws;
using std::noskipws;

#if 0	// TODO
// [std.ios.manip], manipulators
ios_base& skipws(ios_base& str);
ios_base& noskipws(ios_base& str);
#endif

}	// namespace hamon

#endif // HAMON_IOS_SKIPWS_HPP
