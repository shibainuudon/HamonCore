/**
 *	@file	text_oarchive.hpp
 *
 *	@brief	text_oarchiveの定義
 */

#ifndef HAMON_SERIALIZATION_TEXT_OARCHIVE_HPP
#define HAMON_SERIALIZATION_TEXT_OARCHIVE_HPP

#include <hamon/serialization/detail/save_value.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/config.hpp>
#include <cstdint>
#include <type_traits>
#include <memory>
#include <limits>
#include <array>
#include <iomanip>
#include <string>

#if HAMON_HAS_INCLUDE(<charconv>) && (HAMON_CXX_STANDARD >= 17)
#include <charconv>
#endif

namespace hamon
{

namespace serialization
{

class text_oarchive_impl_base
{
public:
	virtual ~text_oarchive_impl_base()
	{}

	virtual void save(std::intmax_t) = 0;
	virtual void save(std::uintmax_t) = 0;
	virtual void save(float) = 0;
	virtual void save(double) = 0;
	virtual void save(long double) = 0;
	virtual void save_quoted_string(std::string const&) = 0;
	virtual void save_quoted_string(std::wstring const&) = 0;
#if defined(HAMON_HAS_CXX20_CHAR8_T)
	virtual void save_quoted_string(std::u8string const&) = 0;
#endif
#if defined(HAMON_HAS_CXX11_CHAR16_T)
	virtual void save_quoted_string(std::u16string const&) = 0;
#endif
#if defined(HAMON_HAS_CXX11_CHAR32_T)
	virtual void save_quoted_string(std::u32string const&) = 0;
#endif

	virtual void put(const char*) = 0;
};

template <typename OStream>
class text_oarchive_impl
	: public text_oarchive_impl_base
{
public:
	explicit text_oarchive_impl(OStream& os)
		: m_os(os)
	{}

	void save(std::intmax_t t) override
	{
		m_os << t;
	}

	void save(std::uintmax_t t) override
	{
		m_os << t;
	}
	
	void save(float t) override
	{
		save_float_impl(t);
	}

	void save(double t) override
	{
		save_float_impl(t);
	}

	void save(long double t) override
	{
		save_float_impl(t);
	}
	
	void save_quoted_string(std::string const& t) override
	{
		save_quoted_string_impl(m_os, t);
	}

	void save_quoted_string(std::wstring const& t) override
	{
		save_quoted_string_impl(m_os, t);
	}

#if defined(HAMON_HAS_CXX20_CHAR8_T)
	void save_quoted_string(std::u8string const& t) override
	{
		save_quoted_string_impl(m_os, t);
	}
#endif
#if defined(HAMON_HAS_CXX11_CHAR16_T)
	void save_quoted_string(std::u16string const& t) override
	{
		save_quoted_string_impl(m_os, t);
	}
#endif
#if defined(HAMON_HAS_CXX11_CHAR32_T)
	void save_quoted_string(std::u32string const& t) override
	{
		save_quoted_string_impl(m_os, t);
	}
#endif

	void put(const char* s) override
	{
		m_os << s;
	}

private:
	template <typename T>
	void save_float_impl(T t)
	{
#if defined(__cpp_lib_to_chars) && (__cpp_lib_to_chars >= 201611L)
		// to_charsが使えるなら使う
		auto constexpr digits =
			4 +	// sign, decimal point, "e+" or "e-"
			std::numeric_limits<T>::max_digits10 +
			3;	// log10(max_exponent10)
		std::array<char, digits + 1> buf{};
		auto result = std::to_chars(buf.data(), buf.data() + buf.size(), t);
		m_os << buf.data();
		(void)result;
#else
		auto const flags = m_os.flags();
		m_os << std::setprecision(std::numeric_limits<T>::max_digits10)
			<< std::scientific << t;
		m_os.flags(flags);
#endif
	}

	template <typename CharT, typename Traits>
	static void save_quoted_string_impl(
		std::basic_ostream<CharT, Traits>& os,
		std::basic_string<CharT, Traits> const& s)
	{
#if defined(__cpp_lib_quoted_string_io) && (__cpp_lib_quoted_string_io >= 201304L)
		os << std::quoted(s);
#else
		const typename std::basic_ostream<CharT, Traits>::sentry ok(os);
		if (!ok)
		{
			os.setstate(std::ios_base::badbit);
			return;
		}
		
		std::ios_base::iostate state = std::ios_base::goodbit;

		auto const delim  = CharT('\"');
		auto const escape = CharT('\\');

		auto const rdbuf = os.rdbuf();

		auto sputc = [&rdbuf, &state](CharT c)
		{
			if (state == std::ios_base::goodbit &&
				rdbuf->sputc(c) == Traits::eof())
			{
				state |= std::ios_base::badbit;
				return false;
			}
			return true;
		};

		sputc(delim);

		for (auto c : s)
		{
			if (c == delim || c == escape)
			{
				if (!sputc(escape))
				{
					break;
				}
			}
			
			if (!sputc(c))
			{
				break;
			}
		}

		sputc(delim);

		os.width(0);
		os.setstate(state);
#endif
	}

	template <
		typename CharT1, typename Traits1,
		typename CharT2, typename Traits2
	>
	static void save_quoted_string_impl(
		std::basic_ostream<CharT1, Traits1>& os,
		std::basic_string<CharT2, Traits2> const& s)
	{
		auto const delim  = CharT1('\"');
		auto const escape = CharT1('\\');
		auto const zero   = CharT1('0');

		os << delim;
		for (auto c : s)
		{
			// "\x"の後に16進数で文字コードを出力する
			os << escape;
			os << "x";

			// c を符号なし整数型として出力したい。
			// ただし、unsigned char型はoperator<<が特殊な動作をするので、
			// (符号拡張を避けながら)uint64_t型にキャストする。
			using unsigned_type =
				hamon::conditional_t<sizeof(CharT2) == 1, std::uint8_t,
				hamon::conditional_t<sizeof(CharT2) == 2, std::uint16_t,
				hamon::conditional_t<sizeof(CharT2) == 4, std::uint32_t,
				std::uint64_t
			>>>;
			auto const t = std::uint64_t(unsigned_type(c));
			constexpr auto digits = sizeof(CharT2) * 2;

#if defined(__cpp_lib_to_chars) && (__cpp_lib_to_chars >= 201611L)
			// to_charsを使うパターン
			std::array<char, digits + 1> buf{};
			auto result = std::to_chars(buf.data(), buf.data() + buf.size(), t, 16);
			// 先頭を'0'で埋める
			for (std::size_t i = 0; i < digits - (result.ptr - buf.data()); ++i)
			{
				os << zero;
			}
			os << buf.data();
#elif 0
			// snprintfを使うパターン
			std::array<char, 5> fmt{};	// フォーマット文字列。"%02x"など。
			std::snprintf(fmt.data(), fmt.size(), "%%0%dx", (int)digits);
			std::array<char, digits + 1> buf{};
			std::snprintf(buf.data(), buf.size(), fmt.data(), c);
			os << buf.data();
#else
			// operator<<を使うパターン
			auto const old_flags = os.flags();
			os << std::hex << std::right << std::setw(digits)
			   << std::setfill(zero) << t;
			os.flags(old_flags);
#endif
		}
		os << delim;
	}

private:
	text_oarchive_impl& operator=(text_oarchive_impl const&) = delete;

	OStream&	m_os;
};

class text_oarchive
{
public:
	template <typename OStream>
	explicit text_oarchive(OStream& os)
		: m_impl(new text_oarchive_impl<OStream>(os))
	{
	}

	template <typename T>
	text_oarchive& operator<<(T const& t)
	{
		hamon::serialization::save_value(*this, t);
		m_impl->put(" ");
		return *this;
	}

	template <typename T>
	text_oarchive& operator&(T const& t)
	{
		return *this << t;
	}

private:
	template <typename T, typename = hamon::enable_if_t<std::is_floating_point<T>::value>>
	void save_arithmetic_impl(T const& t, hamon::detail::overload_priority<2>)
	{
		m_impl->save(t);
	}
	template <typename T, typename = hamon::enable_if_t<std::is_unsigned<T>::value>>
	void save_arithmetic_impl(T const& t, hamon::detail::overload_priority<1>)
	{
		m_impl->save(static_cast<std::uintmax_t>(t));
	}
	template <typename T, typename = hamon::enable_if_t<std::is_signed<T>::value>>
	void save_arithmetic_impl(T const& t, hamon::detail::overload_priority<0>)
	{
		m_impl->save(static_cast<std::intmax_t>(t));
	}

	template <typename T>
	friend void save_arithmetic(text_oarchive& oa, T const& t)
	{
		oa.save_arithmetic_impl(t, hamon::detail::overload_priority<2>{});
	}

	template <typename T>
	friend void save_string(text_oarchive& oa, T const& t)
	{
		oa.m_impl->save_quoted_string(t);
	}

private:
	std::unique_ptr<text_oarchive_impl_base>	m_impl;
};

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_TEXT_OARCHIVE_HPP
