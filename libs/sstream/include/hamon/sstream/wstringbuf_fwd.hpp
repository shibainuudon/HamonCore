/**
 *	@file	wstringbuf_fwd.hpp
 *
 *	@brief	wstringbuf の前方宣言
 */

#ifndef HAMON_SSTREAM_WSTRINGBUF_FWD_HPP
#define HAMON_SSTREAM_WSTRINGBUF_FWD_HPP

#include <hamon/sstream/basic_stringbuf_fwd.hpp>

namespace hamon
{

// [stringbuf], class template basic_stringbuf

using wstringbuf = hamon::basic_stringbuf<wchar_t>;

}	// namespace hamon

#endif // HAMON_SSTREAM_WSTRINGBUF_FWD_HPP
