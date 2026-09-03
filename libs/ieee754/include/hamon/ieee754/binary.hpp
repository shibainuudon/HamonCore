/**
 *	@file	binary.hpp
 *
 *	@brief	binary の定義
 */

#ifndef HAMON_IEEE754_BINARY_HPP
#define HAMON_IEEE754_BINARY_HPP

#include <hamon/ieee754/binary_traits.hpp>
#include <hamon/bit/bit_cast.hpp>
#include <hamon/bit/bit_width.hpp>
#include <hamon/bit/countr_zero.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/make_int_least_n.hpp>
#include <hamon/type_traits/make_uint_least_n.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ieee754
{

template <typename T>
class binary
{
private:
	using Traits = hamon::ieee754::binary_traits<T>;

public:
	static int constexpr sign_bits     = Traits::sign_bits;
	static int constexpr exponent_bits = Traits::exponent_bits;
	static int constexpr fraction_bits = Traits::fraction_bits;
	static int constexpr padding_bits = Traits::padding_bits;

	static int constexpr total_bits = sign_bits + exponent_bits + fraction_bits;

	static int constexpr sign_shift     = fraction_bits + exponent_bits;
	static int constexpr exponent_shift = fraction_bits;
	static int constexpr fraction_shift = 0;

	using float_type = T;
	using uint_type  = hamon::make_uint_least_n_t<sign_bits + exponent_bits + fraction_bits + padding_bits>;

	static_assert(sizeof(float_type) == sizeof(uint_type), "");

	using sign_type     = hamon::make_uint_least_n_t<sign_bits>;
	using exponent_type = hamon::make_int_least_n_t<exponent_bits + 1>;
	using fraction_type = hamon::make_uint_least_n_t<fraction_bits>;

private:
	static uint_type constexpr sign_mask     = ((uint_type(1) << sign_bits)     - 1) << sign_shift;
	static uint_type constexpr exponent_mask = ((uint_type(1) << exponent_bits) - 1) << exponent_shift;
	static uint_type constexpr fraction_mask = ((uint_type(1) << fraction_bits) - 1) << fraction_shift;
	static uint_type constexpr fraction_msb_mask = ((uint_type(1) << (fraction_bits - 1)) << fraction_shift);

//	static uint_type constexpr exponent_component_min = 0;
	static uint_type constexpr exponent_component_max = (uint_type(1) << exponent_bits) - 1;

public:
	static exponent_type constexpr exponent_max = exponent_component_max >> 1;
	static exponent_type constexpr exponent_min = 1 - exponent_max;

	static exponent_type constexpr exponent_bias = exponent_max;
	static uint_type constexpr fraction_bias =
		Traits::has_fraction_implicit_bits ? (uint_type(1) << fraction_bits) : 0;

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
			if (exponent < exponent_min - 1)
			{
				// subnormal
				int shift = fraction_bits + exponent - exponent_min;
				fraction <<= shift;
				exponent = 0;
			}
			else
			{
				// normal
				int shift = fraction_bits + (Traits::has_fraction_implicit_bits ? 1 : 0) - hamon::bit_width(fraction);
				fraction <<= shift;
				exponent = static_cast<exponent_type>(fraction_bits + exponent + exponent_bias - shift);
			}
		}

		auto s = (static_cast<uint_type>(sign)     << sign_shift)     & sign_mask;
		auto f = (static_cast<uint_type>(fraction) << fraction_shift) & fraction_mask;
		auto e = (static_cast<uint_type>(exponent) << exponent_shift) & exponent_mask;

		return s | f | e;
	}

	// bit_castするだけだと、パディングビットがある時に不定の値になる部分があるので対処しないといけない

	template <typename To, typename From>
	HAMON_CXX11_CONSTEXPR To
	safe_bit_cast_impl(From const& from, hamon::true_type) HAMON_NOEXCEPT
	{
		return hamon::bit_cast<To>(from);
	}

	template <typename To, typename From>
	HAMON_CXX11_CONSTEXPR To
	safe_bit_cast_impl(From const& from, hamon::false_type) HAMON_NOEXCEPT
	{
#if defined(HAMON_CLANG)
		// C++標準仕様では、パディングビットを持つ型に対してbit_castを使うとUBになってしまう。
		// (これを修正しようと、C++29に向けて P3969R2 が提案されている)
		// GCCではbit_castをそのまま使っても問題ないが、Clangではconstexprにできなくなってしまう。
		// そこで、一度unsigned char配列にbit_castしてから手動で値をコピーすることで回避する。
		constexpr hamon::size_t N = sizeof(uint_type) - (padding_bits / 8);
		struct alignas(sizeof(uint_type)) S
		{
			unsigned char a[N];
		};
		auto tmp = hamon::bit_cast<S>(from);
		uint_type result = 0;
		for (hamon::size_t i = 0; i < N; ++i)
		{
			result |= static_cast<uint_type>(tmp.a[i]) << (i * 8);
		}
		return result;
#else
		// パディングビット以外の部分でマスクする
		uint_type const mask = (uint_type(1) << (sign_bits + exponent_bits + fraction_bits)) - 1;
		return hamon::bit_cast<To>(from) & mask;
#endif
	}

	template <typename To, typename From>
	HAMON_CXX11_CONSTEXPR To
	safe_bit_cast(From const& from) HAMON_NOEXCEPT
	{
		return safe_bit_cast_impl<To>(from, hamon::bool_constant<padding_bits == 0>{});
	}

public:
	/**
	 *	@brief 浮動小数点数からのコンストラクタ
	 */
	explicit HAMON_CXX11_CONSTEXPR
	binary(float_type v) HAMON_NOEXCEPT
		: m_uint_value(safe_bit_cast<uint_type>(v))
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

	/**
	 *	@brief 整数型での表現を取得
	 */
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	uint_type to_uint() const HAMON_NOEXCEPT
	{
		return m_uint_value;
	}

	/**
	 *	@brief 浮動小数点数型での表現を取得
	 */
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	float_type to_float() const HAMON_NOEXCEPT
	{
		return hamon::bit_cast<float_type>(m_uint_value);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	uint_type sign_component() const HAMON_NOEXCEPT
	{
		return static_cast<uint_type>((m_uint_value & sign_mask) >> sign_shift);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	uint_type exponent_component() const HAMON_NOEXCEPT
	{
		return static_cast<uint_type>((m_uint_value & exponent_mask) >> exponent_shift);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	uint_type fraction_component() const HAMON_NOEXCEPT
	{
		return static_cast<uint_type>((m_uint_value & fraction_mask) >> fraction_shift);
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
				static_cast<fraction_type>(fraction_component());
	}

	/**
	 *	@brief 符号を取得
	 */
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	sign_type sign() const HAMON_NOEXCEPT
	{
		return static_cast<sign_type>(sign_component());
	}

	/**
	 *	@brief 指数を取得
	 */
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
		return static_cast<exponent_type>(exp + s);
	}

	/**
	 *	@brief 仮数を取得
	 */
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR
	fraction_type fraction() const HAMON_NOEXCEPT
	{
		if (!is_finite() || is_zero())
		{
			return static_cast<fraction_type>(fraction_component());
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
