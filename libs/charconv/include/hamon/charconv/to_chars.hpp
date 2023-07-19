/**
 *	@file	to_chars.hpp
 *
 *	@brief	to_chars の定義
 */

#ifndef HAMON_CHARCONV_TO_CHARS_HPP
#define HAMON_CHARCONV_TO_CHARS_HPP

#include <hamon/charconv/config.hpp>

#if defined(HAMON_USE_STD_CHARCONV)

#include <charconv>

namespace hamon
{

using std::to_chars;

}	// namespace hamon

#else

#include <hamon/config.hpp>

namespace hamon
{


}	// namespace hamon

#endif

#endif // HAMON_CHARCONV_TO_CHARS_HPP
