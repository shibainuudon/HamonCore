/**
 *	@file	flush.hpp
 *
 *	@brief	flush の定義
 */

#ifndef HAMON_OSTREAM_FLUSH_HPP
#define HAMON_OSTREAM_FLUSH_HPP

#include <ostream>

namespace hamon
{

using std::flush;

#if 0	// TODO
// [ostream.manip], standard basic_ostream manipulators
template <typename charT, typename traits>
basic_ostream<charT, traits>& flush(basic_ostream<charT, traits>& os);
#endif

}	// namespace hamon

#endif // HAMON_OSTREAM_FLUSH_HPP
