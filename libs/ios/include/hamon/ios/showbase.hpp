/**
 *	@file	showbase.hpp
 *
 *	@brief	showbase の定義
 */

#ifndef HAMON_IOS_SHOWBASE_HPP
#define HAMON_IOS_SHOWBASE_HPP

#include <ios>

namespace hamon
{

using std::showbase;
using std::noshowbase;

#if 0	// TODO
// [std.ios.manip], manipulators
ios_base& showbase(ios_base& str);
ios_base& noshowbase(ios_base& str);
#endif

}	// namespace hamon

#endif // HAMON_IOS_SHOWBASE_HPP
