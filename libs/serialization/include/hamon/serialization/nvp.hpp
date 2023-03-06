/**
 *	@file	nvp.hpp
 *
 *	@brief	nvpの定義
 */

#ifndef HAMON_SERIALIZATION_NVP_HPP
#define HAMON_SERIALIZATION_NVP_HPP

#include <hamon/utility/move.hpp>
#include <string>

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
		: m_name(hamon::move(name))
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
	return nvp<T>(hamon::move(name), t);
}

template <typename T>
inline nvp<T const> const
make_nvp(std::string name, T const& t)
{
	return nvp<T const>(hamon::move(name), t);
}

template <typename Archive, typename T>
void save_value(Archive& oa, nvp<T> const& t)
{
	oa << t.value();
}

template <typename Archive, typename T>
void load_value(Archive& ia, nvp<T> const& t)
{
	ia >> t.value();
}

}	// namespace serialization

}	// namespace hamon

#include <hamon/preprocessor/stringize.hpp>

#define HAMON_SERIALIZATION_NVP(name) \
	hamon::serialization::make_nvp(HAMON_PP_STRINGIZE(name), name)

#endif // HAMON_SERIALIZATION_NVP_HPP
