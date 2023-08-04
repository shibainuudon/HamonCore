﻿/**
 *	@file	fixed_bigint.hpp
 *
 *	@brief	fixed_bigint クラスの定義
 */

#ifndef HAMON_BIGINT_FIXED_BIGINT_HPP
#define HAMON_BIGINT_FIXED_BIGINT_HPP

#include <hamon/bigint/bigint_algo/from_uint.hpp>
#include <hamon/bigint/bigint_algo/from_chars.hpp>
#include <hamon/bigint/bigint_algo/to_uint.hpp>
#include <hamon/bigint/bigint_algo/to_chars.hpp>
#include <hamon/bigint/bigint_algo/to_chars_length.hpp>
#include <hamon/bigint/bigint_algo/add.hpp>
#include <hamon/bigint/bigint_algo/sub.hpp>
#include <hamon/bigint/bigint_algo/multiply.hpp>
#include <hamon/bigint/bigint_algo/div_mod.hpp>
#include <hamon/bigint/bigint_algo/negate.hpp>
#include <hamon/bigint/bigint_algo/bit_and.hpp>
#include <hamon/bigint/bigint_algo/bit_or.hpp>
#include <hamon/bigint/bigint_algo/bit_xor.hpp>
#include <hamon/bigint/bigint_algo/bit_not.hpp>
#include <hamon/bigint/bigint_algo/bit_shift_left.hpp>
#include <hamon/bigint/bigint_algo/bit_shift_right.hpp>
#include <hamon/bigint/bigint_algo/compare.hpp>
#include <hamon/bigint/bigint_algo/is_zero.hpp>
#include <hamon/bigint/bigint_algo/signbit.hpp>
#include <hamon/bigint/detail/abs_unsigned.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/compare/strong_ordering.hpp>
#include <hamon/memory/to_address.hpp>
#include <hamon/type_traits/make_unsigned.hpp>
#include <hamon/string_view.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/config.hpp>
#include <vector>
#include <istream>
#include <ostream>

namespace hamon
{

template <hamon::size_t Bits, bool Signed>
class fixed_bigint;

// 固定ビット・符号付き
using int128_t  = hamon::fixed_bigint< 128, true>;
using int256_t  = hamon::fixed_bigint< 256, true>;
using int512_t  = hamon::fixed_bigint< 512, true>;
using int1024_t = hamon::fixed_bigint<1024, true>;
using int2048_t = hamon::fixed_bigint<2048, true>;

// 固定ビット・符号なし
using uint128_t  = hamon::fixed_bigint< 128, false>;
using uint256_t  = hamon::fixed_bigint< 256, false>;
using uint512_t  = hamon::fixed_bigint< 512, false>;
using uint1024_t = hamon::fixed_bigint<1024, false>;
using uint2048_t = hamon::fixed_bigint<2048, false>;

template <hamon::size_t Bits, bool Signed>
class fixed_bigint
{
private:
	using element_type = hamon::uint32_t;
	static const hamon::size_t N = (Bits / 8) / sizeof(element_type);
	using vector_type = hamon::array<element_type, N>;

public:
	HAMON_CXX14_CONSTEXPR
	fixed_bigint() HAMON_NOEXCEPT
		: m_data{}
	{}

	template <HAMON_CONSTRAINED_PARAM(hamon::integral, Integral)>
	HAMON_CXX14_CONSTEXPR
	fixed_bigint(Integral n) HAMON_NOEXCEPT
		: m_data{}
	{
		bigint_algo::from_uint(abs_unsigned(n), m_data);
		if (n < 0)
		{
			bigint_algo::negate(m_data);
		}
	}

	explicit HAMON_CXX14_CONSTEXPR
	fixed_bigint(hamon::string_view str)
		: m_data{}
	{
		int sign = 1;
		if (str.size() >= 1)
		{
			switch (str[0])
			{
			case '-':
				sign = -1;
				str = str.substr(1);
				break;
			case '+':
				str = str.substr(1);
				break;
			}
		}

		int base = 10;
		if (str.size() >= 2)
		{
			if (str[0] == '0')
			{
				switch (str[1])
				{
				case 'b':	// 0b
				case 'B':	// 0B
					base = 2;
					str = str.substr(2);
					break;
				case 'x':	// 0x
				case 'X':	// 0X
					base = 16;
					str = str.substr(2);
					break;
				default:	// 0
					base = 8;
					str = str.substr(1);
					break;
				}
			}
		}

		bigint_algo::from_chars(str.begin(), str.end(), m_data, base);
		if (sign < 0)
		{
			bigint_algo::negate(m_data);
		}
	}

private:
	HAMON_CXX14_CONSTEXPR
	fixed_bigint(vector_type const& data) HAMON_NOEXCEPT
		: m_data{data}
	{}

public:
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR fixed_bigint
	operator+() const HAMON_NOEXCEPT
	{
		return *this;
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR fixed_bigint
	operator-() const HAMON_NOEXCEPT
	{
		return {bigint_algo::negate(m_data)};
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR fixed_bigint
	operator~() const HAMON_NOEXCEPT
	{
		return {bigint_algo::bit_not(m_data)};
	}

	HAMON_CXX14_CONSTEXPR fixed_bigint&
	operator+=(fixed_bigint const& rhs) HAMON_NOEXCEPT
	{
		bigint_algo::add(m_data, rhs.m_data);
		return *this;
	}

	HAMON_CXX14_CONSTEXPR fixed_bigint&
	operator-=(fixed_bigint const& rhs) HAMON_NOEXCEPT
	{
		bigint_algo::sub(m_data, rhs.m_data);
		return *this;
	}

	HAMON_CXX14_CONSTEXPR fixed_bigint&
	operator*=(fixed_bigint const& rhs) HAMON_NOEXCEPT
	{
		m_data = bigint_algo::multiply(m_data, rhs.m_data);
		return *this;
	}

	HAMON_CXX14_CONSTEXPR fixed_bigint&
	operator/=(fixed_bigint const& rhs) HAMON_NOEXCEPT
	{
		m_data = divide(m_data, rhs.m_data);
		return *this;
	}

	HAMON_CXX14_CONSTEXPR fixed_bigint&
	operator%=(fixed_bigint const& rhs) HAMON_NOEXCEPT
	{
		m_data = modulus(m_data, rhs.m_data);
		return *this;
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR fixed_bigint
	operator+(fixed_bigint const& rhs) const HAMON_NOEXCEPT
	{
		return fixed_bigint{*this} += rhs;
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR fixed_bigint
	operator-(fixed_bigint const& rhs) const HAMON_NOEXCEPT
	{
		return fixed_bigint{*this} -= rhs;
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR fixed_bigint
	operator*(fixed_bigint const& rhs) const HAMON_NOEXCEPT
	{
		return fixed_bigint{*this} *= rhs;
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR fixed_bigint
	operator/(fixed_bigint const& rhs) const HAMON_NOEXCEPT
	{
		return fixed_bigint{*this} /= rhs;
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR fixed_bigint
	operator%(fixed_bigint const& rhs) const HAMON_NOEXCEPT
	{
		return fixed_bigint{*this} %= rhs;
	}

	HAMON_CXX14_CONSTEXPR fixed_bigint&
	operator&=(fixed_bigint const& rhs) HAMON_NOEXCEPT
	{
		bigint_algo::bit_and(m_data, rhs.m_data);
		return *this;
	}

	HAMON_CXX14_CONSTEXPR fixed_bigint&
	operator|=(fixed_bigint const& rhs) HAMON_NOEXCEPT
	{
		bigint_algo::bit_or(m_data, rhs.m_data);
		return *this;
	}

	HAMON_CXX14_CONSTEXPR fixed_bigint&
	operator^=(fixed_bigint const& rhs) HAMON_NOEXCEPT
	{
		bigint_algo::bit_xor(m_data, rhs.m_data);
		return *this;
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR fixed_bigint
	operator&(fixed_bigint const& rhs) const HAMON_NOEXCEPT
	{
		return fixed_bigint{*this} &= rhs;
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR fixed_bigint
	operator|(fixed_bigint const& rhs) const HAMON_NOEXCEPT
	{
		return fixed_bigint{*this} |= rhs;
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR fixed_bigint
	operator^(fixed_bigint const& rhs) const HAMON_NOEXCEPT
	{
		return fixed_bigint{*this} ^= rhs;
	}

	HAMON_CXX14_CONSTEXPR fixed_bigint&
	operator<<=(hamon::size_t pos) HAMON_NOEXCEPT
	{
		bigint_algo::bit_shift_left(m_data, pos);
		return *this;
	}

	HAMON_CXX14_CONSTEXPR fixed_bigint&
	operator>>=(hamon::size_t pos) HAMON_NOEXCEPT
	{
		bigint_algo::bit_shift_right(m_data, pos);
		return *this;
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR fixed_bigint
	operator<<(hamon::size_t pos) const HAMON_NOEXCEPT
	{
		return fixed_bigint{*this} <<= pos;
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR fixed_bigint
	operator>>(hamon::size_t pos) const HAMON_NOEXCEPT
	{
		return fixed_bigint{*this} >>= pos;
	}

	HAMON_CXX14_CONSTEXPR fixed_bigint&
	operator++() HAMON_NOEXCEPT
	{
		return *this += 1;
	}

	HAMON_CXX14_CONSTEXPR fixed_bigint&
	operator--() HAMON_NOEXCEPT
	{
		return *this -= 1;
	}

	HAMON_CXX14_CONSTEXPR fixed_bigint
	operator++(int) HAMON_NOEXCEPT
	{
		auto tmp = *this;
		++(*this);
		return tmp;
	}

	HAMON_CXX14_CONSTEXPR fixed_bigint
	operator--(int) HAMON_NOEXCEPT
	{
		auto tmp = *this;
		--(*this);
		return tmp;
	}

	//HAMON_NODISCARD unsigned long to_ulong() const;
	//HAMON_NODISCARD unsigned long long to_ullong() const;

	template <
		typename CharT = char,
		typename Traits = std::char_traits<CharT>,
		typename Allocator = std::allocator<CharT>>
	HAMON_NODISCARD std::basic_string<CharT, Traits, Allocator>
	to_string() const
	{
		int base = 10;
		hamon::size_t len =
			bigint_algo::to_chars_length(m_data, base) +
			2;
		std::basic_string<CharT, Traits, Allocator> result;
		result.resize(len);
		auto first = hamon::to_address(result.begin());
		auto last = first + len;
		auto p = first;
		if (Signed)
		{
			if (bigint_algo::signbit(m_data))
			{
				*p++ = '-';
			}
		}
		auto ret = bigint_algo::to_chars(p, last, abs(m_data), base);
		result.resize(static_cast<hamon::size_t>(ret.ptr - first));
		return result;
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR int
	compare(fixed_bigint const& rhs) const HAMON_NOEXCEPT
	{
		if (Signed)
		{
			auto lsign = bigint_algo::signbit(m_data);
			auto rsign = bigint_algo::signbit(rhs.m_data);
			if (lsign != rsign)
			{
				return lsign ? -1 : 1;
			}
		}
		return bigint_algo::compare(m_data, rhs.m_data);
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR bool
	operator==(fixed_bigint const& rhs) const HAMON_NOEXCEPT
	{
		return this->compare(rhs) == 0;
	}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR hamon::strong_ordering
	operator<=>(fixed_bigint const& rhs) const HAMON_NOEXCEPT
	{
		return this->compare(rhs) <=> 0;
	}
#else
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR bool
	operator!=(fixed_bigint const& rhs) const HAMON_NOEXCEPT
	{
		return !(*this == rhs);
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR bool
	operator<(fixed_bigint const& rhs) const HAMON_NOEXCEPT
	{
		return this->compare(rhs) < 0;
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR bool
	operator>(fixed_bigint const& rhs) const HAMON_NOEXCEPT
	{
		return rhs < *this;
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR bool
	operator<=(fixed_bigint const& rhs) const HAMON_NOEXCEPT
	{
		return !(*this > rhs);
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR bool
	operator>=(fixed_bigint const& rhs) const HAMON_NOEXCEPT
	{
		return !(*this < rhs);
	}
#endif

private:
	static HAMON_CXX14_CONSTEXPR vector_type
	abs(vector_type const& v) HAMON_NOEXCEPT
	{
		if (Signed)
		{
			return bigint_algo::signbit(v) ? bigint_algo::negate(v) : v;
		}
		else
		{
			return v;
		}
	}

	static HAMON_CXX14_CONSTEXPR vector_type
	divide(vector_type const& lhs, vector_type const& rhs) HAMON_NOEXCEPT
	{
		if (Signed)
		{
			auto ret = bigint_algo::div_mod(abs(lhs), abs(rhs));
			if (bigint_algo::signbit(lhs) !=
				bigint_algo::signbit(rhs))
			{
				bigint_algo::negate(ret.quo);
			}
			return ret.quo;
		}
		else
		{
			auto ret = bigint_algo::div_mod(lhs, rhs);
			return ret.quo;
		}
	}

	static HAMON_CXX14_CONSTEXPR vector_type
	modulus(vector_type const& lhs, vector_type const& rhs) HAMON_NOEXCEPT
	{
		if (Signed)
		{
			auto ret = bigint_algo::div_mod(abs(lhs), abs(rhs));
			if (bigint_algo::signbit(lhs))
			{
				bigint_algo::negate(ret.rem);
			}
			return ret.rem;
		}
		else
		{
			auto ret = bigint_algo::div_mod(lhs, rhs);
			return ret.rem;
		}
	}

private:
	vector_type	m_data;
};

//template <typename CharT, typename Traits>
//inline std::basic_istream<CharT, Traits>&
//operator>>(std::basic_istream<CharT, Traits>& is, fixed_bigint& x);

template <typename CharT, typename Traits, hamon::size_t B, bool S>
inline std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, fixed_bigint<B, S> const& x)
{
	return os << x.to_string();
}

}	// namespace hamon

#include <functional>

namespace std
{

template <hamon::size_t B, bool S>
struct hash<hamon::fixed_bigint<B, S>>
{
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR
	hamon::size_t operator()(hamon::fixed_bigint<B, S> const& x) const HAMON_NOEXCEPT;
};

}	// namespace std

#endif // HAMON_BIGINT_FIXED_BIGINT_HPP
