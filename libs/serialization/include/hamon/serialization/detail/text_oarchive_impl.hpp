/**
 *	@file	text_oarchive_impl.hpp
 *
 *	@brief	text_oarchive_implの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_TEXT_OARCHIVE_IMPL_HPP
#define HAMON_SERIALIZATION_DETAIL_TEXT_OARCHIVE_IMPL_HPP

#include <hamon/serialization/detail/write_float_as_string.hpp>
#include <hamon/serialization/detail/write_string.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/cstdint/intmax_t.hpp>
#include <hamon/cstdint/uintmax_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace serialization
{
namespace detail
{

class text_oarchive_impl_base
{
public:
	virtual ~text_oarchive_impl_base() {}

	virtual void save(hamon::intmax_t) = 0;
	virtual void save(hamon::uintmax_t) = 0;
	virtual void save(float) = 0;
	virtual void save(double) = 0;
	virtual void save(long double) = 0;

	virtual void save_string(char const*, hamon::size_t) = 0;
	virtual void save_string(wchar_t const*, hamon::size_t) = 0;
#if defined(HAMON_HAS_CXX20_CHAR8_T)
	virtual void save_string(char8_t const*, hamon::size_t) = 0;
#endif
#if defined(HAMON_HAS_CXX11_CHAR16_T)
	virtual void save_string(char16_t const*, hamon::size_t) = 0;
#endif
#if defined(HAMON_HAS_CXX11_CHAR32_T)
	virtual void save_string(char32_t const*, hamon::size_t) = 0;
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

	void save_string(char const* str, hamon::size_t length) override
	{
		hamon::serialization::detail::write_string(m_os, str, length);
	}

	void save_string(wchar_t const* str, hamon::size_t length) override
	{
		hamon::serialization::detail::write_string(m_os, str, length);
	}

#if defined(HAMON_HAS_CXX20_CHAR8_T)
	void save_string(char8_t const* str, hamon::size_t length) override
	{
		hamon::serialization::detail::write_string(m_os, str, length);
	}
#endif

#if defined(HAMON_HAS_CXX11_CHAR16_T)
	void save_string(char16_t const* str, hamon::size_t length) override
	{
		hamon::serialization::detail::write_string(m_os, str, length);
	}
#endif

#if defined(HAMON_HAS_CXX11_CHAR32_T)
	void save_string(char32_t const* str, hamon::size_t length) override
	{
		hamon::serialization::detail::write_string(m_os, str, length);
	}
#endif

	void put(const char* str) override
	{
		m_os << str;
	}

private:
	text_oarchive_impl& operator=(text_oarchive_impl const&) = delete;

private:
	OStream& m_os;
};

}	// namespace detail
}	// namespace serialization
}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_TEXT_OARCHIVE_IMPL_HPP
