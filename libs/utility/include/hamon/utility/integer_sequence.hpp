/**
 *	@file	integer_sequence.hpp
 *
 *	@brief	integer_sequence を定義
 */

#ifndef HAMON_UTILITY_INTEGER_SEQUENCE_HPP
#define HAMON_UTILITY_INTEGER_SEQUENCE_HPP

#include <utility>

#if defined(__cpp_lib_integer_sequence) && (__cpp_lib_integer_sequence >= 201304)

namespace hamon
{

using std::integer_sequence;

}	// namespace hamon

#else

#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{

template <typename T, T... I>
struct integer_sequence
{
	using value_type = T;
	HAMON_STATIC_CONSTEXPR hamon::size_t
	size() HAMON_NOEXCEPT { return sizeof...(I); }
};

}	// namespace hamon

#endif

#endif // HAMON_UTILITY_INTEGER_SEQUENCE_HPP
