/**
 *	@file	basic_stringstream_fwd.hpp
 *
 *	@brief	basic_stringstream の前方宣言
 */

#ifndef HAMON_SSTREAM_BASIC_STRINGSTREAM_FWD_HPP
#define HAMON_SSTREAM_BASIC_STRINGSTREAM_FWD_HPP

#include <hamon/memory/allocator_fwd.hpp>
#include <hamon/string/char_traits_fwd.hpp>
#include <sstream>

namespace hamon
{

using std::basic_stringstream;

#if 0	// TODO
// [stringstream], class template basic_stringstream
template <typename charT, typename traits = char_traits<charT>, typename Allocator = allocator<charT>>
class basic_stringstream;
#endif

}	// namespace hamon

#endif // HAMON_SSTREAM_BASIC_STRINGSTREAM_FWD_HPP
