/**
 *	@file	pointer_loader.hpp
 *
 *	@brief	pointer_loaderの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_POINTER_LOADER_HPP
#define HAMON_SERIALIZATION_DETAIL_POINTER_LOADER_HPP

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
class pointer_loader
{
public:
	static pointer_loader& get_instance()
	{
		static pointer_loader s_instance;
		return s_instance;
	}

private:
	template <typename T, bool = std::is_default_constructible<T>::value>
	struct load_func
	{
		void* operator()(Archive& ia) const
		{
			auto p = new T();
			ia >> make_nvp("value", *p);
			return p;
		}
	};
	
	template <typename T>
	struct load_func<T, false>
	{
		void* operator()(Archive& ia) const
		{
			std::allocator<T> alloc{};
			T* p = alloc.allocate(1);
			hamon::serialization::detail::construct_data<T> data{p};
			ia >> make_nvp("value", data);
			return p;
		}
	};

public:
	template <typename T>
	void register_class(void)
	{
		auto name = access::static_class_id<T>();
		m_f[name] = load_func<T>{};
	}

	template <typename T>
	void load(Archive& ia, std::string const& name, T*& p)
	{
		if (m_f.find(name) != m_f.end())
		{
			p = (T*)m_f[name](ia);
			return;
		}

		/*if constexpr (hamon::is_abstract_v<T>)
		{
			return nullptr;
		}
		else*/
		{
			p = (T*)load_func<T>{}(ia);
			return;
		}
	}

private:
	pointer_loader()
	{
	}

	std::map<std::string, std::function<void*(Archive&)>> m_f;
};

}	// namespace detail

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_POINTER_LOADER_HPP
