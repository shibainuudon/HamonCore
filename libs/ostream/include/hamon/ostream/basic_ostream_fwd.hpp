/**
 *	@file	basic_ostream_fwd.hpp
 *
 *	@brief	basic_ostream の前方宣言
 */

#ifndef HAMON_OSTREAM_BASIC_OSTREAM_FWD_HPP
#define HAMON_OSTREAM_BASIC_OSTREAM_FWD_HPP

#include <hamon/string/char_traits_fwd.hpp>
#include <ostream>

namespace hamon
{

using std::basic_ostream;

#if 0	// TODO
// [ostream], class template basic_ostream
template <typename charT, typename traits = char_traits<charT>>
class basic_ostream;
#endif

}	// namespace hamon

#endif // HAMON_OSTREAM_BASIC_OSTREAM_FWD_HPP
