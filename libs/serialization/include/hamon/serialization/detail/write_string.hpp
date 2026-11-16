/**
 *	@file	write_string.hpp
 *
 *	@brief	write_stringの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_WRITE_STRING_HPP
#define HAMON_SERIALIZATION_DETAIL_WRITE_STRING_HPP

#include <hamon/algorithm/transform.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/ios/streamsize.hpp>
#include <hamon/ostream/basic_ostream.hpp>
#include <hamon/string.hpp>
#include <hamon/type_traits/enable_if.hpp>

namespace hamon
{
namespace serialization
{
namespace detail
{

template <
	typename CharT1, typename Traits1,
	typename CharT2,
	hamon::enable_if_t<(sizeof(CharT1) > sizeof(CharT2))>* = nullptr
>
void write_string(
	hamon::basic_ostream<CharT1, Traits1>& os,
	CharT2 const* str, hamon::size_t length)
{
	hamon::basic_string<CharT1> tmp;
	tmp.resize(length);
	hamon::transform(str, str + length, tmp.begin(),
		[](CharT2 c){return static_cast<CharT1>(c);});
	os.write(tmp.c_str(), static_cast<hamon::streamsize>(tmp.size()));
}

template <
	typename CharT1, typename Traits1,
	typename CharT2,
	hamon::enable_if_t<sizeof(CharT1) <= sizeof(CharT2)>* = nullptr
>
void write_string(
	hamon::basic_ostream<CharT1, Traits1>& os,
	CharT2 const* str, hamon::size_t length)
{
	auto const count = (length * sizeof(CharT2)) / sizeof(CharT1);
	os.write(reinterpret_cast<CharT1 const*>(str), static_cast<hamon::streamsize>(count));
}

}	// namespace detail
}	// namespace serialization
}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_WRITE_STRING_HPP
