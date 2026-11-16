/**
 *	@file	write_float_as_string.hpp
 *
 *	@brief	write_float_as_stringの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_WRITE_FLOAT_AS_STRING_HPP
#define HAMON_SERIALIZATION_DETAIL_WRITE_FLOAT_AS_STRING_HPP

#include <hamon/array.hpp>
#include <hamon/charconv/to_chars.hpp>
#include <hamon/limits.hpp>
#include <hamon/type_traits/is_floating_point.hpp>

namespace hamon
{
namespace serialization
{
namespace detail
{

template <typename OStream, typename Float>
void write_float_as_string(OStream& os, Float t)
{
	static_assert(hamon::is_floating_point_v<Float>, "");
	auto constexpr digits =
		4 +	// sign, decimal point, "e+" or "e-"
		hamon::numeric_limits<Float>::max_digits10 +
		4;	// log10(max_exponent10)
	hamon::array<char, digits + 1> buf{};
	auto result = hamon::to_chars(buf.data(), buf.data() + buf.size(), t);
	os << buf.data();
	(void)result;
}

}	// namespace detail
}	// namespace serialization
}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_WRITE_FLOAT_AS_STRING_HPP
