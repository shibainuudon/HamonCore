/**
 *	@file	stringstream_fwd.hpp
 *
 *	@brief	stringstream の前方宣言
 */

#ifndef HAMON_SSTREAM_STRINGSTREAM_FWD_HPP
#define HAMON_SSTREAM_STRINGSTREAM_FWD_HPP

#include <hamon/sstream/basic_stringstream_fwd.hpp>

namespace hamon
{

// [stringstream], class template basic_stringstream

using stringstream = hamon::basic_stringstream<char>;

}	// namespace hamon

#endif // HAMON_SSTREAM_STRINGSTREAM_FWD_HPP
