/**
 *	@file	nvp.hpp
 *
 *	@brief	nvpの定義
 */

#ifndef HAMON_SERIALIZATION_NVP_HPP
#define HAMON_SERIALIZATION_NVP_HPP

#include <string>
#include <utility>

namespace hamon
{

namespace serialization
{

template <typename T>
class nvp
{
public:
	explicit nvp(char const* name, T& t)
		: m_name(name)
		, m_value(t)
	{}

	explicit nvp(std::string name, T& t)
		: m_name(std::move(name))
		, m_value(t)
	{}

	std::string const& name() const
	{
		return m_name;
	}

	T& value() const
	{
		return m_value;
	}

private:
	std::string	m_name;
	T&			m_value;

private:
	template <typename Archive>
	friend void save_class(Archive& oa, nvp<T> const& t)
	{
		oa << t.value();
	}

	template <typename Archive>
	friend void load_class(Archive& ia, nvp<T> const& t)
	{
		ia >> t.value();
	}
};

template <typename T>
inline nvp<T> const
make_nvp(char const* name, T& t)
{
	return nvp<T>(name, t);
}

template <typename T>
inline nvp<T> const
make_nvp(std::string name, T& t)
{
	return nvp<T>(std::move(name), t);
}

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_NVP_HPP
