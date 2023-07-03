/**
 *	@file	polymorphic.hpp
 *
 *	@brief
 */

#ifndef HAMON_SERIALIZATION_DETAIL_POLYMORPHIC_HPP
#define HAMON_SERIALIZATION_DETAIL_POLYMORPHIC_HPP

#include <hamon/serialization/detail/pointer_saver.hpp>
#include <hamon/serialization/detail/pointer_loader.hpp>
#include <hamon/serialization/detail/singleton.hpp>
#include <hamon/type_traits/is_polymorphic.hpp>
#include <hamon/type_traits/is_abstract.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace serialization
{
namespace detail
{

struct bind_oarchive_tag {};
struct bind_iarchive_tag {};

template <typename Archive, typename T, typename Tag>
struct bind_archive;

template <typename Archive, typename T>
struct bind_archive<Archive, T, bind_oarchive_tag>
{
	bind_archive()
	{
		hamon::serialization::detail::pointer_saver<Archive>::get_instance().template register_class<T>();
	}
};

template <typename Archive, typename T>
struct bind_archive<Archive, T, bind_iarchive_tag>
{
	bind_archive()
	{
		hamon::serialization::detail::pointer_loader<Archive>::get_instance().template register_class<T>();
	}
};

template <void(*)()>
struct instantiate_function {};

template <typename Archive, typename T, typename Tag>
struct polymorphic_serialization_support
{
#if defined(HAMON_MSVC)
	virtual void instantiate();
#else
	static void instantiate();
	typedef instantiate_function<instantiate> unused;
#endif
};

template <typename Archive, typename T, typename Tag>
void polymorphic_serialization_support<Archive, T, Tag>::instantiate()
{
	hamon::serialization::detail::singleton<bind_archive<Archive, T, Tag>>::get_instance();
}

template <typename T>
struct bind_to_archives
{
	struct dummy {};

	bind_to_archives()
	{
		static_assert(hamon::is_polymorphic<T>::value, "");
		static_assert(!hamon::is_abstract<T>::value, "");

		instantiate_polymorphic_binding(static_cast<T*>(nullptr), 0, dummy{});
	}
};

template <typename T, typename BindingTag>
void instantiate_polymorphic_binding(T*, int, BindingTag) {}

}	// namespace detail
}	// namespace serialization
}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_POLYMORPHIC_HPP
