/**
 *	@file	json_oarchive_impl.hpp
 *
 *	@brief	json_oarchive_implの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_JSON_OARCHIVE_IMPL_HPP
#define HAMON_SERIALIZATION_DETAIL_JSON_OARCHIVE_IMPL_HPP

#include <hamon/serialization/detail/write_float_as_string.hpp>
#include <hamon/serialization/detail/write_string.hpp>
#include <hamon/cstdint/intmax_t.hpp>
#include <hamon/cstdint/uintmax_t.hpp>
#include <hamon/ios/boolalpha.hpp>
#include <hamon/ios/detail/flags_saver.hpp>
#include <hamon/string.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace serialization
{
namespace detail
{

class json_oarchive_impl_base
{
public:
	virtual ~json_oarchive_impl_base() {}

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
};

template <typename OStream>
class json_oarchive_impl
	: public json_oarchive_impl_base
{
public:
	explicit json_oarchive_impl(OStream& os)
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
		hamon::serialization::detail::write_string(m_os, str.data(), str.length());
	}

	void save_string(hamon::wstring const& str) override
	{
		hamon::serialization::detail::write_string(m_os, str.data(), str.length());
	}

#if defined(HAMON_HAS_CXX20_CHAR8_T)
	void save_string(hamon::u8string const& str) override
	{
		hamon::serialization::detail::write_string(m_os, str.data(), str.length());
	}
#endif

#if defined(HAMON_HAS_CXX11_CHAR16_T)
	void save_string(hamon::u16string const& str) override
	{
		hamon::serialization::detail::write_string(m_os, str.data(), str.length());
	}
#endif

#if defined(HAMON_HAS_CXX11_CHAR32_T)
	void save_string(hamon::u32string const& str) override
	{
		hamon::serialization::detail::write_string(m_os, str.data(), str.length());
	}
#endif

	void put(const char* s) override
	{
		m_os << s;
	}

private:
	json_oarchive_impl& operator=(json_oarchive_impl const&) = delete;

private:
	OStream& m_os;
};

}	// namespace detail
}	// namespace serialization
}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_JSON_OARCHIVE_IMPL_HPP
