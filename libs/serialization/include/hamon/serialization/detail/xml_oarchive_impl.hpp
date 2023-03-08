/**
 *	@file	xml_oarchive_impl.hpp
 *
 *	@brief	xml_oarchive_implの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_XML_OARCHIVE_IMPL_HPP
#define HAMON_SERIALIZATION_DETAIL_XML_OARCHIVE_IMPL_HPP

#include <hamon/base64/base64_xml_name.hpp>
#include <hamon/cstdint/intmax_t.hpp>
#include <hamon/cstdint/uintmax_t.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/config.hpp>
#include <algorithm>
#include <string>
#include <array>
#include <limits>
#include <iomanip>
#include <ostream>	// basic_ostream
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

class xml_oarchive_impl_base
{
public:
	virtual ~xml_oarchive_impl_base() {}

	virtual void save(bool) = 0;
	virtual void save(hamon::intmax_t) = 0;
	virtual void save(hamon::uintmax_t) = 0;
	virtual void save(float) = 0;
	virtual void save(double) = 0;
	virtual void save(long double) = 0;

	virtual void save_string(std::string const&) = 0;
	virtual void save_string(std::wstring const&) = 0;
#if defined(HAMON_HAS_CXX20_CHAR8_T)
	virtual void save_string(std::u8string const&) = 0;
#endif
#if defined(HAMON_HAS_CXX11_CHAR16_T)
	virtual void save_string(std::u16string const&) = 0;
#endif
#if defined(HAMON_HAS_CXX11_CHAR32_T)
	virtual void save_string(std::u32string const&) = 0;
#endif

	virtual void put(const char*) = 0;
	virtual void put(std::string const&) = 0;
};

template <typename OStream>
class xml_oarchive_impl
	: public xml_oarchive_impl_base
{
public:
	explicit xml_oarchive_impl(OStream& os)
		: m_os(os)
	{}

	void save(bool t) override
	{
		auto const old_flags = m_os.flags();
		m_os << std::boolalpha << t;
		m_os.flags(old_flags);
	}

	void save(hamon::intmax_t t) override
	{
		m_os << t;
	}

	void save(hamon::uintmax_t t) override
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

private:
	template <typename CharT, typename Traits>
	static void save_string_impl(
		std::basic_ostream<CharT, Traits>& os,
		std::basic_string<CharT, Traits> const& s)
	{
		os << s;
	}

	template <
		typename CharT1, typename Traits1,
		typename CharT2, typename Traits2
	>
	static void save_string_impl(
		std::basic_ostream<CharT1, Traits1>& os,
		std::basic_string<CharT2, Traits2> const& s)
	{
		using String = std::basic_string<CharT1, Traits1>;
		auto tmp = hamon::base64_xml_name::encode<String>(s);
		os << tmp;
	}

public:
	void save_string(std::string const& str) override
	{
		save_string_impl(m_os, str);
	}

	void save_string(std::wstring const& str) override
	{
		save_string_impl(m_os, str);
	}

#if defined(HAMON_HAS_CXX20_CHAR8_T)
	void save_string(std::u8string const& str) override
	{
		save_string_impl(m_os, str);
	}
#endif

#if defined(HAMON_HAS_CXX11_CHAR16_T)
	void save_string(std::u16string const& str) override
	{
		save_string_impl(m_os, str);
	}
#endif

#if defined(HAMON_HAS_CXX11_CHAR32_T)
	void save_string(std::u32string const& str) override
	{
		save_string_impl(m_os, str);
	}
#endif
	
	void put(const char* s) override
	{
		m_os << s;
	}
	
	void put(std::string const& s) override
	{
		m_os << s.c_str();
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
			4;	// log10(max_exponent10)
		std::array<char, digits + 1> buf{};
		auto result = std::to_chars(buf.data(), buf.data() + buf.size(), t);
		m_os << buf.data();
		(void)result;
#elif 1
		// snprintfを使う
		auto constexpr digits10 = std::numeric_limits<T>::max_digits10;
		auto constexpr digits =
			4 +	// sign, decimal point, "e+" or "e-"
			digits10 +
			4;	// log10(max_exponent10)
		const char* length_modifier = hamon::is_same<T, long double>::value ? "L" : "";
		std::array<char, 10> fmt{};	// フォーマット文字列。"%.9g"など。
		std::snprintf(fmt.data(), fmt.size(), "%%.%d%sg", digits10, length_modifier);
		std::array<char, digits + 1> buf{};
		std::snprintf(buf.data(), buf.size(), fmt.data(), t);
		m_os << buf.data();
#else
		// operator<< を使う方法だと最も短い文字列にならない。
		// (TODO: 良い方法があるなら修正したい)
		auto const flags = m_os.flags();
		m_os << std::setprecision(std::numeric_limits<T>::max_digits10)
			<< std::scientific << t;
		m_os.flags(flags);
#endif
	}

private:
	xml_oarchive_impl& operator=(xml_oarchive_impl const&) = delete;

	OStream&	m_os;
};

}	// namespace detail

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_XML_OARCHIVE_IMPL_HPP
