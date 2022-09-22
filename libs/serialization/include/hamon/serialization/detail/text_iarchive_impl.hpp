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
#include <algorithm>

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

	virtual void load_string(std::string&) = 0;
	virtual void load_string(std::wstring&) = 0;
#if defined(HAMON_HAS_CXX20_CHAR8_T)
	virtual void load_string(std::u8string&) = 0;
#endif
#if defined(HAMON_HAS_CXX11_CHAR16_T)
	virtual void load_string(std::u16string&) = 0;
#endif
#if defined(HAMON_HAS_CXX11_CHAR32_T)
	virtual void load_string(std::u32string&) = 0;
#endif

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
	
private:
	template <
		typename CharT1, typename Traits1,
		typename CharT2, typename Traits2,
		hamon::enable_if_t<(sizeof(CharT1) > sizeof(CharT2))>* = nullptr
	>
	static void load_string_impl_2(
		std::basic_istream<CharT1, Traits1>& is,
		std::basic_string<CharT2, Traits2>& s)
	{
		std::basic_string<CharT1> tmp;
		tmp.resize(s.size());
		is.read(&tmp[0], tmp.size());
		std::transform(tmp.begin(), tmp.end(), s.begin(),
			[](CharT1 c){return static_cast<CharT2>(c);});
	}

	template <
		typename CharT1, typename Traits1,
		typename CharT2, typename Traits2,
		hamon::enable_if_t<sizeof(CharT1) <= sizeof(CharT2)>* = nullptr
	>
	static void load_string_impl_2(
		std::basic_istream<CharT1, Traits1>& is,
		std::basic_string<CharT2, Traits2>& s)
	{
		std::streamsize count = (s.size() * sizeof(CharT2)) / sizeof(CharT1);
		is.read(reinterpret_cast<CharT1*>(&s[0]), count);
	}

	template <
		typename CharT1, typename Traits1,
		typename CharT2, typename Traits2
	>
	static void load_string_impl(
		std::basic_istream<CharT1, Traits1>& is,
		std::basic_string<CharT2, Traits2>& s,
		bool skip_whitespace)
	{
		using istream_type = std::basic_istream<CharT1, Traits1>;
		const typename istream_type::sentry ok(is, !skip_whitespace);

		if (ok)
		{
			load_string_impl_2(is, s);
		}
	}

public:
	void load_string(std::string& str) override
	{
		load_string_impl(m_is, str, true);
	}

	void load_string(std::wstring& str) override
	{
		load_string_impl(m_is, str, true);
	}

#if defined(HAMON_HAS_CXX20_CHAR8_T)
	void load_string(std::u8string& str) override
	{
		load_string_impl(m_is, str, true);
	}
#endif

#if defined(HAMON_HAS_CXX11_CHAR16_T)
	void load_string(std::u16string& str) override
	{
		load_string_impl(m_is, str, true);
	}
#endif

#if defined(HAMON_HAS_CXX11_CHAR32_T)
	void load_string(std::u32string& str) override
	{
		load_string_impl(m_is, str, true);
	}
#endif

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
		std::string s;
		s.resize(tmp.size());
		std::transform(tmp.begin(), tmp.end(), s.begin(),
			[](char_type c){return static_cast<char>(c);});
		auto first = s.data();
		auto last  = s.data() + s.length();
#if defined(__cpp_lib_to_chars) && (__cpp_lib_to_chars >= 201611L)
		auto result = std::from_chars(first, last, t);
		m_is.seekg(result.ptr - last, std::ios_base::cur);	// 変換できなかったぶん戻す
#else
		char* end;
		t = static_cast<T>(std::strtold(first, &end));
		m_is.seekg(end - last, std::ios_base::cur);	// 変換できなかったぶん戻す
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
#if 0//defined(__cpp_lib_quoted_string_io) && (__cpp_lib_quoted_string_io >= 201304L)
		is >> std::quoted(s);
#else
		using String = std::basic_string<CharT2, Traits2>;
		auto const delim  = String(1, '"');
		auto const escape = String(1, '\\');

		String tmp;
		tmp.resize(1);
		load_string_impl(is, tmp, true);

		if (tmp != delim)
		{
			return;
		}

		for (;;)
		{
			load_string_impl(is, tmp, false);
			if (tmp == delim)
			{
				break;
			}

			s += tmp;

			if (tmp == escape)
			{
				load_string_impl(is, tmp, false);
				s += tmp;
			}
		}
#endif
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
