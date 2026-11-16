/**
 *	@file	read_float_from_string.hpp
 *
 *	@brief	read_float_from_stringの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_READ_FLOAT_FROM_STRING_HPP
#define HAMON_SERIALIZATION_DETAIL_READ_FLOAT_FROM_STRING_HPP

#include <hamon/algorithm/transform.hpp>
#include <hamon/charconv/from_chars.hpp>
#include <hamon/ios/ios_base.hpp>
#include <hamon/istream/basic_istream.hpp>
#include <hamon/string.hpp>
#include <hamon/type_traits/is_floating_point.hpp>

namespace hamon
{
namespace serialization
{
namespace detail
{

// is >> t;
// だとinfとnanのときに正常にパースされない。
// これは標準ライブラリの不具合で、将来的に修正される予定。
// https://cplusplus.github.io/LWG/issue2381

template <typename Traits, typename Float>
void read_float_from_string(hamon::basic_istream<char, Traits>& is, Float& t)
{
	static_assert(hamon::is_floating_point_v<Float>, "");

	hamon::string s;
	is >> s;
	auto first = s.data();
	auto last  = s.data() + s.length();
	auto result = hamon::from_chars(first, last, t);
	is.seekg(result.ptr - last, hamon::ios_base::cur);	// 変換できなかったぶん戻す
}

template <typename CharT, typename Traits, typename Float>
void read_float_from_string(hamon::basic_istream<CharT, Traits>& is, Float& t)
{
	static_assert(hamon::is_floating_point_v<Float>, "");

	hamon::basic_string<CharT> tmp;
	is >> tmp;
	hamon::string s;
	s.resize(tmp.size());
	hamon::transform(tmp.begin(), tmp.end(), s.begin(),
		[](CharT c){return static_cast<char>(c);});
	auto first = s.data();
	auto last  = s.data() + s.length();
	auto result = hamon::from_chars(first, last, t);
	is.seekg(result.ptr - last, hamon::ios_base::cur);	// 変換できなかったぶん戻す
}

}	// namespace detail
}	// namespace serialization
}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_READ_FLOAT_FROM_STRING_HPP
