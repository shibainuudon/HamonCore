/**
 *	@file	complex.hpp
 *
 *	@brief	complex の定義
 */

#ifndef HAMON_COMPLEX_COMPLEX_HPP
#define HAMON_COMPLEX_COMPLEX_HPP

#include <hamon/complex/config.hpp>

#if defined(HAMON_USE_STD_COMPLEX)

#include <complex>

namespace hamon
{

using std::complex;

}	// namespace hamon

#else

#include <hamon/type_traits/float_promote.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// [complex], class template complex
template <typename T>
class complex
{
public:
	using value_type = T;

	// [complex.members]
	HAMON_CXX11_CONSTEXPR complex(T const& re = T(), T const& im = T())
		: m_real(re)
		, m_imag(im)
	{
		// [complex.members]/1
	}

	HAMON_CXX11_CONSTEXPR complex(complex const&) = default;

#if defined(HAMON_HAS_CXX20_CONDITIONAL_EXPLICIT)

	template <typename X>
	HAMON_CXX11_CONSTEXPR explicit(!hamon::is_same<hamon::float_promote_t<X, T>, T>::value)	// [complex.members]/3
	complex(complex<X> const& other)
		: m_real(static_cast<T>(other.real()))
		, m_imag(static_cast<T>(other.imag()))
	{
		// [complex.members]/2
	}

#else

	template <typename X, hamon::enable_if_t<!hamon::is_same<hamon::float_promote_t<X, T>, T>::value>* = nullptr>
	explicit HAMON_CXX11_CONSTEXPR
	complex(complex<X> const& other)
		: m_real(static_cast<T>(other.real()))
		, m_imag(static_cast<T>(other.imag()))
	{}

	template <typename X, hamon::enable_if_t<hamon::is_same<hamon::float_promote_t<X, T>, T>::value>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	complex(complex<X> const& other)
		: m_real(static_cast<T>(other.real()))
		, m_imag(static_cast<T>(other.imag()))
	{}

#endif

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR T real() const
	{
		// [complex.members]/4
		return m_real;
	}

	HAMON_CXX14_CONSTEXPR void real(T val)
	{
		// [complex.members]/5
		m_real = val;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR T imag() const
	{
		// [complex.members]/6
		return m_imag;
	}

	HAMON_CXX14_CONSTEXPR void imag(T val)
	{
		// [complex.members]/7
		m_imag = val;
	}

	// [complex.member.ops]
	HAMON_CXX14_CONSTEXPR complex& operator=(T const& rhs)
	{
		m_real = rhs;
		m_imag = T{};
		return *this;
	}

	HAMON_CXX14_CONSTEXPR complex& operator+=(T const& rhs)
	{
		// [complex.member.ops]/1
		m_real += rhs;
		// [complex.member.ops]/2
		return *this;
	}

	HAMON_CXX14_CONSTEXPR complex& operator-=(T const& rhs)
	{
		// [complex.member.ops]/3
		m_real -= rhs;
		// [complex.member.ops]/4
		return *this;
	}

	HAMON_CXX14_CONSTEXPR complex& operator*=(T const& rhs)
	{
		// [complex.member.ops]/5
		m_real *= rhs;
		m_imag *= rhs;
		// [complex.member.ops]/6
		return *this;
	}

	HAMON_CXX14_CONSTEXPR complex& operator/=(T const& rhs)
	{
		// [complex.member.ops]/7
		m_real /= rhs;
		m_imag /= rhs;
		// [complex.member.ops]/8
		return *this;
	}

	HAMON_CXX14_CONSTEXPR complex& operator=(complex const&) = default;

	template <typename X>
	HAMON_CXX14_CONSTEXPR complex& operator=(complex<X> const& rhs)
	{
		m_real = static_cast<T>(rhs.real());
		m_imag = static_cast<T>(rhs.imag());
		return *this;
	}

	template <typename X>
	HAMON_CXX14_CONSTEXPR complex& operator+=(complex<X> const& rhs)
	{
		// [complex.member.ops]/9
		*this = *this + complex(rhs);
		// [complex.member.ops]/10
		return *this;
	}

	template <typename X>
	HAMON_CXX14_CONSTEXPR complex& operator-=(complex<X> const& rhs)
	{
		// [complex.member.ops]/11
		*this = *this - complex(rhs);
		// [complex.member.ops]/12
		return *this;
	}

	template <typename X>
	HAMON_CXX14_CONSTEXPR complex& operator*=(complex<X> const& rhs)
	{
		// [complex.member.ops]/13
		*this = *this * complex(rhs);
		// [complex.member.ops]/14
		return *this;
	}

	template <typename X>
	HAMON_CXX14_CONSTEXPR complex& operator/=(complex<X> const& rhs)
	{
		// [complex.member.ops]/15
		*this = *this / complex(rhs);
		// [complex.member.ops]/16
		return *this;
	}

private:
	T	m_real;
	T	m_imag;
};

namespace complex_detail
{

template <typename T>
HAMON_CXX11_CONSTEXPR complex<T>
multiply(T a, T b, T c, T d)
{
	return complex<T>(
		(a * c) - (b * d),
		(a * d) + (b * c));
}

template <typename T>
HAMON_CXX11_CONSTEXPR complex<T>
divide(T a, T b, T c, T d)
{
	return complex<T>(
		((a * c) + (b * d)) / ((c * c) + (d * d)),
		((b * c) - (a * d)) / ((c * c) + (d * d)));
}

}	// namespace complex_detail

// [complex.ops], operators
template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<T>
operator+(complex<T> const& lhs, complex<T> const& rhs)
{
	return complex<T>{lhs.real() + rhs.real(), lhs.imag() + rhs.imag()};
}

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<T>
operator+(complex<T> const& lhs, T const& rhs)
{
	return lhs + complex<T>{rhs};
}

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<T>
operator+(T const& lhs, complex<T> const& rhs)
{
	return complex<T>{lhs} + rhs;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<T>
operator-(complex<T> const& lhs, complex<T> const& rhs)
{
	return complex<T>{lhs.real() - rhs.real(), lhs.imag() - rhs.imag()};
}

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<T>
operator-(complex<T> const& lhs, T const& rhs)
{
	return lhs - complex<T>{rhs};
}

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<T>
operator-(T const& lhs, complex<T> const& rhs)
{
	return complex<T>{lhs} - rhs;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<T>
operator*(complex<T> const& lhs, complex<T> const& rhs)
{
	return complex_detail::multiply(
		lhs.real(), lhs.imag(),
		rhs.real(), rhs.imag());
}

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<T>
operator*(complex<T> const& lhs, T const& rhs)
{
	return complex<T>{lhs.real() * rhs, lhs.imag() * rhs};
}

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<T>
operator*(T const& lhs, complex<T> const& rhs)
{
	return complex<T>{lhs} * rhs;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<T>
operator/(complex<T> const& lhs, complex<T> const& rhs)
{
	return complex_detail::divide(
		lhs.real(), lhs.imag(),
		rhs.real(), rhs.imag());
}

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<T>
operator/(complex<T> const& lhs, T const& rhs)
{
	return complex<T>{lhs.real() / rhs, lhs.imag() / rhs};
}

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<T>
operator/(T const& lhs, complex<T> const& rhs)
{
	return complex<T>{lhs} / rhs;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<T>
operator+(complex<T> const& lhs)
{
	return lhs;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<T>
operator-(complex<T> const& lhs)
{
	return complex<T>(-lhs.real(), -lhs.imag());
}

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool
operator==(complex<T> const& lhs, complex<T> const& rhs)
{
	return lhs.real() == rhs.real() && lhs.imag() == rhs.imag();
}

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool
operator==(complex<T> const& lhs, T const& rhs)
{
	return lhs == complex<T>{rhs};
}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool
operator==(T const& lhs, complex<T> const& rhs)
{
	return complex<T>{lhs} == rhs;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool
operator!=(complex<T> const& lhs, complex<T> const& rhs)
{
	return !(lhs == rhs);
}

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool
operator!=(complex<T> const& lhs, T const& rhs)
{
	return !(lhs == rhs);
}

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool
operator!=(T const& lhs, complex<T> const& rhs)
{
	return !(lhs == rhs);
}

#endif

}	// namespace hamon

#include <istream>
#include <ostream>
#include <sstream>

namespace hamon
{

template <typename T, typename CharT, typename traits>
std::basic_istream<CharT, traits>&
operator>>(std::basic_istream<CharT, traits>& is, complex<T>& x)
{
	if (is.good())
	{
		std::ws(is);
		if (is.peek() == CharT('('))
		{
			is.get();
			T r;
			is >> r;
			if (!is.fail())
			{
				std::ws(is);
				CharT c = static_cast<CharT>(is.peek());
				if (c == CharT(','))
				{
					is.get();
					T i;
					is >> i;
					if (!is.fail())
					{
						std::ws(is);
						c = static_cast<CharT>(is.peek());
						if (c == CharT(')'))
						{
							is.get();
							x = complex<T>(r, i);
						}
						else
						{
							is.setstate(is.failbit);
						}
					}
					else
					{
						is.setstate(is.failbit);
					}
				}
				else if (c == CharT(')'))
				{
					is.get();
					x = complex<T>(r, T(0));
				}
				else
				{
					is.setstate(is.failbit);
				}
			}
			else
			{
				is.setstate(is.failbit);
			}
		}
		else
		{
			T r;
			is >> r;
			if (!is.fail())
			{
				x = complex<T>(r, T(0));
			}
			else
			{
				is.setstate(is.failbit);
			}
		}
	}
	else
	{
		is.setstate(is.failbit);
	}

	return is;
}

template <typename T, typename CharT, typename traits>
std::basic_ostream<CharT, traits>&
operator<<(std::basic_ostream<CharT, traits>& o, complex<T> const& x)
{
	// [complex.ops]/14
	// Inserts the complex number x onto the stream o as if it were implemented as follows:
	std::basic_ostringstream<CharT, traits> s;
	s.flags(o.flags());
	s.imbue(o.getloc());
	s.precision(o.precision());
	s << '(' << x.real() << ',' << x.imag() << ')';
	return o << s.str();
}

}	// namespace hamon

#endif

#include <hamon/config.hpp>

namespace hamon
{

// [complex.literals], complex literals
inline namespace literals
{
inline namespace complex_literals
{

// アンダースコアで始まらないユーザー定義リテラルのサフィックス名は、
// 標準C++の将来の拡張のために予約されている。

HAMON_CXX11_CONSTEXPR hamon::complex<long double> operator"" _il(long double d)
{
	// [complex.literals]/2
	return {0.0L, static_cast<long double>(d)};
}

HAMON_CXX11_CONSTEXPR hamon::complex<long double> operator"" _il(unsigned long long d)
{
	// [complex.literals]/2
	return {0.0L, static_cast<long double>(d)};
}

HAMON_CXX11_CONSTEXPR hamon::complex<double> operator"" _i(long double d)
{
	// [complex.literals]/3
	return {0.0, static_cast<double>(d)};
}

HAMON_CXX11_CONSTEXPR hamon::complex<double> operator"" _i(unsigned long long d)
{
	// [complex.literals]/3
	return {0.0, static_cast<double>(d)};
}

HAMON_CXX11_CONSTEXPR hamon::complex<float> operator"" _if(long double d)
{
	// [complex.literals]/4
	return {0.0f, static_cast<float>(d)};
}

HAMON_CXX11_CONSTEXPR hamon::complex<float> operator"" _if(unsigned long long d)
{
	// [complex.literals]/4
	return {0.0f, static_cast<float>(d)};
}

}	// inline namespace complex_literals
}	// inline namespace literals

}	// namespace hamon

#endif // HAMON_COMPLEX_COMPLEX_HPP
