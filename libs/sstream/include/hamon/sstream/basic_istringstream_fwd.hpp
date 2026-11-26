/**
 *	@file	basic_istringstream_fwd.hpp
 *
 *	@brief	basic_istringstream の前方宣言
 */

#ifndef HAMON_SSTREAM_BASIC_ISTRINGSTREAM_FWD_HPP
#define HAMON_SSTREAM_BASIC_ISTRINGSTREAM_FWD_HPP

#include <hamon/memory/allocator_fwd.hpp>
#include <hamon/string/char_traits_fwd.hpp>
#include <sstream>

namespace hamon
{

using std::basic_istringstream;

#if 0	// TODO
// [istringstream], class template basic_istringstream
template <typename charT, typename traits = char_traits<charT>, typename Allocator = allocator<charT>>
class basic_istringstream;
#endif

}	// namespace hamon

#endif // HAMON_SSTREAM_BASIC_ISTRINGSTREAM_FWD_HPP
