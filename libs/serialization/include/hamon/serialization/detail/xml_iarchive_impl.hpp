/**
 *	@file	xml_iarchive_impl.hpp
 *
 *	@brief	xml_iarchive_implの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_XML_IARCHIVE_IMPL_HPP
#define HAMON_SERIALIZATION_DETAIL_XML_IARCHIVE_IMPL_HPP

#include <hamon/base64/base64_xml_name.hpp>
#include <hamon/type_traits/bool_constant.hpp>
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

class xml_iarchive_impl_base
{
public:
	virtual ~xml_iarchive_impl_base() {}

	virtual std::streampos tellg(void) = 0;
	virtual void seekg(std::streampos pos) = 0;

	virtual void load(bool&) = 0;
	virtual void load(std::intmax_t&) = 0;
	virtual void load(std::uintmax_t&) = 0;
	virtual void load(float&) = 0;
	virtual void load(double&) = 0;
	virtual void load(long double&) = 0;

	virtual void load_string_until(std::string&, char delim) = 0;
	virtual void load_string_until(std::wstring&, char delim) = 0;
#if defined(HAMON_HAS_CXX20_CHAR8_T)
	virtual void load_string_until(std::u8string&, char delim) = 0;
#endif
#if defined(HAMON_HAS_CXX11_CHAR16_T)
	virtual void load_string_until(std::u16string&, char delim) = 0;
#endif
#if defined(HAMON_HAS_CXX11_CHAR32_T)
	virtual void load_string_until(std::u32string&, char delim) = 0;
#endif

	virtual char get_one_char() = 0;
	virtual void unget_one_char() = 0;

	virtual std::string read_tag() = 0;
};

template <typename IStream>
class xml_iarchive_impl
	: public xml_iarchive_impl_base
{
public:
	explicit xml_iarchive_impl(IStream& is)
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
	template <typename CharT, typename Traits>
	static void load_string_until_impl(
		std::basic_istream<CharT, Traits>& is,
		std::basic_string<CharT, Traits>& s,
		char delim)
	{
		using istream_type = std::basic_istream<CharT, Traits>;
		const typename istream_type::sentry ok(is);

		if (ok)
		{
			std::getline(is, s, CharT(delim));
		}
	}

	template <
		typename CharT1, typename Traits1,
		typename CharT2, typename Traits2
	>
	static void load_string_until_impl(
		std::basic_istream<CharT1, Traits1>& is,
		std::basic_string<CharT2, Traits2>& s,
		char delim)
	{
		using istream_type = std::basic_istream<CharT1, Traits1>;
		const typename istream_type::sentry ok(is);

		if (ok)
		{
			using String1 = std::basic_string<CharT1, Traits1>;
			using String2 = std::basic_string<CharT2, Traits2>;
			String1 tmp;
			std::getline(is, tmp, CharT1(delim));
			s = hamon::base64_xml_name::decode<String2>(tmp);
		}
	}

public:
	void load_string_until(std::string& str, char delim) override
	{
		load_string_until_impl(m_is, str, delim);
	}

	void load_string_until(std::wstring& str, char delim) override
	{
		load_string_until_impl(m_is, str, delim);
	}

#if defined(HAMON_HAS_CXX20_CHAR8_T)
	void load_string_until(std::u8string& str, char delim) override
	{
		load_string_until_impl(m_is, str, delim);
	}
#endif

#if defined(HAMON_HAS_CXX11_CHAR16_T)
	void load_string_until(std::u16string& str, char delim) override
	{
		load_string_until_impl(m_is, str, delim);
	}
#endif

#if defined(HAMON_HAS_CXX11_CHAR32_T)
	void load_string_until(std::u32string& str, char delim) override
	{
		load_string_until_impl(m_is, str, delim);
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
	template <typename CharT, typename Traits>
	static void read_tag_impl(
		std::basic_istream<CharT, Traits>& is,
		std::basic_string<CharT, Traits>& result,
		char delim)
	{
		using istream_type = std::basic_istream<CharT, Traits>;
		const typename istream_type::sentry ok(is);
		if (ok)
		{
			std::getline(is, result, delim);
			result += delim;
		}
	}

	template <
		typename CharT1, typename Traits1,
		typename CharT2, typename Traits2
	>
	static void read_tag_impl(
		std::basic_istream<CharT1, Traits1>& is,
		std::basic_string<CharT2, Traits2>& result,
		char delim)
	{
		using istream_type = std::basic_istream<CharT1, Traits1>;
		const typename istream_type::sentry ok(is);
		if (ok)
		{
			using String1 = std::basic_string<CharT1, Traits1>;
			String1 tmp;
			std::getline(is, tmp, CharT1(delim));
			result.resize(tmp.size());
			std::transform(tmp.begin(), tmp.end(), result.begin(),
				[](CharT1 c){return static_cast<CharT2>(c);});
			result += delim;
		}
	}

public:
	std::string read_tag() override
	{
		std::string result;
		read_tag_impl(m_is, result, '>');
		return result;
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
	xml_iarchive_impl& operator=(xml_iarchive_impl const&) = delete;

	IStream&	m_is;
};

}	// namespace detail

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_XML_IARCHIVE_IMPL_HPP
