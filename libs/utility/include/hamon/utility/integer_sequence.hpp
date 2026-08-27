/**
 *	@file	integer_sequence.hpp
 *
 *	@brief	integer_sequence を定義
 */

#ifndef HAMON_UTILITY_INTEGER_SEQUENCE_HPP
#define HAMON_UTILITY_INTEGER_SEQUENCE_HPP

#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/is_integral.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 21.2.2 Class template integer_sequence[intseq.intseq]

template <typename T, T... I>
struct integer_sequence
{
	// [intseq.intseq]/1
	static_assert(hamon::is_integral_v<T>, "");

	using value_type = T;

	HAMON_STATIC_CONSTEXPR hamon::size_t
	size() HAMON_NOEXCEPT { return sizeof...(I); }
};

// TODO
// tuple_size, tuple_elemtn, get サポート (since C++26)

}	// namespace hamon

#endif // HAMON_UTILITY_INTEGER_SEQUENCE_HPP
