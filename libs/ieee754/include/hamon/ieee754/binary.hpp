/**
 *	@file	binary.hpp
 *
 *	@brief	binary の定義
 */

#ifndef HAMON_IEEE754_BINARY_HPP
#define HAMON_IEEE754_BINARY_HPP

#include <hamon/bit/bit_cast.hpp>
#include <hamon/bit/bitsof.hpp>
#include <hamon/bit/countr_zero.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/limits.hpp>
#include <hamon/type_traits/make_signed.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ieee754
{

namespace detail
{

template <typename T>
struct binary_traits;

template <>
struct binary_traits<float>
{
	using uint_type     = hamon::uint32_t;
	using sign_type     = hamon::uint8_t;
	using exponent_type = hamon::uint32_t;
	using fraction_type = hamon::uint32_t;
};

template <>
struct binary_traits<double>
{
	using uint_type     = hamon::uint64_t;
	using sign_type     = hamon::uint8_t;
	using exponent_type = hamon::uint32_t;
	using fraction_type = hamon::uint64_t;
};

}	// namespace detail

template <typename T>
class binary
{
private:
	using Traits = hamon::ieee754::detail::binary_traits<T>;

public:
	using uint_type     = typename Traits::uint_type;
	using int_type      = hamon::make_signed_t<uint_type>;
	using sign_type     = typename Traits::sign_type;
	using exponent_type = typename Traits::exponent_type;
	using fraction_type = typename Traits::fraction_type;
	using signed_exponent_type = hamon::make_signed_t<exponent_type>;

	static uint_type constexpr sign_bits = 1;
	static uint_type constexpr fraction_bits = hamon::numeric_limits<T>::digits - 1;
	static uint_type constexpr exponent_bits = static_cast<uint_type>(hamon::bitsof<T>() - 1 - fraction_bits);

	static uint_type constexpr sign_shift = static_cast<uint_type>(hamon::bitsof<T>() - 1);
	static uint_type constexpr exponent_shift = fraction_bits;
	static uint_type constexpr fraction_shift = 0;

	static uint_type constexpr sign_mask     = ((1ULL << sign_bits)     - 1) << sign_shift;
	static uint_type constexpr exponent_mask = ((1ULL << exponent_bits) - 1) << exponent_shift;
	static uint_type constexpr fraction_mask = ((1ULL << fraction_bits) - 1) << fraction_shift;
	static uint_type constexpr fraction_msb_mask = ((1ULL << (fraction_bits - 1)) << fraction_shift);

	static int_type constexpr exponent_bias = hamon::numeric_limits<T>::max_exponent - 1;
	static int_type constexpr exponent_max  = (1ULL << exponent_bits) - 1;
	static int_type constexpr fraction_bias = (1ULL << fraction_bits);

public:
	HAMON_CXX11_CONSTEXPR
	binary(T v) HAMON_NOEXCEPT
		: m_uint_value(hamon::bit_cast<uint_type>(v))
	{}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	uint_type uint() const HAMON_NOEXCEPT
	{
		return m_uint_value;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	sign_type sign() const HAMON_NOEXCEPT
	{
		return static_cast<sign_type>((m_uint_value & sign_mask) >> sign_shift);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	exponent_type exponent() const HAMON_NOEXCEPT
	{
		return static_cast<exponent_type>((m_uint_value & exponent_mask) >> exponent_shift);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	fraction_type fraction() const HAMON_NOEXCEPT
	{
		return static_cast<fraction_type>((m_uint_value & fraction_mask) >> fraction_shift);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	signed_exponent_type unbiased_exponent() const HAMON_NOEXCEPT
	{
		return
			is_normal() ?
				static_cast<signed_exponent_type>(exponent()) - exponent_bias :
			is_subnormal() ?
				1 - exponent_bias :
				static_cast<signed_exponent_type>(exponent());
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	fraction_type unbiased_fraction() const HAMON_NOEXCEPT
	{
		return
			is_normal() ?
				static_cast<fraction_type>(fraction() | fraction_bias) :
				fraction();
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR
	signed_exponent_type normalized_exponent() const HAMON_NOEXCEPT
	{
		if (!is_finite() || is_zero())
		{
			return static_cast<signed_exponent_type>(exponent());
		}
		auto const exp = unbiased_exponent() - signed_exponent_type{fraction_bits};
		auto const frac = unbiased_fraction();
		auto const s = hamon::countr_zero(frac);
		return exp + s;
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR
	fraction_type normalized_fraction() const HAMON_NOEXCEPT
	{
		if (!is_finite() || is_zero())
		{
			return fraction();
		}
		auto const frac = unbiased_fraction();
		auto const s = hamon::countr_zero(frac);
		return frac >> s;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	bool is_zero() const HAMON_NOEXCEPT
	{
		return exponent() == 0 && fraction() == 0;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	bool is_subnormal() const HAMON_NOEXCEPT
	{
		return exponent() == 0 && fraction() != 0;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	bool is_normal() const HAMON_NOEXCEPT
	{
		return exponent() != 0 && exponent() != exponent_max;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	bool is_finite() const HAMON_NOEXCEPT
	{
		return exponent() != exponent_max;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	bool is_infinity() const HAMON_NOEXCEPT
	{
		return exponent() == exponent_max && fraction() == 0;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	bool is_nan() const HAMON_NOEXCEPT
	{
		return exponent() == exponent_max && fraction() != 0;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	bool is_signaling_nan() const HAMON_NOEXCEPT
	{
		return is_nan() &&
#if defined(HAMON_MSVC)
			((m_uint_value & 1) != 0);
#else
			((m_uint_value & fraction_msb_mask) == 0);
#endif
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	bool is_quiet_nan() const HAMON_NOEXCEPT
	{
		return is_nan() && !is_signaling_nan();
	}

private:
	uint_type  m_uint_value;
};

}	// namespace ieee754

}	// namespace hamon

#endif // HAMON_IEEE754_BINARY_HPP
