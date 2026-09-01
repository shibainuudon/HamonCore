/**
 *	@file	stringstream.hpp
 *
 *	@brief	stringstream の定義
 */

#ifndef HAMON_SSTREAM_STRINGSTREAM_HPP
#define HAMON_SSTREAM_STRINGSTREAM_HPP

#include <hamon/sstream/basic_stringstream.hpp>

namespace hamon
{

// [stringstream], class template basic_stringstream

using stringstream = hamon::basic_stringstream<char>;

}	// namespace hamon

#endif // HAMON_SSTREAM_STRINGSTREAM_HPP
