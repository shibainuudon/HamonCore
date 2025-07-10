/**
 *	@file	basic_string_fwd.hpp
 *
 *	@brief	basic_string の前方宣言
 */

#ifndef HAMON_STRING_BASIC_STRING_FWD_HPP
#define HAMON_STRING_BASIC_STRING_FWD_HPP

#include <hamon/string/char_traits_fwd.hpp>
#include <hamon/string/config.hpp>
#include <hamon/memory/allocator.hpp>

#if defined(HAMON_USE_STD_STRING)

#include <string>

namespace hamon
{

using std::basic_string;

}	// namespace hamon

#else

namespace hamon
{

template <
	typename CharT,
	typename Traits = hamon::char_traits<CharT>,
	typename Allocator = hamon::allocator<CharT>>
class basic_string;

}	// namespace hamon

#endif

#include <hamon/memory_resource/polymorphic_allocator.hpp>

namespace hamon {
namespace pmr {

template <typename charT, typename traits = hamon::char_traits<charT>>
using basic_string = hamon::basic_string<charT, traits, hamon::pmr::polymorphic_allocator<charT>>;

}	// namespace pmr
}	// namespace hamon

#endif // HAMON_STRING_BASIC_STRING_FWD_HPP
