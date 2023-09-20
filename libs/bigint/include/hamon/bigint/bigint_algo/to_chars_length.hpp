/**
 *	@file	to_chars_length.hpp
 *
 *	@brief	to_chars_length 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_TO_CHARS_LENGTH_HPP
#define HAMON_BIGINT_BIGINT_ALGO_TO_CHARS_LENGTH_HPP

#include <hamon/bit/has_single_bit.hpp>
#include <hamon/bit/countr_zero.hpp>
#include <hamon/cmath/log2.hpp>
#include <hamon/cmath/ceil.hpp>
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/array.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/limits.hpp>
#include <hamon/vector.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace bigint_algo
{

namespace to_chars_length_detail
{

template <typename VectorType>
inline HAMON_CXX14_CONSTEXPR hamon::size_t
to_chars_length(VectorType const& value, int base)
{
	using T = hamon::ranges::range_value_t<VectorType>;
	auto const d = hamon::numeric_limits<T>::digits;
	auto const l = hamon::log2(base);
	auto const s = static_cast<double>(value.size());
	return static_cast<hamon::size_t>(
		hamon::ceil(d / l * s));
}

}	// namespace to_chars_length_detail

template <typename T>
inline hamon::size_t
to_chars_length(hamon::vector<T> const& value, int base = 10)
{
	return to_chars_length_detail::to_chars_length(value, base);
}

template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR hamon::size_t
to_chars_length(hamon::array<T, N> const& value, int base = 10)
{
	return to_chars_length_detail::to_chars_length(value, base);
}

}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_TO_CHARS_LENGTH_HPP
