/**
 *	@file	wstreambuf.hpp
 *
 *	@brief	wstreambuf の定義
 */

#ifndef HAMON_STREAMBUF_WSTREAMBUF_HPP
#define HAMON_STREAMBUF_WSTREAMBUF_HPP

#include <hamon/streambuf/basic_streambuf.hpp>

namespace hamon
{

using wstreambuf = hamon::basic_streambuf<wchar_t>;

}	// namespace hamon

#endif // HAMON_STREAMBUF_WSTREAMBUF_HPP
