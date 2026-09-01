/**
 *	@file	wstringbuf.hpp
 *
 *	@brief	wstringbuf の定義
 */

#ifndef HAMON_SSTREAM_WSTRINGBUF_HPP
#define HAMON_SSTREAM_WSTRINGBUF_HPP

#include <hamon/sstream/basic_stringbuf.hpp>

namespace hamon
{

// [stringbuf], class template basic_stringbuf

using wstringbuf = hamon::basic_stringbuf<wchar_t>;

}	// namespace hamon

#endif // HAMON_SSTREAM_WSTRINGBUF_HPP
