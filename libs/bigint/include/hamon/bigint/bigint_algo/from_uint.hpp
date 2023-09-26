/**
 *	@file	from_uint.hpp
 *
 *	@brief	from_uint 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_FROM_UINT_HPP
#define HAMON_BIGINT_BIGINT_ALGO_FROM_UINT_HPP

#include <hamon/bigint/bigint_algo/normalize.hpp>
#include <hamon/array.hpp>
#include <hamon/bit/bitsof.hpp>
#include <hamon/bit/shr.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/system_error/errc.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_unsigned.hpp>
#include <hamon/vector.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace bigint_algo
{

struct from_uint_result
{
	hamon::errc ec;
};

namespace from_uint_detail
{

template <typename UInt, typename T>
inline HAMON_CXX14_CONSTEXPR from_uint_result
from_uint(UInt n, T* dst, hamon::size_t size)
{
	for (hamon::size_t i = 0; i < size; ++i)
	{
		dst[i] = static_cast<T>(n);
		n = hamon::shr(n, static_cast<unsigned int>(hamon::bitsof<T>()));
	}
	
	if (n != 0)
	{
		return {hamon::errc::result_out_of_range};
	}

	return {hamon::errc{}};
}

}	// namespace from_uint_detail

template <typename UInt, typename T,
	typename = hamon::enable_if_t<hamon::is_unsigned<UInt>::value>
>
inline from_uint_result
from_uint(UInt n, hamon::vector<T>& value)
{
	value.resize(sizeof(UInt) > sizeof(T) ? sizeof(UInt) / sizeof(T) : 1);
	auto ret = from_uint_detail::from_uint(n, value.data(), value.size());
	bigint_algo::normalize(value);
	return ret;
}

template <typename UInt, typename T, hamon::size_t N,
	typename = hamon::enable_if_t<hamon::is_unsigned<UInt>::value>
>
inline HAMON_CXX14_CONSTEXPR from_uint_result
from_uint(UInt n, hamon::array<T, N>& value)
{
	return from_uint_detail::from_uint(n, value.data(), value.size());
}

}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_FROM_UINT_HPP
