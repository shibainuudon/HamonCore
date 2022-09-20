/**
 *	@file	pointer_saver.hpp
 *
 *	@brief	pointer_saverの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_POINTER_SAVER_HPP
#define HAMON_SERIALIZATION_DETAIL_POINTER_SAVER_HPP

#include <hamon/serialization/detail/construct_data.hpp>
#include <hamon/serialization/nvp.hpp>
#include <hamon/serialization/access.hpp>
#include <map>
#include <string>
#include <functional>
#include <type_traits>

namespace hamon
{

namespace serialization
{

namespace detail
{

template <typename Archive>
class pointer_saver
{
public:
	static pointer_saver& get_instance()
	{
		static pointer_saver s_instance;
		return s_instance;
	}

private:
	template <typename T, bool = std::is_default_constructible<T>::value>
	struct save_func
	{
		void operator()(Archive& oa, void const* p) const
		{
			oa << make_nvp("value", *(static_cast<T const*>(p)));
		}
	};

	template <typename T>
	struct save_func<T, false>
	{
		void operator()(Archive& oa, void const* p) const
		{
			hamon::serialization::detail::construct_data<T const> data{static_cast<T const*>(p)};
			oa << make_nvp("value", data);
		}
	};

public:
	template <typename T>
	void register_class(void)
	{
		auto name = access::static_class_id<T>();
		m_f[name] = save_func<T>{};
	}

	template <typename T>
	void save(Archive& oa, std::string const& name, T const* p)
	{
		if (m_f.find(name) != m_f.end())
		{
			m_f[name](oa, p);
		}
		else
		{
			save_func<T>{}(oa, p);
		}
	}

private:
	pointer_saver()
	{
	}

	std::map<std::string, std::function<void(Archive&, void const*)>> m_f;
};

}	// namespace detail

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_POINTER_SAVER_HPP
