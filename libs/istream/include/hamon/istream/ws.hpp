/**
 *	@file	ws.hpp
 *
 *	@brief	ws の定義
 */

#ifndef HAMON_ISTREAM_WS_HPP
#define HAMON_ISTREAM_WS_HPP

#include <istream>

namespace hamon
{

using std::ws;

#if 0	// TODO
// [istream.manip], standard basic_istream manipulators
template <typename charT, typename traits>
basic_istream<charT, traits>& ws(basic_istream<charT, traits>& is);
#endif

}	// namespace hamon

#endif // HAMON_ISTREAM_WS_HPP
