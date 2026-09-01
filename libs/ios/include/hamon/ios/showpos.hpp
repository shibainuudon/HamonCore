/**
 *	@file	showpos.hpp
 *
 *	@brief	showpos の定義
 */

#ifndef HAMON_IOS_SHOWPOS_HPP
#define HAMON_IOS_SHOWPOS_HPP

#include <ios>

namespace hamon
{

using std::showpos;
using std::noshowpos;

#if 0	// TODO
// [std.ios.manip], manipulators
ios_base& showpos(ios_base& str);
ios_base& noshowpos(ios_base& str);
#endif

}	// namespace hamon

#endif // HAMON_IOS_SHOWPOS_HPP
