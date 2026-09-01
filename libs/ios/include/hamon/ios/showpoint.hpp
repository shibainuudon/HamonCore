/**
 *	@file	showpoint.hpp
 *
 *	@brief	showpoint の定義
 */

#ifndef HAMON_IOS_SHOWPOINT_HPP
#define HAMON_IOS_SHOWPOINT_HPP

#include <ios>

namespace hamon
{

using std::showpoint;
using std::noshowpoint;

#if 0	// TODO
// [std.ios.manip], manipulators
ios_base& showpoint(ios_base& str);
ios_base& noshowpoint(ios_base& str);
#endif

}	// namespace hamon

#endif // HAMON_IOS_SHOWPOINT_HPP
