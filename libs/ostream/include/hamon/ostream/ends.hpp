/**
 *	@file	ends.hpp
 *
 *	@brief	ends の定義
 */

#ifndef HAMON_OSTREAM_ENDS_HPP
#define HAMON_OSTREAM_ENDS_HPP

#include <ostream>

namespace hamon
{

using std::ends;

#if 0	// TODO
// [ostream.manip], standard basic_ostream manipulators
template <typename charT, typename traits>
basic_ostream<charT, traits>& ends(basic_ostream<charT, traits>& os);
#endif

}	// namespace hamon

#endif // HAMON_OSTREAM_ENDS_HPP
