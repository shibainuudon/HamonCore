/**
 *	@file	binary_iarchive.hpp
 *
 *	@brief	binary_iarchiveの定義
 */

#ifndef HAMON_SERIALIZATION_ARCHIVES_BINARY_IARCHIVE_HPP
#define HAMON_SERIALIZATION_ARCHIVES_BINARY_IARCHIVE_HPP

#include <hamon/serialization/detail/archive_base.hpp>
#include <hamon/serialization/detail/binary_iarchive_impl.hpp>
#include <hamon/serialization/detail/load_value.hpp>
#include <memory>

namespace hamon
{

namespace serialization
{

class binary_iarchive : public detail::archive_base
{
public:
	template <typename IStream>
	explicit binary_iarchive(IStream& is)
		: m_impl(new detail::binary_iarchive_impl<IStream>(is))
	{
	}

	template <typename T>
	binary_iarchive& operator>>(T& t)
	{
		hamon::serialization::detail::load_value(*this, t);
		return *this;
	}

	template <typename T>
	binary_iarchive& operator&(T& t)
	{
		return *this >> t;
	}

private:
	template <typename T>
	friend void load_arithmetic(binary_iarchive& oa, T& t)
	{
		oa.m_impl->load(&t, sizeof(T));
	}

	std::unique_ptr<detail::binary_iarchive_impl_base>	m_impl;
};

}	// namespace serialization

}	// namespace hamon

#include <hamon/serialization/register_archive.hpp>
HAMON_SERIALIZATION_REGISTER_IARCHIVE(hamon::serialization::binary_iarchive)

#endif // HAMON_SERIALIZATION_ARCHIVES_BINARY_IARCHIVE_HPP
