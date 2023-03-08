/**
 *	@file	text_oarchive.hpp
 *
 *	@brief	text_oarchiveの定義
 */

#ifndef HAMON_SERIALIZATION_TEXT_OARCHIVE_HPP
#define HAMON_SERIALIZATION_TEXT_OARCHIVE_HPP

#include <hamon/serialization/detail/archive_base.hpp>
#include <hamon/serialization/detail/text_oarchive_impl.hpp>
#include <hamon/serialization/detail/save_value.hpp>
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

class text_oarchive : public detail::archive_base
{
public:
	template <typename OStream>
	explicit text_oarchive(OStream& os)
		: m_impl(new detail::text_oarchive_impl<OStream>(os))
	{
	}

	template <typename T>
	text_oarchive& operator<<(T const& t)
	{
		hamon::serialization::detail::save_value(*this, t);
		m_impl->put(" ");
		return *this;
	}

	template <typename T>
	text_oarchive& operator&(T const& t)
	{
		return *this << t;
	}

private:
	template <typename T, typename = hamon::enable_if_t<hamon::is_floating_point<T>::value>>
	void save_arithmetic_impl(T const& t, hamon::detail::overload_priority<2>)
	{
		m_impl->save(t);
	}
	template <typename T, typename = hamon::enable_if_t<hamon::is_unsigned<T>::value>>
	void save_arithmetic_impl(T const& t, hamon::detail::overload_priority<1>)
	{
		m_impl->save(static_cast<hamon::uintmax_t>(t));
	}
	template <typename T, typename = hamon::enable_if_t<hamon::is_signed<T>::value>>
	void save_arithmetic_impl(T const& t, hamon::detail::overload_priority<0>)
	{
		m_impl->save(static_cast<hamon::intmax_t>(t));
	}

	template <typename T>
	friend void save_arithmetic(text_oarchive& oa, T const& t)
	{
		oa.save_arithmetic_impl(t, hamon::detail::overload_priority<2>{});
	}

	template <typename T>
	friend void save_string(text_oarchive& oa, T const& t)
	{
		oa << t.length();
		oa.m_impl->save_string(t);
	}

private:
	std::unique_ptr<detail::text_oarchive_impl_base>	m_impl;
};

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_TEXT_OARCHIVE_HPP
