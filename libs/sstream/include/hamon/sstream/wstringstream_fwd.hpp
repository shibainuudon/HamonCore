/**
 *	@file	wstringstream_fwd.hpp
 *
 *	@brief	wstringstream の前方宣言
 */

#ifndef HAMON_SSTREAM_WSTRINGSTREAM_FWD_HPP
#define HAMON_SSTREAM_WSTRINGSTREAM_FWD_HPP

#include <hamon/sstream/basic_stringstream_fwd.hpp>

namespace hamon
{

// [stringstream], class template basic_stringstream

using wstringstream = hamon::basic_stringstream<wchar_t>;

}	// namespace hamon

#endif // HAMON_SSTREAM_WSTRINGSTREAM_FWD_HPP
