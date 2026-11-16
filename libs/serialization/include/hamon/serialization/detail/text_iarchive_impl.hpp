/**
 *	@file	text_iarchive_impl.hpp
 *
 *	@brief	text_iarchive_implの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_TEXT_IARCHIVE_IMPL_HPP
#define HAMON_SERIALIZATION_DETAIL_TEXT_IARCHIVE_IMPL_HPP

#include <hamon/serialization/detail/read_float_from_string.hpp>
#include <hamon/algorithm/transform.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/cstdint/intmax_t.hpp>
#include <hamon/cstdint/uintmax_t.hpp>
#include <hamon/ios/streamsize.hpp>
#include <hamon/istream/basic_istream.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/string.hpp>
#include <hamon/config.hpp>

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

	virtual void load(hamon::intmax_t&) = 0;
	virtual void load(hamon::uintmax_t&) = 0;
	virtual void load(float&) = 0;
	virtual void load(double&) = 0;
	virtual void load(long double&) = 0;

	virtual void load_string(char*, hamon::size_t) = 0;
	virtual void load_string(wchar_t*, hamon::size_t) = 0;
#if defined(HAMON_HAS_CXX20_CHAR8_T)
	virtual void load_string(char8_t*, hamon::size_t) = 0;
#endif
#if defined(HAMON_HAS_CXX11_CHAR16_T)
	virtual void load_string(char16_t*, hamon::size_t) = 0;
#endif
#if defined(HAMON_HAS_CXX11_CHAR32_T)
	virtual void load_string(char32_t*, hamon::size_t) = 0;
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
		hamon::serialization::detail::read_float_from_string(m_is, t);
	}

	void load(double& t) override
	{
		hamon::serialization::detail::read_float_from_string(m_is, t);
	}

	void load(long double& t) override
	{
		hamon::serialization::detail::read_float_from_string(m_is, t);
	}

private:
	template <
		typename CharT1, typename Traits1,
		typename CharT2,
		hamon::enable_if_t<(sizeof(CharT1) > sizeof(CharT2))>* = nullptr
	>
	static void load_string_impl_2(
		hamon::basic_istream<CharT1, Traits1>& is,
		CharT2* str, hamon::size_t length)
	{
		hamon::basic_string<CharT1> tmp;
		tmp.resize(length);
		is.read(&tmp[0], static_cast<hamon::streamsize>(tmp.size()));
		hamon::transform(tmp.begin(), tmp.end(), str,
			[](CharT1 c){return static_cast<CharT2>(c);});
	}

	template <
		typename CharT1, typename Traits1,
		typename CharT2,
		hamon::enable_if_t<sizeof(CharT1) <= sizeof(CharT2)>* = nullptr
	>
	static void load_string_impl_2(
		hamon::basic_istream<CharT1, Traits1>& is,
		CharT2* str, hamon::size_t length)
	{
		auto const count = (length * sizeof(CharT2)) / sizeof(CharT1);
		is.read(reinterpret_cast<CharT1*>(str), static_cast<hamon::streamsize>(count));
	}

	template <
		typename CharT1, typename Traits1,
		typename CharT2
	>
	static void load_string_impl(
		hamon::basic_istream<CharT1, Traits1>& is,
		CharT2* str, hamon::size_t length,
		bool skip_whitespace)
	{
		using istream_type = hamon::basic_istream<CharT1, Traits1>;
		const typename istream_type::sentry ok(is, !skip_whitespace);

		if (ok)
		{
			load_string_impl_2(is, str, length);
		}
	}

public:
	void load_string(char* str, hamon::size_t length) override
	{
		load_string_impl(m_is, str, length, true);
	}

	void load_string(wchar_t* str, hamon::size_t length) override
	{
		load_string_impl(m_is, str, length, true);
	}

#if defined(HAMON_HAS_CXX20_CHAR8_T)
	void load_string(char8_t* str, hamon::size_t length) override
	{
		load_string_impl(m_is, str, length, true);
	}
#endif

#if defined(HAMON_HAS_CXX11_CHAR16_T)
	void load_string(char16_t* str, hamon::size_t length) override
	{
		load_string_impl(m_is, str, length, true);
	}
#endif

#if defined(HAMON_HAS_CXX11_CHAR32_T)
	void load_string(char32_t* str, hamon::size_t length) override
	{
		load_string_impl(m_is, str, length, true);
	}
#endif

private:
	text_iarchive_impl& operator=(text_iarchive_impl const&) = delete;

private:
	IStream& m_is;
};

}	// namespace detail

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_TEXT_IARCHIVE_IMPL_HPP
