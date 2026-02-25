/**
 *	@file	basic_bigint.hpp
 *
 *	@brief	basic_bigint クラスの定義
 */

#ifndef HAMON_BIGINT_BASIC_BIGINT_HPP
#define HAMON_BIGINT_BASIC_BIGINT_HPP

#include <hamon/bigint/basic_bigint_fwd.hpp>
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
#include <hamon/bigint/bigint_algo/bit_width.hpp>
#include <hamon/bigint/bigint_algo/compare.hpp>
#include <hamon/bigint/bigint_algo/countl_zero.hpp>
#include <hamon/bigint/bigint_algo/countr_zero.hpp>
#include <hamon/bigint/bigint_algo/is_zero.hpp>
#include <hamon/bigint/bigint_algo/detail/move.hpp>
#include <hamon/bigint/bigint_algo/detail/copy.hpp>
#include <hamon/bigint/detail/abs_unsigned.hpp>
#include <hamon/bigint/detail/negate_unsigned.hpp>
#include <hamon/algorithm/max.hpp>
#include <hamon/array.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/compare/strong_ordering.hpp>
#include <hamon/memory/to_address.hpp>
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/string_view.hpp>
#include <hamon/string.hpp>
#include <hamon/type_traits/is_integral.hpp>
#include <hamon/type_traits/is_unsigned.hpp>
#include <hamon/type_traits/make_unsigned.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/config.hpp>
#include <hamon/assert.hpp>
#include <istream>
#include <ostream>

namespace hamon
{

namespace detail
{

struct bigint_access;

}	// namespace detail

template <typename VectorType>
class basic_bigint
{
private:
	friend hamon::detail::bigint_access;

	using sign_type = int;
	using vector_type = VectorType;
	using element_type = hamon::ranges::range_value_t<VectorType>;

	static_assert(hamon::is_integral<element_type>::value, "");
	static_assert(hamon::is_unsigned<element_type>::value, "");

private:
	template <HAMON_CONSTRAINED_PARAM(hamon::integral, Integral)>
	static HAMON_CXX11_CONSTEXPR sign_type
	sign(Integral n) HAMON_NOEXCEPT
	{
		return n < 0 ? -1 : 1;
	}

	HAMON_CXX14_CONSTEXPR
	basic_bigint(sign_type sign, vector_type const& mag) HAMON_NOEXCEPT
		: m_sign(sign)
		, m_magnitude{mag}
	{}

public:
	HAMON_CXX14_CONSTEXPR
	basic_bigint() HAMON_NOEXCEPT
		: m_sign(1)
		, m_magnitude{0}
	{}

	HAMON_CXX14_CONSTEXPR
	basic_bigint(basic_bigint const& rhs)
		: m_sign(rhs.m_sign)
	{
		bigint_algo::detail::copy(m_magnitude, rhs.m_magnitude);
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::integral, Integral)>
	HAMON_CXX14_CONSTEXPR
	basic_bigint(Integral n) HAMON_NOEXCEPT
		: m_sign(sign(n))
	{
		bigint_algo::from_uint(hamon::abs_unsigned(n), m_magnitude);
	}

	explicit HAMON_CXX14_CONSTEXPR
	basic_bigint(hamon::string_view str)
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

		bigint_algo::from_chars(str.data(), str.data() + str.size(), m_magnitude, base);

		if (bigint_algo::is_zero(m_magnitude))
		{
			m_sign = 1;
		}
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR basic_bigint
	operator+() const HAMON_NOEXCEPT
	{
		return *this;
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR basic_bigint
	operator-() const HAMON_NOEXCEPT
	{
		if (bigint_algo::is_zero(m_magnitude))
		{
			return *this;
		}
		return {-m_sign, m_magnitude};
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR basic_bigint
	operator~() const HAMON_NOEXCEPT
	{
		return -(basic_bigint{*this} += 1);
	}

private:
	template <typename VectorType2>
	HAMON_CXX14_CONSTEXPR void
	add(VectorType2 const& rhs) HAMON_NOEXCEPT
	{
		bigint_algo::add(m_magnitude, rhs);
	}

	template <typename VectorType2>
	HAMON_CXX14_CONSTEXPR void
	sub(VectorType2 const& rhs) HAMON_NOEXCEPT
	{
		auto const c = bigint_algo::compare(m_magnitude, rhs);

		if (c == 0)
		{
			m_magnitude = {0};
			m_sign = 1;
		}
		else if (c > 0)
		{
			// lhs = lhs - rhs
			bigint_algo::sub(m_magnitude, rhs);
		}
		else if (c < 0)
		{
			// lhs = rhs - lhs
			vector_type tmp{};
			bigint_algo::sub(tmp, rhs, m_magnitude);
			m_magnitude = tmp;
			m_sign = -m_sign;
		}
	}
	
public:
	HAMON_CXX14_CONSTEXPR basic_bigint&
	operator+=(basic_bigint const& rhs) HAMON_NOEXCEPT
	{
		if (m_sign == rhs.m_sign)
		{
			this->add(rhs.m_magnitude);
		}
		else
		{
			this->sub(rhs.m_magnitude);
		}

		return *this;
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::integral, Integral)>
	HAMON_CXX14_CONSTEXPR basic_bigint&
	operator+=(Integral rhs) HAMON_NOEXCEPT
	{
		constexpr auto N = hamon::max(hamon::size_t{1}, sizeof(Integral) / sizeof(element_type));
		hamon::array<element_type, N> tmp{};
		bigint_algo::from_uint(hamon::abs_unsigned(rhs), tmp);

		if (m_sign == sign(rhs))
		{
			this->add(tmp);
		}
		else
		{
			this->sub(tmp);
		}

		return *this;
	}

	HAMON_CXX14_CONSTEXPR basic_bigint&
	operator-=(basic_bigint const& rhs) HAMON_NOEXCEPT
	{
		if (m_sign == rhs.m_sign)
		{
			this->sub(rhs.m_magnitude);
		}
		else
		{
			this->add(rhs.m_magnitude);
		}

		return *this;
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::integral, Integral)>
	HAMON_CXX14_CONSTEXPR basic_bigint&
	operator-=(Integral rhs) HAMON_NOEXCEPT
	{
		constexpr auto N = hamon::max(hamon::size_t{1}, sizeof(Integral) / sizeof(element_type));
		hamon::array<element_type, N> tmp{};
		bigint_algo::from_uint(hamon::abs_unsigned(rhs), tmp);

		if (m_sign == sign(rhs))
		{
			this->sub(tmp);
		}
		else
		{
			this->add(tmp);
		}

		return *this;
	}

	HAMON_CXX14_CONSTEXPR basic_bigint&
	operator*=(basic_bigint const& rhs) HAMON_NOEXCEPT
	{
		vector_type tmp;
		bigint_algo::multiply(tmp, m_magnitude, rhs.m_magnitude);
		bigint_algo::detail::move(m_magnitude, tmp);
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

	HAMON_CXX14_CONSTEXPR basic_bigint&
	operator/=(basic_bigint const& rhs) HAMON_NOEXCEPT
	{
		vector_type quo;
		vector_type rem;
		bigint_algo::div_mod(quo, rem, m_magnitude, rhs.m_magnitude);
		bigint_algo::detail::move(m_magnitude, quo);
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

	HAMON_CXX14_CONSTEXPR basic_bigint&
	operator%=(basic_bigint const& rhs) HAMON_NOEXCEPT
	{
		vector_type quo;
		vector_type rem;
		bigint_algo::div_mod(quo, rem, m_magnitude, rhs.m_magnitude);
		bigint_algo::detail::move(m_magnitude, rem);
		if (bigint_algo::is_zero(m_magnitude))
		{
			m_sign = 1;
		}
		return *this;
	}

	HAMON_CXX14_CONSTEXPR basic_bigint&
	operator&=(basic_bigint const& rhs) HAMON_NOEXCEPT
	{
		bigint_algo::bit_and(m_magnitude, rhs.m_magnitude);
		return *this;
	}

	HAMON_CXX14_CONSTEXPR basic_bigint&
	operator|=(basic_bigint const& rhs) HAMON_NOEXCEPT
	{
		bigint_algo::bit_or(m_magnitude, rhs.m_magnitude);
		return *this;
	}

	HAMON_CXX14_CONSTEXPR basic_bigint&
	operator^=(basic_bigint const& rhs) HAMON_NOEXCEPT
	{
		bigint_algo::bit_xor(m_magnitude, rhs.m_magnitude);
		return *this;
	}

	HAMON_CXX14_CONSTEXPR basic_bigint&
	operator<<=(hamon::size_t pos) HAMON_NOEXCEPT
	{
		bigint_algo::bit_shift_left(m_magnitude, pos);
		return *this;
	}

	HAMON_CXX14_CONSTEXPR basic_bigint&
	operator>>=(hamon::size_t pos) HAMON_NOEXCEPT
	{
		bigint_algo::bit_shift_right(m_magnitude, pos);
		return *this;
	}

	HAMON_CXX14_CONSTEXPR basic_bigint&
	operator++() HAMON_NOEXCEPT
	{
		return *this += element_type{1};
	}

	HAMON_CXX14_CONSTEXPR basic_bigint&
	operator--() HAMON_NOEXCEPT
	{
		return *this -= element_type{1};
	}

	HAMON_CXX14_CONSTEXPR basic_bigint
	operator++(int) HAMON_NOEXCEPT
	{
		auto tmp = *this;
		++(*this);
		return tmp;
	}

	HAMON_CXX14_CONSTEXPR basic_bigint
	operator--(int) HAMON_NOEXCEPT
	{
		auto tmp = *this;
		--(*this);
		return tmp;
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::integral, Integral)>
	explicit HAMON_CXX14_CONSTEXPR operator Integral() const HAMON_NOEXCEPT
	{
		using UT = hamon::make_unsigned_t<Integral>;
		UT result{};
		bigint_algo::to_uint(result, m_magnitude);
		return static_cast<Integral>(m_sign < 0 ? negate_unsigned(result) : result);
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR int
	compare(basic_bigint const& rhs) const HAMON_NOEXCEPT
	{
		if (m_sign != rhs.m_sign)
		{
			return m_sign;
		}

		return bigint_algo::compare(m_magnitude, rhs.m_magnitude) * m_sign;
	}

private:
	sign_type   m_sign = 1;	// m_magnitude >= 0 なら 1、m_magnitude < 0 なら -1
	vector_type m_magnitude;
};

template <typename V>
HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR basic_bigint<V>
operator+(basic_bigint<V> const& lhs, basic_bigint<V> const& rhs) HAMON_NOEXCEPT
{
	return basic_bigint<V>(lhs) += rhs;
}

template <typename V>
HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR basic_bigint<V>
operator-(basic_bigint<V> const& lhs, basic_bigint<V> const& rhs) HAMON_NOEXCEPT
{
	return basic_bigint<V>(lhs) -= rhs;
}

template <typename V>
HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR basic_bigint<V>
operator*(basic_bigint<V> const& lhs, basic_bigint<V> const& rhs) HAMON_NOEXCEPT
{
	return basic_bigint<V>(lhs) *= rhs;
}

template <typename V>
HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR basic_bigint<V>
operator/(basic_bigint<V> const& lhs, basic_bigint<V> const& rhs) HAMON_NOEXCEPT
{
	return basic_bigint<V>(lhs) /= rhs;
}

template <typename V>
HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR basic_bigint<V>
operator%(basic_bigint<V> const& lhs, basic_bigint<V> const& rhs) HAMON_NOEXCEPT
{
	return basic_bigint<V>(lhs) %= rhs;
}

template <typename V>
HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR basic_bigint<V>
operator&(basic_bigint<V> const& lhs, basic_bigint<V> const& rhs) HAMON_NOEXCEPT
{
	return basic_bigint<V>(lhs) &= rhs;
}

template <typename V>
HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR basic_bigint<V>
operator|(basic_bigint<V> const& lhs, basic_bigint<V> const& rhs) HAMON_NOEXCEPT
{
	return basic_bigint<V>(lhs) |= rhs;
}

template <typename V>
HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR basic_bigint<V>
operator^(basic_bigint<V> const& lhs, basic_bigint<V> const& rhs) HAMON_NOEXCEPT
{
	return basic_bigint<V>(lhs) ^= rhs;
}

template <typename V>
HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR basic_bigint<V>
operator<<(basic_bigint<V> const& lhs, hamon::size_t pos) HAMON_NOEXCEPT
{
	return basic_bigint<V>(lhs) <<= pos;
}

template <typename V>
HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR basic_bigint<V>
operator>>(basic_bigint<V> const& lhs, hamon::size_t pos) HAMON_NOEXCEPT
{
	return basic_bigint<V>(lhs) >>= pos;
}

template <typename V>
HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR bool
operator==(basic_bigint<V> const& lhs, basic_bigint<V> const& rhs) HAMON_NOEXCEPT
{
	return lhs.compare(rhs) == 0;
}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
template <typename V>
HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR hamon::strong_ordering
operator<=>(basic_bigint<V> const& lhs, basic_bigint<V> const& rhs) HAMON_NOEXCEPT
{
	return lhs.compare(rhs) <=> 0;
}
#else
template <typename V>
HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR bool
operator!=(basic_bigint<V> const& lhs, basic_bigint<V> const& rhs) HAMON_NOEXCEPT
{
	return !(lhs == rhs);
}

template <typename V>
HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR bool
operator<(basic_bigint<V> const& lhs, basic_bigint<V> const& rhs) HAMON_NOEXCEPT
{
	return lhs.compare(rhs) < 0;
}

template <typename V>
HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR bool
operator>(basic_bigint<V> const& lhs, basic_bigint<V> const& rhs) HAMON_NOEXCEPT
{
	return rhs < lhs;
}

template <typename V>
HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR bool
operator<=(basic_bigint<V> const& lhs, basic_bigint<V> const& rhs) HAMON_NOEXCEPT
{
	return !(lhs > rhs);
}

template <typename V>
HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR bool
operator>=(basic_bigint<V> const& lhs, basic_bigint<V> const& rhs) HAMON_NOEXCEPT
{
	return !(lhs < rhs);
}
#endif

namespace detail
{

struct bigint_access
{
	template <typename V>
	static HAMON_CXX14_CONSTEXPR
	typename basic_bigint<V>::sign_type&
	sign(basic_bigint<V>& x) HAMON_NOEXCEPT
	{
		return x.m_sign;
	}

	template <typename V>
	static HAMON_CXX14_CONSTEXPR
	typename basic_bigint<V>::sign_type const&
	sign(basic_bigint<V> const& x) HAMON_NOEXCEPT
	{
		return x.m_sign;
	}

	template <typename V>
	static HAMON_CXX14_CONSTEXPR
	typename basic_bigint<V>::vector_type&
	magnitude(basic_bigint<V>& x) HAMON_NOEXCEPT
	{
		return x.m_magnitude;
	}

	template <typename V>
	static HAMON_CXX14_CONSTEXPR
	typename basic_bigint<V>::vector_type const&
	magnitude(basic_bigint<V> const& x) HAMON_NOEXCEPT
	{
		return x.m_magnitude;
	}
};

}	// namespace detail

template <typename V>
inline HAMON_CXX14_CONSTEXPR bool
pow_n(basic_bigint<V>& out, basic_bigint<V> const& x, hamon::uintmax_t y)
{
	using access = hamon::detail::bigint_access;

	if (bigint_algo::pow_n(access::magnitude(out), access::magnitude(x), y))
	{
		return true;
	}

	access::sign(out) = 1;
	if (access::sign(x) < 0)
	{
		if (y % 2 == 1)
		{
			access::sign(out) = -1;
		}
	}

	return false;
}

template <typename V>
HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR int
bit_width(basic_bigint<V> const& x) HAMON_NOEXCEPT
{
	using access = hamon::detail::bigint_access;
	HAMON_ASSERT(access::sign(x) >= 0);
	return bigint_algo::bit_width(access::magnitude(x));
}

template <typename V>
HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR int
countl_zero(basic_bigint<V> const& x) HAMON_NOEXCEPT
{
	using access = hamon::detail::bigint_access;
	HAMON_ASSERT(access::sign(x) >= 0);
	return bigint_algo::countl_zero(access::magnitude(x));
}

template <typename V>
HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR int
countr_zero(basic_bigint<V> const& x) HAMON_NOEXCEPT
{
	using access = hamon::detail::bigint_access;
	HAMON_ASSERT(access::sign(x) >= 0);
	return bigint_algo::countr_zero(access::magnitude(x));
}

template <typename V>
inline HAMON_CXX14_CONSTEXPR hamon::from_chars_result
from_chars(char const* first, char const* last, basic_bigint<V>& value, int base)
{
	using access = hamon::detail::bigint_access;

	access::sign(value) = 1;
	if (first != last && *first == '-')
	{
		access::sign(value) = -1;
		++first;
	}
	return bigint_algo::from_chars(first, last, access::magnitude(value), base);
}

template <typename V>
inline HAMON_CXX14_CONSTEXPR hamon::to_chars_result
to_chars(char* first, char* last, basic_bigint<V> const& value, int base)
{
	using access = hamon::detail::bigint_access;

	if (access::sign(value) < 0 && first != last)
	{
		*first++ = '-';
	}
	return bigint_algo::to_chars(first, last, access::magnitude(value), base);
}

template <typename V>
inline HAMON_CXX20_CONSTEXPR hamon::string
to_string(basic_bigint<V> const& value)
{
	using access = hamon::detail::bigint_access;

	int base = 10;
	hamon::size_t len =
		bigint_algo::to_chars_length(access::magnitude(value), base) +
		1 +	// '-' 
		1;	// '\0'
	hamon::string result;
	result.resize(len);
	auto first = hamon::to_address(result.begin());
	auto ret = hamon::to_chars(first, first + len, value, base);
	result.resize(static_cast<hamon::size_t>(ret.ptr - first));
	return result;
}

//template <typename CharT, typename Traits, typename V>
//inline std::basic_istream<CharT, Traits>&
//operator>>(std::basic_istream<CharT, Traits>& is, basic_bigint<V>& x);

template <typename CharT, typename Traits, typename V>
inline std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, basic_bigint<V> const& x)
{
	return os << to_string(x);
}

}	// namespace hamon

#include <functional>

namespace std
{

template <typename V>
struct hash<hamon::basic_bigint<V>>
{
	HAMON_NODISCARD
	hamon::size_t operator()(hamon::basic_bigint<V> const& x) const HAMON_NOEXCEPT;
};

}	// namespace std

#endif // HAMON_BIGINT_BASIC_BIGINT_HPP
