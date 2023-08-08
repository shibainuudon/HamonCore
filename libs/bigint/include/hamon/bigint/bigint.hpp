/**
 *	@file	bigint.hpp
 *
 *	@brief	bigint クラスの定義
 */

#ifndef HAMON_BIGINT_BIGINT_HPP
#define HAMON_BIGINT_BIGINT_HPP

#include <hamon/bigint/bigint_algo/from_uint.hpp>
#include <hamon/bigint/bigint_algo/from_chars.hpp>
#include <hamon/bigint/bigint_algo/to_uint.hpp>
#include <hamon/bigint/bigint_algo/to_chars.hpp>
#include <hamon/bigint/bigint_algo/to_chars_length.hpp>
#include <hamon/bigint/bigint_algo/add.hpp>
#include <hamon/bigint/bigint_algo/sub.hpp>
#include <hamon/bigint/bigint_algo/multiply.hpp>
#include <hamon/bigint/bigint_algo/div_mod.hpp>
#include <hamon/bigint/bigint_algo/bit_and.hpp>
#include <hamon/bigint/bigint_algo/bit_or.hpp>
#include <hamon/bigint/bigint_algo/bit_xor.hpp>
#include <hamon/bigint/bigint_algo/bit_shift_left.hpp>
#include <hamon/bigint/bigint_algo/bit_shift_right.hpp>
#include <hamon/bigint/bigint_algo/compare.hpp>
#include <hamon/bigint/bigint_algo/is_zero.hpp>
#include <hamon/bigint/detail/abs_unsigned.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/compare/strong_ordering.hpp>
#include <hamon/memory/to_address.hpp>
#include <hamon/string_view.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/config.hpp>
#include <vector>
#include <istream>
#include <ostream>

namespace hamon
{

class bigint;

hamon::to_chars_result
to_chars(char* first, char* last, bigint const& value, int base = 10);

class bigint
{
private:
	using MagnitudeType = std::vector<hamon::uint32_t>;

public:
	bigint() HAMON_NOEXCEPT
		: m_sign(1)
		, m_magnitude{0}
	{}

	template <HAMON_CONSTRAINED_PARAM(hamon::integral, Integral)>
	bigint(Integral n) HAMON_NOEXCEPT
		: m_sign(n < 0 ? -1 : 1)
	{
		bigint_algo::from_uint(hamon::abs_unsigned(n), m_magnitude);
	}

	explicit bigint(hamon::string_view str)
		: m_sign(1)
		, m_magnitude{0}
	{
		if (str.size() >= 1)
		{
			switch (str[0])
			{
			case '-':
				m_sign = -1;
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

		bigint_algo::from_chars(str.begin(), str.end(), m_magnitude, base);

		if (bigint_algo::is_zero(m_magnitude))
		{
			m_sign = 1;
		}
	}

private:
	bigint(int sign, MagnitudeType const& mag) HAMON_NOEXCEPT
		: m_sign(sign)
		, m_magnitude{mag}
	{}

public:
	HAMON_NODISCARD bigint operator+() const HAMON_NOEXCEPT
	{
		return *this;
	}

	HAMON_NODISCARD bigint operator-() const HAMON_NOEXCEPT
	{
		if (bigint_algo::is_zero(m_magnitude))
		{
			return *this;
		}
		return {-m_sign, m_magnitude};
	}

	HAMON_NODISCARD bigint operator~() const HAMON_NOEXCEPT
	{
		return -(bigint{*this} += 1);
	}

private:
	void add(bigint const& rhs) HAMON_NOEXCEPT
	{
		bigint_algo::add(m_magnitude, rhs.m_magnitude);
	}

	void sub(bigint const& rhs) HAMON_NOEXCEPT
	{
		auto const c = bigint_algo::compare(m_magnitude, rhs.m_magnitude);

		if (c == 0)
		{
			m_magnitude = {0};
			m_sign = 1;
		}
		else if (c > 0)
		{
			// lhs = lhs - rhs
			bigint_algo::sub(m_magnitude, rhs.m_magnitude);
		}
		else if (c < 0)
		{
			// lhs = rhs - lhs
			MagnitudeType tmp(rhs.m_magnitude);
			bigint_algo::sub(tmp, m_magnitude);
			m_magnitude = tmp;
			m_sign = -m_sign;
		}
	}
	
public:
	bigint& operator+=(bigint const& rhs) HAMON_NOEXCEPT
	{
		if (m_sign != rhs.m_sign)
		{
			this->sub(rhs);
		}
		else
		{
			this->add(rhs);
		}

		return *this;
	}

	bigint& operator-=(bigint const& rhs) HAMON_NOEXCEPT
	{
		if (m_sign != rhs.m_sign)
		{
			this->add(rhs);
		}
		else
		{
			this->sub(rhs);
		}

		return *this;
	}

	bigint& operator*=(bigint const& rhs) HAMON_NOEXCEPT
	{
		m_magnitude = bigint_algo::multiply(m_magnitude, rhs.m_magnitude);
		if (bigint_algo::is_zero(m_magnitude))
		{
			m_sign = 1;
		}
		else
		{
			m_sign *= rhs.m_sign;
		}
		return *this;
	}

	bigint& operator/=(bigint const& rhs) HAMON_NOEXCEPT
	{
		auto ret = bigint_algo::div_mod(m_magnitude, rhs.m_magnitude);
		m_magnitude = ret.quo;
		if (bigint_algo::is_zero(m_magnitude))
		{
			m_sign = 1;
		}
		else
		{
			m_sign /= rhs.m_sign;
		}
		return *this;
	}

	bigint& operator%=(bigint const& rhs) HAMON_NOEXCEPT
	{
		auto ret = bigint_algo::div_mod(m_magnitude, rhs.m_magnitude);
		m_magnitude = ret.rem;
		if (bigint_algo::is_zero(m_magnitude))
		{
			m_sign = 1;
		}
		return *this;
	}

	bigint& operator&=(bigint const& rhs) HAMON_NOEXCEPT
	{
		bigint_algo::bit_and(m_magnitude, rhs.m_magnitude);
		return *this;
	}

	bigint& operator|=(bigint const& rhs) HAMON_NOEXCEPT
	{
		bigint_algo::bit_or(m_magnitude, rhs.m_magnitude);
		return *this;
	}

	bigint& operator^=(bigint const& rhs) HAMON_NOEXCEPT
	{
		bigint_algo::bit_xor(m_magnitude, rhs.m_magnitude);
		return *this;
	}

	bigint& operator<<=(hamon::size_t pos) HAMON_NOEXCEPT
	{
		bigint_algo::bit_shift_left(m_magnitude, pos);
		return *this;
	}

	bigint& operator>>=(hamon::size_t pos) HAMON_NOEXCEPT
	{
		bigint_algo::bit_shift_right(m_magnitude, pos);
		return *this;
	}

	bigint& operator++() HAMON_NOEXCEPT
	{
		return *this += 1;
	}

	bigint& operator--() HAMON_NOEXCEPT
	{
		return *this -= 1;
	}

	bigint operator++(int) HAMON_NOEXCEPT
	{
		auto tmp = *this;
		++(*this);
		return tmp;
	}

	bigint operator--(int) HAMON_NOEXCEPT
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
			bigint_algo::to_chars_length(m_magnitude, base) +
			2;
		std::basic_string<CharT, Traits, Allocator> result;
		result.resize(len);
		auto first = hamon::to_address(result.begin());
		auto last = first + len;
		auto p = first;
		if (m_sign < 0)
		{
			*p++ = '-';
		}
		auto ret = bigint_algo::to_chars(p, last, m_magnitude, base);
		result.resize(static_cast<hamon::size_t>(ret.ptr - first));
		return result;
	}

	HAMON_NODISCARD int compare(bigint const& rhs) const HAMON_NOEXCEPT
	{
		if (m_sign != rhs.m_sign)
		{
			return m_sign;
		}

		return bigint_algo::compare(m_magnitude, rhs.m_magnitude) * m_sign;
	}

private:
	int				m_sign = 1;	// m_magnitude >= 0 なら 1、m_magnitude < 0 なら -1
	MagnitudeType	m_magnitude;

private:
	friend hamon::to_chars_result
	to_chars(char* first, char* last, bigint const& value, int base);
};

HAMON_NODISCARD inline bigint
operator+(bigint const& lhs, bigint const& rhs) HAMON_NOEXCEPT
{
	return bigint(lhs) += rhs;
}

HAMON_NODISCARD inline bigint
operator-(bigint const& lhs, bigint const& rhs) HAMON_NOEXCEPT
{
	return bigint(lhs) -= rhs;
}

HAMON_NODISCARD inline bigint
operator*(bigint const& lhs, bigint const& rhs) HAMON_NOEXCEPT
{
	return bigint(lhs) *= rhs;
}

HAMON_NODISCARD inline bigint
operator/(bigint const& lhs, bigint const& rhs) HAMON_NOEXCEPT
{
	return bigint(lhs) /= rhs;
}

HAMON_NODISCARD inline bigint
operator%(bigint const& lhs, bigint const& rhs) HAMON_NOEXCEPT
{
	return bigint(lhs) %= rhs;
}

HAMON_NODISCARD inline bigint
operator&(bigint const& lhs, bigint const& rhs) HAMON_NOEXCEPT
{
	return bigint(lhs) &= rhs;
}

HAMON_NODISCARD inline bigint
operator|(bigint const& lhs, bigint const& rhs) HAMON_NOEXCEPT
{
	return bigint(lhs) |= rhs;
}

HAMON_NODISCARD inline bigint
operator^(bigint const& lhs, bigint const& rhs) HAMON_NOEXCEPT
{
	return bigint(lhs) ^= rhs;
}

HAMON_NODISCARD inline bigint
operator<<(bigint const& lhs, hamon::size_t pos) HAMON_NOEXCEPT
{
	return bigint(lhs) <<= pos;
}

HAMON_NODISCARD inline bigint
operator>>(bigint const& lhs, hamon::size_t pos) HAMON_NOEXCEPT
{
	return bigint(lhs) >>= pos;
}

HAMON_NODISCARD inline bool
operator==(bigint const& lhs, bigint const& rhs) HAMON_NOEXCEPT
{
	return lhs.compare(rhs) == 0;
}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
HAMON_NODISCARD inline hamon::strong_ordering
operator<=>(bigint const& lhs, bigint const& rhs) HAMON_NOEXCEPT
{
	return lhs.compare(rhs) <=> 0;
}
#else
HAMON_NODISCARD inline bool
operator!=(bigint const& lhs, bigint const& rhs) HAMON_NOEXCEPT
{
	return !(lhs == rhs);
}

HAMON_NODISCARD inline bool
operator<(bigint const& lhs, bigint const& rhs) HAMON_NOEXCEPT
{
	return lhs.compare(rhs) < 0;
}

HAMON_NODISCARD inline bool
operator>(bigint const& lhs, bigint const& rhs) HAMON_NOEXCEPT
{
	return rhs < lhs;
}

HAMON_NODISCARD inline bool
operator<=(bigint const& lhs, bigint const& rhs) HAMON_NOEXCEPT
{
	return !(lhs > rhs);
}

HAMON_NODISCARD inline bool
operator>=(bigint const& lhs, bigint const& rhs) HAMON_NOEXCEPT
{
	return !(lhs < rhs);
}
#endif

inline hamon::to_chars_result
to_chars(char* first, char* last, bigint const& value, int base)
{
	if (value.m_sign < 0 && first != last)
	{
		*first++ = '-';
	}
	return bigint_algo::to_chars(first, last, value.m_magnitude, base);
}

//template <typename CharT, typename Traits>
//inline std::basic_istream<CharT, Traits>&
//operator>>(std::basic_istream<CharT, Traits>& is, bigint& x);

template <typename CharT, typename Traits>
inline std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, bigint const& x)
{
	return os << x.to_string();
}

}	// namespace hamon

#include <functional>

namespace std
{

template <>
struct hash<hamon::bigint>
{
	HAMON_NODISCARD
	hamon::size_t operator()(hamon::bigint const& x) const HAMON_NOEXCEPT;
};

}	// namespace std

#endif // HAMON_BIGINT_BIGINT_HPP
