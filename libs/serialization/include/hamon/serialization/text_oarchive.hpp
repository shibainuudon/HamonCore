/**
 *	@file	text_oarchive.hpp
 *
 *	@brief	text_oarchiveの定義
 */

#ifndef HAMON_SERIALIZATION_TEXT_OARCHIVE_HPP
#define HAMON_SERIALIZATION_TEXT_OARCHIVE_HPP

#include <cstdint>
#include <type_traits>
#include <memory>

namespace hamon
{

namespace serialization
{

class text_oarchive_impl_base
{
public:
	virtual ~text_oarchive_impl_base()
	{}

	virtual void save(std::intmax_t) = 0;
	virtual void save(std::uintmax_t) = 0;
};

template <typename OStream>
class text_oarchive_impl
	: public text_oarchive_impl_base
{
public:
	explicit text_oarchive_impl(OStream& os)
		: m_os(os)
	{}

	void save(std::intmax_t t) override
	{
		m_os << t << " ";
	}

	void save(std::uintmax_t t) override
	{
		m_os << t << " ";
	}

private:
	text_oarchive_impl& operator=(text_oarchive_impl const&) = delete;

	OStream&	m_os;
};

class text_oarchive
{
public:
	template <typename OStream>
	explicit text_oarchive(OStream& os)
		: m_impl(new text_oarchive_impl<OStream>(os))
	{
	}

	template <typename T>
	text_oarchive& operator<<(T const& t)
	{
		save(t);
		return *this;
	}

	template <typename T>
	text_oarchive& operator&(T const& t)
	{
		return *this << t;
	}

private:
	template <typename T>
	void save(T const& t)
	{
		if (std::is_unsigned<T>::value)
		{
			m_impl->save(static_cast<std::uintmax_t>(t));
		}
		else
		{
			m_impl->save(static_cast<std::intmax_t>(t));
		}
	}

	std::unique_ptr<text_oarchive_impl_base>	m_impl;
};

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_TEXT_OARCHIVE_HPP
