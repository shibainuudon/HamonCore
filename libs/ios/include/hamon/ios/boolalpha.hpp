/**
 *	@file	boolalpha.hpp
 *
 *	@brief	boolalpha の定義
 */

#ifndef HAMON_IOS_BOOLALPHA_HPP
#define HAMON_IOS_BOOLALPHA_HPP

#include <ios>

namespace hamon
{

using std::boolalpha;
using std::noboolalpha;

#if 0	// TODO
// [std.ios.manip], manipulators
ios_base& boolalpha(ios_base& str);
ios_base& noboolalpha(ios_base& str);
#endif

}	// namespace hamon

#endif // HAMON_IOS_BOOLALPHA_HPP
