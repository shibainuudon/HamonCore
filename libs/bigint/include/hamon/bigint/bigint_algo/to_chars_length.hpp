/**
 *	@file	to_chars_length.hpp
 *
 *	@brief	to_chars_length 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_TO_CHARS_LENGTH_HPP
#define HAMON_BIGINT_BIGINT_ALGO_TO_CHARS_LENGTH_HPP

#include <hamon/bigint/bigint_algo/detail/actual_size.hpp>
#include <hamon/bigint/bigint_algo/detail/vector_value_t.hpp>
#include <hamon/cmath/log2.hpp>
#include <hamon/cmath/ceil.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace bigint_algo
{

template <typename VectorType>
inline HAMON_CXX14_CONSTEXPR hamon::size_t
to_chars_length(VectorType const& value, int base = 10)
{
	using T = detail::vector_value_t<VectorType>;
	auto const d = hamon::numeric_limits<T>::digits;
	auto const l = hamon::log2(base);
	auto const s = static_cast<double>(detail::actual_size(value));
	return static_cast<hamon::size_t>(hamon::ceil(d / l * s));
}

}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_TO_CHARS_LENGTH_HPP
