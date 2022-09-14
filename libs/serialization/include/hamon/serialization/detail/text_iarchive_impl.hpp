/**
 *	@file	text_iarchive_impl.hpp
 *
 *	@brief	text_iarchive_implの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_TEXT_IARCHIVE_IMPL_HPP
#define HAMON_SERIALIZATION_DETAIL_TEXT_IARCHIVE_IMPL_HPP

#include <hamon/config.hpp>
#include <cstdint>
#include <cstdlib>	// strtold
#include <string>
#include <istream>	// basic_istream
#include <iomanip>
#include <ios>		// ios_base
#if HAMON_HAS_INCLUDE(<charconv>) && (HAMON_CXX_STANDARD >= 17)
#include <charconv>
#endif

namespace hamon
{

namespace serialization
{

namespace detail
{

class text_iarchive_impl_base
{
public:
	virtual ~text_iarchive_impl_base() {}

	virtual void load(bool&) = 0;
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

	virtual char get_one_char() = 0;
	virtual void unget_one_char() = 0;
};

template <typename IStream>
class text_iarchive_impl
	: public text_iarchive_impl_base
{
public:
	explicit text_iarchive_impl(IStream& is)
		: m_is(is)
	{}

	void load(bool& t) override
	{
		auto const old_flags = m_is.flags();
		m_is >> std::boolalpha >> t;
		m_is.flags(old_flags);
	}

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
	
	char get_one_char() override
	{
		return static_cast<char>(get_one_char_impl(m_is));
	}

	void unget_one_char() override
	{
		auto const rdbuf = m_is.rdbuf();
		rdbuf->sungetc();
	}

private:
HAMON_WARNING_PUSH();
HAMON_WARNING_DISABLE_MSVC(4244)	// '引数': 'wchar_t' から 'const CharT' への変換です。データが失われる可能性があります。
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
		auto first = s.data();
		auto last  = s.data() + s.length();
#if defined(__cpp_lib_to_chars) && (__cpp_lib_to_chars >= 201611L)
		auto result = std::from_chars(first, last, t);
		m_is.seekg(result.ptr - last, std::ios_base::cur);	// 変換できなかったぶん戻す
#else
		char* end;
		t = std::strtold(first, &end);
		m_is.seekg(end - last, std::ios_base::cur);	// 変換できなかったぶん戻す
#endif
	}
HAMON_WARNING_POP();

	template <typename CharT, typename Traits>
	static void load_quoted_string_impl(
		std::basic_istream<CharT, Traits>& is,
		std::basic_string<CharT, Traits>& s)
	{
#if 0//defined(__cpp_lib_quoted_string_io) && (__cpp_lib_quoted_string_io >= 201304L)
		is >> std::quoted(s);
#else
		std::ios_base::iostate state = std::ios_base::goodbit;
		const typename std::basic_istream<CharT, Traits>::sentry ok(is);

		if (ok)// state okay, extract characters
		{
			try
			{
				const auto rdbuf  = is.rdbuf();
				const auto delim  = Traits::to_int_type('"');
				const auto escape = Traits::to_int_type('\\');
				auto c = rdbuf->sgetc();

				if (!Traits::eq_int_type(c, delim))
				{
					// no leading delimiter
					is >> s;
					return;
				}

				s.clear();
				for (;;)
				{
					c = rdbuf->snextc();
					if (Traits::eq_int_type(Traits::eof(), c))
					{
						// no trailing delimiter; fail
						state = std::ios_base::eofbit | std::ios_base::failbit;
						break;
					}
					else if (Traits::eq_int_type(c, escape))
					{
						// escape; read next character literally
						auto c2 = rdbuf->snextc();
						if (Traits::eq_int_type(Traits::eof(), c2))
						{
							// bad escape; fail
							state = std::ios_base::eofbit | std::ios_base::failbit;
							break;
						}
						if (!Traits::eq_int_type(delim, c2))
						{
							s.push_back(Traits::to_char_type(c));
						}
						c = c2;
					}
					else if (Traits::eq_int_type(c, delim))
					{
						// found trailing delimiter
						if (Traits::eq_int_type(Traits::eof(), rdbuf->sbumpc()))
						{
							// consume trailing delimiter
							state = std::ios_base::eofbit;
						}

						break;
					}

					s.push_back(Traits::to_char_type(c));
				}
			}
			catch (...)
			{
				is.setstate(std::ios_base::badbit);
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
	
	template <typename CharT, typename Traits>
	static CharT get_one_char_impl(
		std::basic_istream<CharT, Traits>& is)
	{
		const typename std::basic_istream<CharT, Traits>::sentry ok(is);
		if (ok)
		{
			auto const rdbuf = is.rdbuf();
			return static_cast<CharT>(rdbuf->sbumpc());
		}
		return 0;
	}

private:
	text_iarchive_impl& operator=(text_iarchive_impl const&) = delete;

	IStream&	m_is;
};

}	// namespace detail

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_TEXT_IARCHIVE_IMPL_HPP
