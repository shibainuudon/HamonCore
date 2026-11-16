/**
 *	@file	xml_oarchive_impl.hpp
 *
 *	@brief	xml_oarchive_implの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_XML_OARCHIVE_IMPL_HPP
#define HAMON_SERIALIZATION_DETAIL_XML_OARCHIVE_IMPL_HPP

#include <hamon/serialization/detail/write_float_as_string.hpp>
#include <hamon/base64/base64_xml_name.hpp>
#include <hamon/cstdint/intmax_t.hpp>
#include <hamon/cstdint/uintmax_t.hpp>
#include <hamon/ios/boolalpha.hpp>
#include <hamon/ios/detail/flags_saver.hpp>
#include <hamon/ostream/basic_ostream.hpp>
#include <hamon/string.hpp>
#include <hamon/config.hpp>

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

	virtual void save_string(hamon::string const&) = 0;
	virtual void save_string(hamon::wstring const&) = 0;
#if defined(HAMON_HAS_CXX20_CHAR8_T)
	virtual void save_string(hamon::u8string const&) = 0;
#endif
#if defined(HAMON_HAS_CXX11_CHAR16_T)
	virtual void save_string(hamon::u16string const&) = 0;
#endif
#if defined(HAMON_HAS_CXX11_CHAR32_T)
	virtual void save_string(hamon::u32string const&) = 0;
#endif

	virtual void put(const char*) = 0;
	virtual void put(hamon::string const&) = 0;
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
		hamon::detail::flags_saver fs(m_os);
		m_os << hamon::boolalpha << t;
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
		hamon::serialization::detail::write_float_as_string(m_os, t);
	}

	void save(double t) override
	{
		hamon::serialization::detail::write_float_as_string(m_os, t);
	}

	void save(long double t) override
	{
		hamon::serialization::detail::write_float_as_string(m_os, t);
	}

	void save_string(hamon::string const& str) override
	{
		save_string_impl(m_os, str);
	}

	void save_string(hamon::wstring const& str) override
	{
		save_string_impl(m_os, str);
	}

#if defined(HAMON_HAS_CXX20_CHAR8_T)
	void save_string(hamon::u8string const& str) override
	{
		save_string_impl(m_os, str);
	}
#endif

#if defined(HAMON_HAS_CXX11_CHAR16_T)
	void save_string(hamon::u16string const& str) override
	{
		save_string_impl(m_os, str);
	}
#endif

#if defined(HAMON_HAS_CXX11_CHAR32_T)
	void save_string(hamon::u32string const& str) override
	{
		save_string_impl(m_os, str);
	}
#endif

	void put(const char* s) override
	{
		m_os << s;
	}

	void put(hamon::string const& s) override
	{
		m_os << s.c_str();
	}

private:
	template <typename CharT, typename Traits>
	static void save_string_impl(
		hamon::basic_ostream<CharT, Traits>& os,
		hamon::basic_string<CharT, Traits> const& s)
	{
		os << s;
	}

	template <
		typename CharT1, typename Traits1,
		typename CharT2, typename Traits2
	>
	static void save_string_impl(
		hamon::basic_ostream<CharT1, Traits1>& os,
		hamon::basic_string<CharT2, Traits2> const& s)
	{
		using String = hamon::basic_string<CharT1, Traits1>;
		auto tmp = hamon::base64_xml_name::encode<String>(s);
		os << tmp;
	}

private:
	xml_oarchive_impl& operator=(xml_oarchive_impl const&) = delete;

private:
	OStream& m_os;
};

}	// namespace detail
}	// namespace serialization
}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_XML_OARCHIVE_IMPL_HPP
