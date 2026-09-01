/**
 *	@file	wstringstream.hpp
 *
 *	@brief	wstringstream の定義
 */

#ifndef HAMON_SSTREAM_WSTRINGSTREAM_HPP
#define HAMON_SSTREAM_WSTRINGSTREAM_HPP

#include <hamon/sstream/basic_stringstream.hpp>

namespace hamon
{

// [stringstream], class template basic_stringstream

using wstringstream = hamon::basic_stringstream<wchar_t>;

}	// namespace hamon

#endif // HAMON_SSTREAM_WSTRINGSTREAM_HPP
