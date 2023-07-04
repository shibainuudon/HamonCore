/**
 *	@file	text_iarchive.hpp
 *
 *	@brief	text_iarchiveの定義
 */

#ifndef HAMON_SERIALIZATION_ARCHIVES_TEXT_IARCHIVE_HPP
#define HAMON_SERIALIZATION_ARCHIVES_TEXT_IARCHIVE_HPP

#include <hamon/serialization/detail/archive_base.hpp>
#include <hamon/serialization/detail/text_iarchive_impl.hpp>
#include <hamon/serialization/detail/load_value.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/cstdint/intmax_t.hpp>
#include <hamon/cstdint/uintmax_t.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_floating_point.hpp>
#include <hamon/type_traits/is_signed.hpp>
#include <hamon/type_traits/is_unsigned.hpp>
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
	template <typename T, typename = hamon::enable_if_t<hamon::is_floating_point<T>::value>>
	void load_arithmetic_impl(T& t, hamon::detail::overload_priority<2>)
	{
		m_impl->load(t);
	}
	template <typename T, typename = hamon::enable_if_t<hamon::is_unsigned<T>::value>>
	void load_arithmetic_impl(T& t, hamon::detail::overload_priority<1>)
	{
		hamon::uintmax_t i;
		m_impl->load(i);
		t = static_cast<T>(i);
	}
	template <typename T, typename = hamon::enable_if_t<hamon::is_signed<T>::value>>
	void load_arithmetic_impl(T& t, hamon::detail::overload_priority<0>)
	{
		hamon::intmax_t i;
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
		hamon::size_t length;
		ia >> length;
		ia.m_impl->load_string(t, length);
	}

private:
	std::unique_ptr<detail::text_iarchive_impl_base>	m_impl;
};

}	// namespace serialization

}	// namespace hamon

#include <hamon/serialization/register_archive.hpp>
HAMON_SERIALIZATION_REGISTER_IARCHIVE(hamon::serialization::text_iarchive)

#endif // HAMON_SERIALIZATION_ARCHIVES_TEXT_IARCHIVE_HPP
