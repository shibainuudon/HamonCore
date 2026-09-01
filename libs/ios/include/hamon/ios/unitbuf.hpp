/**
 *	@file	unitbuf.hpp
 *
 *	@brief	unitbuf の定義
 */

#ifndef HAMON_IOS_UNITBUF_HPP
#define HAMON_IOS_UNITBUF_HPP

#include <ios>

namespace hamon
{

using std::unitbuf;
using std::nounitbuf;

#if 0	// TODO
// [std.ios.manip], manipulators
ios_base& unitbuf(ios_base& str);
ios_base& nounitbuf(ios_base& str);
#endif

}	// namespace hamon

#endif // HAMON_IOS_UNITBUF_HPP
