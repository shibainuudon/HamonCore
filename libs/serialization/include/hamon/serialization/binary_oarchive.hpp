/**
 *	@file	binary_oarchive.hpp
 *
 *	@brief	binary_oarchiveの定義
 */

#ifndef HAMON_SERIALIZATION_BINARY_OARCHIVE_HPP
#define HAMON_SERIALIZATION_BINARY_OARCHIVE_HPP

#include <hamon/serialization/detail/archive_base.hpp>
#include <hamon/serialization/detail/binary_oarchive_impl.hpp>
#include <hamon/serialization/detail/save_value.hpp>
#include <memory>

namespace hamon
{

namespace serialization
{

class binary_oarchive : public detail::archive_base
{
public:
	template <typename OStream>
	explicit binary_oarchive(OStream& os)
		: m_impl(new detail::binary_oarchive_impl<OStream>(os))
	{
	}

	template <typename T>
	binary_oarchive& operator<<(T const& t)
	{
		hamon::serialization::detail::save_value(*this, t);
		return *this;
	}

	template <typename T>
	binary_oarchive& operator&(T const& t)
	{
		return *this << t;
	}

private:
	template <typename T>
	friend void save_arithmetic(binary_oarchive& oa, T const& t)
	{
		oa.m_impl->save(&t, sizeof(T));
	}

	std::unique_ptr<detail::binary_oarchive_impl_base>	m_impl;
};

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_BINARY_OARCHIVE_HPP
