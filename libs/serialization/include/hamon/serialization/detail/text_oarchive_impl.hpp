/**
 *	@file	text_oarchive_impl.hpp
 *
 *	@brief	text_oarchive_implの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_TEXT_OARCHIVE_IMPL_HPP
#define HAMON_SERIALIZATION_DETAIL_TEXT_OARCHIVE_IMPL_HPP

#include <hamon/algorithm/transform.hpp>
#include <hamon/charconv/to_chars.hpp>
#include <hamon/cstdint/intmax_t.hpp>
#include <hamon/cstdint/uintmax_t.hpp>
#include <hamon/ios/boolalpha.hpp>
#include <hamon/ios/scientific.hpp>
#include <hamon/ios/streamsize.hpp>
#include <hamon/ostream/basic_ostream.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/array.hpp>
#include <hamon/string.hpp>
#include <hamon/limits.hpp>
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

	virtual void save(bool) = 0;
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
	virtual void put(hamon::string const&) = 0;
};

template <typename OStream>
class text_oarchive_impl
	: public text_oarchive_impl_base
{
public:
	explicit text_oarchive_impl(OStream& os)
		: m_os(os)
	{}

	void save(bool t) override
	{
		auto const old_flags = m_os.flags();
		m_os << hamon::boolalpha << t;
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
	template <
		typename CharT1, typename Traits1,
		typename CharT2,
		hamon::enable_if_t<(sizeof(CharT1) > sizeof(CharT2))>* = nullptr
	>
	static void save_string_impl(
		hamon::basic_ostream<CharT1, Traits1>& os,
		CharT2 const* str, hamon::size_t length)
	{
		hamon::basic_string<CharT1> tmp;
		tmp.resize(length);
		hamon::transform(str, str + length, tmp.begin(),
			[](CharT2 c){return static_cast<CharT1>(c);});
		os.write(tmp.c_str(), static_cast<hamon::streamsize>(tmp.size()));
	}

	template <
		typename CharT1, typename Traits1,
		typename CharT2,
		hamon::enable_if_t<sizeof(CharT1) <= sizeof(CharT2)>* = nullptr
	>
	static void save_string_impl(
		hamon::basic_ostream<CharT1, Traits1>& os,
		CharT2 const* str, hamon::size_t length)
	{
		auto const count = (length * sizeof(CharT2)) / sizeof(CharT1);
		os.write(reinterpret_cast<CharT1 const*>(str), static_cast<hamon::streamsize>(count));
	}

public:
	void save_string(char const* str, hamon::size_t length) override
	{
		save_string_impl(m_os, str, length);
	}

	void save_string(wchar_t const* str, hamon::size_t length) override
	{
		save_string_impl(m_os, str, length);
	}

#if defined(HAMON_HAS_CXX20_CHAR8_T)
	void save_string(char8_t const* str, hamon::size_t length) override
	{
		save_string_impl(m_os, str, length);
	}
#endif

#if defined(HAMON_HAS_CXX11_CHAR16_T)
	void save_string(char16_t const* str, hamon::size_t length) override
	{
		save_string_impl(m_os, str, length);
	}
#endif

#if defined(HAMON_HAS_CXX11_CHAR32_T)
	void save_string(char32_t const* str, hamon::size_t length) override
	{
		save_string_impl(m_os, str, length);
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
	template <typename T>
	void save_float_impl(T t)
	{
		auto constexpr digits =
			4 +	// sign, decimal point, "e+" or "e-"
			hamon::numeric_limits<T>::max_digits10 +
			4;	// log10(max_exponent10)
		hamon::array<char, digits + 1> buf{};
		auto result = hamon::to_chars(buf.data(), buf.data() + buf.size(), t);
		m_os << buf.data();
		(void)result;
	}

private:
	text_oarchive_impl& operator=(text_oarchive_impl const&) = delete;

	OStream&	m_os;
};

}	// namespace detail

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_TEXT_OARCHIVE_IMPL_HPP
