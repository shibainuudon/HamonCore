/**
 *	@file	text_iarchive.hpp
 *
 *	@brief	text_iarchiveの定義
 */

#ifndef HAMON_SERIALIZATION_TEXT_IARCHIVE_HPP
#define HAMON_SERIALIZATION_TEXT_IARCHIVE_HPP

#include <cstdint>
#include <type_traits>
#include <memory>

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
	template <typename T>
	void load(T& t)
	{
		if (std::is_unsigned<T>::value)
		{
			std::uintmax_t i;
			m_impl->load(i);
			t = static_cast<T>(i);
		}
		else
		{
			std::intmax_t i;
			m_impl->load(i);
			t = static_cast<T>(i);
		}
	}

	std::unique_ptr<text_iarchive_impl_base>	m_impl;
};

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_TEXT_IARCHIVE_HPP
