/**
 *	@file	singleton.hpp
 *
 *	@brief	singletonの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_SINGLETON_HPP
#define HAMON_SERIALIZATION_DETAIL_SINGLETON_HPP

namespace hamon
{

namespace serialization
{

namespace detail
{

template <typename T>
class singleton
{
private:
	static T& create()
	{
		static T t;
		(void)instance;
		return t;
	}

	singleton(singleton const& /*other*/) {}

public:
	static T& get_instance()
	{
		return create();
	}

private:
	static T& instance;
};

template <typename T>
T& singleton<T>::instance = singleton<T>::create();

}	// namespace detail

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_SINGLETON_HPP
