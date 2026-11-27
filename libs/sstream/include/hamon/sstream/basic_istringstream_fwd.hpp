/**
 *	@file	basic_istringstream_fwd.hpp
 *
 *	@brief	basic_istringstream の前方宣言
 */

#ifndef HAMON_SSTREAM_BASIC_ISTRINGSTREAM_FWD_HPP
#define HAMON_SSTREAM_BASIC_ISTRINGSTREAM_FWD_HPP

#include <hamon/memory/allocator_fwd.hpp>
#include <hamon/string/char_traits_fwd.hpp>

#if 0
#include <sstream>
namespace hamon
{
using std::basic_istringstream;
}	// namespace hamon

#else
namespace hamon
{

// [istringstream], class template basic_istringstream
template <typename charT, typename traits = hamon::char_traits<charT>, typename Allocator = hamon::allocator<charT>>
class basic_istringstream;

}	// namespace hamon
#endif

#endif // HAMON_SSTREAM_BASIC_ISTRINGSTREAM_FWD_HPP
