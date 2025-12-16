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
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace complex_detail
{

template <typename T, hamon::size_t>
struct complex_tuple;

}

// 28.4.3 Class template complex[complex]
template <typename T>
class complex
{
public:
	using value_type = T;

	// [complex.members]
	HAMON_CXX11_CONSTEXPR complex(T const& re = T(), T const& im = T()) HAMON_NOEXCEPT	// noexcept as an extension
		: m_real(re)
		, m_imag(im)
	{
		// [complex.members]/1
	}

	HAMON_CXX11_CONSTEXPR complex(complex const&) = default;

#if defined(HAMON_HAS_CXX20_CONDITIONAL_EXPLICIT)

	template <typename X>
	HAMON_CXX11_CONSTEXPR explicit(!hamon::is_same<hamon::float_promote_t<X, T>, T>::value)	// [complex.members]/3
	complex(complex<X> const& other) HAMON_NOEXCEPT	// noexcept as an extension
		: m_real(static_cast<T>(other.real()))
		, m_imag(static_cast<T>(other.imag()))
	{
		// [complex.members]/2
	}

#else

	template <typename X, hamon::enable_if_t<!hamon::is_same<hamon::float_promote_t<X, T>, T>::value>* = nullptr>
	explicit HAMON_CXX11_CONSTEXPR
	complex(complex<X> const& other) HAMON_NOEXCEPT	// noexcept as an extension
		: m_real(static_cast<T>(other.real()))
		, m_imag(static_cast<T>(other.imag()))
	{}

	template <typename X, hamon::enable_if_t<hamon::is_same<hamon::float_promote_t<X, T>, T>::value>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	complex(complex<X> const& other) HAMON_NOEXCEPT	// noexcept as an extension
		: m_real(static_cast<T>(other.real()))
		, m_imag(static_cast<T>(other.imag()))
	{}

#endif

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	T real() const HAMON_NOEXCEPT	// noexcept as an extension
	{
		// [complex.members]/4
		return m_real;
	}

	HAMON_CXX14_CONSTEXPR void
	real(T val) HAMON_NOEXCEPT	// noexcept as an extension
	{
		// [complex.members]/5
		m_real = val;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	T imag() const HAMON_NOEXCEPT	// noexcept as an extension
	{
		// [complex.members]/6
		return m_imag;
	}

	HAMON_CXX14_CONSTEXPR void
	imag(T val) HAMON_NOEXCEPT	// noexcept as an extension
	{
		// [complex.members]/7
		m_imag = val;
	}

	// [complex.member.ops]
	HAMON_CXX14_CONSTEXPR complex&
	operator=(T const& rhs) HAMON_NOEXCEPT	// noexcept as an extension
	{
		m_real = rhs;
		m_imag = T{};
		return *this;
	}

	HAMON_CXX14_CONSTEXPR complex&
	operator+=(T const& rhs) HAMON_NOEXCEPT	// noexcept as an extension
	{
		// [complex.member.ops]/1
		m_real += rhs;
		// [complex.member.ops]/2
		return *this;
	}

	HAMON_CXX14_CONSTEXPR complex&
	operator-=(T const& rhs) HAMON_NOEXCEPT	// noexcept as an extension
	{
		// [complex.member.ops]/3
		m_real -= rhs;
		// [complex.member.ops]/4
		return *this;
	}

	HAMON_CXX14_CONSTEXPR complex&
	operator*=(T const& rhs) HAMON_NOEXCEPT	// noexcept as an extension
	{
		// [complex.member.ops]/5
		m_real *= rhs;
		m_imag *= rhs;
		// [complex.member.ops]/6
		return *this;
	}

	HAMON_CXX14_CONSTEXPR complex&
	operator/=(T const& rhs) HAMON_NOEXCEPT	// noexcept as an extension
	{
		// [complex.member.ops]/7
		m_real /= rhs;
		m_imag /= rhs;
		// [complex.member.ops]/8
		return *this;
	}

	HAMON_CXX14_CONSTEXPR complex& operator=(complex const&) = default;

	template <typename X>
	HAMON_CXX14_CONSTEXPR complex&
	operator=(complex<X> const& rhs) HAMON_NOEXCEPT	// noexcept as an extension
	{
		// [complex.member.ops]/9
		m_real = static_cast<T>(rhs.real());
		// [complex.member.ops]/10
		m_imag = static_cast<T>(rhs.imag());
		return *this;
	}

	template <typename X>
	HAMON_CXX14_CONSTEXPR complex&
	operator+=(complex<X> const& rhs) HAMON_NOEXCEPT	// noexcept as an extension
	{
		// [complex.member.ops]/11
		*this = *this + complex(rhs);
		// [complex.member.ops]/12
		return *this;
	}

	template <typename X>
	HAMON_CXX14_CONSTEXPR complex&
	operator-=(complex<X> const& rhs) HAMON_NOEXCEPT	// noexcept as an extension
	{
		// [complex.member.ops]/13
		*this = *this - complex(rhs);
		// [complex.member.ops]/14
		return *this;
	}

	template <typename X>
	HAMON_CXX14_CONSTEXPR complex&
	operator*=(complex<X> const& rhs) HAMON_NOEXCEPT	// noexcept as an extension
	{
		// [complex.member.ops]/15
		*this = *this * complex(rhs);
		// [complex.member.ops]/16
		return *this;
	}

	template <typename X>
	HAMON_CXX14_CONSTEXPR complex&
	operator/=(complex<X> const& rhs) HAMON_NOEXCEPT	// noexcept as an extension
	{
		// [complex.member.ops]/17
		*this = *this / complex(rhs);
		// [complex.member.ops]/18
		return *this;
	}

private:
	T	m_real;
	T	m_imag;

	friend complex_detail::complex_tuple<T, 0>;
	friend complex_detail::complex_tuple<T, 1>;
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
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<T>	// nodiscard as an extension
operator+(complex<T> const& lhs, complex<T> const& rhs) HAMON_NOEXCEPT	// noexcept as an extension
{
	// [complex.ops]/2
	return complex<T>{lhs.real() + rhs.real(), lhs.imag() + rhs.imag()};
}

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<T>	// nodiscard as an extension
operator+(complex<T> const& lhs, T const& rhs) HAMON_NOEXCEPT	// noexcept as an extension
{
	// [complex.ops]/2
	return lhs + complex<T>{rhs};
}

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<T>	// nodiscard as an extension
operator+(T const& lhs, complex<T> const& rhs) HAMON_NOEXCEPT	// noexcept as an extension
{
	// [complex.ops]/2
	return complex<T>{lhs} + rhs;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<T>	// nodiscard as an extension
operator-(complex<T> const& lhs, complex<T> const& rhs) HAMON_NOEXCEPT	// noexcept as an extension
{
	// [complex.ops]/4
	return complex<T>{lhs.real() - rhs.real(), lhs.imag() - rhs.imag()};
}

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<T>	// nodiscard as an extension
operator-(complex<T> const& lhs, T const& rhs) HAMON_NOEXCEPT	// noexcept as an extension
{
	// [complex.ops]/4
	return lhs - complex<T>{rhs};
}

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<T>	// nodiscard as an extension
operator-(T const& lhs, complex<T> const& rhs) HAMON_NOEXCEPT	// noexcept as an extension
{
	// [complex.ops]/4
	return complex<T>{lhs} - rhs;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<T>	// nodiscard as an extension
operator*(complex<T> const& lhs, complex<T> const& rhs) HAMON_NOEXCEPT	// noexcept as an extension
{
	// [complex.ops]/5
	return complex_detail::multiply(
		lhs.real(), lhs.imag(),
		rhs.real(), rhs.imag());
}

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<T>	// nodiscard as an extension
operator*(complex<T> const& lhs, T const& rhs) HAMON_NOEXCEPT	// noexcept as an extension
{
	// [complex.ops]/5
	return complex<T>{lhs.real() * rhs, lhs.imag() * rhs};
}

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<T>	// nodiscard as an extension
operator*(T const& lhs, complex<T> const& rhs) HAMON_NOEXCEPT	// noexcept as an extension
{
	// [complex.ops]/5
	return complex<T>{lhs} * rhs;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<T>	// nodiscard as an extension
operator/(complex<T> const& lhs, complex<T> const& rhs) HAMON_NOEXCEPT	// noexcept as an extension
{
	// [complex.ops]/6
	return complex_detail::divide(
		lhs.real(), lhs.imag(),
		rhs.real(), rhs.imag());
}

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<T>	// nodiscard as an extension
operator/(complex<T> const& lhs, T const& rhs) HAMON_NOEXCEPT	// noexcept as an extension
{
	// [complex.ops]/6
	return complex<T>{lhs.real() / rhs, lhs.imag() / rhs};
}

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<T>	// nodiscard as an extension
operator/(T const& lhs, complex<T> const& rhs) HAMON_NOEXCEPT	// noexcept as an extension
{
	// [complex.ops]/6
	return complex<T>{lhs} / rhs;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<T>	// nodiscard as an extension
operator+(complex<T> const& lhs) HAMON_NOEXCEPT	// noexcept as an extension
{
	// [complex.ops]/1
	return lhs;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<T>	// nodiscard as an extension
operator-(complex<T> const& lhs) HAMON_NOEXCEPT	// noexcept as an extension
{
	// [complex.ops]/3
	return complex<T>(-lhs.real(), -lhs.imag());
}

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator==(complex<T> const& lhs, complex<T> const& rhs) HAMON_NOEXCEPT	// noexcept as an extension
{
	// [complex.ops]/7
	return lhs.real() == rhs.real() && lhs.imag() == rhs.imag();
}

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator==(complex<T> const& lhs, T const& rhs) HAMON_NOEXCEPT	// noexcept as an extension
{
	// [complex.ops]/7
	// [complex.ops]/8
	return lhs == complex<T>{rhs};
}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator==(T const& lhs, complex<T> const& rhs) HAMON_NOEXCEPT	// noexcept as an extension
{
	return complex<T>{lhs} == rhs;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator!=(complex<T> const& lhs, complex<T> const& rhs) HAMON_NOEXCEPT	// noexcept as an extension
{
	return !(lhs == rhs);
}

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator!=(complex<T> const& lhs, T const& rhs) HAMON_NOEXCEPT	// noexcept as an extension
{
	return !(lhs == rhs);
}

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator!=(T const& lhs, complex<T> const& rhs) HAMON_NOEXCEPT	// noexcept as an extension
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
	// [complex.ops]/10

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

	// [complex.ops]/12
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

#include <hamon/utility/move.hpp>

namespace hamon
{

namespace complex_detail
{

template <typename T>
struct complex_tuple<T, 0>
{
	static HAMON_CXX11_CONSTEXPR T&
	get(hamon::complex<T>& z) HAMON_NOEXCEPT
	{
		return z.m_real;
	}

	static HAMON_CXX11_CONSTEXPR T&&
	get(hamon::complex<T>&& z) HAMON_NOEXCEPT
	{
		return hamon::move(z.m_real);
	}

	static HAMON_CXX11_CONSTEXPR T const&
	get(hamon::complex<T> const& z) HAMON_NOEXCEPT
	{
		return z.m_real;
	}

	static HAMON_CXX11_CONSTEXPR T const&&
	get(hamon::complex<T> const&& z) HAMON_NOEXCEPT
	{
		return hamon::move(z.m_real);
	}
};

template <typename T>
struct complex_tuple<T, 1>
{
	static HAMON_CXX11_CONSTEXPR T&
	get(hamon::complex<T>& z) HAMON_NOEXCEPT
	{
		return z.m_imag;
	}

	static HAMON_CXX11_CONSTEXPR T&&
	get(hamon::complex<T>&& z) HAMON_NOEXCEPT
	{
		return hamon::move(z.m_imag);
	}

	static HAMON_CXX11_CONSTEXPR T const&
	get(hamon::complex<T> const& z) HAMON_NOEXCEPT
	{
		return z.m_imag;
	}

	static HAMON_CXX11_CONSTEXPR T const&&
	get(hamon::complex<T> const&& z) HAMON_NOEXCEPT
	{
		return hamon::move(z.m_imag);
	}
};

}	// namespace complex_detail

template <hamon::size_t I, typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR T&	// nodiscard as an extension
get(hamon::complex<T>& z) HAMON_NOEXCEPT
{
	// [complex.tuple]/2
	static_assert(I < 2, "index is out of bounds");
	// [complex.tuple]/3
	return complex_detail::complex_tuple<T, I>::get(z);
}

template <hamon::size_t I, typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR T&&	// nodiscard as an extension
get(hamon::complex<T>&& z) HAMON_NOEXCEPT
{
	// [complex.tuple]/2
	static_assert(I < 2, "index is out of bounds");
	// [complex.tuple]/3
	return complex_detail::complex_tuple<T, I>::get(hamon::move(z));
}

template <hamon::size_t I, typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR T const&	// nodiscard as an extension
get(hamon::complex<T> const& z) HAMON_NOEXCEPT
{
	// [complex.tuple]/2
	static_assert(I < 2, "index is out of bounds");
	// [complex.tuple]/3
	return complex_detail::complex_tuple<T, I>::get(z);
}

template <hamon::size_t I, typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR T const&&	// nodiscard as an extension
get(hamon::complex<T> const&& z) HAMON_NOEXCEPT
{
	// [complex.tuple]/2
	static_assert(I < 2, "index is out of bounds");
	// [complex.tuple]/3
	return complex_detail::complex_tuple<T, I>::get(hamon::move(z));
}

}	// namespace hamon

#include <hamon/concepts/detail/is_specialization_of_complex.hpp>
#include <hamon/type_traits/bool_constant.hpp>

namespace hamon {
namespace detail {

// is_specialization_of_complex の特殊化
template <typename T>
struct is_specialization_of_complex<hamon::complex<T>>
	: public hamon::true_type {};

}	// namespace detail
}	// namespace hamon

#include <hamon/type_traits/integral_constant.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <tuple>

namespace std
{

// tuple_size の特殊化
template <typename T>
struct tuple_size<hamon::complex<T>>
	: public hamon::integral_constant<hamon::size_t, 2> {};

// tuple_element の特殊化
template <hamon::size_t I, typename T>
struct tuple_element<I, hamon::complex<T>>
{
	// [complex.tuple]/1
	static_assert(I < 2, "index is out of bounds");
	using type = T;
};

}	// namespace std

#endif

#include <hamon/config.hpp>

namespace hamon
{

// [complex.literals], complex literals
inline namespace literals
{
inline namespace complex_literals
{

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(5311)	// '演算子文字列-リテラル識別子' の形式のリテラル演算子 ID は非推奨になりました

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

HAMON_WARNING_POP()

}	// inline namespace complex_literals
}	// inline namespace literals

}	// namespace hamon

#endif // HAMON_COMPLEX_COMPLEX_HPP
