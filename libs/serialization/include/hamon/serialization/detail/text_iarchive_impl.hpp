/**
 *	@file	text_iarchive_impl.hpp
 *
 *	@brief	text_iarchive_implの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_TEXT_IARCHIVE_IMPL_HPP
#define HAMON_SERIALIZATION_DETAIL_TEXT_IARCHIVE_IMPL_HPP

#include <hamon/algorithm/transform.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/cstdint/intmax_t.hpp>
#include <hamon/cstdint/uintmax_t.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>
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

	virtual std::streampos tellg(void) = 0;
	virtual void seekg(std::streampos pos) = 0;

	virtual void load(bool&) = 0;
	virtual void load(hamon::intmax_t&) = 0;
	virtual void load(hamon::uintmax_t&) = 0;
	virtual void load(float&) = 0;
	virtual void load(double&) = 0;
	virtual void load(long double&) = 0;

	virtual void load_string(std::string&, hamon::size_t length) = 0;
	virtual void load_string(std::wstring&, hamon::size_t length) = 0;
#if defined(HAMON_HAS_CXX20_CHAR8_T)
	virtual void load_string(std::u8string&, hamon::size_t length) = 0;
#endif
#if defined(HAMON_HAS_CXX11_CHAR16_T)
	virtual void load_string(std::u16string&, hamon::size_t length) = 0;
#endif
#if defined(HAMON_HAS_CXX11_CHAR32_T)
	virtual void load_string(std::u32string&, hamon::size_t length) = 0;
#endif

public:
	template <typename CharT, typename Traits>
	void load_quoted_string(
		std::basic_string<CharT, Traits>& s,
		CharT leading_delim  = CharT('"'),
		CharT trailing_delim = CharT('"'))
	{
		vload_quoted_string(s, leading_delim, trailing_delim);
	}

private:
	virtual void vload_quoted_string(
		std::string&, char, char) = 0;
	virtual void vload_quoted_string(
		std::wstring&, wchar_t, wchar_t) = 0;
#if defined(HAMON_HAS_CXX20_CHAR8_T)
	virtual void vload_quoted_string(
		std::u8string&, char8_t, char8_t) = 0;
#endif
#if defined(HAMON_HAS_CXX11_CHAR16_T)
	virtual void vload_quoted_string(
		std::u16string&, char16_t, char16_t) = 0;
#endif
#if defined(HAMON_HAS_CXX11_CHAR32_T)
	virtual void vload_quoted_string(
		std::u32string&, char32_t, char32_t) = 0;
#endif

public:
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
	
	std::streampos tellg(void) override
	{
		return m_is.tellg();
	}

	void seekg(std::streampos pos) override
	{
		m_is.seekg(pos);
	}

	void load(bool& t) override
	{
		auto const old_flags = m_is.flags();
		m_is >> std::boolalpha >> t;
		m_is.flags(old_flags);
	}

	void load(hamon::intmax_t& t) override
	{
		m_is >> t;
	}

	void load(hamon::uintmax_t& t) override
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
		typename CharT2, typename Traits2
	>
	static void load_string_impl_2(
		std::basic_istream<CharT1, Traits1>& is,
		std::basic_string<CharT2, Traits2>& s,
		hamon::size_t length,
		hamon::true_type)
	{
		std::basic_string<CharT1> tmp;
		tmp.resize(length);
		is.read(&tmp[0], static_cast<std::streamsize>(tmp.size()));
		s.resize(length);
		hamon::transform(tmp.begin(), tmp.end(), s.begin(),
			[](CharT1 c){return static_cast<CharT2>(c);});
	}

	template <
		typename CharT1, typename Traits1,
		typename CharT2, typename Traits2
	>
	static void load_string_impl_2(
		std::basic_istream<CharT1, Traits1>& is,
		std::basic_string<CharT2, Traits2>& s,
		hamon::size_t length,
		hamon::false_type)
	{
		auto const count = (length * sizeof(CharT2)) / sizeof(CharT1);
		s.resize(length);
		is.read(reinterpret_cast<CharT1*>(&s[0]), static_cast<std::streamsize>(count));
	}

	template <
		typename CharT1, typename Traits1,
		typename CharT2, typename Traits2
	>
	static void load_string_impl(
		std::basic_istream<CharT1, Traits1>& is,
		std::basic_string<CharT2, Traits2>& s,
		hamon::size_t length,
		bool skip_whitespace)
	{
		using istream_type = std::basic_istream<CharT1, Traits1>;
		const typename istream_type::sentry ok(is, !skip_whitespace);

		if (ok)
		{
			load_string_impl_2(is, s, length,
				hamon::bool_constant<(sizeof(CharT1) > sizeof(CharT2))>{});
		}
	}

private:
	template <
		typename CharT1, typename Traits1,
		typename CharT2, typename Traits2
	>
	static void load_quoted_string_impl(
		std::basic_istream<CharT1, Traits1>& is,
		std::basic_string<CharT2, Traits2>& s,
		CharT2 leading_delim,
		CharT2 trailing_delim)
	{
#if 0//defined(__cpp_lib_quoted_string_io) && (__cpp_lib_quoted_string_io >= 201304L)
		is >> std::quoted(s);
#else
		using String = std::basic_string<CharT2, Traits2>;
		auto const leading_delim_str  = String(1, leading_delim);
		auto const trailing_delim_str = String(1, trailing_delim);
		auto const escape = String(1, '\\');

		String tmp;
		load_string_impl(is, tmp, 1, true);

		if (tmp != leading_delim_str)
		{
			return;
		}

		for (;;)
		{
			load_string_impl(is, tmp, 1, false);
			if (tmp == trailing_delim_str)
			{
				break;
			}

			s += tmp;

			if (tmp == escape)
			{
				load_string_impl(is, tmp, 1, false);
				s += tmp;
			}
		}
#endif
	}

public:
	void vload_quoted_string(
		std::string& t,
		char leading_delim,
		char trailing_delim) override
	{
		load_quoted_string_impl(m_is, t, leading_delim, trailing_delim);
	}

	void vload_quoted_string(
		std::wstring& t,
		wchar_t leading_delim,
		wchar_t trailing_delim) override
	{
		load_quoted_string_impl(m_is, t, leading_delim, trailing_delim);
	}

#if defined(HAMON_HAS_CXX20_CHAR8_T)
	void vload_quoted_string(
		std::u8string& t,
		char8_t leading_delim,
		char8_t trailing_delim) override
	{
		load_quoted_string_impl(m_is, t, leading_delim, trailing_delim);
	}
#endif
#if defined(HAMON_HAS_CXX11_CHAR16_T)
	void vload_quoted_string(
		std::u16string& t,
		char16_t leading_delim,
		char16_t trailing_delim) override
	{
		load_quoted_string_impl(m_is, t, leading_delim, trailing_delim);
	}
#endif
#if defined(HAMON_HAS_CXX11_CHAR32_T)
	void vload_quoted_string(
		std::u32string& t,
		char32_t leading_delim,
		char32_t trailing_delim) override
	{
		load_quoted_string_impl(m_is, t, leading_delim, trailing_delim);
	}
#endif

public:
	void load_string(std::string& str, hamon::size_t length) override
	{
		load_string_impl(m_is, str, length, true);
	}

	void load_string(std::wstring& str, hamon::size_t length) override
	{
		load_string_impl(m_is, str, length, true);
	}

#if defined(HAMON_HAS_CXX20_CHAR8_T)
	void load_string(std::u8string& str, hamon::size_t length) override
	{
		load_string_impl(m_is, str, length, true);
	}
#endif

#if defined(HAMON_HAS_CXX11_CHAR16_T)
	void load_string(std::u16string& str, hamon::size_t length) override
	{
		load_string_impl(m_is, str, length, true);
	}
#endif

#if defined(HAMON_HAS_CXX11_CHAR32_T)
	void load_string(std::u32string& str, hamon::size_t length) override
	{
		load_string_impl(m_is, str, length, true);
	}
#endif

public:
	char get_one_char() override
	{
		return static_cast<char>(get_one_char_impl(m_is));
	}

private:
	template <typename CharT1, typename Traits1>
	static void unget_one_char_impl(
		std::basic_istream<CharT1, Traits1>& is)
	{
		is.rdbuf()->sungetc();
	}

public:
	void unget_one_char() override
	{
		unget_one_char_impl(m_is);
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
		hamon::transform(tmp.begin(), tmp.end(), s.begin(),
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
