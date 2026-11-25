/**
 *	@file	basic_iostream_fwd.hpp
 *
 *	@brief	basic_iostream の前方宣言
 */

#ifndef HAMON_ISTREAM_BASIC_IOSTREAM_FWD_HPP
#define HAMON_ISTREAM_BASIC_IOSTREAM_FWD_HPP

#include <hamon/string/char_traits_fwd.hpp>
#include <istream>

namespace hamon
{

using std::basic_iostream;

#if 0	// TODO
// [iostreamclass], class template basic_iostream
template <typename charT, typename traits = char_traits<charT>>
class basic_iostream;
#endif

}	// namespace hamon

#endif // HAMON_ISTREAM_BASIC_IOSTREAM_FWD_HPP
