/**
 *	@file	text_iarchive.hpp
 *
 *	@brief	text_iarchiveの定義
 */

#ifndef HAMON_SERIALIZATION_TEXT_IARCHIVE_HPP
#define HAMON_SERIALIZATION_TEXT_IARCHIVE_HPP

#include <hamon/serialization/detail/archive_base.hpp>
#include <hamon/serialization/detail/text_iarchive_impl.hpp>
#include <hamon/serialization/detail/load_value.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <type_traits>
#include <cstdint>
#include <memory>

namespace hamon
{

namespace serialization
{

class text_iarchive : public detail::archive_base
{
public:
	template <typename IStream>
	explicit text_iarchive(IStream& is)
		: m_impl(new detail::text_iarchive_impl<IStream>(is))
	{
	}

	template <typename T>
	text_iarchive& operator>>(T& t)
	{
		hamon::serialization::detail::load_value(*this, t);
		return *this;
	}

	template <typename T>
	text_iarchive& operator&(T& t)
	{
		return *this >> t;
	}

private:
	template <typename T, typename = hamon::enable_if_t<std::is_floating_point<T>::value>>
	void load_arithmetic_impl(T& t, hamon::detail::overload_priority<2>)
	{
		m_impl->load(t);
	}
	template <typename T, typename = hamon::enable_if_t<std::is_unsigned<T>::value>>
	void load_arithmetic_impl(T& t, hamon::detail::overload_priority<1>)
	{
		std::uintmax_t i;
		m_impl->load(i);
		t = static_cast<T>(i);
	}
	template <typename T, typename = hamon::enable_if_t<std::is_signed<T>::value>>
	void load_arithmetic_impl(T& t, hamon::detail::overload_priority<0>)
	{
		std::intmax_t i;
		m_impl->load(i);
		t = static_cast<T>(i);
	}

	template <typename T>
	friend void load_arithmetic(text_iarchive& ia, T& t)
	{
		ia.load_arithmetic_impl(t, hamon::detail::overload_priority<2>{});
	}

	template <typename T>
	friend void load_string(text_iarchive& ia, T& t)
	{
		std::size_t length;
		ia >> length;
		ia.m_impl->load_string(t, length);
	}

private:
	std::unique_ptr<detail::text_iarchive_impl_base>	m_impl;
};

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_TEXT_IARCHIVE_HPP
