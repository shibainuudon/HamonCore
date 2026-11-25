/**
 *	@file	basic_istream_fwd.hpp
 *
 *	@brief	basic_istream の前方宣言
 */

#ifndef HAMON_ISTREAM_BASIC_ISTREAM_FWD_HPP
#define HAMON_ISTREAM_BASIC_ISTREAM_FWD_HPP

#include <hamon/string/char_traits_fwd.hpp>
#include <istream>

namespace hamon
{

using std::basic_istream;

#if 0	// TODO
// [istream], class template basic_istream
template <typename charT, typename traits = char_traits<charT>>
class basic_istream;
#endif

}	// namespace hamon

#endif // HAMON_ISTREAM_BASIC_ISTREAM_FWD_HPP
