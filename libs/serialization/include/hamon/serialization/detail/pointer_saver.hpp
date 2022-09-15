/**
 *	@file	pointer_saver.hpp
 *
 *	@brief	pointer_saverの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_POINTER_SAVER_HPP
#define HAMON_SERIALIZATION_DETAIL_POINTER_SAVER_HPP

#include <hamon/serialization/nvp.hpp>
#include <hamon/serialization/access.hpp>
#include <map>
#include <string>
#include <functional>

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
	template <typename T>
	struct save_func
	{
		void operator()(Archive& oa, void const* p) const
		{
			oa << make_nvp("value", *(static_cast<T const*>(p)));
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
