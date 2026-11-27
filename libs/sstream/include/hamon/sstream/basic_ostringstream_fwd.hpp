/**
 *	@file	basic_ostringstream_fwd.hpp
 *
 *	@brief	basic_ostringstream の前方宣言
 */

#ifndef HAMON_SSTREAM_BASIC_OSTRINGSTREAM_FWD_HPP
#define HAMON_SSTREAM_BASIC_OSTRINGSTREAM_FWD_HPP

#include <hamon/memory/allocator_fwd.hpp>
#include <hamon/string/char_traits_fwd.hpp>

#if 0
#include <sstream>
namespace hamon
{
using std::basic_ostringstream;
}	// namespace hamon

#else
namespace hamon
{

// [ostringstream], class template basic_ostringstream
template <typename charT, typename traits = hamon::char_traits<charT>, typename Allocator = hamon::allocator<charT>>
class basic_ostringstream;

}	// namespace hamon
#endif

#endif // HAMON_SSTREAM_BASIC_OSTRINGSTREAM_FWD_HPP
