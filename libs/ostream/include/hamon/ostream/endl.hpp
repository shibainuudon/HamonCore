/**
 *	@file	endl.hpp
 *
 *	@brief	endl の定義
 */

#ifndef HAMON_OSTREAM_ENDL_HPP
#define HAMON_OSTREAM_ENDL_HPP

#include <ostream>

namespace hamon
{

using std::endl;

#if 0	// TODO
// [ostream.manip], standard basic_ostream manipulators
template <typename charT, typename traits>
basic_ostream<charT, traits>& endl(basic_ostream<charT, traits>& os);
#endif

}	// namespace hamon

#endif // HAMON_OSTREAM_ENDL_HPP
