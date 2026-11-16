/**
 *	@file	json_iarchive_impl.hpp
 *
 *	@brief	json_iarchive_implの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_JSON_IARCHIVE_IMPL_HPP
#define HAMON_SERIALIZATION_DETAIL_JSON_IARCHIVE_IMPL_HPP

#include <hamon/serialization/detail/read_float_from_string.hpp>
#include <hamon/cstdint/intmax_t.hpp>
#include <hamon/cstdint/uintmax_t.hpp>
#include <hamon/ios/boolalpha.hpp>
#include <hamon/ios/streamsize.hpp>
#include <hamon/ios/detail/flags_saver.hpp>
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

class json_iarchive_impl_base
{
public:
	virtual ~json_iarchive_impl_base() {}

	virtual void load(bool&) = 0;
	virtual void load(hamon::intmax_t&) = 0;
	virtual void load(hamon::uintmax_t&) = 0;
	virtual void load(float&) = 0;
	virtual void load(double&) = 0;
	virtual void load(long double&) = 0;

	virtual void load_string(hamon::string&) = 0;
	virtual void load_string(hamon::wstring&) = 0;
#if defined(HAMON_HAS_CXX20_CHAR8_T)
	virtual void load_string(hamon::u8string&) = 0;
#endif
#if defined(HAMON_HAS_CXX11_CHAR16_T)
	virtual void load_string(hamon::u16string&) = 0;
#endif
#if defined(HAMON_HAS_CXX11_CHAR32_T)
	virtual void load_string(hamon::u32string&) = 0;
#endif

	virtual char get_one_char() = 0;
	virtual void unget_one_char() = 0;
};

template <typename IStream>
class json_iarchive_impl
	: public json_iarchive_impl_base
{
public:
	explicit json_iarchive_impl(IStream& is)
		: m_is(is)
	{}

	void load(bool& t) override
	{
		hamon::detail::flags_saver fs(m_is);
		m_is >> hamon::boolalpha >> t;
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
	static void read_one_char(
		hamon::basic_istream<CharT1, Traits1>& is,
		CharT2* c)
	{
		CharT1 tmp;
		is.read(&tmp, 1);
		*c = static_cast<CharT2>(tmp);
	}

	template <
		typename CharT1, typename Traits1,
		typename CharT2,
		hamon::enable_if_t<sizeof(CharT1) <= sizeof(CharT2)>* = nullptr
	>
	static void read_one_char(
		hamon::basic_istream<CharT1, Traits1>& is,
		CharT2* c)
	{
		auto const count = sizeof(CharT2) / sizeof(CharT1);
		is.read(reinterpret_cast<CharT1*>(c), static_cast<hamon::streamsize>(count));
	}

private:
	template <
		typename CharT1, typename Traits1,
		typename CharT2, typename Traits2
	>
	static void load_string_impl(
		hamon::basic_istream<CharT1, Traits1>& is,
		hamon::basic_string<CharT2, Traits2>& s)
	{
		using istream_type = hamon::basic_istream<CharT1, Traits1>;
		const typename istream_type::sentry ok(is);

		if (!ok)
		{
			return;
		}

		auto const delim = CharT2('"');
		auto const escape = CharT2('\\');

		CharT2 c;
		read_one_char(is, &c);

		if (c != delim)
		{
			return;
		}

		for (;;)
		{
			read_one_char(is, &c);
			if (c == delim)
			{
				break;
			}

			if (c == escape)
			{
				read_one_char(is, &c);
				switch (c)
				{
				case 'b': c = '\b'; break;
				case 'f': c = '\f'; break;
				case 'n': c = '\n'; break;
				case 'r': c = '\r'; break;
				case 't': c = '\t'; break;
				}
			}

			s += c;
		}
	}

public:
	void load_string(hamon::string& str) override
	{
		load_string_impl(m_is, str);
	}

	void load_string(hamon::wstring& str) override
	{
		load_string_impl(m_is, str);
	}

#if defined(HAMON_HAS_CXX20_CHAR8_T)
	void load_string(hamon::u8string& str) override
	{
		load_string_impl(m_is, str);
	}
#endif
#if defined(HAMON_HAS_CXX11_CHAR16_T)
	void load_string(hamon::u16string& str) override
	{
		load_string_impl(m_is, str);
	}
#endif
#if defined(HAMON_HAS_CXX11_CHAR32_T)
	void load_string(hamon::u32string& str) override
	{
		load_string_impl(m_is, str);
	}
#endif

	char get_one_char() override
	{
		return static_cast<char>(get_one_char_impl(m_is));
	}

	void unget_one_char() override
	{
		m_is.rdbuf()->sungetc();
	}

private:
	template <typename CharT, typename Traits>
	static CharT get_one_char_impl(
		hamon::basic_istream<CharT, Traits>& is)
	{
		const typename hamon::basic_istream<CharT, Traits>::sentry ok(is);
		if (ok)
		{
			auto const rdbuf = is.rdbuf();
			return static_cast<CharT>(rdbuf->sbumpc());
		}
		return 0;
	}

private:
	json_iarchive_impl& operator=(json_iarchive_impl const&) = delete;

private:
	IStream& m_is;
};

}	// namespace detail

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_JSON_IARCHIVE_IMPL_HPP
