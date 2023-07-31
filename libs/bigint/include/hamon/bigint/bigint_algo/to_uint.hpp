/**
 *	@file	to_uint.hpp
 *
 *	@brief	to_uint 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_TO_UINT_HPP
#define HAMON_BIGINT_BIGINT_ALGO_TO_UINT_HPP

#include <hamon/array.hpp>
#include <hamon/bit/bitsof.hpp>
#include <hamon/bit/shl.hpp>
#include <hamon/bit/countl_zero.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_unsigned.hpp>
#include <hamon/config.hpp>
#include <system_error>
#include <vector>

namespace hamon
{
namespace bigint_algo
{

struct to_uint_result
{
	std::errc ec;
};

namespace to_uint_detail
{

template <typename UInt, typename T>
inline HAMON_CXX14_CONSTEXPR to_uint_result
to_uint(UInt& dst, T const* src, hamon::size_t size)
{
	dst = 0;
	for (hamon::size_t i = 0; i < size; ++i)
	{
		if (src[i] > std::numeric_limits<UInt>::max())
		{
			return {std::errc::value_too_large};
		}

		auto const v = static_cast<UInt>(src[i]);
		auto const shift = static_cast<unsigned int>(i * hamon::bitsof<T>());

		if (v != 0 && shift > static_cast<unsigned int>(hamon::countl_zero(v)))
		{
			return {std::errc::value_too_large};
		}

		dst = static_cast<UInt>(dst | hamon::shl(v, shift));
	}
	return {std::errc{}};
}

}	// namespace to_uint_detail

template <typename UInt, typename T,
	typename = hamon::enable_if_t<hamon::is_unsigned<UInt>::value>
>
inline to_uint_result
to_uint(UInt& dst, std::vector<T> const& value)
{
	return to_uint_detail::to_uint(dst, value.data(), value.size());
}

template <typename UInt, typename T, hamon::size_t N,
	typename = hamon::enable_if_t<hamon::is_unsigned<UInt>::value>
>
inline HAMON_CXX14_CONSTEXPR to_uint_result
to_uint(UInt& dst, hamon::array<T, N> const& value)
{
	return to_uint_detail::to_uint(dst, value.data(), value.size());
}

}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_TO_UINT_HPP
