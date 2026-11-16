/**
 *	@file	text_iarchive_impl.hpp
 *
 *	@brief	text_iarchive_implの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_TEXT_IARCHIVE_IMPL_HPP
#define HAMON_SERIALIZATION_DETAIL_TEXT_IARCHIVE_IMPL_HPP

#include <hamon/algorithm/transform.hpp>
#include <hamon/charconv/from_chars.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/cstdint/intmax_t.hpp>
#include <hamon/cstdint/uintmax_t.hpp>
#include <hamon/iomanip/quoted.hpp>
#include <hamon/ios/boolalpha.hpp>
#include <hamon/ios/ios_base.hpp>
#include <hamon/ios/streamsize.hpp>
#include <hamon/istream/basic_istream.hpp>
#include <hamon/type_traits/bool_constant.hpp>
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

	virtual void load_string(hamon::string&, hamon::size_t length) = 0;
	virtual void load_string(hamon::wstring&, hamon::size_t length) = 0;
#if defined(HAMON_HAS_CXX20_CHAR8_T)
	virtual void load_string(hamon::u8string&, hamon::size_t length) = 0;
#endif
#if defined(HAMON_HAS_CXX11_CHAR16_T)
	virtual void load_string(hamon::u16string&, hamon::size_t length) = 0;
#endif
#if defined(HAMON_HAS_CXX11_CHAR32_T)
	virtual void load_string(hamon::u32string&, hamon::size_t length) = 0;
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
		hamon::basic_istream<CharT1, Traits1>& is,
		hamon::basic_string<CharT2, Traits2>& s,
		hamon::size_t length,
		hamon::true_type)
	{
		hamon::basic_string<CharT1> tmp;
		tmp.resize(length);
		is.read(&tmp[0], static_cast<hamon::streamsize>(tmp.size()));
		s.resize(length);
		hamon::transform(tmp.begin(), tmp.end(), s.begin(),
			[](CharT1 c){return static_cast<CharT2>(c);});
	}

	template <
		typename CharT1, typename Traits1,
		typename CharT2, typename Traits2
	>
	static void load_string_impl_2(
		hamon::basic_istream<CharT1, Traits1>& is,
		hamon::basic_string<CharT2, Traits2>& s,
		hamon::size_t length,
		hamon::false_type)
	{
		auto const count = (length * sizeof(CharT2)) / sizeof(CharT1);
		s.resize(length);
		is.read(reinterpret_cast<CharT1*>(&s[0]), static_cast<hamon::streamsize>(count));
	}

	template <
		typename CharT1, typename Traits1,
		typename CharT2, typename Traits2
	>
	static void load_string_impl(
		hamon::basic_istream<CharT1, Traits1>& is,
		hamon::basic_string<CharT2, Traits2>& s,
		hamon::size_t length,
		bool skip_whitespace)
	{
		using istream_type = hamon::basic_istream<CharT1, Traits1>;
		const typename istream_type::sentry ok(is, !skip_whitespace);

		if (ok)
		{
			load_string_impl_2(is, s, length,
				hamon::bool_constant<(sizeof(CharT1) > sizeof(CharT2))>{});
		}
	}

public:
	void load_string(hamon::string& str, hamon::size_t length) override
	{
		load_string_impl(m_is, str, length, true);
	}

	void load_string(hamon::wstring& str, hamon::size_t length) override
	{
		load_string_impl(m_is, str, length, true);
	}

#if defined(HAMON_HAS_CXX20_CHAR8_T)
	void load_string(hamon::u8string& str, hamon::size_t length) override
	{
		load_string_impl(m_is, str, length, true);
	}
#endif

#if defined(HAMON_HAS_CXX11_CHAR16_T)
	void load_string(hamon::u16string& str, hamon::size_t length) override
	{
		load_string_impl(m_is, str, length, true);
	}
#endif

#if defined(HAMON_HAS_CXX11_CHAR32_T)
	void load_string(hamon::u32string& str, hamon::size_t length) override
	{
		load_string_impl(m_is, str, length, true);
	}
#endif

private:
	template <typename T>
	void load_float(T& t)
	{
		// m_is >> t;
		// だとinfとnanのときに正常にパースされない。
		// これは標準ライブラリの不具合で、将来的に修正される予定。
		// https://cplusplus.github.io/LWG/issue2381

		using char_type = typename IStream::char_type;
		hamon::basic_string<char_type> tmp;
		m_is >> tmp;
		hamon::string s;
		s.resize(tmp.size());
		hamon::transform(tmp.begin(), tmp.end(), s.begin(),
			[](char_type c){return static_cast<char>(c);});
		auto first = s.data();
		auto last  = s.data() + s.length();
		auto result = hamon::from_chars(first, last, t);
		m_is.seekg(result.ptr - last, hamon::ios_base::cur);	// 変換できなかったぶん戻す
	}

private:
	text_iarchive_impl& operator=(text_iarchive_impl const&) = delete;

	IStream&	m_is;
};

}	// namespace detail

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_TEXT_IARCHIVE_IMPL_HPP
