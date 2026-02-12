/**
 *	@file	binary.hpp
 *
 *	@brief	binary の定義
 */

#ifndef HAMON_IEEE754_BINARY_HPP
#define HAMON_IEEE754_BINARY_HPP

#include <hamon/bit/bit_cast.hpp>
#include <hamon/bit/bit_width.hpp>
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

	using sign_component_type     = hamon::uint8_t;
	using exponent_component_type = hamon::uint32_t;
	using fraction_component_type = hamon::uint32_t;

	using sign_type     = hamon::uint8_t;
	using exponent_type = hamon::int32_t;
	using fraction_type = hamon::uint32_t;
};

template <>
struct binary_traits<double>
{
	using uint_type     = hamon::uint64_t;

	using sign_component_type     = hamon::uint8_t;
	using exponent_component_type = hamon::uint32_t;
	using fraction_component_type = hamon::uint64_t;

	using sign_type     = hamon::uint8_t;
	using exponent_type = hamon::int32_t;
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

	using sign_component_type     = typename Traits::sign_component_type;
	using exponent_component_type = typename Traits::exponent_component_type;
	using fraction_component_type = typename Traits::fraction_component_type;

	using sign_type     = typename Traits::sign_type;
	using exponent_type = typename Traits::exponent_type;
	using fraction_type = typename Traits::fraction_type;

	static int constexpr sign_bits     = 1;
	static int constexpr fraction_bits = hamon::numeric_limits<T>::digits - 1;
	static int constexpr exponent_bits = static_cast<int>(hamon::bitsof<T>() - sign_bits - fraction_bits);

	static int constexpr sign_shift     = fraction_bits + exponent_bits;
	static int constexpr exponent_shift = fraction_bits;
	static int constexpr fraction_shift = 0;

	static uint_type constexpr sign_mask     = ((1ULL << sign_bits)     - 1) << sign_shift;
	static uint_type constexpr exponent_mask = ((1ULL << exponent_bits) - 1) << exponent_shift;
	static uint_type constexpr fraction_mask = ((1ULL << fraction_bits) - 1) << fraction_shift;
	static uint_type constexpr fraction_msb_mask = ((1ULL << (fraction_bits - 1)) << fraction_shift);

	static exponent_component_type constexpr exponent_component_min = 0;
	static exponent_component_type constexpr exponent_component_max = (1ULL << exponent_bits) - 1;

	static exponent_type constexpr exponent_max = hamon::numeric_limits<T>::max_exponent - 1;
	static exponent_type constexpr exponent_min = 1 - exponent_max;

	static exponent_type constexpr exponent_bias = exponent_max;

	static fraction_component_type constexpr fraction_bias = (1ULL << fraction_bits);

private:
	static HAMON_CXX14_CONSTEXPR uint_type
	make_floating_point_value(sign_type sign, exponent_type exponent, fraction_type fraction) HAMON_NOEXCEPT
	{
		if (exponent == exponent_component_max || fraction == 0)
		{
			// NaN or Inf or Zero
		}
		else
		{
			if (exponent < exponent_min)
			{
				// subnormal
				int shift = static_cast<int>(fraction_bits) + exponent - exponent_min;
				exponent = 0;
				fraction <<= shift;
			}
			else
			{
				// normal
				exponent = static_cast<int>(fraction_bits) + exponent + exponent_bias;
				int shift = static_cast<int>(fraction_bits) + 1 - hamon::bit_width(fraction);
				fraction <<= shift;
				exponent -= shift;
			}
		}

		auto s = (static_cast<uint_type>(sign)     << sign_shift)     & sign_mask;
		auto f = (static_cast<uint_type>(fraction) << fraction_shift) & fraction_mask;
		auto e = (static_cast<uint_type>(exponent) << exponent_shift) & exponent_mask;

		return s | f | e;
	}

public:
	/**
	 *	@brief 浮動小数点数からのコンストラクタ
	 */
	explicit HAMON_CXX11_CONSTEXPR
	binary(T v) HAMON_NOEXCEPT
		: m_uint_value(hamon::bit_cast<uint_type>(v))
	{}

	/**
	 *	@brief 整数型からのコンストラクタ
	 */
	explicit HAMON_CXX11_CONSTEXPR
	binary(uint_type v) HAMON_NOEXCEPT
		: m_uint_value(v)
	{}

	/**
	 *	@brief	sign, exponent, fraction からのコンストラクタ
	 *
	 *	sign, exponent, fraction から浮動小数点数を得る
	 *	(-1^sign) * (2^exponent) * fraction と同じ結果になる
	 *
	 *	任意の浮動小数点数をfとしたとき、
	 *	binary b1(f);
	 *	binary b2(b1.sign(), b1.exponent(), b1.fraction());
	 *	とすると、b1 と b2 の値は等しくなる
	 */
	HAMON_CXX11_CONSTEXPR
	binary(sign_type sign, exponent_type exponent, fraction_type fraction) HAMON_NOEXCEPT
		: m_uint_value(make_floating_point_value(sign, exponent, fraction))
	{}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	uint_type to_uint() const HAMON_NOEXCEPT
	{
		return m_uint_value;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	T to_float() const HAMON_NOEXCEPT
	{
		return hamon::bit_cast<T>(m_uint_value);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	sign_component_type sign_component() const HAMON_NOEXCEPT
	{
		return static_cast<sign_component_type>((m_uint_value & sign_mask) >> sign_shift);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	exponent_component_type exponent_component() const HAMON_NOEXCEPT
	{
		return static_cast<exponent_component_type>((m_uint_value & exponent_mask) >> exponent_shift);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	fraction_component_type fraction_component() const HAMON_NOEXCEPT
	{
		return static_cast<fraction_component_type>((m_uint_value & fraction_mask) >> fraction_shift);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	exponent_type unbiased_exponent() const HAMON_NOEXCEPT
	{
		return
			is_normal() ?
				static_cast<exponent_type>(exponent_component()) - exponent_bias :
			is_subnormal() ?
				exponent_min :
				static_cast<exponent_type>(exponent_component());
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	fraction_type unbiased_fraction() const HAMON_NOEXCEPT
	{
		return
			is_normal() ?
				static_cast<fraction_type>(fraction_component() | fraction_bias) :
				fraction_component();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	sign_type sign() const HAMON_NOEXCEPT
	{
		return static_cast<sign_type>(sign_component());
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR
	exponent_type exponent() const HAMON_NOEXCEPT
	{
		if (!is_finite() || is_zero())
		{
			return static_cast<exponent_type>(exponent_component());
		}
		auto const exp = unbiased_exponent() - exponent_type{fraction_bits};
		auto const frac = unbiased_fraction();
		auto const s = hamon::countr_zero(frac);
		return exp + s;
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR
	fraction_type fraction() const HAMON_NOEXCEPT
	{
		if (!is_finite() || is_zero())
		{
			return fraction_component();
		}
		auto const frac = unbiased_fraction();
		auto const s = hamon::countr_zero(frac);
		return frac >> s;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	bool is_zero() const HAMON_NOEXCEPT
	{
		return exponent_component() == 0 && fraction_component() == 0;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	bool is_subnormal() const HAMON_NOEXCEPT
	{
		return exponent_component() == 0 && fraction_component() != 0;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	bool is_normal() const HAMON_NOEXCEPT
	{
		return exponent_component() != 0 && exponent_component() != exponent_component_max;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	bool is_finite() const HAMON_NOEXCEPT
	{
		return exponent_component() != exponent_component_max;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	bool is_infinity() const HAMON_NOEXCEPT
	{
		return exponent_component() == exponent_component_max && fraction_component() == 0;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	bool is_nan() const HAMON_NOEXCEPT
	{
		return exponent_component() == exponent_component_max && fraction_component() != 0;
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
