/**
 *	@file	text_iarchive.hpp
 *
 *	@brief	text_iarchiveの定義
 */

#ifndef HAMON_SERIALIZATION_TEXT_IARCHIVE_HPP
#define HAMON_SERIALIZATION_TEXT_IARCHIVE_HPP

#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>
#include <cstdint>
#include <type_traits>
#include <memory>
#include <charconv>
#include <string>

namespace hamon
{

namespace serialization
{

class text_iarchive_impl_base
{
public:
	virtual ~text_iarchive_impl_base()
	{
	}

	virtual void load(std::intmax_t&) = 0;
	virtual void load(std::uintmax_t&) = 0;
	virtual void load(float&) = 0;
	virtual void load(double&) = 0;
	virtual void load(long double&) = 0;
};

template <typename IStream>
class text_iarchive_impl
	: public text_iarchive_impl_base
{
public:
	explicit text_iarchive_impl(IStream& is)
		: m_is(is)
	{}

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
HAMON_WARNING_PUSH();
HAMON_WARNING_DISABLE_MSVC(4244)	// '引数': 'wchar_t' から 'const _Elem' への変換です。データが失われる可能性があります。
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
		std::string s(tmp.begin(), tmp.end());
#if defined(__cpp_lib_to_chars) && (__cpp_lib_to_chars >= 201611L)
		std::from_chars(s.data(), s.data() + s.length(), t);
#else
		t = std::strtold(s.data(), nullptr);
#endif
	}
HAMON_WARNING_POP();

private:
	text_iarchive_impl& operator=(text_iarchive_impl const&) = delete;

	IStream&	m_is;
};

class text_iarchive
{
public:
	template <typename IStream>
	explicit text_iarchive(IStream& is)
		: m_impl(new text_iarchive_impl<IStream>(is))
	{
	}

	template <typename T>
	text_iarchive& operator>>(T& t)
	{
		load(t);
		return *this;
	}

	template <typename T>
	text_iarchive& operator&(T& t)
	{
		return *this >> t;
	}

private:
	template <typename T, typename = hamon::enable_if_t<std::is_floating_point<T>::value>>
	void load_impl(T& t, hamon::detail::overload_priority<2>)
	{
		m_impl->load(t);
	}
	template <typename T, typename = hamon::enable_if_t<std::is_unsigned<T>::value>>
	void load_impl(T& t, hamon::detail::overload_priority<1>)
	{
		std::uintmax_t i;
		m_impl->load(i);
		t = static_cast<T>(i);
	}
	template <typename T, typename = hamon::enable_if_t<std::is_signed<T>::value>>
	void load_impl(T& t, hamon::detail::overload_priority<0>)
	{
		std::intmax_t i;
		m_impl->load(i);
		t = static_cast<T>(i);
	}

	template <typename T>
	void load(T& t)
	{
		load_impl(t, hamon::detail::overload_priority<2>{});
	}

	std::unique_ptr<text_iarchive_impl_base>	m_impl;
};

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_TEXT_IARCHIVE_HPP
