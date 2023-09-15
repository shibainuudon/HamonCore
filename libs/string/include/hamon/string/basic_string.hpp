/**
 *	@file	basic_string.hpp
 *
 *	@brief	basic_string の定義
 */

#ifndef HAMON_STRING_BASIC_STRING_HPP
#define HAMON_STRING_BASIC_STRING_HPP

#include <hamon/string/config.hpp>

#if 1	// TODO defined(HAMON_USE_STD_STRING)

#include <string>

namespace hamon
{

using std::basic_string;

}	// namespace hamon

#else

// TODO

#endif

#endif // HAMON_STRING_BASIC_STRING_HPP
