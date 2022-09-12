/**
 *	@file	text_iarchive.hpp
 *
 *	@brief	text_iarchiveの定義
 */

#ifndef HAMON_SERIALIZATION_TEXT_IARCHIVE_HPP
#define HAMON_SERIALIZATION_TEXT_IARCHIVE_HPP

#include <hamon/serialization/detail/load_value.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>
#include <cstdint>
#include <type_traits>
#include <memory>
#include <string>
#include <iomanip>
#include <ios>

#if HAMON_HAS_INCLUDE(<charconv>) && (HAMON_CXX_STANDARD >= 17)
#include <charconv>
#endif

namespace hamon
{

namespace serialization
{

class text_iarchive_impl_base
{
public:
	virtual ~text_iarchive_impl_base()
	{
	}

	virtual void load(std::intmax_t&) = 0;
	virtual void load(std::uintmax_t&) = 0;
	virtual void load(float&) = 0;
	virtual void load(double&) = 0;
	virtual void load(long double&) = 0;
	virtual void load_quoted_string(std::string&) = 0;
	virtual void load_quoted_string(std::wstring&) = 0;
#if defined(HAMON_HAS_CXX20_CHAR8_T)
	virtual void load_quoted_string(std::u8string&) = 0;
#endif
#if defined(HAMON_HAS_CXX11_CHAR16_T)
	virtual void load_quoted_string(std::u16string&) = 0;
#endif
#if defined(HAMON_HAS_CXX11_CHAR32_T)
	virtual void load_quoted_string(std::u32string&) = 0;
#endif
};

template <typename IStream>
class text_iarchive_impl
	: public text_iarchive_impl_base
{
public:
	explicit text_iarchive_impl(IStream& is)
		: m_is(is)
	{}

	void load(std::intmax_t& t) override
	{
		m_is >> t;
	}

	void load(std::uintmax_t& t) override
	{
		m_is >> t;
	}
	
	void load(float& t) override
	{
		load_float(t);
	}

	void load(double& t) override
	{
		load_float(t);
	}

	void load(long double& t) override
	{
		load_float(t);
	}
	
	void load_quoted_string(std::string& t) override
	{
		load_quoted_string_impl(m_is, t);
	}

	void load_quoted_string(std::wstring& t) override
	{
		load_quoted_string_impl(m_is, t);
	}

#if defined(HAMON_HAS_CXX20_CHAR8_T)
	void load_quoted_string(std::u8string& t) override
	{
		load_quoted_string_impl(m_is, t);
	}
#endif
#if defined(HAMON_HAS_CXX11_CHAR16_T)
	void load_quoted_string(std::u16string& t) override
	{
		load_quoted_string_impl(m_is, t);
	}
#endif
#if defined(HAMON_HAS_CXX11_CHAR32_T)
	void load_quoted_string(std::u32string& t) override
	{
		load_quoted_string_impl(m_is, t);
	}
#endif

private:
HAMON_WARNING_PUSH();
HAMON_WARNING_DISABLE_MSVC(4244)	// '引数': 'wchar_t' から 'const _Elem' への変換です。データが失われる可能性があります。
	template <typename T>
	void load_float(T& t)
	{
		// m_is >> t;
		// だとinfとnanのときに正常にパースされない。
		// これは標準ライブラリの不具合で、将来的に修正される予定。
		// https://cplusplus.github.io/LWG/issue2381

		using char_type = typename IStream::char_type;
		std::basic_string<char_type> tmp;
		m_is >> tmp;
		std::string s(tmp.begin(), tmp.end());
#if defined(__cpp_lib_to_chars) && (__cpp_lib_to_chars >= 201611L)
		std::from_chars(s.data(), s.data() + s.length(), t);
#else
		t = std::strtold(s.data(), nullptr);
#endif
	}
HAMON_WARNING_POP();

	template <typename CharT, typename Traits>
	static void load_quoted_string_impl(
		std::basic_istream<CharT, Traits>& is,
		std::basic_string<CharT, Traits>& s)
	{
#if defined(__cpp_lib_quoted_string_io) && (__cpp_lib_quoted_string_io >= 201304L)
		is >> std::quoted(s);
#else
		std::ios_base::iostate state = std::ios_base::goodbit;
		const typename std::basic_istream<CharT, Traits>::sentry ok(is);
		if (ok)
		{
			auto const delim  = CharT('\"');
			auto const escape = CharT('\\');

			auto const rdbuf = is.rdbuf();
			auto c = rdbuf->sgetc();
			if (c != delim)
			{
				is >> s;
				return;
			}

			for (;;)
			{
				c = rdbuf->snextc();

				if (c == Traits::eof())
				{
					state = std::ios_base::eofbit |
					        std::ios_base::failbit;
					break;
				}

				if (c == delim)
				{
					c = rdbuf->sbumpc();
					if (c == Traits::eof())
					{
						state = std::ios_base::eofbit;
					}
					break;
				}

				if (c == escape)
				{
					c = rdbuf->snextc();
					if (c == Traits::eof())
					{
						state = std::ios_base::eofbit |
								std::ios_base::failbit;
						break;
					}
				}
			
				s.push_back(Traits::to_char_type(c));
			}
		}

		is.setstate(state);
#endif
	}

	template <
		typename CharT1, typename Traits1,
		typename CharT2, typename Traits2
	>
	static void load_quoted_string_impl(
		std::basic_istream<CharT1, Traits1>& is,
		std::basic_string<CharT2, Traits2>& s)
	{
		std::ios_base::iostate state = std::ios_base::goodbit;
		const typename std::basic_istream<CharT1, Traits1>::sentry ok(is);
		if (ok)
		{
			auto const delim  = CharT1('\"');
			auto const escape = CharT1('\\');

			auto const rdbuf = is.rdbuf();
			auto c = rdbuf->sgetc();
			if (c != delim)
			{
				//is >> s;
				// TODO: delim から始まっていなければエラー
				return;
			}

			for (;;)
			{
				c = rdbuf->snextc();

				if (c == Traits1::eof())
				{
					state = std::ios_base::eofbit |
					        std::ios_base::failbit;
					break;
				}

				if (c == delim)
				{
					c = rdbuf->sbumpc();
					if (c == Traits1::eof())
					{
						state = std::ios_base::eofbit;
					}
					break;
				}

				// "\x"の後に16進数で文字コードが入っている

				if (c == escape)
				{
					c = rdbuf->snextc();
					if (c == Traits1::eof())
					{
						state = std::ios_base::eofbit |
								std::ios_base::failbit;
						break;
					}

					// TODO: c == 'x' のはずなのでチェックする
				}

				char buf[sizeof(CharT2) * 2 + 1]{};
				for (std::size_t i = 0; i < sizeof(CharT2) * 2; ++i)
				{
					c = rdbuf->snextc();
					buf[i] = static_cast<char>(c);
				}
				auto ul = std::strtoul(buf, nullptr, 16);
				s += static_cast<CharT2>(ul);
			}
		}

		is.setstate(state);
	}

private:
	text_iarchive_impl& operator=(text_iarchive_impl const&) = delete;

	IStream&	m_is;
};

class text_iarchive
{
public:
	template <typename IStream>
	explicit text_iarchive(IStream& is)
		: m_impl(new text_iarchive_impl<IStream>(is))
	{
	}

	template <typename T>
	text_iarchive& operator>>(T& t)
	{
		hamon::serialization::load_value(*this, t);
		return *this;
	}

	template <typename T>
	text_iarchive& operator&(T& t)
	{
		return *this >> t;
	}

private:
	template <typename T, typename = hamon::enable_if_t<std::is_floating_point<T>::value>>
	void load_arithmetic_impl(T& t, hamon::detail::overload_priority<2>)
	{
		m_impl->load(t);
	}
	template <typename T, typename = hamon::enable_if_t<std::is_unsigned<T>::value>>
	void load_arithmetic_impl(T& t, hamon::detail::overload_priority<1>)
	{
		std::uintmax_t i;
		m_impl->load(i);
		t = static_cast<T>(i);
	}
	template <typename T, typename = hamon::enable_if_t<std::is_signed<T>::value>>
	void load_arithmetic_impl(T& t, hamon::detail::overload_priority<0>)
	{
		std::intmax_t i;
		m_impl->load(i);
		t = static_cast<T>(i);
	}

	template <typename T>
	friend void load_arithmetic(text_iarchive& ia, T& t)
	{
		ia.load_arithmetic_impl(t, hamon::detail::overload_priority<2>{});
	}

	template <typename T>
	friend void load_string(text_iarchive& ia, T& t)
	{
		ia.m_impl->load_quoted_string(t);
	}

private:
	std::unique_ptr<text_iarchive_impl_base>	m_impl;
};

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_TEXT_IARCHIVE_HPP
