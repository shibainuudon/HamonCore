/**
 *	@file	basic_ostream.hpp
 *
 *	@brief	basic_ostream の定義
 */

#ifndef HAMON_OSTREAM_BASIC_OSTREAM_HPP
#define HAMON_OSTREAM_BASIC_OSTREAM_HPP

#include <hamon/ostream/basic_ostream_fwd.hpp>
#include <hamon/string/char_traits.hpp>

namespace hamon
{

#if 0	// TODO
// [ostream], class template basic_ostream
template <typename charT, typename traits = char_traits<charT>>
class basic_ostream;

// [ostream.rvalue], rvalue stream insertion
template <typename Ostream, typename T>
Ostream&& operator<<(Ostream&& os, const T& x);
#endif

}	// namespace hamon

#endif // HAMON_OSTREAM_BASIC_OSTREAM_HPP
